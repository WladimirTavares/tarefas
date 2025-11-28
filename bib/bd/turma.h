/*
 * Tabela Turma
 *
 * CREATE TABLE Turma (
	idTurma integer PRIMARY KEY,
	idDisciplina integer REFERENCES Disciplina (idDisciplina),
	codigo text,
	descricao text,
	ano text,
	semestre text,
	obs text
) STRICT;
 *
 */


int bdInserirTurma (long long int idTurma, char* idDisciplina, long long int idProfCriador, char* codigo, char* descricao, char* ano, char* semestre, char* encerrada, char* obs);

int bdCadastrarTurma(char* idDisciplina, long long int idProfCriador, char* codigo, char* descricao, char* ano, char* semestre, char* obs, long long int* idTurma);

int bdSelTurmaId(long long int id, long long int*** idTurma, long long int*** idDisciplina, long long int*** idProfCriador, char*** codigo, char*** descricao, char*** ano, char*** semestre, int*** encerrada, char*** obs, int* numlins);

int bdAtualizarTurmaId(char* id, char* idDisciplina, char* idProfCriador, char* codigo, char* descricao, char* ano, char* semestre, char* encerrada, char* obs);

int bdAtualizarTurmaId2(char* id, char* idDisciplina, char* codigo, char* descricao, char* ano, char* semestre, char* encerrada, char* obs);

int bdApagarTurmaId(char* id);


/* Implementação
 * - - - - - - -
 */





int bdInserirTurma (long long int idTurma, char* idDisciplina, long long int idProfCriador, char* codigo, char* descricao, char* ano, char* semestre, char* encerrada, char* obs) {

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Turma values (%lld, %s, %lld, \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', %s)", idTurma, idDisciplina, idProfCriador, codigo, descricao, ano, semestre, obs, encerrada);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdCadastrarTurma(char* idDisciplina, long long int idProfCriador, char* codigo, char* descricao, char* ano, char* semestre, char* obs, long long int* idTurma) {

	long long int proxIdTurma;
	int ret = bdProxContadorIdTurma(&proxIdTurma);

	if (ret) return ret;

	ret = bdInserirTurma(proxIdTurma, idDisciplina, idProfCriador, codigo, descricao, ano, semestre, "0", obs);

	// se o cadastro foi realizado com sucesso e a referência idInstituicao não for NULL, escrever o id do novo cadastro na posição idInstituicao
	if (!ret && idTurma) *idTurma = proxIdTurma;

	return ret;
}


int bdSelTurmaId(long long int id, long long int*** idTurma, long long int*** idDisciplina, long long int*** idProfCriador, char*** codigo, char*** descricao, char*** ano, char*** semestre, int*** encerrada, char*** obs, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Turma where idTurma = %lld", id);

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

	*idTurma = (long long int **) resultado[0];
	*idDisciplina = (long long int **) resultado[1];
	*idProfCriador = (long long int **) resultado[2];
	*codigo = (char **) resultado[3];
	*descricao = (char **) resultado[4];
	*ano = (char **) resultado[5];
	*semestre = (char **) resultado[6];
	*encerrada = (int **) resultado[7];
	*obs = (char **) resultado[8];

	return 0;
}


int bdAtualizarTurmaId(char* id, char* idDisciplina, char* idProfCriador, char* codigo, char* descricao, char* ano, char* semestre, char* encerrada, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Turma set idDisciplina = %s, idProfCriador = %s, codigo = \'%s\', descricao = \'%s\', ano = \'%s\', semestre = \'%s\', encerrada = %s,  obs = \'%s\' where idTurma = %s", idDisciplina, idProfCriador, codigo, descricao, ano, semestre, encerrada, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}

int bdAtualizarTurmaId2(char* id, char* idDisciplina, char* codigo, char* descricao, char* ano, char* semestre, char* encerrada, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Turma set idDisciplina = %s, codigo = \'%s\', descricao = \'%s\', ano = \'%s\', semestre = \'%s\', encerrada = %s,  obs = \'%s\' where idTurma = %s", idDisciplina, codigo, descricao, ano, semestre, encerrada, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarTurmaId(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Turma where idTurma = %s", id);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarTurmaId2(char* id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Turma where idTurma = %s", id);

	//printf("%s", consulta);

	return bdExecConsIAR(caminho_banco, consulta);
}
