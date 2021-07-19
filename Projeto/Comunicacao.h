#ifndef Comunicacao
#define Comunicacao
#include "Definicoes.h"

class Comunica{                       // Classe Comunicação Com Esp
  public:
    Comunica();
	  void UpdateAda(int valorSensorIntLuz, int valorSensorIntAgua,int valorSensorIntUmi,int valorSensorIntTemp);	
};

#endif
