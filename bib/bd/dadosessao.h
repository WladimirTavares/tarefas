/*
 * Tabela DadosSessao
 *
 * 
 * CREATE TABLE DadoSessao (
        idSessao integer NOT NULL,                    
        grupo text NOT NULL,
        chave text NOT NULL,
        valor text,  
        PRIMARY KEY (idSessao, grupo, chave), 
        CHECK (grupo <> '' AND chave <> '')
) STRICT;
*
*
*/


int bdInserirDadoSessao (long long int idSessao, char* grupo, char* chave, char* valor);

//int bdSelDadoSessaoGrupo (long long int idSessao, char* grupo, long long int*** idSessao, char*** grupo, char*** chave, char*** valor, int* numlins);


int bdApagarDadosDadoSessao(long long int id);

int bdApagarGrupoDadoSessao(long long int id, char* grupo);




/* Implementação
 * - - - - - - -
 */



int bdInserirDadoSessao (long long int idSessao, char* grupo, char* chave, char* valor){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into DadoSessao values (%lld, \'%s\', \'%s\', %s')", idSessao, grupo, chave, valor);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdApagarDadosDadoSessao(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from DadoSessao where idSessao = %lld", id);

	return bdExecConsIAR(caminho_banco, consulta);
}

int bdApagarGrupoDadoSessao(long long int id, char* grupo) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from DadoSessao where idSessao = %lld and grupo = \'%s%%\'", id, grupo);

	return bdExecConsIAR(caminho_banco, consulta);
}