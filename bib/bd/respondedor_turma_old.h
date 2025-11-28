/*
 * Tabela Respondedor_Turma
 *
 * CREATE TABLE Respondedor_Turma (
	idRespondedor integer NOT NULL REFERENCES Respondedor (idRespondedor),
	idTurma integer NOT NULL REFERENCES Turma (idTurma),

	PRIMARY KEY (idRespondedor, idTurma)
) STRICT;
 *
 */


int bdInserirRespondedorTurma (long long int idRespondedor, long long int idTurma);

int bdSelTurmasIdRespondedor(long long int id, long long int*** idRespondedor, long long int*** idTurma, int* numlins);

int bdApagarRespondedorTurma(long long int idRespondedor, long long int idTurma);


/* Implementação
 * - - - - - - -
 */





int bdInserirRespondedorTurma (long long int idRespondedor, long long int idTurma){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Respondedor_Turma values (%lld, %lld)", idRespondedor, idTurma);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelTurmasIdRespondedor(long long int id, long long int*** idRespondedor, long long int*** idTurma, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Respondedor_Turma where idRespondedor = %lld", id);

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

	*idRespondedor = (long long int **) resultado[0];
	*idTurma = (long long int **) resultado[1];

	return 0;
}


int bdApagarRespondedorTurma(long long int idRespondedor, long long int idTurma) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Respondedor_Turma where idRespondedor = %lld and idTurma = %lld", idRespondedor, idTurma);

	return bdExecConsIAR(caminho_banco, consulta);
}
