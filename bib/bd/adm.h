/*
 * Tabela Adm
 * - - - -
 *
 * CREATE TABLE Adm (
 *	idAdm integer PRIMARY KEY,
 *	idUsuario integer REFERENCES Usuario (idUsuario)
 * ) STRICT;
 */



int bdInserirAdm (long long int idAdm, long long int idUsuario);

int bdSelAdmId(long long int id, long long int*** idAdm, long long int*** idUsuario, int* numlins);

int bdApagarAdmId(long long int id);


/* Implementação
 * - - - - - - -
 */





int bdInserirAdm (long long int idAdm, long long int idUsuario){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Adm values (%lld, %lld)", idAdm, idUsuario);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelAdmId(long long int id, long long int*** idAdm, long long int*** idUsuario, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Adm where idAdm = %lld", id);

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

	*idAdm = (long long int **) resultado[0];
	*idUsuario = (long long int **) resultado[1];

	return 0;
}


int bdApagarAdmId(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Adm where idAdm = %lld", id);

	return bdExecConsIAR(caminho_banco, consulta);
}
