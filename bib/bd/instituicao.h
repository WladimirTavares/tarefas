/*
 * Tabela Instituicao
 *
 * CREATE TABLE Instituicao (
	idInstituicao integer PRIMARY KEY,
	sigla text UNIQUE,
	nome text UNIQUE,
	obs text
) STRICT;
 *
 */


int bdInserirInstituicao (long long int idInstituicao, char* sigla, char* nome, char* obs);

int bdCadastrarInstituicao (char* sigla, char* nome, char* obs, long long int* idInstituicao);

int bdSelInstituicaoId(long long int id, long long int*** idInstituicao, char*** sigla, char*** nome, char*** obs, int* numlins);

int bdAtualizarInstituicaoId(long long int id, char* sigla, char* nome, char* obs);

int bdAtualizarInstId(char* id, char* sigla, char* nome, char* obs);

int bdApagarInstituicaoId(long long int id);

int bdApagarInstId(char* id);


/* Implementação
 * - - - - - - -
 */





int bdInserirInstituicao (long long int idInstituicao, char* sigla, char* nome, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Instituicao values (%lld, \'%s\', \'%s\', \'%s\')", idInstituicao, sigla, nome, obs);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarInstituicao (char* sigla, char* nome, char* obs, long long int* idInstituicao) {

	long long int proxIdInstituicao;
	int ret = bdProxContadorIdInstituicao(&proxIdInstituicao);

	if (ret) return ret;

	ret = bdInserirInstituicao(proxIdInstituicao, sigla, nome, obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idInstituicao) *idInstituicao = proxIdInstituicao;

	return ret;
}


int bdSelInstituicaoId(long long int id, long long int*** idInstituicao, char*** sigla, char*** nome, char*** obs, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Instituicao where idInstituicao = %lld", id);

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

	*idInstituicao = (long long int **) resultado[0];
	*sigla = (char **) resultado[1];
	*nome = (char **) resultado[2];
	*obs = (char **) resultado[3];

	return 0;
}


int bdAtualizarInstituicaoId(long long int id, char* sigla, char* nome, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Instituicao set sigla = \'%s\', nome = \'%s\', obs = \'%s\' where idInstituicao = %lld", sigla, nome, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdAtualizarInstId(char* id, char* sigla, char* nome, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Instituicao set sigla = \'%s\', nome = \'%s\', obs = \'%s\' where idInstituicao = %s", sigla, nome, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarInstituicaoId(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Instituicao where idInstituicao = %lld", id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarInstId(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Instituicao where idInstituicao = \'%s\'", id);

	return bdExecConsIAR(caminho_banco, consulta);
}


/* TODO
 *
 * A função cadastrarInstituicao() deveria ser executada
 * dentro de uma transação para que o contador de idInstituicao
 * possa retornar ao valor inicial caso haja erro na inserção
 * da instituicao.
 *
 */
