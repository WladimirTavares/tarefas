/*
 * multilinhas.h
 *
 * implementa a estrutura Multilinhas, basicamente uma lista de linhas.
 *
 */


#ifndef MULTILINHAS_H
#define MULTILINHAS_H


#include <stdio.h>
#include <string.h>

#include "bibstring2.h"



typedef struct NoLinha {

	char* linha;
	struct NoLinha* ante;
	struct NoLinha* prox;
} NoLinha;

// Cria nó fazendo cópia da linha
NoLinha* nlCriarNo(char* linha);

// Tamanho da linha em bytes, não inclui '\0'
size_t nlTamanhoLinha(NoLinha* nl);


typedef struct Multilinhas {

	NoLinha* prim;
	NoLinha* ult;

	int numlins;
} Multilinhas;



Multilinhas* mlCriar();

void mlImprimir(Multilinhas* ml);

void mlImprimirNoPorNo(Multilinhas* ml, char* eol);

void mlMetaInfo(Multilinhas* ml);

// Cria cópia de 'linha' e adiciona um nó no final de 'ml'
// 'ml' deve estar inicializado
int mlAnexarLinha(char* linha, Multilinhas* ml);

// Copia linhas dos texto e anexa uma a uma
int mlAnexarTexto(char* texto, Multilinhas* ml);

int mlAnexar(Multilinhas* ml, Multilinhas* anexo);

int mlEmpilharLinha(char* linha, Multilinhas* ml);

int mlCarregarArquivoTexto(char* caminho, Multilinhas* ml);

int mlSalvarArquivoTexto(char* caminho, Multilinhas* ml);

int mlSubstituirTodos(char* sub, char* substituto, Multilinhas* ml);

int mlSubstituirTodosEmLinha(char* sub, char* substituto, NoLinha* nl);

// Procura a substring sub e retorna o nó onde aparece, caso haja, retorna nulo caso contrário
NoLinha* mlEncontrar(char* sub, Multilinhas* ml);

// Procura a substring sub a partir de e abaixo do nó nl
NoLinha* mlEncontrarApos(char* sub, NoLinha* nl);

// Procura a substring sub a partir de e acima do nó nl
NoLinha* mlEncontrarAntes(char* sub, NoLinha* nl);

// Insere linha criando nó
// Cria cópia da linha
NoLinha* mlInserirAbaixo(char* linha, NoLinha* nl, Multilinhas* ml);

// Insere texto abaixo do nó nl
NoLinha* mlInserirTextoAbaixo(char* texto, NoLinha* nl, Multilinhas* ml);

// Insere linha criando nó
// Cria cópia da linha
NoLinha* mlInserirAcima(char* linha, NoLinha* nl, Multilinhas* ml);

// Remove linhas acima
int mlRemoverAcima(NoLinha* nl, Multilinhas* ml);

// Copia um multilinhas em uma certa posição de outro
int mlCopiarAbaixo(Multilinhas* mlTrecho, NoLinha* nl, Multilinhas* ml);

// Calcula tamanho do texto em bytes, não inclui '\0'.
size_t mlTamanhoTexto(Multilinhas* ml);

// Gera string correpondente à concatenação simples dos conteúdos das linhas
// Aloca espaço
char* mlExtrairTexto(Multilinhas* ml);

// Ordena
void mlOrdenar(Multilinhas* ml);



// Métodos de edição

// Cuidado! Não checa se nl pertence a ml.
int mlRemoverNoLinha(NoLinha* nl, Multilinhas* ml);

int mlRemoverLinhasEmBranco(Multilinhas* ml);

int mlRemoverLinhasInclude(Multilinhas* ml);

int mlLinhaInclude(NoLinha* ml);


/* Implementações */



NoLinha* nlCriarNo(char* linha) {

	NoLinha* nl = (NoLinha *) malloc( sizeof(NoLinha));

	nl->prox = NULL;
	nl->ante = NULL;

	nl->linha = copiastr(linha);

	return nl;
}


size_t nlTamanhoLinha(NoLinha* nl) {

	if (nl && nl->linha)
		return strlen(nl->linha);
	else
		return 0;
}



Multilinhas* mlCriar() {
	Multilinhas* ml = (Multilinhas *) malloc(sizeof(Multilinhas));

	ml->prim = NULL;
	ml->ult = NULL;

	ml->numlins = 0;

	return ml;
}


void mlImprimir(Multilinhas* ml) {

	if (ml) {
		NoLinha* nl = ml->prim;

		while (nl) {
			if (nl->linha) {
				printf("%s", nl->linha);
			}
			else {
				printf("[LINHA NULA!]\n");
			}

			nl = nl->prox;
		}
	}
	else printf("[MLNULL!]\n");
}


void mlImprimirNoPorNo(Multilinhas* ml, char* eol) {

	if (ml) {
		NoLinha* nl = ml->prim;

		while (nl) {
			if (nl->linha) {
				printf("%s%s", nl->linha, eol);
			}
			else {
				printf("[LINHA NULA!]\n");
			}

			nl = nl->prox;
		}
	}
	else printf("[MLNULL!]\n");
}


void mlMetaInfo(Multilinhas* ml) {

	if (ml) {
		printf("numlinss: %d\n", ml->numlins);
		int n = 1;

		NoLinha* nl = ml->prim;

		while (nl) {
			if (nl->linha) {
				size_t tam = strlen(nl->linha);
				printf("l%d: %ld", n++,tam);
				if ( tam > 0 && nl->linha[tam-1] == '\n' ) {
					printf("[\\n]");
				}
				printf("\n");
			}
			else
				printf("[LINHA NULA!]\n");

			nl = nl->prox;
		}
	}
	else printf("[MLNULL!]\n");

}


int mlAnexarLinha(char* linha, Multilinhas* ml) {

	if (linha && ml) {
		// copiar linha
		NoLinha* nl = nlCriarNo(linha);

		// encadear
		nl->prox = NULL;
		nl->ante = ml->ult;

		if (ml->ult) {
			ml->ult->prox = nl;
		}
		else {
			ml->prim = nl;
		}

		// atualizar último nó
		ml->ult = nl;

		ml->numlins++;

		return 0;
	}

	return 1;

}


int mlAnexarTexto(char* texto, Multilinhas* ml) {

	if (texto && ml) {

		char* inil = texto;
		char* fiml = NULL;

		while (inil) {

			fiml = strchr(inil, '\n');

			if (fiml) {

				size_t tamlinha = fiml - inil + 1;

				char* linha = (char *) malloc((tamlinha + 1) * sizeof(char));
				strncpy(linha, inil, tamlinha);
				linha[tamlinha] = '\0';

				mlAnexarLinha(linha, ml);

				inil = fiml + 1;
			}
			else {

				mlAnexarLinha(inil, ml);

				inil = NULL;
			}
		}

		return 0;
	}

	return 1;
}

int mlAnexar(Multilinhas* ml, Multilinhas* anexo) {

	if (ml && anexo) {
		NoLinha* nl = anexo->prim;

		while (nl) {
			mlAnexarLinha(nl->linha, ml);
			nl = nl->prox;
		}
	}

}

int mlEmpilharLinha(char* linha, Multilinhas* ml) {

	if (linha && ml) {

		// copiar linha
		NoLinha* nl = nlCriarNo(linha);

		// encadear
		nl->ante = NULL;
		nl->prox = ml->prim;

		if (ml->prim) {
			ml->prim->ante = nl;
		}
		else {
			ml->ult = nl;
		}

		// atualizar primeiro nó
		ml->prim = nl;

		ml->numlins++;

		return 0;
	}

	return 1;
}



int mlCarregarArquivoTexto(char* caminho, Multilinhas* ml) {

	if (caminho && ml){
		FILE* f = fopen(caminho, "r");

		if (!f) {
			return 1;
		}

		char* linha = NULL;

		int tamseg = 1025;

		char* segmento = (char *) malloc( tamseg + 1 * sizeof(char));
		size_t tamlido = 0;

		while (fgets(segmento, tamseg + 1, f)) {

			while (strlen(segmento) == tamseg && segmento[tamseg - 1] != '\n') {		// caso linha maior que 1024

				anexarstr(&linha, segmento);		// montar linha

				segmento[0] = '\0';
				fgets(segmento, tamseg + 1, f);
			}

			anexarstr(&linha, segmento);		// montar linha

			mlAnexarLinha(linha, ml);

			free(linha);
			linha = NULL;
		}

		fclose(f);

		return 0;
	}

	return 1;
}


int mlSalvarArquivoTexto(char* caminho, Multilinhas* ml) {

	if (caminho && ml) {
		FILE* f = fopen(caminho, "w");

		if (!f) {
			return 1;
		}

		NoLinha* nl = ml->prim;

		while (nl) {
			if (nl->linha) {
				fwrite(nl->linha, 1, strlen(nl->linha), f);
			}

			nl = nl->prox;
		}

		fclose(f);
	}

	return 1;
}


int mlSubstituirTodos(char* sub, char* substituto, Multilinhas* ml) {

	if (ml && sub && substituto) {

		NoLinha* nl = ml->prim;

		int num = 0;
		while (nl) {

			num += subststr(sub, substituto, &(nl->linha));
			nl = nl->prox;
		}

		return num;
	}

	return 0;
}


int mlSubstituirTodosEmLinha(char* sub, char* substituto, NoLinha* nl) {

	if (nl && sub && substituto) {

		int num = subststr(sub, substituto, &(nl->linha));

		return num;
	}

	return 0;

}


NoLinha* mlEncontrar(char* sub, Multilinhas* ml) {

	if (sub && ml) {

		NoLinha* nl = ml->prim;

		while (nl) {
			if (nl->linha) {
				char* pos;
				if (pos = strstr(nl->linha, sub)) {
					return nl;
				}
			}

			nl = nl->prox;
		}
	}

	return NULL;
}


NoLinha* mlEncontrarApos(char* sub, NoLinha* nl) {

	if (sub && nl) {

		while (nl) {
			if (nl->linha) {
				char* pos;
				if (pos = strstr(nl->linha, sub)) {
					return nl;
				}
			}

			nl = nl->prox;
		}
	}

	return NULL;
}


NoLinha* mlEncontrarAntes(char* sub, NoLinha* nl) {

	if (sub && nl) {

		while (nl) {
			if (nl->linha) {
				char* pos;
				if (pos = strstr(nl->linha, sub)) {
					return nl;
				}
			}

			nl = nl->ante;
		}
	}

	return NULL;
}


NoLinha* mlInserirAbaixo(char* linha, NoLinha* nl, Multilinhas* ml) {

	if (ml && linha) {

		NoLinha* nlaux = nlCriarNo(linha);

		if (nl) {

			nlaux->ante = nl;
			nlaux->prox = nl->prox;
			if (nl->prox) {
				nl->prox->ante = nlaux;
			}
			nl->prox = nlaux;

			if (ml->ult == nl) {
				ml->ult = nlaux;
			}

			ml->numlins++;
		}
		else {

			mlAnexarLinha(linha, ml);
		}

		return nlaux;
	}

	return NULL;

}


NoLinha* mlInserirTextoAbaixo(char* texto, NoLinha* nl, Multilinhas* ml) {

	if (texto && ml) {

		char* inil = texto;
		char* fiml = NULL;

		NoLinha* nlIni = NULL;

		while (inil) {

			fiml = strchr(inil, '\n');

			if (fiml) {

				size_t tamlinha = fiml - inil + 1;

				char* linha = (char *) malloc((tamlinha + 1) * sizeof(char));
				strncpy(linha, inil, tamlinha);
				linha[tamlinha] = '\0';

				if (nlIni != NULL)
					nlIni = mlInserirAbaixo(linha, nl, ml);
				else
					mlInserirAbaixo(linha, nl, ml);

				inil = fiml + 1;
			}
			else {

				mlInserirAbaixo(inil, nl, ml);

				inil = NULL;
			}
		}

		return nlIni;
	}

	return NULL;
}


NoLinha* mlInserirAcima(char* linha, NoLinha* nl, Multilinhas* ml) {

	if (ml && linha) {

		NoLinha* nlaux = nlCriarNo(linha);

		if (nl) {

			nlaux->ante = nl->ante;
			if (nl->ante) {
				nl->ante->prox = nlaux;
			}
			nlaux->prox = nl;
			nl->ante = nlaux;

			if (ml->prim == nl) {
				ml->prim = nlaux;
			}

			ml->numlins++;
		}
		else {

			mlEmpilharLinha(linha, ml);
		}

		return nlaux;
	}

	return NULL;

}


int mlRemoverAcima(NoLinha* nl, Multilinhas* ml) {

	if (nl && ml) {

		// checar se nl é no de ml
		NoLinha* nlaux = ml->prim;

		while (nlaux && nlaux != nl) {
			nlaux = nlaux->prox;
		}

		if (nl == nlaux) {
			ml->prim = nl;
			nl = nl->ante;

			while (nl) {
				nlaux = nl->ante;

				free(nl->linha);
				free(nl);

				nl = nlaux;
			}

			ml->prim->ante = NULL;

			return 0;
		}

		return 1;
	}

	return 2;
}


int mlCopiarAbaixo(Multilinhas* mlTrecho, NoLinha* nl, Multilinhas* ml) {

	if (mlTrecho && nl && ml) {
		NoLinha* nlaux = mlTrecho->ult;

		while (nlaux) {

			mlInserirAbaixo(nlaux->linha, nl, ml);
			nlaux = nlaux->ante;
		}

		return 0;
	}

	return 1;
}


size_t mlTamanhoTexto(Multilinhas* ml) {

	if (ml) {
		NoLinha* nl = ml->prim;

		size_t tam = 0;

		while (nl) {
			if (nl->linha)
				tam = tam + strlen(nl->linha);

			nl = nl->prox;
		}

		return tam;
	}

	return 0;
}


char* mlExtrairTexto(Multilinhas* ml) {

	char* texto = NULL;

	if (ml && ml->prim) {

		size_t tam = mlTamanhoTexto(ml);
		tam++;

		texto = (char *) malloc((tam + 1) * sizeof(char));

		texto[0] = '\0';

		NoLinha* nl = ml->prim;

		while (nl) {

			if (nl->linha)
				strcat(texto, nl->linha);

			nl = nl->prox;
		}
	}

	return texto;
}



/*		Métodos de edição		*/



int mlRemoverNoLinha(NoLinha* nl, Multilinhas* ml) {

	if (nl && ml) {

		// checar se é o primeiro

		if (nl->ante)
			nl->ante->prox = nl->prox;
		else
			ml->prim = nl->prox;

		// checar se é o último

		if (nl->prox)
			nl->prox->ante = nl->ante;
		else
			ml->ult = nl->ante;

		(ml->numlins)--;

		nl->ante = NULL;
		nl->prox = NULL;

		return 0;
	}

	return 1;

}



int mlRemoverLinhasEmBranco(Multilinhas* ml) {

	if (ml) {
		NoLinha* nl = ml->prim;

		while (nl) {
			if (nl->linha && strlen(nl->linha) == 0) {

				NoLinha* aux = nl;
				nl = nl->prox;

				mlRemoverNoLinha(aux, ml);
			}
			else
				nl = nl->prox;
		}

		return 0;
	}

	return 1;
}


int mlRemoverLinhasInclude(Multilinhas* ml) {

	int n = 0;

	if (ml) {
		NoLinha* nl = ml->prim;

		while (nl) {
			NoLinha* nlaux = nl->prox;

			if (mlLinhaInclude(nl)) {
				mlRemoverNoLinha(nl, ml);
				n++;
			}

			nl = nlaux;
		}
	}

	return n;
}


int mlLinhaInclude(NoLinha* nl) {

	if (nl) {
		if (nl->linha) {
			char* aux = primcar(nl->linha);
			
			if (*aux == '#') {

				aux++;
				aux = primcar(aux);

				if (ePrefixo(aux, "include")) {
					return 1;
				}
			}
		}
	}

	return 0;
}


// Linhas nulas são colocadas no final
// Linha nula é diferente de linha vazia "", que ficarão no começo
// Embora não pareça fazer sentido linhas vazias, os procedimentos não devem quebrar por causa disso

void mlOrdenar(Multilinhas* ml) {

	// bolha

	if (ml) {

		NoLinha* ult = ml->ult;

		while (ult) {

			NoLinha* nl = ml->prim;

			while (nl && nl->prox && nl != ult) {		// existe o próximo nó, checar inversões e
														// realizar troca, se necessário

				if (nl->linha) {		// linha não nula

					if (nl->prox->linha) {		// existe linha não nula no próximo nó. (caso contrário, não altera a ordem)

						if (strcmp(nl->linha, nl->prox->linha) > 0) {

							// inversão, trocar

							char* linha = nl->linha;
							nl->linha = nl->prox->linha;
							nl->prox->linha = linha;
						}
					}
				}
				else {		// caso a linha seja nula, trocar com a próxima, caso a próxima seja não nula

					if (nl->prox->linha) {

						// trocar

						char* linha = nl->linha;
						nl->linha = nl->prox->linha;
						nl->prox->linha = linha;
					}
				}

				nl = nl->prox;
			}

			ult = ult->ante;
		}
	}

}




#endif
