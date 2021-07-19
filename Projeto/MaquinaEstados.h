#ifndef MaquinaEstados
#define MaquinaEstados

int obterEvento();
int obterAcao(int estado, int codigoEvento);
int obterProximoEstado(int estado, int codigoEvento);
void executarAcao(int codigoAcao);

#endif