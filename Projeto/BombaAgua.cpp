#include "BombaAgua.h"
#include "Definicoes.h"

Bomba::Bomba(){
    pinMode(PORTA_BOMBA, OUTPUT);       // Seta a porta como output
};
  
void Bomba::Liga_Bomba(){
    digitalWrite(PORTA_BOMBA, HIGH);    // Liga a bomba
    delay(TEMPO_BOMBA);                 // Espera o tempo designado para regar a planta
    digitalWrite(PORTA_BOMBA, LOW);     // Desliga a bomba
};
