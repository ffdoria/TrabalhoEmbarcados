#include "Sensores.h"
#include "DHT.h"
#include "Definicoes.h"
DHT dht(DHTPIN, DHTTYPE);

Dht11::Dht11(){
  dht.begin();
};
  
int Dht11::get_Temperatura(){
     temperatura = dht.readTemperature();
     return temperatura;
};

int Dht11::get_Umidade(){
     umidade = dht.readHumidity();
     return umidade;
};

Solo::Solo(){};

int Solo::get_UmidSolo(){
    int Leitura = analogRead(Umidade);
    UmidSolo = map(Leitura, AirValue, WaterValue, 0, 100);
    if (UmidSolo < 0)
      UmidSolo = 0;
    if (UmidSolo > 100)
      UmidSolo = 100;
    return UmidSolo;
};

LDR::LDR(){};

int LDR::get_Luz(){
    int leitura = analogRead(ldr);
    Luz = round(leitura/10.23);     // Para transformar em porcentagem (0 - 1023 = 0  - 100%)
    return Luz;
};

Nivel::Nivel(){};

int Nivel::get_Nivel(){
    int Leitura = analogRead(NIVEL);
    NivelAgua = map(Leitura, NivelMin, NivelMax, 0, 100);
    if (NivelAgua < 0)
      NivelAgua = 0;
    if (NivelAgua > 100)
      NivelAgua = 100;
    return NivelAgua;
};
