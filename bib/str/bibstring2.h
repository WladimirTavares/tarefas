/*
 * bibstring.h:	Implementa métodos de manipuação de string
 *
 *
 * Versão: 0.1
 *
 */


#ifndef BIBSTRING_H
#define BIBSTRING_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>





/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Tipos de Dados
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


typedef struct Segmento {
	char* ini;
	char* fim;
} Segmento;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Constantes
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


char* ALFANUM    = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ";
char* ALFANUMEXT = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*$#@.,;:!?(){}[]|\\/ ";
//char* ALFANUMEXT = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*%$#@_.,;:!?(){}[]|\\/ ";
//char* CARVALS = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ- ";
char* CHARDIG    = "0123456789";
char* CHARCODIGO = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789:-(){}[]";
//char* CHARCODIGO = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789:-_(){}[]";
char* CHARMAT    = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789:-(){}[]_/\\";
char* CHARNOME   = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ- ";
char* CHARSIGLA   = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ:-()_/\\";
char* CHAREMAIL  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789-+#*&.!@";
//char* CHAREMAIL  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789-+_#*&.!@";
char* CHARLOGIN  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789-.";
//char* CHARLOGIN  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789-._";
char* CHARSENHA  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*$#@.,;!?|";
//char* CHARSENHA  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*%$#@_.,;!?|";
char* CARVALS    = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+#$*&;,.!?@";
//char* CARVALS    = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+_#$*&;,.!?@";
char* CARVALSESP = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+#$*&;,.!?@ ";
//char* CARVALSESP = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+_#$*&;,.!?@ ";
char* CARVALSML  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+#$*&;,.!?@ \n";
//char* CARVALSML  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+_#$*&;,.!?@ \n";
char* CARVALSMLEXT  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*&$#@.,;:!?><(){}[]|\\/ \n\r";
char* CARVALSOBS  = "\"~abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*_&$#@.,;:!?><(){}[]|\\/ \n\r";
//char* CARVALSMLEXT  = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙãẽĩõũÃẼĨÕŨâêîôûÂÊÎÔÛäëïöüÄËÏÖÜçÇ-+=*&%$#@_.,;:!?(){}[]|\\/ \n";
char* CARDATA  =  "0123456789-";
char* CARHORA  =  "0123456789:.";
char* CHARSIMPLES = "abcdefghijlmnopqrstuvxzkwyABCDEFGHIJLMNOPQRSTUVXZKWY0123456789";


/* * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Cabeçalho de métodos
 *
 * * * * * * * * * * * * * * * * * * * * * * * * */

/*   Strings   */


// Cria cópia da string str e retorna um ponteiro para a cópia
char* copiastr(char* str);

// Retorna a concatenação das strings, alocando espaço automaticamente
// Não altera as strings passadas como parâmetro (cria cópia)
// Retorna NULL caso um dos parâmetros seja NULL
char* concatstr(char* stra, char* strb);

// Retorna a concatenação das strings, alocando espaço automaticamente
// Não altera as strings passadas como parâmetro (cria cópia)
// Retorna NULL caso um dos parâmetros seja NULL ou o malloc retorna null
char* concatstr2(char* stra, char* strb);

// Anexa o 'sufixo' em 'str'
// Não altera 'sufixo'
// Realoca espaço para 'str', que deve ter sido alocado com malloc ou realloc
char* anexarstr(char** str, char* sufixo);


// Substitui as ocorrências de uma substring por outra
// Aloca espaço para a nova string, libera espaço de 'str', que deve portante ter sido o retorno de malloc ou realloc.
int subststr(char* sub, char* substituto, char** str);


// Remove espaços das extremidades
// Altera a string de entrada
char* aparar(char** str);


// Checa se str é string vazia ou formada por espaços em branco ou tabs ou \n
int eBranco(char* str);


// Extrai o prefixo da string de bytes que corresponde ao primeiro code-point (caractere) em unicode
char* utf8Prefixo(unsigned char* str);

// Retorna o tamanho em bytes do primeiro caractere utf8.
// Caso não seja um caractere utf8, retorna 0.
// O \0 é um caractere de tamanho 1 byte.
// Caso seja passado um ponteiro nulo, retorna 0.
int utf8Tamanho(unsigned char* str);

// Checa se uma sequência de bytes (unsigned char) é composta por caracteres no gabarito codificados em utf-8
int utf8Val(unsigned char* str, unsigned char* gabarito, char** poserr);

//
int soDigitos(char* str);

// verifica se uma string é sufixo de outra
int eSufixo(char* str, char* suf);

// verifica se uma string é prefixo de outra
int ePrefixo(char* str, char* pref);

// verifica se uma string tem um dentre um conjunto de sufixos
int checaSufixo(char* str, char** sufs, int nsufs);

// extrai a extensão de um nome de arquivo
char* extensaoArq(char* nome);

// extrai string (cópia) antes da extensão de um nome do arquivo
// se não houver extensão, retorna o nome inteiro
char* preExtensaoArq(char* nome);

// Conta número de um determinado caractere em uma string
size_t contacar(char* str, char c);

// Fragmenta str em segmentos separados pelo caractere c
// Retorna sequência de segmentos e número de segmentos
int fragstr(char* str, char c, char*** segs, int* nsegs);

// Retorna ponteiro para o primeiro caractere não branco
// ou para \0 caso todos sejam brancos
char* primcar(char* str);

/* Conversões */

char* llistr(long long int lli);

char* intstr(int i);



/* Vetores Char */

// busca bloco de memória b dentro de bloco de memória a
char* memmem2(char* aini, char* afim, char* bini, char* bfim);

// busca string dentro de bloco de memória
char* memstr(char* aini, char* afim, char* str);

// busca caractere dentro de bloco de memória
char* mmemchr(char* aini, char* afim, char chr);

// Retorna a primeira posição a partir de ini (inclusive) diferente de espaço em branco
char* memns(char* ini, char* fim);


//int mempstr(char* ini, char* fim, char* str);


int mempmem(char* aini, char* afim, char* bini, char* bfim);


// Compara dois blocos de char, retorna 0 se forem iguais e 1 cc
int memcmpmem(char* aini, char* afim, char* bini, char* bfim);

// Compara bloco de char com string C, retorna 0 se forem iguais e 1 cc
int memcmpstr(char* aini, char* afim, char* str);


// Retorna um string C, vetor de char uma unidade maior que o tamanho do segmento com a última posição igual a '\0'
// Note que no meio do segmento pode haver um '\0', pois se trata de vetor binário
// Cria uma cópia.
char* memtostr(char* ini, char* fim);


void impmem(char* ini, char* fim);



/*   Segmento   */

char* segseg(Segmento* seg1, Segmento* seg2);

int segcmpstr(Segmento* seg, char* str);

// Cria cópia
char* segtostr(Segmento* seg);

void impseg(Segmento* seg);

char* segchr(Segmento* seg, char chr);

// Retorna os limites da string str
Segmento* limites(char* str);

// Cria segmento a partir de ponteiros inicio e fim
Segmento* criarSegmento(char* ini, char* fim);



/* * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Implementação dos métodos
 *
 * * * * * * * * * * * * * * * * * * * * * * * * */



/*   Strings   */


char* copiastr(char* str){

	if (str) {
		char* cp = (char *) malloc ( (strlen(str) + 1) * sizeof(char) );

		if (cp)
			return strcpy(cp, str);

		return NULL;
	}

	return NULL;

}


char* concatstr(char* stra, char* strb){

	if (stra && strb) {

		char* str = (char *) malloc( (strlen(stra) + strlen(strb) + 1) * sizeof(char));
		strcpy(str, stra);
		strcat(str, strb);

		return str;
	}
	else
		return NULL;

}

char* concatstr2(char* stra, char* strb){

	if (stra && strb) {

		char* str = (char *) malloc( (strlen(stra) + strlen(strb) + 1) * sizeof(char));

		if (str) {
			strcpy(str, stra);
			strcat(str, strb);

			return str;
		}
	}

	return NULL;

}


char* anexarstr(char** str, char* sufixo) {

	size_t tamstr;
	if (*str) {		// checa se foi passado ponteiro nulo antes de calcular tamanho
		tamstr = strlen(*str);
	}
	else {
		tamstr = 0;
	}

	size_t tam = tamstr + strlen(sufixo) + 1;

	*str = (char *) realloc( *str, tam * sizeof(char));
	strcpy(*str + tamstr, sufixo);

	return *str;
}


int subststr(char* sub, char* substituto, char** str) {


	/*
	 * Identifica as ocorrências de 'sub' sem sobreposição
	 * e as substitui por 'substituto'
	 */

	if (sub && substituto && *str) {

		int tamsub = strlen(sub);
		int tamsubstituto = strlen(substituto);
		int tamstr = strlen(*str);

		char* pos = *str;


		// contar ocorrências de 'sub'
		int num = 0;

		while (pos = strstr(pos, sub)) {
			num++;
			pos = pos + tamsub;
		}

		char* res = NULL;

		if (num) {

			// aloca espaço para nova string
			int tamres = tamstr + (num * (tamsubstituto - tamsub));
			res = (char *) malloc( (tamres + 1) * sizeof(char) );

			pos = *str;
			char* posant = pos;		// inicio do bloco a se copiado

			// posição onde o próximo segmento a será copiado
			char* posr = res;

			for (int i = 0; i < num; i++) {

				// encontra a próxima ocorrência de 'sub'
				pos = strstr(pos, sub);

				// copia o segmento antes da próxima ocorrência
				if (pos - posant > 0) {
					memcpy(posr, posant, pos - posant);
					posr = posr + (pos - posant);
				}

				// copia a substring substituta
				memcpy(posr, substituto, tamsubstituto);
				posr = posr + tamsubstituto;

				// avança 'pos' para além da ocorrência atual de sub
				pos = pos + tamsub;
				posant = pos;
			}

			// copiar restante da string
			if (*str + tamstr - pos > 0)
				memcpy(posr, pos, *str + tamstr - pos);

			res[tamres] = '\0';

			free(*str);
			*str = res;

		}

		return num;
	}

	return 0;

}



char* aparar(char** str) {

	if (str && *str) {
		char* ini = *str;

		if (ini) {
			size_t tam = strlen(*str);

			if (tam > 0) {
				char* fim = *str + (tam-1);

				while ((*ini == ' ' || *ini == '\t' || *ini == '\n') && ini <= fim)
					ini++;

				while ((*fim == ' ' || *fim == '\t' || *fim == '\n') && fim >= ini)
					fim--;

				*str = ini;
				fim++;
				*fim = '\0';
			}
		}

		return ini;
	}

	return NULL;
}


int eBranco(char* str) {

	char* ini = str;

	if (ini) {

		while ((*ini == ' ' || *ini == '\t' || *ini == '\n') && *ini != '\0')
			ini++;

		if (*ini == '\0')
			return 1;
		else
			return 0;

	}

	return 0;

}


char* utf8Prefixo(unsigned char* str) {

	if (str) {
		int tam = 0;

		if (str[0] < 128) {
			tam = 1;

			if (str[0] == '\0') {
				return NULL;
			}
		}
		else if (str[0] >= 192 && str[0] < 224) {
			tam = 2;

			if (str[0] == '\0' || str[1] == '\0' || str[1] >= 192 || str[1] < 128) {
				return NULL;
			}
		}
		else if (str[0] >= 224 && str[0] < 240) {
			tam = 3;

			if (str[0] == '\0' || str[1] == '\0' || str[2] == '0' || str[1] >= 192 || str[1] < 128 || str[2] >= 192 || str[2] < 128) {
				return NULL;
			}
		}
		else if (str[0] >= 240) {
			tam = 4;

			if (str[0] == '\0' || str[1] == '\0' || str[2] == '\0' || str[3] == '\0' || str[1] >= 192 || str[1] < 128 || str[2] >= 192 || str[2] < 128 || str[3] >= 192 || str[3] < 128) {
				return NULL;
			}
		}
		else {
			return NULL;
		}

		char* pref = (char *) malloc ((tam + 1) * sizeof(char));

		memcpy(pref, str, tam);
		pref[tam] = '\0';

		return pref;
	}
}


int utf8Tamanho(unsigned char* str) {

	int tam = 0;

	if (str) {
		if (str[0] < 128) {
			tam = 1;
		}
		else if (str[0] >= 192 && str[0] < 224) {
			tam = 2;
		}
		else if (str[0] >= 224 && str[0] < 240) {
			tam = 3;
		}
		else if (str[0] >= 240) {
			tam = 4;
		}
	}

	return tam;
}


int utf8Val(unsigned char* str, unsigned char* gabarito, char** poserr) {

	if (str) {
		unsigned char* pos = str;
		unsigned char* utf8Char;

		while (*pos != '\0') {

			utf8Char = utf8Prefixo(pos);

			if (utf8Char) {
				if (strstr(gabarito, utf8Char)) {
					pos = pos + utf8Tamanho(utf8Char);
					free(utf8Char);
				}
				else {
					// não é caractere válido

					if (poserr) {
						*poserr = pos;
					}

					return 1;
				}
			}
			else {
				// não é caractere utf8
				if (poserr) {
						*poserr = pos;
					}
				return 2;
			}
		}

		// todos caracteres válidos
		if (poserr) {
			*poserr = NULL;
		}
		return 0;

	}
	else
		return 3;

}


int soDigitos(char* str) {

	char digitos[11] = "0123456789";

	while (*str != '\0') {

		if (strchr(digitos, *str) != NULL) {
			str++;
		}
		else {
			break;
		}
	}

	if (*str == '\0') {

		return 1;
	}

	return 0;
}


int eSufixo(char* str, char* suf) {

	if (str && suf) {
		size_t tam = strlen(str);
		size_t tams = strlen(suf);

		char* ini = str + tam - tams;

		while(*ini && *suf) {
			if (*ini == *suf) {
				ini++;
				suf++;
			}
			else return 0;
		}

		if (*ini == '\0' && *suf == '\0') {
			return 1;
		}
	}

	return 0;
}


int ePrefixo(char* str, char* pref) {

	if (str && pref) {
		while (*pref && *str && (*pref == *str)) {

			pref++;
			str++;
		}

		if (*pref) return 0;
		return 1;
	}

	return 0;
	
}


int checaSufixo(char* str, char** sufs, int nsufs) {

	if (str && sufs && nsufs) {
		for (int i = 0; i < nsufs; i++) {
			if (eSufixo(str, sufs[i])) return i;
		}
	}

	return -1;
}


char* extensaoArq(char* nome) {

	if (nome) {
		char* pos = nome + strlen(nome);

		while (pos > nome) {

			if (*pos == '.')
				break;

			pos--;
		}

		if (*pos == '.') {
			return copiastr(pos + 1);
		}
	}

	return NULL;
	
}



char* preExtensaoArq(char* nome) {

	if (nome) {
		char* pos = nome + strlen(nome);

		while (pos > nome) {

			if (*pos == '.')
				break;

			pos--;
		}

		if (*pos == '.') {
			size_t tam = pos - nome;
			char* ret = (char *) malloc((tam + 1) * sizeof(char));
			return strncpy(ret, nome, tam);
		}
		else return copiastr(nome);
	}

	return NULL;
}



size_t contacar(char* str, char c) {

	if (str) {

		size_t nc = 0;
		while (*str) {

			if (*str == c) nc++;

			str++;
		}

		return nc;
	}

	return 0;
}



int fragstr(char* str, char c, char*** segs, int* nsegs) {

	if (str) {
		if (c) {		// delimitador não pode ser '\0'

			char* iniseg = NULL;
			char* fimseg = NULL;

			char** lsegs = NULL;
			int lnsegs = 0;

			iniseg = str;

			while (iniseg) {

				// alocar espaço para o ponteiro do novo segmento

				lsegs = (char **) realloc(lsegs, ((lnsegs + 1) * sizeof(char *)));

				// encontrar próximo delimitador ou final da string

				fimseg = strchr(iniseg, c);

				if (fimseg) {		// encontrou um delimitador


					// alocar espaço para o segmento

					size_t tambloco = fimseg - iniseg;
					lsegs[lnsegs] = (char *) malloc((tambloco + 1) * sizeof(char));

					// copiar segmento

					strncpy(lsegs[lnsegs], iniseg, tambloco);
					lsegs[lnsegs][tambloco] = '\0';

					iniseg = fimseg + 1;

				}
				else {		// chegou no final


					// alocar espaço para segmento

					size_t tambloco = strlen(iniseg);
					lsegs[lnsegs] = (char *) malloc((tambloco + 1) * sizeof(char));

					// copiar segmento

					strncpy(lsegs[lnsegs], iniseg, tambloco);
					lsegs[lnsegs][tambloco] = '\0';

					iniseg = NULL;

				}

				lnsegs++;
			}

			*nsegs = lnsegs;
			*segs = lsegs;

			return 0;
		}

		return 1;
	}

	return 2;
}



char* primcar(char* str) {

	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f' || *str == '\v')) {

		str++;
	}

	return str;
}



/* Conversões */

char* llistr(long long int lli) {

	char* str = (char *) malloc(21);

	sprintf(str, "%lld", lli);

	return str;
}

char* intstr(int i) {

	char* str = (char *) malloc(12);

	sprintf(str, "%d", i);

	return str;
}



/* Vetores char */


char* memmem2(char* aini, char* afim, char* bini, char* bfim) {

	if (aini && afim && bini && bfim) {
		if (afim >= aini && bfim >= bini) {

			size_t tamb = bfim - bini;		//tamanho do bloco a ser buscado -1

			if ((afim - aini) >= tamb) {

				char* i;

				for (i = aini; i <= afim - (tamb); i++) {
					char* j, *jj;
					int flag = 1;

					for (j = i, jj = bini; j <= i + (tamb); j++, jj++) {

						if (*j != *jj) {
							flag = 0;
							break;
						}
					}

					if (flag) {		//encontrou
						return i;
					}

				}

				return NULL;
			}
			else
				return NULL;
		}
		else
			return NULL;
	}
	else
		return NULL;
}


char* memstr(char* aini, char* afim, char* str){

	return memmem2(aini, afim, str, str + strlen(str) - 1);
}


char* mmemchr(char* aini, char* afim, char chr) {

	if (aini && afim && aini <= afim) {
		return memchr(aini, chr, afim - aini + 1);
	}
	else
		return NULL;
}



char* memns(char* ini, char* fim) {

	if (ini && fim && fim >= ini) {
		char* pos = ini;

		while (pos <= fim && *pos == ' ') {
			pos++;
		}

		if (pos <= fim) {
			return pos;
		}
		else
			return NULL;
	}
	else
		return NULL;

}


/*
int mempstr(char* ini, char* fim, char* str){
	if (ini && fim && ini <= fim && str) {

		char* i = str;
		char* j = ini;

		while (*i && j <= fim && *i == *j) {
			i++;
			j++;
		}

		if (!(*i)) {
			return 1;
		}
		else
			return 0;

	}
}*/

// Checa se o bloco b(ini-fim) é prefixo do bloco a(ini-fim)
int mempmem(char* aini, char* afim, char* bini, char* bfim){
	if (aini && afim && aini <= afim && bini && bfim && bini <= bfim) {

		char* i = bini;
		char* j = aini;

		while (i <= bfim && j <= afim && *i == *j) {
			i++;
			j++;
		}

		if (i > bfim) {
			return 1;
		}
		else
			return 0;

	}
}




int memcmpmem(char* aini, char* afim, char* bini, char* bfim) {
	if (aini && afim && bini && bfim && (afim - aini) == (bfim - bini)) {
		char* i = aini;
		char* j = bini;

		while (i <= afim && j<= bfim && *i == *j) {
			i++;
			j++;
		}

		if (i > afim)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}


int memcmpstr(char* aini, char* afim, char* str) {

	return memcmpmem(aini, afim, str, str + strlen(str) - 1);
}




char* memtostr(char* ini, char* fim) {

	if (ini && fim) {

		if (fim >= ini) {

			size_t tam = fim - ini + 1;			// tamanho do bloco, não inclui o '\0' da string de retorno

			char* str = (char *) malloc( (tam + 1) * sizeof(char) );		// inclui o '\0' da string de retorno

			memcpy(str, ini, tam);
			str[tam] = '\0';

			return str;
		}
		else {		// em caso de inversão dos limites, retorna a string vazia

			char* str = (char *) malloc( sizeof(char) );		// inclui o '\0' da string de retorno

			str[0] = '\0';

			return str;
		}
	}

	return NULL;

}


void impmem(char* ini, char* fim) {
	if (ini && fim) {
		if (fim >= ini) {
			for (; ini != fim + 1; ini++){
				printf("%c", *ini);
			}
		}
	}
}




/*   Segmento   */




char* segseg(Segmento* seg1, Segmento* seg2){


}


int segcmpstr(Segmento* seg, char* str) {

	if (seg) {
		return memcmpstr(seg->ini, seg->fim, str);
	}
	else
		return 1;
}


char* segtostr(Segmento* seg) {

	if (seg) {
		return memtostr(seg->ini, seg->fim);
	}
	else
		return NULL;
}


void impseg(Segmento* seg){
	if (seg)
		impmem(seg->ini, seg->fim);
}


Segmento* strtoseg(char* str){

	if (str) {
		Segmento* seg = (Segmento *) malloc( sizeof(Segmento) );
		seg->ini = str;
		seg->fim = str + strlen(str) - 1;

		return seg;
	}
	else
		return NULL;
}


char* segchr(Segmento* seg, char chr) {
	if (seg && seg->fim < seg->ini){

		return memchr(seg->ini, chr, seg->fim - seg->ini + 1);
	}
	else
		return NULL;

}



Segmento* limites(char* str){

	if (str) {
		Segmento* seg = (Segmento *) malloc( sizeof(Segmento) );
		seg->ini = str;
		seg->fim = str + strlen(str) - 1;

		return seg;
	}

	return NULL;
}



Segmento* criarSegmento(char* ini, char* fim) {

	if (ini && fim) {
		Segmento* seg = (Segmento *) malloc(sizeof(Segmento));
		seg->ini = ini;
		seg->fim = fim;

		return seg;
	}

	return NULL;
}




#endif
