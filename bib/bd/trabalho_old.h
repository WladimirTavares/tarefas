/*
 * Tabela Trabalho
 *
 * CREATE TABLE Trabalho (
	idTrabalho integer PRIMARY KEY,
	codigo text UNIQUE,
	segHoraInicio integer,
	segHoraFim integer,
	oculto integer,
	descricao text,
	obs text
) STRICT;
 *
 */


int bdInserirTrabalho (long long int idTrabalho, char* codigo, long long int segHoraInicio, long long int segHoraFim, int oculto, char* descricao, char* obs);

int bdSelTrabalhoId(long long int id, long long int*** idTrabalho, char*** codigo, long long int*** segHoraInicio, long long int*** segHoraFim, int*** oculto, char*** descricao, char*** obs, int* numlins);

int bdAtualizarTrabalhoId(long long int id, char* codigo, long long int segHoraInicio, long long int segHoraFim, int oculto, char* descricao, char* obs);

int bdApagarTrabalhoId(long long int id);


/* Implementação
 * - - - - - - -
 */





int bdInserirTrabalho (long long int idTrabalho, char* codigo, long long int segHoraInicio, long long int segHoraFim, int oculto, char* descricao, char* obs){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Trabalho values (%lld, \'%s\', %lld, %lld, %d, \'%s\', \'%s\')", idTrabalho, codigo, segHoraInicio, segHoraFim, oculto, descricao, obs);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelTrabalhoId(long long int id, long long int*** idTrabalho, char*** codigo, long long int*** segHoraInicio, long long int*** segHoraFim, int*** oculto, char*** descricao, char*** obs, int* numlins) {

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


int bdAtualizarTrabalhoId(long long int id, char* codigo, long long int segHoraInicio, long long int segHoraFim, int oculto, char* descricao, char* obs) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Trabalho set codigo = \'%s\', segHoraInicio = %lld, segHoraFim = %lld, oculto = %d, descricao = \'%s\', obs = \'%s\' where idTrabalho = %lld", codigo, segHoraInicio, segHoraFim, oculto, descricao, obs, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarTrabalhoId(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Trabalho where idTrabalho = %lld", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
