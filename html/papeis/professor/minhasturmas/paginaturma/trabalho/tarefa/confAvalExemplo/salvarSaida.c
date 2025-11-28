// esta rotina será executada ao final de cada caso de teste
// do programa submetido para salvar a resposta em arquivo
// a variável dirctresp é o diretório onde a saída do caso de teste
// gerada pelo programa submetido é armazenada

int __salvar_saida_casoteste(int __ct, char* __dirctresp) {
	// a variável 'dirctresp' é o caminho até o diretório do caso de teste
	// onde os dados gerados pelo caso de teste do programa submetido
	// são guardados (saida.fb)

	//abrir arquivo de saída
	char __caminho[4097];
	sprintf(__caminho, "%s/saida.txt", __dirctresp);
	FILE* __f = fopen(__caminho, "w");

	// gravar dados de saída
	fprintf(__f, "%d", z);

	
	fclose(__f);
}