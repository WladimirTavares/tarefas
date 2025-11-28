#ifndef LUGAR_H
#define LUGAR_H



#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "str/bibstring2.h"

#include "diretorio.h"

#include "notifica.h"




/*
 * Os diretórios de tarefas e dos diretórios de trabalhos
 * serão armazenados em uma árvore de diretórios com dois níveis,
 * o primeiro nível terá no máximo 70000 diretórios, cada um desses
 * terá no máximo 70000 diretórios de cada tipo de elemento (tarefa ou trabalho).
 *
 * Se esses limites forem excedidos, não será fornecido diretório, significando
 * que o limite máximo foi atingido.
 *
 * O limite se refere ao número de id da tarefa ou trabalho.
 *
 * Essas condições podem ser modificadas posteriormente. A única coisa
 * que o usuário precisa saber é que os diretórios são obtidos apenas
 * pelas funções desta biblioteca, e que pode não ser fornecido diretório
 * indicando que o diretório não deve ser criado porque alguma condição
 * foi ferida ou limite foi atingido.
 *
 * Assim, caso a forma de atribuição de diretórios seja modificada,
 * basta reimplementar as funções e mapear os existentes para os
 * novos diretórios.
 *
 *
 * - Diretório de tarefa
 *
 * dirDadosTarefas/<dirN1>/<idTarefa>
 *
 * - Diretório de respostas de trabalho
 *
 * dirRespostasTrabalhos/<dirN1>/<idTrabalho>
 *
 * - Diretório de respostas de item de tarefa
 *
 * dirRespostasTrabalhos/<dirN1>/<idTrabalho>/<idItemTarefa>
 *
 *
 * OBS.: Evitar executar comandos do tipo rm -r xxxxxx/*.
 *
 */



int MAX_NUM_SUBDIR_N1 = 70000;
int MAX_NUM_SUBDIR_N2 = 70000;



char* dirTarefas = "/usr/lib/cgi-bin/tarefas2";		// ok!

char* dirHtml = "/usr/lib/cgi-bin/tarefas2/html";



char* urlTarefas = "http://127.0.0.1/tarefas2dev/tarefas.cgi";

char* urlTarefasDwl = "http://127.0.0.1/tarefasdwl";

char* urlTarefasDwlTarefas = "http://127.0.0.1/tarefasdwl/tarefas";

//char* urlTarefasDwldr = "http://127.0.0.1/tarefas2dev/dwldr/dwldr.cgi";


/*
//char* urlTarefas = "http://200.19.179.27:8091/tarefas2dev/tarefas.cgi";
char* urlTarefas = "http://tarefas.dc.ufc.br";

//char* urlTarefasDwl = "http://200.19.179.27:8091/tarefasdevdwl";
char* urlTarefasDwl = "http://tarefas.dc.ufc.br/tarefasdwl";

char* urlTarefasDwlTarefas = "http://tarefas.dc.ufc.br/tarefasdwl/tarefas";

//char* urlTarefasDwldr = "http://200.19.179.27:8091/tarefas2/dwldr/dwldr.cgi";
*/



char* caminhoTarefasBD = "/usr/lib/cgi-bin/tarefas2/dados/tarefas.bd";



char* dirDados = "/usr/lib/cgi-bin/tarefas2/dados";

char* dirDadosTarefas = "/usr/lib/cgi-bin/tarefas2/dados/tarefas";

char* dirDadosTrabalhos = "/usr/lib/cgi-bin/tarefas2/dados/trabalhos";



char* dirDownloads = "/usr/lib/cgi-bin/tarefas2/downloads";

char* dirDownloadsTarefas = "/usr/lib/cgi-bin/tarefas2/downloads/tarefas";

char* dirDownloadsTrabalhos = "/usr/lib/cgi-bin/tarefas2/downloads/trabalhos";




/*		Assinatura de métodos		*/




// Cria string de diretório em dois níveis.
// O primeiro nível é o quociente da divisão por MAX_NUM_SUBDIR_N2
//   e não pode ser maior que MAX_NUM_SUBDIR_N1.
// O segundo nível éo próprio id.
char* dirN1N2(long long int id);

// String de diretório do primeiro nível
char* dirN1(long long int id);



/* * * * * * * * * * * * * * * * * * *
*
*	Diretórios da tarefa
*
* * * * * * * * * * * * * * * * * * * */



char* dirDadosTarefaN1(long long int idTarefa);
char* dirDadosTarefa(long long int idTarefa);
char* dirDadosTarefaStr(char* idTarefa);

char* dirDownloadsTarefaN1(long long int idTarefa);
char* dirDownloadsTarefa(long long int idTarefa);
char* dirDownloadsTarefaStr(char* idTarefa);

// Retorna erro caso o diretório já exista
int dirCriarDirDadosTarefa(long long int idTarefa);

// Não apaga o diretório de nível 1
int dirEsvaziarDirDadosTarefa(long long int idTarefa);
int dirRemoverDirDadosTarefa(long long int idTarefa);

// Retorna erro caso o diretório já exista
int dirCriarDirDownloadsTarefa(long long int idTarefa);

// Não apaga o diretório de nível 1
int dirEsvaziarDirDownloadsTarefa(long long int idTarefa);
int dirRemoverDirDownloadsTarefa(long long int idTarefa);


// Cria os diretórios relativos a uma tarefa
int dirCriarDiretoriosTarefa(long long int idTarefa, RegNoti** rn);
// Remove os diretórios relativos a uma tarefa
int dirRemoverDiretoriosTarefa(long long int idTarefa, RegNoti** rn);



/* * * * * * * * * * * * * * * * * * *
*
*	Diretórios do trabalho
*
* * * * * * * * * * * * * * * * * * * */



char* dirDadosTrabalhoN1(long long int idTrabalho);
char* dirDadosTrabalho(long long int idTrabalho);
char* dirDadosTrabalhoStr(char* idTrabalho);

char* dirDownloadsTrabalhoN1(long long int idTrabalho);
char* dirDownloadsTrabalho(long long int idTrabalho);
char* dirDownloadsTrabalhoStr(char* idTrabalho);

int dirCriarDirDadosTrabalho(long long int idTrabalho);
int dirRemoverDirDadosTrabalho(long long int idTrabalho);

int dirCriarDirDownloadsTrabalho(long long int idTrabalho);
int dirRemoverDirDownloadsTrabalho(long long int idTrabalho);


// Cria os diretórios relativos a um trabalho
int dirCriarDiretoriosTrabalho(long long int idTrabalho, RegNoti** rn);
// Remove os diretórios relativos a um trabalho
int dirRemoverDiretoriosTrabalho(long long int idTrabalho, RegNoti** rn);



/* * * * * * * * * * * * * * * * * * *
*
*	Diretórios do item de tarefa
*
* * * * * * * * * * * * * * * * * * * */



char* dirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa);
char* dirDadosItemTarefaStr(char* idTrabalho, char* idItemTarefa);

char* dirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa);
char* dirDownloadsItemTarefaStr(char* idTrabalho, char* idItemTarefa);

int dirCriarDirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa);
int dirRemoverDirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa);

int dirCriarDirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa);
int dirRemoverDirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa);


// Cria os diretórios relativos a um trabalho
int dirCriarDiretoriosItemTarefa(long long int idTrabalho, long long int idItemTarefa, RegNoti** rn);
// Remove os diretórios relativos a um trabalho
int dirRemoverDiretoriosItemTarefa(long long int idTrabalho, long long int idItemTarefa, RegNoti** rn);



int dirListaDirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa, Multilinhas** ml);
int dirListaDirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa, Multilinhas** ml);



/* * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*	Diretórios do perfil relativos a um item de tarefa
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * */



char* dirDadosPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor);
char* dirDadosPerfilItemTarefaStr(char* idTrabalho, char* idItemTarefa, char* idPerfilRespondedor);

char* dirDownloadsPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor);
char* dirDownloadsPerfilItemTarefaStr(char* idTrabalho, char* idItemTarefa, char* idPerfilRespondedor);

int dirCriarDirDadosPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor);
int dirRemoverDirDadosPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor);




/* * * * * * * * * * * * * * * * * * *
*
*	Dados da tarefa
*
* * * * * * * * * * * * * * * * * * * */



char* urlEnunciadoPNG(long long int idTarefa);

char* caminhoEnunciadoPNG(long long int idTarefa);

char* caminhoEnunciadoPDF(long long int idTarefa);

char* caminhoDadosResposta(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor);

char* caminhoDownloadsResposta(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor);



/* * * * * * * * * * * * * * * * * * * * *
 *
 *	Codigo C, Avaliação Estática
 *  
 * * * * * * * * * * * * * * * * * * * * */


char* dirAvaliacaoTarefa(long long int idTarefa);
char* dirCaminhoNumCts(long long int idTarefa);

char* dirCasoTesteTarefa(long long int idTarefa, int numct);

int dirCriarDirAvalicaoTarefa(long long int idTarefa, int numcts);

int dirEsvaziarDirAvaliacaoTarefa(long long int idTarefa);
int dirRemoverDirAvaliacaoTarefa(long long int idTarefa);



char* dirAreaDeTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);
int existeAreaDeTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);

char* dirCaminhoRespostaPrepITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);

char* dirCasoTesteITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor, int numct);

int dirCriarDirAreaTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor, int numcts);

int dirEsvaziarAreaTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);
int dirRemoverAreaTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);

int dirEsvaziarDirPerfilIT(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);
int dirRemoverDirPerfilIT(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);



char* dirCaminhoModelosC();
char* dirCaminhoModeloCGecat();
char* dirCaminhoModeloCCab();
char* dirCaminhoModeloCExecCt();
char* dirCaminhoModeloCExecAval();
char* dirCaminhoModeloCExecFeedback();
char* dirCaminhoModeloCCarregarCt();
char* dirCaminhoModeloCSalvarSaida();

char* dirCaminhoGcat(long long int idTarefa);



/*		Implementações		*/






char* dirN1N2(long long int id) {

	// calcular diretório do primeiro nível

	long long int n1 = id/MAX_NUM_SUBDIR_N2;

	if (n1 < MAX_NUM_SUBDIR_N1) {

		// dentro do limite

		char dN1[21] = "";
		char dN2[21] = "";

		sprintf(dN1, "%lld", n1);
		sprintf(dN2, "%lld", id);

		if (strlen(dN1) > 0 && strlen(dN2) > 0) {

			return concatstr2(dN1, concatstr2("/", dN2));

		}
	}

	return NULL;

}


char* dirN1(long long int id) {

	// calcular diretório do primeiro nível

	long long int n1 = id/MAX_NUM_SUBDIR_N2;

	if (n1 < MAX_NUM_SUBDIR_N1) {

		// dentro do limite

		char dN1[21] = "";

		sprintf(dN1, "%lld", n1);

		if (strlen(dN1) > 0) {

				return copiastr(dN1);
		}

	}

	return NULL;
}



/* * * * * * * * * * * * * * * * * * *
*
*	Diretórios da tarefa
*
* * * * * * * * * * * * * * * * * * * */



char* dirDadosTarefa(long long int idTarefa) {

	// calcular diretório do primeiro nível

	char* dirn1n2 = dirN1N2(idTarefa);

	if (dirn1n2) {

		return concatstr2(dirDadosTarefas, concatstr2("/", dirn1n2));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}

char* dirDadosTarefaN1(long long int idTarefa) {

	// calcular diretório do primeiro nível

	char* dirn1 = dirN1(idTarefa);

	if (dirn1) {

		return concatstr2(dirDadosTarefas, concatstr2("/", dirn1));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}


char* dirDadosTarefaStr(char* idStr) {

	long long int idTarefa = 0;

	if (sscanf(idStr, "%lld", &idTarefa) == 1) {

		return dirDadosTarefa(idTarefa);

	}
	else {
		return NULL;
	}

}


char* dirDownloadsTarefa(long long int idTarefa) {

	// calcular diretório do primeiro nível

	char* dirn1n2 = dirN1N2(idTarefa);

	if (dirn1n2) {

		return concatstr2(dirDownloadsTarefas, concatstr2("/", dirn1n2));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}

char* dirDownloadsTarefaN1(long long int idTarefa) {

	// calcular diretório do primeiro nível

	char* dirn1 = dirN1(idTarefa);

	if (dirn1) {

		return concatstr2(dirDownloadsTarefas, concatstr2("/", dirn1));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}


char* dirDownloadsTarefaStr(char* idStr) {

	long long int idTarefa = 0;

	if (sscanf(idStr, "%lld", &idTarefa) == 1) {

		return dirDownloadsTarefa(idTarefa);

	}
	else {
		return NULL;
	}

}



int dirCriarDirDadosTarefa(long long int idTarefa) {

	int ret = 0;

	// checar se diretório do primeiro nível existe

	char* dirn1 = dirDadosTarefaN1(idTarefa);

	if (dirn1) {

		if (access(dirn1, F_OK)) {		// diretório não existe

			// criar diretório de nível 1

			ret = mkdir(dirn1, 0755);

			//printf("%s\n", dirn1);

			if (ret) {
				// não foi possível criar o diretório de nível 1

				return 1;
			}
		}

		// criar diretório de nível 2

		char* dirn1n2 = dirDadosTarefa(idTarefa);

		// checar se diretório de nível 2 já existe

		if (dirn1n2) {

			if (access(dirn1n2, F_OK)) {		// diretório não existe

				//criar diretório

				ret = mkdir(dirn1n2, 0755);

				if (ret) {		// não foi possível criar diretório

					return 2;

				}

				// diretório criado com sucesso

				return 0;

			}

			// diretório de nível 2 já existe

			return 3;

		}

		// problema na criação do caminho do diretório de segundo nível

		return 4;

	}

	// problema na criação do caminho do diretório de primeiro nível

	return 5;
}


int dirEsvaziarDirDadosTarefa(long long int idTarefa) {

	// obter diretório da tarefa

	char* dirtar = dirDadosTarefa(idTarefa);

	return dirEsvaziarDir(dirtar);
}


int dirRemoverDirDadosTarefa(long long int idTarefa) {

	// obter diretório da tarefa

	char* dirtar = dirDadosTarefa(idTarefa);

	/*
	// remover enunciado

	char* enunc = concatstr2(dirtar, "/enunciado.pdf");

	if (enunc) {



		int ret = remove(enunc);

		if (ret) {

			// erro ao tentar remover enunciado;

			return 1;
		}
		*/

		// remover diretório da tarefa

		int ret = rmdir(dirtar);

		if (ret) {

			// erro ao tentar remover diretório da tarefa

			return 2;
		}

		return 0;
	//}


}


int dirCriarDirDownloadsTarefa(long long int idTarefa) {

	int ret = 0;

	// checar se diretório do primeiro nível existe

	char* dirn1 = dirDownloadsTarefaN1(idTarefa);

	if (dirn1) {

		if (access(dirn1, F_OK)) {		// diretório não existe

			// criar diretório de nível 1

			ret = mkdir(dirn1, 0755);

			//printf("%s\n", dirn1);

			if (ret) {
				// não foi possível criar o diretório de nível 1

				return 1;
			}
		}

		// criar diretório de nível 2

		char* dirn1n2 = dirDownloadsTarefa(idTarefa);

		// checar se diretório de nível 2 já existe

		if (dirn1n2) {

			if (access(dirn1n2, F_OK)) {		// diretório não existe

				//criar diretório

				ret = mkdir(dirn1n2, 0755);

				if (ret) {		// não foi possível criar diretório

					return 2;

				}

				// diretório criado com sucesso

				return 0;

			}

			// diretório de nível 2 já existe

			return 3;

		}

		// problema na criação do caminho do diretório de segundo nível

		return 4;

	}

	// problema na criação do caminho do diretório de primeiro nível

	return 5;

}


int dirEsvaziarDirDownloadsTarefa(long long int idTarefa) {

	// obter diretório da tarefa

	char* dirtar = dirDownloadsTarefa(idTarefa);

	return dirEsvaziarDir(dirtar);
}


int dirRemoverDirDownloadsTarefa(long long int idTarefa) {

	// obter diretório da tarefa

	char* dirtar = dirDownloadsTarefa(idTarefa);

		// remover diretório da tarefa

		int ret = rmdir(dirtar);

		if (ret) {

			// erro ao tentar remover diretório da tarefa

			return 2;
		}

		return 0;


}


int dirCriarDiretoriosTarefa(long long int idTarefa, RegNoti** rn) {

	/* A tarefa do tipo submissao simples possui dois diretórios:
     *
     * dirDadosTarefa/tarefas/N1/idTarefa
     * dirDownloadsTarefa/tarefas/N1/idTarefa
     *
     */

	int ret = dirCriarDirDadosTarefa(idTarefa);
    if (ret) {

        *rn = criarRegNoti(2, "Erro ao tentar criar diretório de dados da tarefa.");
        return 1;
    }

    ret = dirCriarDirDownloadsTarefa(idTarefa);
    if (ret) {

        // remover diretório de dados
        dirRemoverDirDadosTarefa(idTarefa);

        *rn = criarRegNoti(3, "Erro ao tentar criar diretório de downloads da tarefa.");
        return 2;
    }

	*rn = criarRegNoti(0, "Diretórios da tarefa criados com sucesso.");
	return 0;
	
}


int dirRemoverDiretoriosTarefa(long long int idTarefa, RegNoti** rn) {

	// retorna 1 em caso de falha na remoção do diretório de dados
	// retorna 2 em caso de falha na remoção do diretório de downloads
	// retorna 3 em caso de falha nos dois
	// retorna 0 em caso de sucesso

	int ret = 0;

	// remover diretório de dados
    int ret1 = dirRemoverDirDadosTarefa(idTarefa);

	// remover diretório de downloads
	int ret2 = dirRemoverDirDownloadsTarefa(idTarefa);

	char* msg = "";
	
	if (ret1) {
		ret++;
		msg = "Erro ao tentar apagar diretório de dados da tarefa.";
	}
		
	if (ret2) {
		ret += 2;
		msg = concatstr2(msg, "Erro ao tentar a pagar diretório de downloads da tarefa.");
	}
		
	return ret;
}


/* * * * * * * * * * * * * * * * * * *
*
*	Diretórios do trabalho
*
* * * * * * * * * * * * * * * * * * * */



char* dirDadosTrabalho(long long int idTrabalho) {

	// calcular diretório do primeiro nível

	char* dirn1n2 = dirN1N2(idTrabalho);

	if (dirn1n2) {

		return concatstr2(dirDadosTrabalhos, concatstr2("/", dirn1n2));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}


char* dirDadosTrabalhoN1(long long int idTrabalho) {

	// calcular diretório do primeiro nível

	char* dirn1 = dirN1(idTrabalho);

	if (dirn1) {

		return concatstr2(dirDadosTrabalhos, concatstr2("/", dirn1));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}


char* dirDadosTrabalhoStr(char* idStr) {

	long long int idTrabalho = 0;

	if (sscanf(idStr, "%lld", &idTrabalho) == 1) {

		return dirDadosTrabalho(idTrabalho);

	}
	else {
		return NULL;
	}

}


char* dirDownloadsTrabalho(long long int idTrabalho) {

	// calcular diretório do primeiro nível

	char* dirn1n2 = dirN1N2(idTrabalho);

	if (dirn1n2) {

		return concatstr2(dirDownloadsTrabalhos, concatstr2("/", dirn1n2));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}


char* dirDownloadsTrabalhoN1(long long int idTrabalho) {

	// calcular diretório do primeiro nível

	char* dirn1 = dirN1(idTrabalho);

	if (dirn1) {

		return concatstr2(dirDownloadsTrabalhos, concatstr2("/", dirn1));
	}
	else {

		// fora do limite, retorna nulo indicando que não pode ser criado diretório

		return NULL;
	}

}


char* dirDownloadsTrabalhoStr(char* idStr) {

	long long int idTrabalho = 0;

	if (sscanf(idStr, "%lld", &idTrabalho) == 1) {

		return dirDownloadsTrabalho(idTrabalho);

	}
	else {
		return NULL;
	}

}


int dirCriarDirDadosTrabalho(long long int idTrabalho) {

	int ret = 0;

	// checar se diretório do primeiro nível existe

	char* dirn1 = dirDadosTrabalhoN1(idTrabalho);

	if (dirn1) {

		if (access(dirn1, F_OK)) {		// diretório não existe

			// criar diretório de nível 1

			ret = mkdir(dirn1, 0755);

			//printf("%s\n", dirn1);

			if (ret) {
				// não foi possível criar o diretório de nível 1

				return 1;
			}
		}

		// criar diretório de nível 2

		char* dirn1n2 = dirDadosTrabalho(idTrabalho);

		if (dirn1n2) {

			// checar se diretório de nível 2 já existe

			if (access(dirn1n2, F_OK)) {		// diretório não existe

				//criar diretório

				ret = mkdir(dirn1n2, 0755);

				if (ret) {		// não foi possível criar diretório

					return 2;

				}

				// diretório criado com sucesso

				return 0;

			}

			// diretório de nível 2 já existe

			return 3;

		}

		// problema na criação do caminho do diretório de segundo nível

		return 4;

	}

	// problema na criação do caminho do diretório de primeiro nível

	return 5;
}

int dirRemoverDirDadosTrabalho(long long int idTrabalho) {

	char* dirTrab = dirDadosTrabalho(idTrabalho);

	//printf("%s", dirTrab);

	int ret = rmdir(dirTrab);

	if (ret) {

		// erro na remoção do diretório

		return 1;
	}

	return 0;

}


int dirCriarDirDownloadsTrabalho(long long int idTrabalho) {

	int ret = 0;

	// checar se diretório do primeiro nível existe

	char* dirn1 = dirDownloadsTrabalhoN1(idTrabalho);

	if (dirn1) {

		if (access(dirn1, F_OK)) {		// diretório não existe

			// criar diretório de nível 1

			ret = mkdir(dirn1, 0755);

			//printf("%s\n", dirn1);

			if (ret) {
				// não foi possível criar o diretório de nível 1

				return 1;
			}
		}

		// criar diretório de nível 2

		char* dirn1n2 = dirDownloadsTrabalho(idTrabalho);

		if (dirn1n2) {

			// checar se diretório de nível 2 já existe

			if (access(dirn1n2, F_OK)) {		// diretório não existe

				//criar diretório

				ret = mkdir(dirn1n2, 0755);

				if (ret) {		// não foi possível criar diretório

					return 2;

				}

				// diretório criado com sucesso

				return 0;

			}

			// diretório de nível 2 já existe

			return 3;

		}

		// problema na criação do caminho do diretório de segundo nível

		return 4;

	}

	// problema na criação do caminho do diretório de primeiro nível

	return 5;
}


int dirRemoverDirDownloadsTrabalho(long long int idTrabalho) {

	char* dirTrab = dirDownloadsTrabalho(idTrabalho);

	int ret = rmdir(dirTrab);

	if (ret) {

		// erro na remoção do diretório

		return 1;
	}

	return 0;

}



// Cria os diretórios relativos a um trabalho
int dirCriarDiretoriosTrabalho(long long int idTrabalho, RegNoti** rn) {

	int ret = dirCriarDirDadosTrabalho(idTrabalho);

	if (ret) {
		*rn = criarRegNoti(1, "Erro ao criar diretório de dados do trabalho.");
		return 1;
	}

	ret = dirCriarDirDownloadsTrabalho(idTrabalho);

	if (ret) {
		dirRemoverDirDadosTrabalho(idTrabalho);
		*rn = criarRegNoti(2, "Erro ao tentar criar diretório de downloads do trabalho.");
		return 2;
	}

	*rn = criarRegNoti(0, "Diretórios do trabalho criados com sucesso.");

}

// Remove os diretórios relativos a um trabalho
int dirRemoverDiretoriosTrabalho(long long int idTrabalho, RegNoti** rn) {

	int ret = 0;

	int ret1 = dirRemoverDirDadosTrabalho(idTrabalho);
	int ret2 = dirRemoverDirDownloadsTrabalho(idTrabalho);
	char* msg = "";

	if (ret1) {
		ret++;
		msg = "Erro ao tentar remover diretório de dados do trabalho.";
	}
	if (ret2)  {
		ret += 2;
		msg = concatstr2(msg, "Erro ao tentar criar diretório de Downloads do trabalho.");
	}

	if (!ret) msg = "Diretórios do trabalho removidos com sucesso.";

	*rn = criarRegNoti(ret, msg);
	return ret;
}



/* * * * * * * * * * * * * * * * * * *
*
*	Diretórios do item de tarefa
*
* * * * * * * * * * * * * * * * * * * */



char* dirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa) {

	char* idIT = (char *) malloc(21 * sizeof(char));

	if (sprintf(idIT, "%lld", idItemTarefa) > 0) {
		return concatstr2( dirDadosTrabalho(idTrabalho), concatstr2("/", idIT ) );
	}

	return NULL;

}


char* dirDadosItemTarefaStr(char* idTrabalho, char* idItemTarefa) {

	long long int idIT = 0;
	long long int idT = 0;

	if (sscanf(idItemTarefa, "%lld", &idIT) == 1) {
		if (sscanf(idTrabalho, "%lld", &idT) == 1) {
			return dirDadosItemTarefa(idIT, idT);
		}
	}

	return NULL;
}


char* dirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa) {

	char* idIT = (char *) malloc(21 * sizeof(char));

	if (sprintf(idIT, "%lld", idItemTarefa) > 0) {
		return concatstr2( dirDownloadsTrabalho(idTrabalho), concatstr2("/", idIT ) );
	}

	return NULL;

}


char* dirDownloadsItemTarefaStr(char* idTrabalho, char* idItemTarefa) {

	long long int idIT = 0;
	long long int idT = 0;

	if (sscanf(idItemTarefa, "%lld", &idIT) == 1) {
		if (sscanf(idTrabalho, "%lld", &idT) == 1) {
			return dirDownloadsItemTarefa(idIT, idT);
		}
	}

	return NULL;
}



int dirCriarDirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa) {

	int ret = 0;

	// checar se diretório do trabalho existe

	char* dt = dirDadosTrabalho(idTrabalho);

	if (dt) {

		if (access(dt, F_OK)){		// diretório de trabalho não existe

			// criar diretório de trabalho

			ret = dirCriarDirDadosTrabalho(idTrabalho);

			if (ret) {

				// erro ao tentar criar diretório do trabalho

				return 1;
			}

		}

		// criar diretório do item de tarefa

		char* dirit = dirDadosItemTarefa(idTrabalho, idItemTarefa);

		if (dirit) {

			ret = mkdir(dirit, 0755);

			if (ret) {

				// erro ao tentar criar diretório

				return 2;
			}

			//printf("%s", dirit);

			// diretório criado com sucesso

			return 0;
		}

		// erro ao tentar criar caminho do diretório de item de tarefa

		return 3;

	}
	else {

		// erro ao tentar construir caminho do diretório do trabalho

		return 4;
	}

}


int dirRemoverDirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa) {

	// obter lista de diretórios de respostas dos perfis que enviaram respostas

	// remover arquivos de cada diretório de perfil

	// remover cada diretório de perfil

	// remover diretório de respostas do item de tarefas

	char* dirDadosIT = dirDadosItemTarefa(idTrabalho, idItemTarefa);

	if (dirDadosIT) {

		int ret = rmdir(dirDadosIT);

		return ret;

	}

}


int dirCriarDirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa) {

	int ret = 0;

	// checar se diretório do trabalho existe

	char* dt = dirDadosTrabalho(idTrabalho);

	if (dt) {

		if (access(dt, F_OK)){		// diretório de trabalho não existe

			// criar diretório de trabalho

			ret = dirCriarDirDownloadsTrabalho(idTrabalho);

			if (ret) {

				// erro ao tentar criar diretório do trabalho

				return 1;
			}

		}

		// criar diretório do item de tarefa

		char* dirit = dirDownloadsItemTarefa(idTrabalho, idItemTarefa);

		if (dirit) {

			ret = mkdir(dirit, 0755);

			if (ret) {

				// erro ao tentar criar diretório

				return 2;
			}

			//printf("%s", dirit);

			// diretório criado com sucesso

			return 0;
		}

		// erro ao tentar criar caminho do diretório de item de tarefa

		return 3;

	}
	else {

		// erro ao tentar construir caminho do diretório do trabalho

		return 4;
	}

}


int dirRemoverDirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa) {

	// obter lista de diretórios de respostas dos perfis que enviaram respostas

	// remover arquivos de cada diretório de perfil

	// remover cada diretório de perfil

	// remover diretório de respostas do item de tarefas

	char* dirDownloadsIT = dirDownloadsItemTarefa(idTrabalho, idItemTarefa);

	if (dirDownloadsIT) {

		int ret = rmdir(dirDownloadsIT);

		return ret;

	}

}



// Cria os diretórios relativos a um trabalho
int dirCriarDiretoriosItemTarefa(long long int idTrabalho, long long int idItemTarefa, RegNoti** rn) {

	int ret = dirCriarDirDadosItemTarefa(idTrabalho, idItemTarefa);
	if (ret) {
		*rn = criarRegNoti(1, "Erro ao tentar criar diretório de dados do item de tarefa.");
		return 1;
	}

	ret = dirCriarDirDownloadsItemTarefa(idTrabalho, idItemTarefa);
	if (ret) {
		*rn = criarRegNoti(1, "Erro ao criar diretório de downloads do item de tarefa.");
		return 2;
	}

	*rn = criarRegNoti(0, "Diretórios criados com sucesso.");
	return 0;
}


// Remove os diretórios relativos a um trabalho
int dirRemoverDiretoriosItemTarefa(long long int idTrabalho, long long int idItemTarefa, RegNoti** rn) {



}



int dirListaDirDadosItemTarefa(long long int idTrabalho, long long int idItemTarefa, Multilinhas** ml) {

	// obter diretório de respostas do item de tarefa

	char* dirIT = dirDadosItemTarefa(idTrabalho, idItemTarefa);

	int ret = 0;

	if (dirIT) {

		if (access(dirIT, F_OK)){

			// diretório não existe

			return 1;
		}
		else {

			ret = dirSubDirs(dirIT, ml);

			if (ret) {

				// erro ao tentar resgatar subdiretórios

				return 2;
			}

			return 0;
		}
	}
	else {

		// erro ao montar caminho

		return 3;
	}
}


int dirListaDirDownloadsItemTarefa(long long int idTrabalho, long long int idItemTarefa, Multilinhas** ml) {

	// obter diretório de respostas do item de tarefa

	char* dirIT = dirDownloadsItemTarefa(idTrabalho, idItemTarefa);

	int ret = 0;

	if (dirIT) {

		if (access(dirIT, F_OK)){

			// diretório não existe

			return 1;
		}
		else {

			ret = dirSubDirs(dirIT, ml);

			if (ret) {

				// erro ao tentar resgatar subdiretórios

				return 2;
			}

			return 0;
		}
	}
	else {

		// erro ao montar caminho

		return 3;
	}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*	Diretórios do perfil relativos a um item de tarefa
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * */



char* dirDadosPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor){

	char idPR[21] = "";

	if (sprintf(idPR, "%lld", idPerfilRespondedor) > 0) {
		return concatstr2(dirDadosItemTarefa(idTrabalho, idItemTarefa), concatstr2("/", idPR));
	}

	return NULL;
}

char* dirDadosPerfilItemTarefaStr(char* idTrabalho, char* idItemTarefa, char* idPerfilRespondedor){

	long long int idIT = 0;
	long long int idTrab = 0;
	long long int idPR = 0;

	if (sscanf(idItemTarefa, "%lld", &idIT) == 1) {
		if (sscanf(idTrabalho, "%lld", &idTrab) == 1) {
			if (sscanf(idPerfilRespondedor, "%lld", &idPR) == 1) {
				return dirDadosPerfilItemTarefa(idTrab, idIT, idPR);
			}
		}
	}

	return NULL;
}


char* dirDownloadsPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor){

	char idPR[21] = "";

	if (sprintf(idPR, "%lld", idPerfilRespondedor) > 0) {
		return concatstr2(dirDownloadsItemTarefa(idTrabalho, idItemTarefa), concatstr2("/", idPR));
	}

	return NULL;
}


char* dirDownloadsPerfilItemTarefaStr(char* idTrabalho, char* idItemTarefa, char* idPerfilRespondedor){

	long long int idIT = 0;
	long long int idTrab = 0;
	long long int idPR = 0;

	if (sscanf(idItemTarefa, "%lld", &idIT) == 1) {
		if (sscanf(idTrabalho, "%lld", &idTrab) == 1) {
			if (sscanf(idPerfilRespondedor, "%lld", &idPR) == 1) {
				return dirDownloadsPerfilItemTarefa(idTrab, idIT, idPR);
			}
		}
	}

	return NULL;
}



int dirCriarDirDadosPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor){

	char* dirDPIT = dirDadosPerfilItemTarefa(idTrabalho, idItemTarefa, idPerfilRespondedor);

	if (dirDPIT) {

		int ret = mkdir(dirDPIT, 0755);

		if (ret) {

			// erro ao tentat criar diretório

			return 1;
		}

		return 0;
	}

	return 2;

}


int dirRemoverDirDadosPerfilItemTarefa(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRespondedor) {

	char* dirDPIT = dirDadosPerfilItemTarefa(idTrabalho, idItemTarefa, idPerfilRespondedor);

	if (dirDPIT) {

		if (access(dirDPIT, F_OK)) {

			// diretório não existe

			return 1;
		}
		else {

			int ret = rmdir(dirDPIT);

			if (ret) {

				// erro ao tentar apagar diretório

				return 2;
			}

			return 0;
		}
	}

	return 3;
}



/* * * * * * * * * * * * * * * * * * *
*
*	Dados da tarefa
*
* * * * * * * * * * * * * * * * * * * */



char* urlEnunciadoPNG(long long int idTarefa) {

	//return concatstr2(urlTarefasDwl, concatstr2("/", concatstr2(dirN1N2(idTarefa), "/enunciado.png")));
	return concatstr2(urlTarefasDwlTarefas, concatstr2("/", concatstr2(dirN1N2(idTarefa), "/enunciado.png")));

}


char* caminhoEnunciadoPNG(long long int idTarefa) {

	return concatstr2(dirDownloadsTarefa(idTarefa), "/enunciado.png");
}


char* caminhoEnunciadoPDF(long long int idTarefa) {

	return concatstr2(dirDownloadsTarefa(idTarefa), "/enunciado.pdf");
}




/* * * * * * * * * * * * * * * * * * * * *
 *
 *	Codigo C, Avaliação Estática
 *  
 * * * * * * * * * * * * * * * * * * * * */



char* dirAvaliacaoTarefa(long long int idTarefa) {

	return concatstr2(dirDadosTarefa(idTarefa), "/avaliacao");
}

char* dirCaminhoNumCts(long long int idTarefa) {

	return concatstr2(dirAvaliacaoTarefa(idTarefa), "/numCts.txt");
}

char* dirCasoTesteTarefa(long long int idTarefa, int numct) {

	char dirct[13];
	sprintf(dirct, "/%d", numct);
	return concatstr2(dirAvaliacaoTarefa(idTarefa), dirct);
}


int dirCriarDirAvalicaoTarefa(long long int idTarefa, int numcts) {

	mkdir(dirAvaliacaoTarefa(idTarefa), 0755);
	//printf("%s", dirAvaliacaoTarefa(idTarefa));

	for (int i = 1; i <= numcts; i++) {
		mkdir(dirCasoTesteTarefa(idTarefa, i), 0755);
	}
}

int dirEsvaziarDirAvaliacaoTarefa(long long int idTarefa) {

	char* dirAvaliacao = dirAvaliacaoTarefa(idTarefa);

	if (access(dirAvaliacao, F_OK)) {
		return 1;
	}


	Multilinhas* mlSubDirs = NULL;
	dirSubDirs(dirAvaliacao, &mlSubDirs);
	Multilinhas* mlArq = NULL;
	dirNaoSubDirs(dirAvaliacao, &mlArq);

	if (mlSubDirs && mlSubDirs->numlins) {

		// para cada caso de teste
		NoLinha* nl = mlSubDirs->prim;
		while(nl) {
			if (nl->linha) {

				char* dirct = concatstr2(dirAvaliacao, concatstr2("/", nl->linha));

				Multilinhas* mlArqsCT = NULL;
				dirNaoSubDirs(dirct, &mlArqsCT);

				if (mlArqsCT && mlArqsCT->numlins) {

					// para cada arquivo do diretório de caso de teste
					NoLinha* nl2 = mlArqsCT->prim;
					while(nl2) {
						if (nl2->linha) {
							char* caminho = concatstr2(dirct, concatstr2("/", nl2->linha));
							remove(caminho);
						}

						nl2 = nl2->prox;
					}
				}

				rmdir(dirct);
			}

			nl = nl->prox;
		}
	}

	if (mlArq && mlArq->numlins) {
		// apagar os arquivos do diretório casosdeteste

		NoLinha* nl = mlArq->prim;
		while(nl) {
			if (nl->linha) {
				char* caminho = concatstr2(dirAvaliacao, concatstr2("/", nl->linha));
				remove(caminho);
			}
			
			nl = nl->prox;
		}
	}
	
}

int dirRemoverDirAvaliacaoTarefa(long long int idTarefa) {

	dirEsvaziarDirAvaliacaoTarefa(idTarefa);
	char* dirAvaliacao = dirAvaliacaoTarefa(idTarefa);

	if (dirAvaliacao)
		rmdir(dirAvaliacao);
}


char* dirAreaDeTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {

	char* dirPerfil = dirDadosPerfilItemTarefa(idTrabalho, idItemTarefa, idPerfilRepondedor);

	return concatstr2(dirPerfil, "/casosdeteste");
}

int existeAreaDeTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {
	char* dirAreaDeTestes = dirAreaDeTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);

	if (!access(dirAreaDeTestes, F_OK))
		return 1;
	
	return 0;
}

char* dirCaminhoRespostaPrepITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {
	char* caminho = concatstr2(dirAreaDeTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor), "/respostaprep.c");

	return caminho;
}

char* dirCasoTesteITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor, int numct) {

	char* dirAreaTeste = dirAreaDeTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);
	
	char dirct[13];
	sprintf(dirct, "/%d", numct);

	return concatstr2(dirAreaTeste, dirct);
}

int dirCriarDirAreaTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor, int numcts) {

	char* dirAreaTestes = dirAreaDeTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);

	mkdir(dirAreaTestes, 0755);

	for (int i = 1; i <= numcts; i++) {
		char* dirCasoTeste = dirCasoTesteITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor, i);

		mkdir(dirCasoTeste, 0755);
	}
}


int dirEsvaziarAreaTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {

	char* dirAreaTeste = dirAreaDeTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);

	Multilinhas* mlSubDirs = NULL;
	dirSubDirs(dirAreaTeste, &mlSubDirs);
	Multilinhas* mlArq = NULL;
	dirNaoSubDirs(dirAreaTeste, &mlArq);

	// apagar subdiretórios
	if (mlSubDirs && mlSubDirs->numlins) {

		NoLinha* nl = mlSubDirs->prim;
		while (nl) {
			if (nl->linha) {
				char* dirct = concatstr2(dirAreaTeste, concatstr2("/", nl->linha));

				Multilinhas* mlArqsCT = NULL;
				dirNaoSubDirs(dirct, &mlArqsCT);

				if (mlArqsCT && mlArqsCT->numlins) {

					NoLinha* nl2 = mlArqsCT->prim;
					while (nl2) {
						if (nl2->linha) {
							char* caminho = concatstr2(dirct, concatstr2("/", nl2->linha));
							remove(caminho);
						}
						
						nl2 = nl2->prox;
					}
				}

				rmdir(dirct);
			}

			nl = nl->prox;
		}
	}

	// apagar arquivos
	if (mlArq && mlArq->numlins) {
		NoLinha* nl = mlArq->prim;

		while(nl) {
			if (nl->linha) {
				char* caminho = concatstr2(dirAreaTeste, concatstr2("/", nl->linha));
				remove(caminho);
			}

			nl = nl->prox;
		}
	}
}

int dirRemoverAreaTestesITPerfil(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {

	dirEsvaziarAreaTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);
	char* dirAreaTeste = dirAreaDeTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);
	if (dirAreaTeste) {
		rmdir(dirAreaTeste);
	}
}

int dirEsvaziarDirPerfilIT(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {


	// Remover area de testes do perfil no item de tarefa
	dirRemoverAreaTestesITPerfil(idTrabalho, idItemTarefa, idPerfilRepondedor);

	char* dirPerfilIT = dirDadosPerfilItemTarefa(idTrabalho, idItemTarefa, idPerfilRepondedor);

	//Multilinhas* mlSubDirs = NULL;
	//dirSubDirs(dirPerfilIT, &mlSubDirs);
	Multilinhas* mlArq = NULL;
	dirNaoSubDirs(dirPerfilIT, &mlArq);

	// apagar arquivos
	if (mlArq && mlArq->numlins) {

		NoLinha* nl = mlArq->prim;
		while (nl) {
			char* caminho = concatstr2(dirPerfilIT, concatstr2("/", nl->linha));

			remove(caminho);
			nl = nl->prox;
		}

	}
}

int dirRemoverDirPerfilIT(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {

	dirEsvaziarDirPerfilIT(idTrabalho, idItemTarefa, idPerfilRepondedor);

	char* dirPerfilIT = dirDadosPerfilItemTarefa(idTrabalho, idItemTarefa, idPerfilRepondedor);

	remove(dirPerfilIT);
}



char* dirCaminhoModelosC() {
	return concatstr2(dirHtml, "/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/confAvalExemplo3");
}

char* dirCaminhoModeloCGecat() {

	return concatstr2(dirHtml, "/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/confAvalExemplo3/gecat.c");
}

char* dirCaminhoModeloCCab() {

	return concatstr2(dirCaminhoModelosC(), "/cab.c");
}

char* dirCaminhoModeloCExecCt() {

	return concatstr2(dirCaminhoModelosC(), "/execCt.c");
}

char* dirCaminhoModeloCExecAval() {

	return concatstr2(dirCaminhoModelosC(), "/execAval.c");
}

char* dirCaminhoModeloCExecFeedback() {

	return concatstr2(dirCaminhoModelosC(), "/execFeedback.c");
}

char* dirCaminhoModeloCSalvarSaida() {

	return concatstr2(dirCaminhoModelosC(), "/salvarSaida.c");
}

char* dirCaminhoModeloCCarregarCt() {

	return concatstr2(dirCaminhoModelosC(), "/carregarCt.c");
}


char* dirCaminhoGcat(long long int idTarefa) {

	return concatstr2(dirAvaliacaoTarefa(idTarefa), "/gecat.c");
}




#endif
