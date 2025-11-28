/*
 * Tabela Curso
 *
 * CREATE TABLE Curso (
	idCurso integer PRIMARY KEY NOT NULL,
	codigo text,
	nome text,
	idInstituicao integer REFERENCES Instituicao(idInstituicao) ON DELETE RESTRICT ON UPDATE RESTRICT,
	obs text,

	Unique (codigo, idInstituicao),
	check(codigo <> '' AND nome <> '')
) STRICT;
 *
 */


int bdInserirCurso (long long int idCurso, char* codigo, char* nome, char* idInstituicao, char* obs);

int bdCadastrarCurso (char* codigo, char* nome, char* idInstituicao, char* obs, long long int* idCurso);

int bdSelCursoId(long long int id, long long int*** idCurso, char*** codigo, char*** nome, long long int*** idInstituicao, char*** obs, int* numlins);

//int bdAtualizarCursoId(long long int id, char* codigo, char* nome, long long int idInstituicao, char* obs);
int bdAtualizarCursoId(char* id, char* codigo, char* nome, char* idInstituicao, char* obs);

int bdApagarCursoId(char* id);


/* Implementação
 * - - - - - - -
 */





int bdInserirCurso (long long int idCurso, char* codigo, char* nome, char* idInstituicao, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Curso values (%lld, \'%s\', \'%s\', %s, \'%s\')", idCurso, codigo, nome, idInstituicao, obs);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarCurso (char* codigo, char* nome, char* idInstituicao, char* obs, long long int* idCurso) {

	long long int proxIdCurso;
	int ret = bdProxContadorIdCurso(&proxIdCurso);

	if (ret) return ret;

	ret = bdInserirCurso(proxIdCurso, codigo, nome, idInstituicao, obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idCurso) *idCurso = proxIdCurso;

	return ret;
}


int bdSelCursoId(long long int id, long long int*** idCurso, char*** codigo, char*** nome, long long int*** idInstituicao, char*** obs, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Curso where idCurso = %lld", id);

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

	*idCurso = (long long int **) resultado[0];
	*codigo = (char **) resultado[1];
	*nome = (char **) resultado[2];
	*idInstituicao = (long long int **) resultado[3];
	*obs = (char **) resultado[4];

	return 0;
}

int bdAtualizarCursoId(char* id, char* codigo, char* nome, char* idInstituicao, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Curso set codigo = \'%s\', nome = \'%s\', idInstituicao = %s, obs = \'%s\' where idCurso = %s", codigo, nome, idInstituicao, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarCursoId(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Curso where idCurso = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
