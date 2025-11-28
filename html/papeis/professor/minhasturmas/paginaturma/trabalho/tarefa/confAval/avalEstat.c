// rotina de avaliação estática de caso de teste
// recebe o número do caso de teste e o diretório onde os dados
// de execução do caso de teste são salvos

// rotina de avaliação global da tarefa
int avaliacaoEstaticaTarefa(int ncts, char* supdirct, char* supdirctresp) {

	for (int i = 1; i <= ncts; i++) {

		// avaliar cada caso de teste
		char dirct[4097] = "";
		char dirctresp[4097] = "";

		sprintf(dirct, "%s/%d", supdirct, i);
		sprintf(dirctresp, "%s/%d", supdirctresp, i);

		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* 
		* 	Avaliação do caso de teste
		* 
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

		// abrir arquivo de gabarito e entrada (caso necessário)
		char caminho[4097];
		sprintf(caminho, "%s/gabarito.txt", dirct);
		FILE* fg = fopen(caminho, "r");
		//sprintf(caminho, "%s/entrada.txt", dirct);
		//FILE* fe = fopen(caminho, "r");
		//  caso tenha sido gerado caso de teste dinâmico
		//sprintf(caminho, "%s/entradadinamica.txt", dirctresp);
		//FILE* fd = fopen(caminho, "r");

		//carregar gabarito (e entrada)

		

		// abrir arquivo de saída
		sprintf(caminho, "%s/saida.txt", dirctresp);
		FILE* fs = fopen(caminho, "r");

		//carregar saída da resposta submetida


		// abrir arquivo de resultado da avaliação
		sprintf(caminho, "%s/avalct.txt", dirctresp);
		FILE* fa = fopen(caminho, "w");

		// avaliar saída com relação ao gabarito e salvar o resultado no arquivo de resultado da avaliação
		// coletar informações sobre a avaliação do caso de teste para compor a avaliação global da tarefa

		fclose(fs);
		fclose(fg);
		//fclose(fe);
		//fclose(fd);
		fclose(fa);
	}

	// escrever avaliação global da tarefa
	char caminho[5000] = "";
	sprintf(caminho, "%s/avaltarefa.txt", supdirctresp);
	FILE* fat = fopen(caminho, "w");

	// escreva o resultado da avaliação global da tarefa


	fclose(fat);
}