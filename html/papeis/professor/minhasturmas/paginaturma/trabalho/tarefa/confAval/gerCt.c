// inicializa a semente randômica
#include <sys/time.h>
void iniRand() {
	struct timeval time;
	gettimeofday(&time,NULL);
	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));


}

// gerar e carregar valores de variáveis globais de entrada e inicializar outras variáveis globais
int gerarCasoTeste(int ct) {
	
}

