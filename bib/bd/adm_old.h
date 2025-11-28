/*
 * Tabela Adm
 * - - - -
 *
 * CREATE TABLE Adm (
 *	idAdm integer PRIMARY KEY,
 *	idUsuario integer REFERENCES Usuario (idUsuario)
 * );
 */

int inserirAdm(long long int idAdm, long long int idUsuario);

int selAdmId(long long int id, long long int** idAdm, long long int** idUsuario, int* numlins);

int apagarAdmId(long long int id);



/* Implementação
 * - - - - - - -
 */



int inserirAdm(long long int idAdm, long long int idUsuario) {

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Adm values (%lld, %lld)", idAdm, idUsuario);

	return execConsIAR(caminho_banco, consulta);
}


int selAdmId(long long int id, long long int** idAdm, long long int** idUsuario, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Adm where idAdm = %lld", id);

	// Preparar consulta

	sqlite3* cbd = NULL;
	sqlite3_stmt* com = NULL;

	prepConsSel(caminho_banco, consulta, &cbd, &com);

	int ret = 0;

	// Inicializar os vetores

	*idAdm = NULL;
	*idUsuario = NULL;


	*numlins = 0;
	while ( (ret = sqlite3_step(com)) == SQLITE_ROW ) {

		// coluna idUsuario integer

		anexarLongLongInt(sqlite3_column_int64(com, 0), idAdm, *numlins);

		anexarLongLongInt(sqlite3_column_int64(com, 1), idUsuario, *numlins);

		(*numlins)++;
	}

	if (ret == SQLITE_DONE) {		// consulta executada com sucesso
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return 0;
	}
	else {		// erro durante a execução da consulta
		fprintf(stderr, "Erro durante recuperação dos dados (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return (1);
	}
}


int apagarAdmId(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Adm where idAdm = %lld", id);

	return execConsIAR(caminho_banco, consulta);
}
