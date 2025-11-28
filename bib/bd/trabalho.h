/*
 * Tabela Trabalho
 *
 * CREATE TABLE Trabalho (
	idTrabalho integer PRIMARY KEY NOT NULL,
	idTurma integer NOT NULL REFERENCES Turma (idTurma),
	codigoTrabalho integer NOT NULL,
	numTrabalho integer,
	titulo text NOT NULL,
	descricao text NOT NULL,
	segHoraCriacao integer,
	segHoraInicio integer,
	segHoraFim integer,
	obs text´
) STRICT;
 *
 */


int bdInserirTrabalho (long long int idTrabalho, char* idTurma, char* titulo, char* numTrabalho, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* descricao, char* oculto, char* obs);

int bdCadastrarTrabalho (char* idTurma, char* titulo, char* numTrabalho, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* descricao, char* oculto, char* obs, long long int* idTrabalho);

int bdInclurTrabalho (char* idTurma, char* titulo, char* numTrabalho, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* descricao, char* oculto, char* obs, long long int* idTrabalho);

//int bdSelTrabalhoId(long long int id, long long int*** idTrabalho, char*** codigo, long long int*** segHoraInicio, long long int*** segHoraFim, int*** oculto, char*** descricao, char*** obs, int* numlins);

//int bdAtualizarTrabalhoId (char* idTrabalho, char* idTurma, char* titulo, char* numTrabalho, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* descricao, char* oculto, char* obs);

int bdAtualizarTrabalhoId (char* idTrabalho, char* idTurma, char* titulo, char* numTrabalho, char* segHoraInicio, char* segHoraFim, char* descricao, char* oculto, char* obs);

int bdApagarTrabalhoId(char* id);

int bdNumTrabalhosTurma(char* idTurma, int* numtrabs);


int bdPosicaoTrabalhoId(char* id, int* posAtual, int* numlins);

int bdAtualizarPosicaoTrabalho(char* idTurma, char* idTrabalho, int novaPos, int* num);



// Checa se trabalho está aberto
int bdTrabalhoAberto(char* idTrabalho);




/* Implementação
 * - - - - - - -
 */


int bdInserirTrabalho (long long int idTrabalho, char* idTurma, char* numTrabalho, char* titulo, char* descricao, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* oculto, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Trabalho values (%lld, %s, %s, \'%s\', \'%s\', %s, %s, %s, %s, \'%s\')", idTrabalho, idTurma, numTrabalho, titulo, descricao, segHoraCriacao, segHoraInicio, segHoraFim, oculto, obs);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarTrabalho (char* idTurma, char* numTrabalho, char* titulo, char* descricao, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* oculto, char* obs, long long int* idTrabalho) {

	long long int proxIdTrabalho;
	int ret = bdProxContadorIdTrabalho(&proxIdTrabalho);

	if (ret) return ret;

	ret = bdInserirTrabalho(proxIdTrabalho, idTurma, numTrabalho, titulo, descricao, segHoraCriacao, segHoraInicio, segHoraFim, oculto, obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idTrabalho) *idTrabalho = proxIdTrabalho;

	return ret;
}

int bdIncluirTrabalho (char* idTurma, char* titulo, char* descricao, char* segHoraCriacao, char* segHoraInicio, char* segHoraFim, char* oculto, char* obs, long long int* idTrabalho) {

	long long int proxIdTrabalho;
	int ret = bdProxContadorIdTrabalho(&proxIdTrabalho);

	if (ret) return ret;

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Trabalho values (%lld, %s, (SELECT COUNT(*) + 1 FROM Trabalho WHERE idTurma = %s), \'%s\', \'%s\', %s, %s, %s, %s, \'%s\')", proxIdTrabalho, idTurma, idTurma, titulo, descricao, segHoraCriacao, segHoraInicio, segHoraFim, oculto, obs);

	//printf("%s", consulta);

	ret = bdExecConsIAR(caminho_banco, consulta);

	//ret = bdInserirTrabalho(proxIdTrabalho, idTurma, numTrabalho, titulo, descricao, segHoraCriacao, segHoraInicio, segHoraFim, oculto, obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idTrabalho) *idTrabalho = proxIdTrabalho;

	return ret;
}


/*
int bdSelTrabalhoId(long long int id, long long int*** idTrabalho, long long int*** idTurma, char* titulo, long long int*** numTrabalho, long long int*** segHoraCriacao, long long int*** segHoraInicio, long long int*** segHoraFim, char*** descricao, long long int*** oculto, long long int*** ativo, char*** obs) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Trabalho where idTrabalho = %lld", id);

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

	*idTrabalho = (long long int **) resultado[0];
	*codigo = (char **) resultado[1];
	*segHoraInicio = (long long int **) resultado[2];
	*segHoraFim = (long long int **) resultado[3];
	*oculto = (int **) resultado[4];
	*descricao = (char **) resultado[5];
	*obs = (char **) resultado[6];

	return 0;
}
*/


int bdAtualizarTrabalhoId (char* idTrabalho, char* idTurma, char* titulo, char* numTrabalho, char* segHoraInicio, char* segHoraFim, char* descricao, char* oculto, char* obs) {

	// bdAtualizarPosicaoTrabalho

	int num = 0;
	int novaPos = 0;
	sscanf(numTrabalho, "%d", &novaPos);
	int ret = bdAtualizarPosicaoTrabalho(idTurma, idTrabalho, novaPos, &num);

	if (ret) {return ret;}

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta,
			"UPDATE Trabalho SET idTurma = %s, titulo = \'%s\', segHoraInicio = %s, segHoraFim = %s, descricao = \'%s\', oculto = %s, obs = \'%s\' WHERE idTrabalho = %s",
			idTurma, titulo, segHoraInicio, segHoraFim, descricao, oculto, obs, idTrabalho);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarTrabalhoId(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "DELETE FROM Trabalho WHERE idTrabalho = %s", id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdNumTrabalhosTurma(char* idTurma, int* numtrabs) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select count(*) from Trabalho where idTurma = %s", idTurma);

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*numtrabs = *( (int **) (resultado[0]) )[0];

	return 0;
}



int bdPosicaoTrabalhoId(char* id, int* posAtual, int* numlins){

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select numTrabalho from Trabalho where idTrabalho = %s", id);

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



int bdAtualizarPosicaoTrabalho(char* idTurma, char* idTrabalho, int novaPos, int* num) {

	// Escrever consulta



	char consulta[4097] = "";

	// Encontrar posição atual

	int posAtual = 0;
	int numlins = 0;

	int ret = bdPosicaoTrabalhoId(idTrabalho, &posAtual, &numlins);

	//if (numlins) {

		if (posAtual > novaPos) {
			sprintf(consulta,
					"UPDATE Trabalho "
					"SET numTrabalho = numTrabalho + 1 "
					"WHERE idTrabalho IN (SELECT idTrabalho FROM Trabalho WHERE idTurma = %s) "
							"AND numTrabalho <= %d "
							"AND numTrabalho >= %d",
			idTurma, posAtual, novaPos);
		}
		else if (posAtual < novaPos) {
			sprintf(consulta,
					"UPDATE Trabalho "
					"SET numTrabalho = numTrabalho - 1 "
					"WHERE idTrabalho IN (SELECT idTrabalho FROM Trabalho WHERE idTurma = %s) "
							"AND numTrabalho <= %d "
							"AND numTrabalho >= %d",
			idTurma, novaPos, posAtual);
		}

		//printf("%s", consulta);

		if (strcmp(consulta, "")) {
			ret = bdExecConsIAR(caminho_banco, consulta);

			if (ret) {
				return ret;
			}

			if (posAtual != novaPos){
				sprintf(consulta,
							"UPDATE Trabalho "
							"SET numTrabalho = %d "
							"WHERE idTrabalho = %s",
						novaPos, idTrabalho);

				return bdExecConsIAR(caminho_banco, consulta);
			}
		}

	*num = 0;

	return 0;
}



int bdTrabalhoAberto(char* idTrabalho){

	

}

