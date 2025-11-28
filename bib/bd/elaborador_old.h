/*
 * Tabela Elaborador
 *
 * CREATE TABLE Elaborador (
 * 	idElaborador integer PRIMARY KEY,
 * 	idUsuario integer REFERENCES Usuario (idUsuario)
) STRICT;
 *
 */


int inserirElaborador (long long int idElaborador, long long int idUsuario);

int selElaboradorId(long long int id, long long int*** idElaborador, long long int*** idUsuario, int* numlins);

int apagarElaboradorId(long long int id);


/* Implementação
 * - - - - - - -
 */





int inserirElaborador (long long int idElaborador, long long int idUsuario){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Elaborador values (%lld, %lld)", idElaborador, idUsuario);

	return execConsIAR(caminho_banco, consulta);
}


int selElaboradorId(long long int id, long long int*** idElaborador, long long int*** idUsuario, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Elaborador where idElaborador = %lld", id);

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	//int numlins = 0;

	int ret = execSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, numlins);

	if (ret)
		return ret;

	// Converter colunas

	*idElaborador = (long long int **) resultado[0];
	*idUsuario = (long long int **) resultado[1];

	return 0;
}


int apagarElaboradorId(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Elaborador where idElaborador = %lld", id);

	return execConsIAR(caminho_banco, consulta);
}
