// gerar os arquivos (dados estáticos) de caso de teste
int gerarArquivosCasoTeste(int ct, char* dirct) {
	// a variável 'dirct' é o caminho até o diretório onde ficam os
	// os arquivos referentes ao caso de teste (entrada.fb, gabarito.fb)
	// você pode colocar qualquer outro arquivo que queira nesse diretório

	// gerar valores de entrada
	gerarCasoTeste(ct);

	// salvar entrada
	char caminho[4097];
	sprintf(caminho, "%s/entrada.txt", dirct);
	FILE* fe = fopen(caminho, "w");

	// gravar entrada
	fprintf(fe, "%d", N);

	for (int i = 0; i < N; i++) {
		fprintf(fe, " %d", L[i]);
	}

	fclose(fe);

	// calcular solução
	solucaoTarefa();

	// salvar gabarito
	sprintf(caminho, "%s/gabarito.txt", dirct);
	FILE* fg = fopen(caminho, "w");

	// gravar gabarito
	fprintf(fg, "%d", maior);

	fclose(fg);
}