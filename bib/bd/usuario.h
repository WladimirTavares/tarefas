/*
 * Tabela Usuario
 * - - - -
 *
 * CREATE TABLE Usuario (
	idUsuario integer PRIMARY KEY NOT NULL,
	nome text NOT NULL,
	login text UNIQUE NOT NULL,
	senha text NOT NULL,
	email text,
	adm integer NOT NULL,
	professor integer NOT NULL,
	habilitado integer NOT NULL
) STRICT;
 */

int bdInserirUsuario(long long int idUsuario, char* nome, char* login, char* senha, char* email, char* adm, char* professor, char* habilitado);

// idUsuario recebe o id criado para o usuário
int bdCadastrarUsuario(char* nome, char* login, char* senha, char* email, char* adm, char* professor, char* habilitado, long long int* idUsuario);

int bdSelUsuarioId(long long int id, long long int** idUsuario, char*** nome, char*** login, char*** senha, char*** email, int** adm, int** professor, int** habilitado, int* numlins);

int bdAtualizarUsuarioIdSenha(char* id, char* nome, char* login, char* senha, char* email, char* adm, char* professor, char* habilitado);

int bdAtualizarUsuarioId(char* id, char* nome, char* login, char* email, char* adm, char* professor, char* habilitado);

int bdApagarUsuarioId(char* id);




/* Implementação
 * - - - - - - -
 */

int bdInserirUsuario(long long int idUsuario, char* nome, char* login, char* senha, char* email, char* adm, char* professor, char* habilitado){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Usuario values (%lld, \'%s\', \'%s\', \'%s\', \'%s\', %s, %s, %s)", idUsuario, nome, login, senha, email, adm, professor, habilitado);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarUsuario(char* nome, char* login, char* senha, char* email, char* adm, char* professor, char* habilitado, long long int* idUsuario) {

	long long int proxIdUsuario;
	int ret = bdProxContadorIdUsuario(&proxIdUsuario);

	if (ret) return ret;

	ret = bdInserirUsuario(proxIdUsuario, nome, login, senha, email, adm, professor, habilitado);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idUsuario) *idUsuario = proxIdUsuario;

	return ret;
}


int bdSelUsuarioId(long long int id, long long int** idUsuario, char*** nome, char*** login, char*** senha, char*** email, int** adm, int** professor, int** habilitado, int* numlins) {

	/* As variáveis:
	 *
	 *		idUsuario,
	 * 		nome,
	 * 		login,
	 * 		senha,
	 * 		email e
	 * 		habilitado
	 *
	 * são referências. Devem, portanto, ser desreferenciadas
	 * para acessar as posições de memória originais.
	 */


	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Usuario where idUsuario = %lld", id);

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, numlins);

	if (ret)
		return ret;

	// Converter colunas

	*idUsuario = (long long int *) resultado[0];
	*nome = (char **) resultado[1];
	*login = (char **) resultado[2];
	*senha = (char **) resultado[3];
	*email = (char **) resultado[4];
	*adm = (int *) resultado[5];
	*professor = (int *) resultado[6];
	*habilitado = (int *) resultado[7];

	return 0;
}


int bdAtualizarUsuarioIdSenha(char* id, char* nome, char* login, char* senha, char* email, char* adm, char* professor, char* habilitado) {

	// Escrever consulta

	char consulta[4097] = "";
	sprintf(consulta, "update Usuario set nome = \'%s\', login = \'%s\', senha = \'%s\', email = \'%s\', adm = %s, professor = %s, habilitado = %s where idUsuario = %s", nome, login, senha, email, adm, professor, habilitado, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdAtualizarUsuarioId(char* id, char* nome, char* login, char* email, char* adm, char* professor, char* habilitado) {

	// Escrever consulta

	char consulta[4097] = "";
	sprintf(consulta, "update Usuario set nome = \'%s\', login = \'%s\', email = \'%s\', adm = %s, professor = %s, habilitado = %s where idUsuario = %s", nome, login, email, adm, professor, habilitado, id);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarUsuarioId(char* id){

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Usuario where idUsuario = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
