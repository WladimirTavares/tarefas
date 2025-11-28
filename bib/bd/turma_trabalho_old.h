/*
 * Tabela Turma_Trabalho
 *
 * CREATE TABLE Turma_Trabalho (
	idTurma integer NOT NULL REFERENCES Turma (idTurma),
	idTrabalho integer NOT NULL REFERENCES Trabalho (idTrabalho),
	numTrabalho integer,
	ativo integer,

	PRIMARY KEY (idTurma, idTrabalho)
) STRICT;
 *
 */


int bdInserirTurmaTrabalho (long long int idTurma, long long int idTrabalho, int numTrabalho, int ativo);

int bdSelTrabalhosIdTurma(long long int id, long long int*** idTurma, long long int*** idTrabalho, int*** numTrabalho, int*** ativo, int* numlins);

int bdApagarTurmaTrabalho(long long int idTurma, long long int idTrabalho);


/* Implementação
 * - - - - - - -
 */





int bdInserirTurmaTrabalho (long long int idTurma, long long int idTrabalho, int numTrabalho, int ativo){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Turma_Trabalho values (%lld, %lld, %d, %d)", idTurma, idTrabalho, numTrabalho, ativo);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelTrabalhosIdTurma(long long int id, long long int*** idTurma, long long int*** idTrabalho, int*** numTrabalho, int*** ativo, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Turma_Trabalho where idTurma = %lld", id);

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

	*idTurma = (long long int **) resultado[0];
	*idTrabalho = (long long int **) resultado[1];
	*numTrabalho = (int **) resultado[2];
	*ativo = (int **) resultado[3];

	return 0;
}


int bdApagarTurmaTrabalho(long long int idTurma, long long int idTrabalho) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Turma_Trabalho where idTurma = %lld and idTrabalho = %lld", idTurma, idTrabalho);

	return bdExecConsIAR(caminho_banco, consulta);
}
