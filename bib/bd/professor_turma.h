/*
 * Tabela Professor_Turma
 *
 * CREATE TABLE Professor_Turma (
	id Usuario integer NOT NULL REFERENCES Usuario (idUsuario),
	idTurma integer NOT NULL REFERENCES Turma (idTurma),

	PRIMARY KEY (idUsuario, idTurma)
) STRICT;
 *
 */


int bdInserirProfessorTurma (char* idUsuario, char* idTurma);

int bdSelTurmasIdProfessor(long long int id, long long int*** idUsuario, long long int*** idTurma, int* numlins);

int bdApagarProfessorTurma(char* idUsuario, char* idTurma);


/* Implementação
 * - - - - - - -
 */





int bdInserirProfessorTurma (char* idUsuario, char* idTurma){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Professor_Turma values (%s, %s)", idUsuario, idTurma);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelTurmasIdProfessor(long long int id, long long int*** idUsuario, long long int*** idTurma, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Professor_Turma where idUsuario = %lld", id);

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

	*idUsuario = (long long int **) resultado[0];
	*idTurma = (long long int **) resultado[1];

	return 0;
}


int bdApagarProfessorTurma(char* idUsuario, char* idTurma) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Professor_Turma where idUsuario = %s and idTurma = %s", idUsuario, idTurma);

	return bdExecConsIAR(caminho_banco, consulta);
}
