#include "CaixaDeSom.h"
#include "Definicoes.h"
#include "SerialMP3Player.h"
#include <Arduino.h>
SoftwareSerial mySerial(rx, tx);           // seta os pinos digitais rx e tx 


SomMP3::SomMP3(){                         
  mySerial.begin(9600);                   // inicializa a comunicacao serial 
  delay(500);                             // espera iniciaizar 
  EnviaMensagemSom(CMD_SEL_DEV, DEV_TF);  // seleciona o cartao SD
};

void SomMP3::EnviaMensagemSom(int command, int dat) // funcao que manda a mensagem de som especifica
{
  static int8_t Send_buf[8] = {0} ;
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]) ;
  }
  delay(3000);
}
