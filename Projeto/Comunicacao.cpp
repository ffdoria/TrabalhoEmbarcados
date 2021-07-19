#include <SoftwareSerial.h>
#include <Arduino.h>
#include "Comunicacao.h"
#include "Definicoes.h"

SoftwareSerial Comum(Rx_ESP,Tx_ESP);

String criaString(int valor1,char prop1){
  String s1 = "";
  if(valor1<10){
        s1 = String(prop1) + String("00") + String(valor1);
   }else if(valor1 >= 100){
        s1 = String(prop1) + String(valor1);
   }else{
        s1 = String(prop1) + String("0") + String(valor1);
      }
   return s1;
}

Comunica::Comunica(){                         
  Comum.begin(115200);                    // inicializa a comunicacao serial comum ESP - Arduino
  delay(500);                             // espera iniciaizar 
};

void Comunica::UpdateAda(int valorSensorIntLuz, int valorSensorIntAgua,int valorSensorIntUmi,int valorSensorIntTemp) // funcao que manda a nova leitura para o ESP via Serial
{
	String sL = criaString(valorSensorIntLuz,'L');
	String sA = criaString(valorSensorIntAgua,'A');
	String sU = criaString(valorSensorIntUmi,'U');
	String sT = criaString(valorSensorIntTemp,'T');
	String mensagem = sL + sA + sU + sT;
	Comum.println(mensagem);
  }




  
