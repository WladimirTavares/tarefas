#include <stdio.h>
#include <stdlib.h>

#include "tarefasbd.h"





int main() {

	//inserirUsuario(1, "Binho", "franc", "111", "b@c", 1);

	//atualizarUsuarioId(1, "Franc", "franc", "123", "a@b", 1);

	//apagarUsuarioId(1);

	/*
	long long int* idUsuario;
	char** nome;
	char** login;
	char** senha;
	char** email;
	int* habilitado;
	int numlins;


	selUsuarioId(1, &idUsuario, &nome, &login, &senha, &email, &habilitado, &numlins);

	printf("Total de linhas retornadas: %d\n", numlins);
	for (int i = 0; i < numlins; i++) {
		printf("%lld, ", idUsuario[i]);
		printf("%s, ", nome[i]);
		printf("%s, ", login[i]);
		printf("%s, ", senha[i]);
		printf("%s, ", email[i]);
		printf("%d\n", habilitado[i]);
	}
	*/


	//int execSelecao(char* caminhoBanco, char* consulta, void*** resultado, char*** nomesCols, int** tiposCols, int* numcols, int* numlins)

	//char consulta[1000] = "select * from Tabelac";


	/*
	char consulta[1000] = "select * from Tabelac";
	char* caminhoBanco = "tarefas.bd";

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	execSelecao2(caminhoBanco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*/
	//int* vlli = resultado[0];
	//printf("%lld", vlli[0]);

	//printf("tipos: %d, %d, %d\n", tiposCols[0], tiposCols[1], tiposCols[2]);

	//imprimirSelecao2(resultado, nomesCols, tiposCols, numcols, numlins);


	//inserirElaborador(1,1);
	//inserirElaborador(2,2);

	/*long long int** idElaborador = NULL;
	long long int** idUsuario = NULL;
	int numlins = 0;

	selElaboradorId(2, &idElaborador, &idUsuario, &numlins);

	printf("numlins: %d\n", numlins);
	printf("%lld, %lld\n", *(idElaborador[0]), *(idUsuario[0]));
	*/

	//int inserirUsuario(long long int idUsuario, char* nome, char* login, char* senha, char* email, int habilitado);

	//inserirUsuario(4, "Joao", "joao", "joao", "jo@o", 1);
	//inserirUsuario(5, "Paulo", "paulo", "paulo", "p@ulo", 1);
	//inserirUsuario(6, "P", "p", "p", "p", 1);

	// int atualizarUsuarioId(long long int id, char* nome, char* login, char* senha, char* email, int habilitado)

	// atualizarUsuarioId(6, "Pedro", "pedro", "pedro", "pe@dro", 1);


	//apagarTurmaTrabalho(1,2);

	//printf("%lld\n", proxIdUsuario);

	/*Usuario* usu = autenticaUsuario("ela2", "ela2");

	if (usu)
		imprimirUsuario(usu);
	else
		printf("login/senha inválidos\n");
*/
	//papeisUsuario(3, NULL, NULL, NULL);

	//cadastrarInstituicao("003", "Universidade2", "obs", NULL);
	//cadastrarCurso("003", "CursoB", "obs", NULL);
	//cadastrarDisciplina("ckxxx", "programação", 1, "obs", NULL);
	//cadastrarUsuario("Zézin", "zezin", "123456", "ze@zin", 1, NULL);
	//cadastrarTurma(1, 1, "t01", "Turma boa", "2023", "1", "obs", NULL);

	//Usuario* usu;
	//autenticaUsuario("franc", "minhasenha", &usu);

	//imprimirUsuario(usu);





/*


	char* caminhoBanco = caminho_banco;

	sqlite3* cbd;		// conexão com o banco

	// Abrir conexão

	int ret = sqlite3_open(caminhoBanco, &cbd);		// código de retorno

	if (ret != SQLITE_OK) {		// erro ao tentar abrir conexão
		fprintf(stderr, "Não foi possível abrir a conexão com banco (sqlite3 err): %s\n", sqlite3_errmsg(cbd));
		sqlite3_close(cbd);
		return(1);
	}

	// Ativar restrições de integridade

	// restrições de chava estrangeira

	char* pragmafk = "PRAGMA FOREIGN_KEYS=ON;";

	sqlite3_stmt* com = NULL;

	ret = sqlite3_prepare_v2(cbd, pragmafk, -1, &com, 0);
	if(ret != SQLITE_OK) {		// erro ao preparar consulta
		fprintf(stderr, "Não foi possível preparar consulta (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);		// checar se isso é realmente necessário, caso a preparação falhe
		sqlite3_close(cbd);
		return(1);
	}

	ret = sqlite3_step(com);

	if (ret == SQLITE_DONE) {		// consulta executada com sucesso
		sqlite3_finalize(com);
		//sqlite3_close(cbd);

		//return 0;
	}
	else {		// erro durante a execução da consulta
		fprintf(stderr, "Erro durante execução da consulta (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return (1);
	}


	// Preparar consulta

	//char* consulta = "delete from Instituicao where idInstituicao=6";
	char* consulta = "update Instituicao set idInstituicao = 7 where idInstituicao=6";

	com = NULL;

	ret = sqlite3_prepare_v2(cbd, consulta, -1, &com, 0);
	if(ret != SQLITE_OK) {		// erro ao preparar consulta
		fprintf(stderr, "Não foi possível preparar consulta (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);		// checar se isso é realmente necessário, caso a preparação falhe
		sqlite3_close(cbd);
		return(1);
	}


	// inserir valores

	ret = sqlite3_step(com);

	if (ret == SQLITE_DONE) {		// consulta executada com sucesso
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return 0;
	}
	else {		// erro durante a execução da consulta
		fprintf(stderr, "Erro durante execução da consulta (sqlite3 err: %d) AQUI: %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return (1);
	}


	*/


	//bdApagarInstituicaoId(6);

	long long int idCurso=0;

	int ret = bdCadastrarCurso("22", "Curso A", "6", "", &idCurso);

	printf("errc: %d\n", ret);



}
