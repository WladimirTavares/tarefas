/*
 * Tabela Respondedor
 *
 * CREATE TABLE Respondedor (
	idRespondedor integer PRIMARY KEY,
	idUsuario integer unique REFERENCES Usuario(idUsuario),
	matricula text,
	idCurso integer REFERENCES Curso(idCurso),
	idInstituicao integer REFERENCES Instituicao(idInstituicao),
	habilitado integer,
	obs text,

	UNIQUE (matricula, idInstituicao)
) STRICT;
 *
 */


int bdInserirRespondedor (long long int idRespondedor, long long int idUsuario, char* matricula, long long int idCurso, long long int idInstituicao, int habilitado, char* obs);

int bdSelRespondedorId(long long int id, long long int*** idRespondedor, long long int*** idUsuario, char*** matricula, long long int*** idCurso, long long int*** idInstituicao, int*** habilitado, char*** obs, int* numlins);

int bdAtualizarRespondedorId(long long int id, char* matricula, long long int idCurso, long long int idInstituicao, int habilitado, char* obs);

int bdApagarRespondedorId(long long int id);


/* Implementação
 * - - - - - - -
 */





int bdInserirRespondedor (long long int idRespondedor, long long int idUsuario, char* matricula, long long int idCurso, long long int idInstituicao, int habilitado, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Respondedor values (%lld, %lld, %s, %lld, %lld, %d, %s)", idRespondedor, idUsuario, matricula, idCurso, idInstituicao, habilitado, obs);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelRespondedorId(long long int id, long long int*** idRespondedor, long long int*** idUsuario, char*** matricula, long long int*** idCurso,  long long int*** idInstituicao, int*** habilitado, char*** obs, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Respondedor where idRespondedor = %lld", id);

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
	*idUsuario = (long long int **) resultado[1];
	*matricula = (char **) resultado[2];
	*idCurso = (long long int **) resultado[3];
	*idInstituicao = (long long int **) resultado[4];
	*habilitado = (int **) resultado[5];
	*obs = (char **) resultado[6];

	return 0;
}


int bdAtualizarRespondedorId(long long int id, char* matricula, long long int idCurso, long long int idInstituicao, int habilitado, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Respondedor set matricula = \'%s\', idCurso = %lld, idInstituicao = %lld, habilitado = %d, obs = \'%s\' where idRespondedor = %lld", matricula, idCurso, idInstituicao, habilitado, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarRespondedorId(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Respondedor where idRespondedor = %lld", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
