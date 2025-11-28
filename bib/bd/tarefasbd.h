#ifndef TAREFASDB_INCLUIDO
#define TAREFASDB_INCLUIDO


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>



//char* caminhonome_banco = "/usr/lib/cgi-bin/tarefas/tarefas.db";
//char* caminhonome_banco = "/var/persist/tarefas/tarefas.db";
//char* caminho_banco = "/var/persist/tarefas2dev/tarefas.bd";
//char* caminho_banco = "/var/persist/tarefas2dev/dados/tarefas.bd";
//char* caminho_banco = "/usr/lib/cgi-bin/tarefas2dev/dados/tarefas.bd";
char* caminho_banco = "";
//char* caminho_banco = "/home/teste/tarefas.bd";


/*
 * Rotinas de anexação em vetor
 *
 */

int anexarLongLongInt(long long int val, long long int** vlli, int tam);

int anexarInt(int val, int** vi, int tam);

int anexarText(const char* val, char*** vtxt, int tam);






/*
 * Rotinas gerais de execução de consulta
 * - - - - - - - - - - - - - - - - - - - -
 */

// Execução de consulta de Inserção, Atualização ou Remoção
int bdExecConsIAR(char* caminhoBanco, char* consulta);

// Execução de consulta de Seleção
int bdPrepConsSel(char* caminhoBanco, char* consulta, sqlite3** cbd, sqlite3_stmt** com);

// Seleção padrão
int bdExecSelecao(char* caminhoBanco, char* consulta, void*** resultado, char*** nomesCols, int** tiposCols, int* numcols, int* numlins);

// Imprimir Seleção
void bdImprimirSelecao(void** resultado, char** nomesCols, int* tiposCols, int numcols, int numlins);

// Liberar memória alocada na seleção
//int liberarResultado(void** resultado, char** nomesCols, int* tiposCols, int numcols, int numlins);





/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Implementações
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*
 * Rotinas de anexação em vetor
 * - - - - - - - - - - - - - - -
 */

int anexarLongLongInt(long long int val, long long int** vlli, int tam) {

	*vlli = (long long int *) realloc(*vlli, (tam + 1) * sizeof(long long int));

	(*vlli)[tam] = val;

	return 0;

}

int anexarInt(int val, int** vi, int tam) {

	*vi = (int *) realloc(*vi, (tam + 1) * sizeof(long long int));

	(*vi)[tam] = val;

	return 0;

}

int anexarText(const char* val, char*** vtxt, int tam) {

	*vtxt = (char **) realloc(*vtxt, (tam + 1) * sizeof(char *));

	if (val) {
		int tamtxt = strlen(val);
		(*vtxt)[tam] = (char *) malloc(tam * sizeof(char));
		strcpy((*vtxt)[tam], val);
	}
	else
		(*vtxt)[tam] = NULL;

	return 0;
}




/*
 * Rotinas gerais de execução de consulta
 * - - - - - - - - - - - - - - - - - - - -
 */

// Execução de consulta de Inserção, Atualização ou Remoção
int bdExecConsIAR(char* caminhoBanco, char* consulta) {

	sqlite3* cbd;		// conexão com o banco

	// Abrir conexão

	int ret = sqlite3_open(caminhoBanco, &cbd);		// código de retorno

	if (ret != SQLITE_OK) {		// erro ao tentar abrir conexão
		fprintf(stderr, "Não foi possível abrir a conexão com banco (sqlite3 err): %s\n", sqlite3_errmsg(cbd));
		sqlite3_close(cbd);
		return(1);
	}


	// Ativar restrições de chave estrangeira

	sqlite3_stmt* com = NULL;

	char* pragmafk = "PRAGMA FOREIGN_KEYS=ON;";

	ret = sqlite3_prepare_v2(cbd, pragmafk, -1, &com, 0);
	if(ret != SQLITE_OK) {		// erro ao preparar consulta
		fprintf(stderr, "Não foi possível preparar consulta (ativação de chave estrangeira) (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);		// checar se isso é realmente necessário, caso a preparação falhe
		sqlite3_close(cbd);
		return(1);
	}

	ret = sqlite3_step(com);

	if (ret == SQLITE_DONE) {		// consulta executada com sucesso
		sqlite3_finalize(com);
	}
	else {		// erro durante a execução da consulta
		fprintf(stderr, "Erro durante execução da consulta (ativação de chave estrangeira) (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return (1);
	}


	// Preparar consulta

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
		fprintf(stderr, "Erro durante execução da consulta (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(cbd));
		sqlite3_finalize(com);
		sqlite3_close(cbd);

		return (1);
	}
}


int bdPrepConsSel(char* caminhoBanco, char* consulta, sqlite3** cbd, sqlite3_stmt** com) {

	// Abrir conexão

	int ret = sqlite3_open(caminhoBanco, cbd);		// código de retorno

	if (ret != SQLITE_OK) {		// erro ao tentar abrir conexão
		fprintf(stderr, "Não foi possível abrir a conexão com banco (sqlite3 err): %s\n", sqlite3_errmsg(*cbd));
		sqlite3_close(*cbd);
		return(1);
	}

	// Preparar comando

	ret = sqlite3_prepare_v2(*cbd, consulta, -1, com, 0);
	if(ret != SQLITE_OK) {		// erro ao preparar consulta
		fprintf(stderr, "Não foi possível preparar consulta (sqlite3 err: %d): %s\n", ret, sqlite3_errmsg(*cbd));
		sqlite3_finalize(*com);		// checar se isso é realmente necessário, caso a preparação falhe
		sqlite3_close(*cbd);
		return(1);
	}

	return 0;
}



int bdExecSelecao(char* caminhoBanco, char* consulta, void*** resultado, char*** nomesCols, int** tiposCols, int* numcols, int* numlins) {


	/*
	 * Retorna uma tabela (resultado de consulta) onde as posições são ponteiros para os valores correspondentes.
	 *
	 * Cada posição é um ponteiro (eg., int *).
	 *
	 * Uma coluna é, portanto, um ponteiro de ponteiros (void **).
	 *
	 * A tabela será, portanto, uma lista de ponteiros de ponteiros, ou seja, ponteiro de ponteiro de ponteiro (void ***).
	 *
	 * A variável resultado é um ponteiro para a posição onde será escrito o retorno (passagem por referência).
	 *
	 * A chamada à função execSelecao, deve ser feita da seguinte forma:
	 *
	 * 		void** res;
	 * 		execSelecao(..., &res, ...);
	 *
	 * Após o retorno da função, as colunas devem ser acessadas da seguinte forma:
	 *
	 * 		int i;
	 * 		res[i];
	 *
	 * Deve ser feita a conversão explícita de acordo com o tipo da coluna da tabela.
	 * Por exemplo, no caso da coluna i ser do tipo inteiro, deve ser feito da seguinte forma:
	 *
	 * 		long long int** col = (long long int **) (res[i]);
	 *
	 * O valor da j-ésima linha dessa coluna deve ser acessado da seguinte forma:
	 *
	 * 		long long int val = *(col[j]);
	 *
	 * Caso haja apenas uma linha, ou caso se queira acessar a linha 0, podemos fazer assim:
	 *
	 * 		long long int val = **col;
	 *
	 * ou
	 *
	 * 		long long int val = **((long long int **) (res[i]));
	 *
	 */


	sqlite3* cbd = NULL;
	sqlite3_stmt* com = NULL;

	// preparar consulta

	int ret = bdPrepConsSel(caminhoBanco, consulta, &cbd, &com);

	if (ret) {		// erro na preparação da consulta
		return 1;
	}

	// obter número de colunas retornadas

	*numcols = sqlite3_column_count(com);

	// obter nomes das colunas

	*nomesCols = (char **) malloc(*numcols * (sizeof(char *)));
	*tiposCols = (int *) malloc(*numcols * (sizeof(int)));


	for (int i = 0; i < *numcols; i++) {

		// obter nome
		size_t tamstr = strlen(sqlite3_column_name(com, i));

		(*nomesCols)[i] = (char *) malloc( (tamstr + 1) * sizeof(char));
		strcpy((*nomesCols)[i], sqlite3_column_name(com, i));

	}


	// obter valores

	// alocar vetor de ponteiros (para vetores)

	*resultado = (void **) malloc (*numcols * (sizeof(void *)));

	// inicializar vetores de resultados

	for (int i = 0; i < *numcols; i++) {
		(*resultado)[i] = NULL;
	}

	// obter tipos das colunas

	// (os tipos são associados aos valores,
	//  então dever ser acessados após cada step,
	//  como eu não pretendo fazer consultas que
	//  retornam colunas com múltiplos tipo,
	//  vou pegar o tipo da coluna logo após o
	//  primeiro step.)

	ret = sqlite3_step(com);

	for (int i = 0; i < *numcols; i++) {

		// obter tipo
		(*tiposCols)[i] = sqlite3_column_type(com, i);
	}

	// carregar vetores de resultados

	*numlins = 0;

	while ( ret == SQLITE_ROW ) {

		// percorrer colunas para resgatar valores

		for (int i = 0; i < *numcols; i++) {

			//printf("%d\n", sqlite3_column_type(com, i));

			//switch (sqlite3_column_type(com, i)) {
			switch ((*tiposCols)[i]) {

				case SQLITE_INTEGER:

					if (sqlite3_column_type(com, i) == SQLITE_NULL) {
						long long int** vlli = (long long int **) (*resultado)[i];
						vlli = (long long int **) realloc(vlli, (*numlins + 1) * sizeof(long long int *));
						vlli[*numlins] = NULL;
						(*resultado)[i] = vlli;
					}
					else {
						long long int** vlli = (long long int **) (*resultado)[i];
						vlli = (long long int **) realloc(vlli, (*numlins + 1) * sizeof(long long int *));
						vlli[*numlins] = (long long int *) malloc(sizeof(long long int));
						*(vlli[*numlins]) = sqlite3_column_int64(com, i);
						(*resultado)[i] = vlli;
					}

					break;

				case SQLITE_FLOAT:

					if (sqlite3_column_type(com, i) == SQLITE_NULL) {
						double** vd = (double **) (*resultado)[i];
						vd = (double **) realloc(vd, (*numlins + 1) * sizeof(double *));
						vd[*numlins] = NULL;
						(*resultado)[i] = vd;
					}
					else {
						double** vd = (double **) (*resultado)[i];
						vd = (double **) realloc(vd, (*numlins + 1) * sizeof(double *));
						vd[*numlins] = (double *) malloc(sizeof(double));
						*(vd[*numlins]) = sqlite3_column_double(com, i);
						(*resultado)[i] = vd;
					}

					break;

				case SQLITE_BLOB:

					if (sqlite3_column_type(com, i) == SQLITE_NULL) {
						unsigned char** vb = (unsigned char **) (*resultado)[i];
						vb = (unsigned char **) realloc(vb, (*numlins + 1) * sizeof(unsigned char *));
						vb[*numlins] = NULL;
						(*resultado)[i] = vb;
					}
					else {
						unsigned char** vb = (unsigned char **) (*resultado)[i];
						vb = (unsigned char **) realloc(vb, (*numlins + 1) * sizeof(unsigned char *));
						size_t tamblob = sqlite3_column_bytes(com, i);
						vb[*numlins] = (unsigned char *) malloc(tamblob * sizeof(unsigned char));
						memcpy(vb[*numlins], sqlite3_column_blob(com, i), tamblob);
						(*resultado)[i] = vb;
					}

					break;

				case SQLITE3_TEXT:

					if (sqlite3_column_type(com, i) == SQLITE_NULL) {
						char** vt = (char **) (*resultado)[i];
						vt = (char **) realloc(vt, (*numlins + 1) * sizeof(char *));
						vt[*numlins] = NULL;
						(*resultado)[i] = vt;
					}
					else {
						char** vt = (char **) (*resultado)[i];
						vt = (char **) realloc(vt, (*numlins + 1) * sizeof(char *));
						size_t tamtext = sqlite3_column_bytes(com, i);
						vt[*numlins] = (char *) malloc((tamtext + 1) * sizeof(char));
						memcpy(vt[*numlins], sqlite3_column_text(com, i), tamtext + 1);
						(*resultado)[i] = vt;
					}

					break;;

				// case SQLITE_NULL:		// não estamos tratando
			}
		}

		(*numlins)++;
		ret = sqlite3_step(com);
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


void bdImprimirSelecao(void** resultado, char** nomesCols, int* tiposCols, int numcols, int numlins) {

	// imprimir nomes de colunas

	for (int j = 0; j < numcols; j++) {
		printf("%s, ", nomesCols[j]);
	}
	printf("\n\n");

	for (int i = 0; i < numlins; i++) {

		for (int j = 0; j < numcols; j++) {

			switch (tiposCols[j]) {

				case SQLITE_INTEGER:
					long long int** vlli = (long long int **) resultado[j];		// obter coluna j
					if (vlli[i])
						printf("%lld, ", *(vlli[i]));									// obter linha i
					else
						printf("NULL, ");
					break;

				case SQLITE_FLOAT:
					double** vd = (double **) resultado[j];						// obter coluna j
					if (vd[i])
						printf("%f, ", *(vd[i]));										// obter linha i
					else
						printf("NULL, ");
					break;

				case SQLITE_BLOB:
					printf("BLOB, ");		// não imprimimos BLOB
					break;

				case SQLITE3_TEXT:
					char** vtext = (char **) resultado[j];						// obter coluna j
					if (vtext[i])
						printf("%s, ", vtext[i]);										// obter linha i
					else
						printf("NULL");
					break;
			}
		}

		printf("\n");
	}

}



/*
 * Módulos de consultas
 *
 */


// Tabelas

#include "contadores.h"

#include "usuario.h"

//#include "adm.h"

#include "perfilrespondedor.h"

#include "curso.h"

#include "instituicao.h"

#include "turma.h"

#include "disciplina.h"

#include "trabalho.h"

#include "sessao.h"

#include "sessaoencerrada.h"

#include "professor_turma.h"

#include "perfilrespondedor_turma.h"

#include "tarefa.h"

#include "itemtarefa.h"

#include "dadosessao.h"




#include "estrutsinterfacebd.h"




#include "autentica.h"

#include "busca.h"



/* TODO
 *
 * - incluir o tamanho do bloco de dados para o tipo BLOB.
 *
 * - implementar as liberações de memória
 *
 * - considerar fazer o mapa de tipos para todos os valores...
 *
 */


#endif
