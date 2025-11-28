/*
 * Tabela PerfilRespondedor_Turma
 *
 * CREATE TABLE PerfilRespondedor_Turma (
	idPerfilRespondedor integer NOT NULL REFERENCES PerfilRespondedor (idPerfilRespondedor),
	idTurma integer NOT NULL REFERENCES Turma (idTurma),

	PRIMARY KEY (idPerfilRespondedor, idTurma)
) STRICT;
 *
 */


int bdInserirPerfilRespondedorTurma (char* idPerfilRespondedor, char* idTurma);

int selTurmasIdPerfilRespondedor(long long int id, long long int*** idPerfilRespondedor, long long int*** idTurma, int* numlins);

int apagarPerfilRespondedorTurma(char* idPerfilRespondedor, char* idTurma);



/* Implementação
 * - - - - - - -
 */





int bdInserirPerfilRespondedorTurma (char* idPerfilRespondedor, char* idTurma){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into PerfilRespondedor_Turma values (%s, %s, 1)", idPerfilRespondedor, idTurma);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int selTurmasIdPerfilRespondedor(long long int id, long long int*** idPerfilRespondedor, long long int*** idTurma, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from PerfilRespondedor_Turma where idPerfilRespondedor = %lld", id);

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	//int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, numlins);

	if (ret)
		return ret;

	// Converter colunas

	*idPerfilRespondedor = (long long int **) resultado[0];
	*idTurma = (long long int **) resultado[1];

	return 0;
}


int apagarPerfilRespondedorTurma(char* idPerfilRespondedor, char* idTurma) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from PerfilRespondedor_Turma where idPerfilRespondedor = %s and idTurma = %s", idPerfilRespondedor, idTurma);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}
