#ifndef Definicoes
#define Definicoes

// Valores a serem definidos pelo usuario 
#define TEMPO_BOMBA 10000

#define NUM_ESTADOS 2       
#define NUM_EVENTOS 4

#define TRUE  1
#define FALSE 0

// Estados
#define idle 0
#define BOMBA_ACIONADA 1

// Eventos
#define ACIONAR_BOMBA 0
#define ACIONAR_MP3 1
#define MANDAR_MSG 2
#define BOMBA_FINALIZADA 3
#define NENHUM_EVENTO -1

// Acoes 
#define A 0
#define B 1
#define C 2
#define D 3
#define NENHUMA_ACAO -1

// Para caixa de som 
#define tx 6
#define rx 5
#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PREVIOUS 0X02
#define CMD_NEXT 0X01

// Sensores
# define ldr A0
# define DHTPIN A1
# define Umidade A2
# define NIVEL A3
# define PORTA_BOMBA A4
# define DHTTYPE DHT11 

// Comunicacao ESP
#define Rx_ESP 7
#define Tx_ESP 8


#endif
