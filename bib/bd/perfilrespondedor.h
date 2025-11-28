/*
 * Tabela PerfilRespondedor
 *
 * CREATE TABLE PerfilRespondedor (
	idPerfilRespondedor integer PRIMARY KEY,
	idUsuario integer REFERENCES Usuario(idUsuario),
	matricula text,
	idCurso integer REFERENCES Curso(idCurso),
	habilitado integer,
	obs text,

	UNIQUE (matricula, idCurso, idInstituicao)
) STRICT;
 *
 */


int bdInserirPerfilRespondedor (long long int idPerfilRespondedor, char* idUsuario, char* matricula, char* idCurso, char* habilitado, char* obs);

//
int bdCadastrarPerfilRespondedor(char* idUsuario, char* matricula, char* idCurso, char* habilitado, char* obs, long long int* idPerfilRespondedor);

int bdSelPerfilRespondedorId(long long int id, long long int*** idPerfilRespondedor, long long int*** idUsuario, char*** matricula, long long int*** idCurso, long long int*** idInstituicao, int*** habilitado, char*** obs, int* numlins);

int bdAtualizarPerfilRespondedorId(char* id, char* matricula, char* idCurso, char* habilitado, char* obs);

int bdApagarPerfilRespondedorId(char* id);


/* Implementação
 * - - - - - - -
 */





int bdInserirPerfilRespondedor (long long int idPerfilRespondedor, char* idUsuario, char* matricula, char* idCurso, char* habilitado, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into PerfilRespondedor values (%lld, %s, \'%s\', %s, %s, \'%s\')", idPerfilRespondedor, idUsuario, matricula, idCurso, habilitado, obs);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarPerfilRespondedor(char* idUsuario, char* matricula, char* idCurso, char* habilitado, char* obs, long long int* idPerfilRespondedor){

	long long int proxIdPerfil;
	int ret = bdProxContadorIdPerfilRespondedor(&proxIdPerfil);

	if (ret) return ret;

	ret = bdInserirPerfilRespondedor(proxIdPerfil, idUsuario, matricula, idCurso, habilitado, obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idPerfilRespondedor) *idPerfilRespondedor = proxIdPerfil;

	return ret;
}


int bdSelPerfilRespondedorId(long long int id, long long int*** idPerfilRespondedor, long long int*** idUsuario, char*** matricula, long long int*** idCurso,  long long int*** idInstituicao, int*** habilitado, char*** obs, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from PerfilRespondedor where idPerfilRespondedor = %lld", id);

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
	*idUsuario = (long long int **) resultado[1];
	*matricula = (char **) resultado[2];
	*idCurso = (long long int **) resultado[3];
	*idInstituicao = (long long int **) resultado[4];
	*habilitado = (int **) resultado[5];
	*obs = (char **) resultado[6];

	return 0;
}


int bdAtualizarPerfilRespondedorId(char* id, char* matricula, char* idCurso, char* habilitado, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update PerfilRespondedor set matricula = \'%s\', idCurso = %s, habilitado = %s, obs = \'%s\' where idPerfilRespondedor = %s", matricula, idCurso, habilitado, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarPerfilRespondedorId(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from PerfilRespondedor where idPerfilRespondedor = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
