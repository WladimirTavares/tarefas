#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// rotina de avaliação estática de caso de teste
// recebe o número do caso de teste e o diretório onde os dados
// de execução do caso de teste são salvos

// rotina de avaliação global da tarefa
int avaliacaoCT(int ct, char* dirct, char* dirctresp) {

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	* 
	* 	Avaliação do caso de teste
	* 
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	// abrir arquivo de gabarito e entrada (caso necessário)
	char caminho[4110];
	sprintf(caminho, "%s/gabarito.txt", dirct);
	FILE* fg = fopen(caminho, "r");
	//sprintf(caminho, "%s/entrada.txt", dirct);
	//FILE* fe = fopen(caminho, "r");
	//  caso tenha sido gerado caso de teste dinâmico
	//sprintf(caminho, "%s/entradadinamica.txt", dirctresp);
	//FILE* fd = fopen(caminho, "r");

	// abrir arquivo de saída
	sprintf(caminho, "%s/saida.txt", dirctresp);
	FILE* fs = fopen(caminho, "r");

	// abrir arquivo de resultado da avaliação
	sprintf(caminho, "%s/avalct.txt", dirctresp);
	FILE* fa = fopen(caminho, "w");

	if (fs == NULL) {
		// execução do caso de teste não chegou ao fim
		fprintf(fa, "-1");
		return;
	}

	

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*
	* 	Carregar gabarito
	* 	Carregar saída da resposta submetida
	* 
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


	int gabz = 0;
	fscanf(fg, "%d", &gabz);

	int z = 0;
	fscanf(fs, "%d", &z);


	



	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*
	* Avaliar saída com relação ao gabarito e salvar o resultado no arquivo de resultado da avaliação
	* 
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	

	if (gabz == z) {
		fprintf(fa, "1");
	}
	else {
		fprintf(fa, "0");
	}

	
	fclose(fs);
	fclose(fg);
	//fclose(fe);
	//fclose(fd);
	fclose(fa);
}