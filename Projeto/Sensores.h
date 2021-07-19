#ifndef Sensores
#define Sensores
#include "Definicoes.h"

class Sensor{                       // Classe mae para todos os sensores 
  public:
    Sensor(){}
};

class Dht11 : public Sensor{        // subclasse para o sensor dht11
  public:
    Dht11();
    int get_Temperatura();
    int get_Umidade();
    
   private:
    int temperatura = 39;           // Inicializa as variaveis para medicoes 
    int umidade = 39;
};

class Solo : public Sensor{         // subclasse para o sensor de umidade do solo
  
    public:
      Solo();
      int get_UmidSolo();
      
    private:
      const int AirValue = 832;     // Valor para calibracao da umidade  
      const int WaterValue = 375; 
      int UmidSolo = 39;            // Inicializa as variaveis para medicoes 
};  

class LDR : public Sensor{          // subclasse para o sensor de luz LDR
    public:
      LDR();
      int get_Luz();
      
    private:
      int Luz = 100;                // Inicializa as variaveis para medicoes 
};

class Nivel : public Sensor{        // subclasse para o sensor de nivel de agua 
    public:
      Nivel();
      const int NivelMax = 650;     // Valor para calibracao   
      const int NivelMin = 0; 
      int get_Nivel();
      
    private:
      int NivelAgua = 100;          // Inicializa as variaveis para medicoes
};

#endif
