/*
CREATE TABLE ItemItemTarefa (
	idItemItemTarefa integer PRIMARY KEY NOT NULL,
	idItemTarefa integer NOT NULL REFERENCES Questao (idQuestao),
	idTrabalho integer NOT NULL REFERENCES Trabalho (idTrabalho),
	numItemTarefa integer
) STRICT;
 *
 */


int bdInserirItemTarefa (long long int idItemTarefa, char* idTarefa, char* idTrabalho, char* numItemTarefa);

int bdIncluirItemTarefa (long long int idItemTarefa, char* idTarefa, char* idTrabalho);

int bdCadastrarItemTarefa (char* idTarefa, char* idTrabalho, char* numItemTarefa, long long int* idItemTarefa);

int bdSelItemTarefaId(char* id, long long int*** idItemTarefa, long long int*** idTarefa, long long int*** idTrabalho, int*** numItemTarefa, int* numlins);

int bdAtualizarItemTarefaId(char* id, char* idTarefa, char* idTrabalho, char* numItemTarefa);

int bdApagarItemTarefaId(char* id);

int bdAtualizarPosicao(char* idTrabalho, char* idItemTarefa, int novaPos, int* num);

int bdNumItensTarefaTrabalho(char* idTrabalho, int* num, int* numlins);


/* Implementação
 * - - - - - - -
 */





int bdInserirItemTarefa (long long int idItemTarefa, char* idTarefa, char* idTrabalho, char* numItemTarefa){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into ItemTarefa values (%lld, %s, %s, %s)", idItemTarefa, idTarefa, idTrabalho, numItemTarefa);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}

int bdIncluirItemTarefa (long long int idItemTarefa, char* idTarefa, char* idTrabalho){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into ItemTarefa values (%lld, %s, %s, (SELECT COUNT(*) + 1 FROM ItemTarefa WHERE idTrabalho = %s))", idItemTarefa, idTarefa, idTrabalho, idTrabalho);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarItemTarefa (char* idTarefa, char* idTrabalho, char* numItemTarefa, long long int* idItemTarefa){

	long long int proxIdItemTarefa;
	int ret = bdProxContadorIdItemTarefa(&proxIdItemTarefa);

	if (ret) return ret;

	ret = bdInserirItemTarefa(proxIdItemTarefa, idTarefa, idTrabalho, numItemTarefa);

	// se o cadastro foi realizado com sucesso e a referência idItemTarefa não for NULL, escrever o id do novo cadastro na posição idItemTarefa
	if (!ret && idItemTarefa) *idItemTarefa = proxIdItemTarefa;

	return ret;
}


int bdSelItemTarefaId(char* id, long long int*** idItemTarefa, long long int*** idTarefa, long long int*** idTrabalho, int*** numItemTarefa, int* numlins){

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from ItemTarefa where idItemTarefa = %s", id);

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

	*idItemTarefa = (long long int **) resultado[0];
	*idTarefa = (long long int **) resultado[1];
	*idTrabalho = (long long int **) resultado[2];
	*numItemTarefa = (int **) resultado[3];

	return 0;
}


int bdAtualizarItemTarefaId(char* id, char* idTarefa, char* idTrabalho, char* numItemTarefa){

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update ItemTarefa set idTarefa = %s, idTrabalho = %s, numItemTarefa = %s where idItemTarefa = %s", idTarefa, idTrabalho, numItemTarefa, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarItemTarefaId(char* id){

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from ItemTarefa where idItemTarefa = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}



int bdPosicaoItemTarefaId(char* id, int* posAtual, int* numlins){

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select numItemTarefa from ItemTarefa where idItemTarefa = %s", id);

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

	if (numlins) {
		*posAtual = *(( (int **) (resultado[0]) )[0] );
	}


	return 0;
}


int bdAtualizarPosicaoItemTarefa(char* idTrabalho, char* idItemTarefa, int novaPos, int* num) {

	// Escrever consulta

	char consulta[4097];

	// Encontrar posição atual

	int posAtual = 0;
	int numlins = 0;

	int ret = bdPosicaoItemTarefaId(idItemTarefa, &posAtual, &numlins);

	if (numlins) {

		if (posAtual > novaPos) {
			sprintf(consulta,
					"UPDATE ItemTarefa "
					"SET numItemTarefa = numItemTarefa + 1 "
					"WHERE idItemTarefa IN (SELECT idItemTarefa FROM ItemTarefa WHERE idTrabalho = %s) "
							"AND numItemTarefa <= %d "
							"AND numItemTarefa >= %d",
			idTrabalho, posAtual, novaPos);
		}
		else if (posAtual < novaPos) {
			sprintf(consulta,
					"UPDATE ItemTarefa "
					"SET numItemTarefa = numItemTarefa - 1 "
					"WHERE idItemTarefa IN (SELECT idItemTarefa FROM ItemTarefa WHERE idTrabalho = %s) "
							"AND numItemTarefa <= %d "
							"AND numItemTarefa >= %d",
			idTrabalho, novaPos, posAtual);
		}

		ret = bdExecConsIAR(caminho_banco, consulta);

		if (ret) {
			return ret;
		}

		if (posAtual != novaPos){
			sprintf(consulta,
						"UPDATE ItemTarefa "
						"SET numItemTarefa = %d "
						"WHERE idItemTarefa = %s",
					novaPos, idItemTarefa);

			return bdExecConsIAR(caminho_banco, consulta);
		}

	}

	*num = 0;

	return 0;
}



int bdNumItensTarefaTrabalho(char* idTrabalho, int* num, int* numlins){

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "SELECT COUNT(*) from ItemTarefa where idTrabalho = %s", idTrabalho);

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

	if (numlins) {
		*num = *(( (int **) (resultado[0]) )[0] );
	}


	return 0;
}


/* TODO
 *
 * A função cadastrarItemTarefa() deveria ser executada
 * dentro de uma transação para que o contador de idItemTarefa
 * possa retornar ao valor inicial caso haja erro na inserção
 * da instituicao.
 *
 */
