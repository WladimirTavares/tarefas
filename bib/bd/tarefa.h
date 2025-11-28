/*
CREATE TABLE ItemTarefa (
	idItemTarefa integer PRIMARY KEY NOT NULL,
	idTarefa integer NOT NULL REFERENCES Questao (idQuestao),
	idTrabalho integer NOT NULL REFERENCES Trabalho (idTrabalho),
	numTarefa integer
) STRICT;
 *
 */


// Tipos de tarefas

int BD_TT_SUBMISSAOSIMPLES = 1;
const char* BD_STT_SUBMISSAOSIMPLES = "1";

int BD_TT_CODIGOC = 2;
const char* BD_STT_CODIGOC = "2";

int BD_TT_CODIGOCSTDIN = 3;
const char* BD_STT_CODIGOCSTDIN = "3";



int bdInserirTarefa (long long int idTarefa, char* tipo, char* titulo, char* descricao, char* obs);

int bdCadastrarTarefa (char* tipo, char* titulo, char* descricao, char* obs, long long int* idTarefa);

int bdSelTarefaId(char* id, long long int*** idTarefa, int*** tipo, char*** titulo, char*** descricao, char*** obs, int* numlins);

int bdAtualizarTarefaId(char* id, char* titulo, char* descricao, char* obs);

int bdApagarTarefaId(char* id);


/* Implementação
 * - - - - - - -
 */





int bdInserirTarefa (long long int idTarefa, char* tipo, char* titulo, char* descricao, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Tarefa values (%lld, %s, \'%s\', \'%s\', \'%s\')", idTarefa, tipo, titulo, descricao, obs);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarTarefa (char* tipo, char* titulo, char* descricao, char* obs, long long int* idTarefa) {

	long long int proxIdTarefa;
	int ret = bdProxContadorIdTarefa(&proxIdTarefa);

	if (ret) return ret;

	ret = bdInserirTarefa(proxIdTarefa, tipo, titulo, descricao, obs);

	// se o cadastro foi realizado com sucesso e a referência idTarefa não for NULL, escrever o id do novo cadastro na posição idTarefa
	if (!ret && idTarefa) *idTarefa = proxIdTarefa;

	return ret;
}


int bdSelTarefaId(char* id, long long int*** idTarefa, int*** tipo, char*** titulo, char*** descricao, char*** obs, int* numlins){

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Tarefa where idTarefa = %s", id);

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

	*idTarefa = (long long int **) resultado[0];
	*tipo = (int **) resultado[1];
	*titulo = (char **) resultado[2];
	*descricao = (char **) resultado[3];
	*obs = (char **) resultado[4];

	return 0;
}


int bdAtualizarTarefaId(char* id, char* titulo, char* descricao, char* obs){

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Tarefa set titulo = \'%s\', descricao = \'%s\', obs = \'%s\' where idTarefa = %s", titulo, descricao, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarTarefaId(char* id){

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Tarefa where idTarefa = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}


/* TODO
 *
 * A função cadastrarTarefa() deveria ser executada
 * dentro de uma transação para que o contador de idTarefa
 * possa retornar ao valor inicial caso haja erro na inserção
 * da instituicao.
 *
 */
