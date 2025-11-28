/*
 * Tabela Disciplina
 *
 * CREATE TABLE Disciplina (
	idDisciplina integer PRIMARY KEY,
	codigo text UNIQUE,
	nome text UNIQUE,
	obs text
) STRICT;
 *
 */


int bdInserirDisciplina (long long int idDisciplina, char* codigo, char* nome, char* idInstituicao, char* obs);

int bdCadastrarDisciplina (char* codigo, char* nome, char* idInstituicao, char* obs, long long int* idDisciplina) ;

int bdSelDisciplinaId(long long int id, long long int*** idDisciplina, char*** codigo, char*** nome, long long int*** idInstituicao, char*** obs, int* numlins);

int bdAtualizarDisciplinaId(char* id, char* codigo, char* nome, char* idInstituicao, char* obs);

int bdApagarDisciplinaId(char* id);


/* Implementação
 * - - - - - - -
 */





int bdInserirDisciplina (long long int idDisciplina, char* codigo, char* nome, char* idInstituicao, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Disciplina values (%lld, \'%s\', \'%s\', %s, \'%s\')", idDisciplina, codigo, nome, idInstituicao, obs);

	return bdExecConsIAR(caminho_banco, consulta);
}

int bdCadastrarDisciplina (char* codigo, char* nome, char* idInstituicao, char* obs, long long int* idDisciplina) {

	long long int proxIdDisciplina;
	int ret = bdProxContadorIdDisciplina(&proxIdDisciplina);

	if (ret) return ret;

	ret = bdInserirDisciplina(proxIdDisciplina, codigo, nome, idInstituicao, obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idDisciplina) *idDisciplina = proxIdDisciplina;

	return ret;
}


int bdSelDisciplinaId(long long int id, long long int*** idDisciplina, char*** codigo, char*** nome, long long int*** idInstituicao, char*** obs, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Disciplina where idDisciplina = %lld", id);

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

	*idDisciplina = (long long int **) resultado[0];
	*codigo = (char **) resultado[1];
	*nome = (char **) resultado[2];
	*idInstituicao = (long long int **) resultado[3];
	*obs = (char **) resultado[4];

	return 0;
}


int bdAtualizarDisciplinaId(char* id, char* codigo, char* nome, char* idInstituicao, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Disciplina set codigo = \'%s\', nome = \'%s\', idInstituicao = \'%s\', obs = \'%s\' where idDisciplina = %s", codigo, nome, idInstituicao, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarDisciplinaId(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Disciplina where idDisciplina = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
