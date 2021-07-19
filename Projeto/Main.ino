// Include de todos os arquivos secundarios 
#include "MaquinaEstados.h"
#include "Definicoes.h"
#include "Sensores.h"
#include "BombaAgua.h"
#include "SerialMP3Player.h"
#include "CaixaDeSom.h"
#include "Comunicacao.h"

// Definicao das Variaveis globais 
int codigoEvento;
int codigoAcao;
int estado = idle;
unsigned long inicio = millis();

void setup(){
  Serial.begin(9600);                                     // Inicia a comunicacao serial  
  Serial.println("Programa Iniciado");
  delay(500);
}

void loop(){
  unsigned long atual = millis();
  long intervalo = 1800000;                         //(30 * 60 * 1000ms) 30 minutos ate ele atualizar todos os sensores e valores do site 
  
  if ((atual-inicio) >= intervalo){
    codigoEvento = obterEvento();                           // obtem o evento atual 
    if (codigoEvento != NENHUM_EVENTO){
        codigoAcao = obterAcao(estado, codigoEvento);       // obtem o codigo da acao 
        estado = obterProximoEstado(estado, codigoEvento);  // obtem o proximo estado
        executarAcao(codigoAcao);                           // Executa a acao atual
        Serial.println("Estado" + String(estado));          // Printa o estado atual sempre que for alterado 
    }
    inicio = atual;
  }
}
