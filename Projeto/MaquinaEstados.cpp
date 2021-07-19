#include <Arduino.h>
#include "MaquinaEstados.h"
#include "Definicoes.h"
#include "Sensores.h"
#include "BombaAgua.h"
#include "CaixaDeSom.h"
#include "Comunicacao.h"

// Variaveis globais que definem os intervalos para as variaveis de estado
int temperaturaMaxima = 40;
int temperaturaMinima = 15; 
int LuzMinDia = 50;
int LuzNoiteMin = 30;
int UmidSoloMin = 30;
int NivelCritico = 93;

int mensagem = 10;           // variavel que carrega o tipo da mensagem  (0,1,2,3) (Nivel, Luz baixa, Temp alta, Temp baixa)
int necessidade = 0;
int finalizada = 0;
int atual = 0;

// Inicializa os objetos para cada um dos sensores 
Nivel SensorNivel;
Dht11 SensorDHT11;
Solo SensorUmidSolo;
LDR SensorLDR;
Bomba BombaDeAgua;

int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {BOMBA_ACIONADA, idle, idle, idle},
    {BOMBA_ACIONADA, BOMBA_ACIONADA, BOMBA_ACIONADA, idle},
};

int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {A, B, C, NENHUMA_ACAO},
    {NENHUMA_ACAO, B, NENHUMA_ACAO, D}
};

int obterAcao(int estado, int codigoEvento) {
  return acao_matrizTransicaoEstados[estado][codigoEvento];
}

int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
}

String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  return conteudo;
}

int obterEvento() {
    delay(200);
    mensagem = 10;
    Comunica Comun1;
    int nivel = SensorNivel.get_Nivel();              // Obtem a leitura de agua 
    int temp = SensorDHT11.get_Temperatura();         // Obtem a temperatura atual
    int umidade = SensorDHT11.get_Umidade();          // Obtem a umidade do ar
    int umidadeSolo = SensorUmidSolo.get_UmidSolo();  // Obtem a umidade do solo
    int IntensidadeLuz = SensorLDR.get_Luz();         // Obtem a luminosidade 
    Comun1.UpdateAda(IntensidadeLuz, nivel,umidadeSolo,temp); // Update valores no site 

    // Imprime no serial os valores de cada um dos sensores para monitoramento 
    Serial.print("Medições dos Sensores: \n");
    Serial.print("Nivel: " + (String)nivel + " %\n");
    Serial.print("Temperatura: " + (String)temp + " *C\n");
    Serial.print("Umidade: " + (String)umidade + " %\n");
    Serial.print("Umidade Solo: " + (String)umidadeSolo + " %\n");
    Serial.print("Intensidade Luz: " + (String)IntensidadeLuz + " %\n");

    necessidade = 0; 
    // A partir das necessidades da planta, define qual o tipo de mensagem 
    if (nivel < NivelCritico) {         // Quando ha pouca agua no reservatorio  
         mensagem = 0;                  // variavel que carrega o tipo da mensagem  (0,1,2,3) = (Nivel, Luz baixa, Temp alta, Temp baixa)
         necessidade = 1;
    }
    else if (LuzNoiteMin < IntensidadeLuz < LuzMinDia) { // Quando a luz eh menor do que o minimo DURANTE O DIA    
      mensagem = 1;
      necessidade = 1;}
    else if (temp > temperaturaMaxima) {                // Quando esta quente demais
      mensagem = 2;
      necessidade = 1;}
    else if (temp < temperaturaMinima) {                // Quando esta muito frio 
      mensagem = 3; 
      necessidade = 1;}
    else{                                               // Quando nao ha nenhuma necessidade 
      mensagem = 4;
      necessidade = 0;
    }

    // Define a acao para cada transicao de estado  
    if (umidadeSolo < UmidSoloMin && atual == 0) {    // Quando a planta precisa de agua 
      if (mensagem != 0)                              // Nao pode acionar a bomba se nao houver agua no reservatorio 
        return ACIONAR_BOMBA; 
      else   
        mensagem = 0;
        return ACIONAR_MP3;
    }
    else if (finalizada == 1) {                       // Indica que a bomba ja bombeou agua 
        return BOMBA_FINALIZADA; 
    }
    else if (necessidade) {                           // Quando a planta tem alguma necessidade, mandar ela por mp3
        return ACIONAR_MP3; 
    }
//    else if (event_str == "Status") { // Mandar por wpp o status atual da planta (valores dos sensores)
//        return MANDAR_MSG; 
//    }
    else {
        return NENHUM_EVENTO;
    }
}

void executarAcao(int codigoAcao) {
      
    if (codigoAcao == NENHUMA_ACAO)
        return;
        
    SomMP3 caixa;
    switch(codigoAcao)
    {
    case A:
        Serial.println("Bomba Acionada.\n");  
        Serial.println("Planta falando: estou me regando \n");
        caixa.EnviaMensagemSom(CMD_PLAY_W_VOL, 0X1E01);    // Aciona mensagem de som que esta se regando 
        BombaDeAgua.Liga_Bomba();                           // Aciona a bomba de agua durante o tempo definido
        finalizada = 1;
        atual = 1;
        break;
    case B:
        Serial.println("Planta falando.\n");
        if (mensagem == 0){                                
          Serial.println("0 = nivel" + mensagem);           // Nivel
          caixa.EnviaMensagemSom(CMD_PLAY_W_VOL, 0X1E03);}  // Mensagem de pouca agua
        if (mensagem == 1){
          Serial.println("1 = luz" + mensagem);             // Luz
          caixa.EnviaMensagemSom(CMD_PLAY_W_VOL, 0X1E05);}  // Mensagem de pouca luz 
        if (mensagem == 2){
          Serial.println("2 = tmax" + mensagem);            // Temperatura alta
          caixa.EnviaMensagemSom(CMD_PLAY_W_VOL, 0X1E07);}  // Mensagem de temperatura alta 
        if (mensagem == 3){
          Serial.println("3 = tmin" + mensagem);            // Temperatura baixa 
          caixa.EnviaMensagemSom(CMD_PLAY_W_VOL, 0X1E09);}  // Mensagem de temperatura baixa 
        break;
    case C:
        Serial.println("Whats enviado.\n");
        break;
    case D:
        Serial.println("Bomba finalizada.\n");
        finalizada = 0;
        atual = 0;
        break;
    }
}
