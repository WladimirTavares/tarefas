// esta rotina será executada antes de cada caso de teste
// do programa submetido, carregando valores para as
// variáveis globais, seja a partir dos dados gerados em arquivo,
// seja gerando dados em tempo de execução

int __carregar_dados_casoteste(int __ct, char* __dirct, char* __dirctresp) {
	// a variável '__dirct' é o caminho até o diretório onde ficam os
	// os arquivos referentes aos casos de teste (entrada.fb, gabarito.fb, etc.)
	// acesse esses arquivos no modo 'readonly'

	// a variável '__dirctresp' é o caminho para o diretório do caso de teste
	// do respondedor. pode ser usado para implementar casos de teste aleatórios
	// gerados dinâmicamente no momento da execução do caso de teste.

	// abrir arquivo com entradas
	char __caminho[4097];
	sprintf(__caminho, "%s/entrada.txt", __dirct);
	FILE* __f = fopen(__caminho, "r");

	// carregar dados de entrada

	fclose(__f);

}