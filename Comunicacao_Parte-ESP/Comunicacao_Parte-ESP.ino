
// INCLUSÃO DE BIBLIOTECAS
#include "config.h"
#include <SoftwareSerial.h>

// DEFINIÇÕES

#define tempoAtualizacao 60000

#define Rx 0
#define Tx 2

SoftwareSerial mySerial(Rx,Tx);

// INSTANCIANDO OBJETOS
AdafruitIO_Feed *sensorLuz = io.feed("Luz");
AdafruitIO_Feed *sensorAgua = io.feed("Umidade");
AdafruitIO_Feed *sensorUmi = io.feed("Nivel");
AdafruitIO_Feed *sensorTemp = io.feed("Temparatura");
AdafruitIO_Feed *but = io.feed("Conex");

// DECLARAÇÃO DE FUNÇÕES
bool monitoraSensor();  //se mudou alguma medida do sensor deve atualizar os dados no site 
void configuraMQTT();   //pegar o status
// DECLARAÇÃO DE VARIÁVEIS
unsigned long controleTempo = 0;
unsigned int valorSensorLuz;
unsigned int valorSensorAgua;
unsigned int valorSensorUmi;
unsigned int valorSensorTemp;

void setup() {
  mySerial.begin(115200);
  Serial.begin(9600);
  
  while (! Serial);
  configuraMQTT();
  io.run();
  delay(500);
  but->save("ON");      //liga o botao avisando que ocorreu a conexao 
  
  Serial.println("Fim Setup");
}

void loop() {
  io.run();
  if (millis() > controleTempo + tempoAtualizacao) {
    controleTempo = millis();
    if (monitoraSensor()) {                     // Se teve mudanca atualiza o site 
      controleTempo = millis();
      sensorLuz->save(valorSensorLuz);
      sensorAgua->save(valorSensorAgua);
      sensorTemp->save(valorSensorTemp);
      sensorUmi->save(valorSensorUmi);
    }
  }
}

// IMPLEMENTO DE FUNÇÕES
void configuraMQTT() {
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

bool monitoraSensor() {
  static int leituraAntAgua;
  static int leituraAntLuz;
  static int leituraAntTemp;
  static int leituraAntUmi;
  String content = "";
  char character;
  int leituraLuz;
  int leituraAgua;
  int leituraTemp;
  int leituraUmi;

    while(mySerial.available()) {
    character = mySerial.read();              //recebe os dados do arduino e retira os valores de cada sensor 
    content.concat(character);
    };
    leituraAgua=(content.substring(5, 8)).toInt();
    leituraLuz=(content.substring(1, 4)).toInt();
    leituraTemp=(content.substring(13, 16)).toInt();
    leituraUmi=(content.substring(9, 12)).toInt();
    
    if (leituraLuz != leituraAntLuz || leituraAgua != leituraAntAgua || leituraTemp != leituraAntTemp || leituraUmi != leituraAntUmi) { //se um mudar retorna true
      valorSensorLuz = leituraLuz;
      leituraAntLuz = leituraLuz;
      valorSensorAgua = leituraAgua;
      leituraAntAgua = leituraAgua;
      valorSensorTemp = leituraTemp;
      leituraAntTemp = leituraTemp;
      valorSensorUmi = leituraUmi;
      leituraAntUmi = leituraUmi;
      return true;
    } 
    else {
      return false;
    }
}
