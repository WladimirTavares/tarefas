/*
 * Tabela Usuario
 * - - - -
 *
 * CREATE TABLE Usuario (idUsuario integer primary key, nome text, login text unique, senha text, email text, habilitado integer);
 */

int inserirUsuario(long long int idUsuario, char* nome, char* login, char* senha, char* email, int habilitado);

int selUsuarioId(long long int id, long long int** idUsuario, char*** nome, char*** login, char*** senha, char*** email, int** habilitado, int* numlins);

int atualizarUsuarioId(long long int id, char* nome, char* login, char* senha, char* email, int habilitado);

int apagarUsuarioId(long long int id);




/* Implementação
 * - - - - - - -
 */

int inserirUsuario(long long int idUsuario, char* nome, char* login, char* senha, char* email, int habilitado){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Usuario values (%lld, \'%s\', \'%s\', \'%s\', \'%s\', %d)", idUsuario, nome, login, senha, email, habilitado);

	return execConsIAR(caminho_banco, consulta);
}


int selUsuarioId(long long int id, long long int** idUsuario, char*** nome, char*** login, char*** senha, char*** email, int** habilitado, int* numlins) {

	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Usuario where idUsuario = %lld", id);

	// Preparar consulta

	sqlite3* cbd = NULL;
	sqlite3_stmt* com = NULL;

	prepConsSel(caminho_banco, consulta, &cbd, &com);

	int ret = 0;

	// Inicializar os vetores

	*idUsuario = NULL;
	*nome = NULL;
	*login = NULL;
	*senha = NULL;
	*email = NULL;
	*habilitado = NULL;

	*numlins = 0;

	while ( (ret = sqlite3_step(com)) == SQLITE_ROW ) {

		anexarLongLongInt(sqlite3_column_int64(com, 0), idUsuario, *numlins);

		anexarText(sqlite3_column_text(com, 1), nome, *numlins);

		anexarText(sqlite3_column_text(com, 2), login, *numlins);

		anexarText(sqlite3_column_text(com, 3), senha, *numlins);

		anexarText(sqlite3_column_text(com, 4), email, *numlins);

		anexarInt(sqlite3_column_int(com, 5), habilitado, *numlins);

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


int atualizarUsuarioId(long long int id, char* nome, char* login, char* senha, char* email, int habilitado) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Usuario set nome = \'%s\', login = \'%s\', senha = \'%s\', email = \'%s\', habilitado = %d where idUsuario = %lld", nome, login, senha, email, habilitado, id);

	return execConsIAR(caminho_banco, consulta);
}


int apagarUsuarioId(long long int id){

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Usuario where idUsuario = %lld", id);

	return execConsIAR(caminho_banco, consulta);
}
