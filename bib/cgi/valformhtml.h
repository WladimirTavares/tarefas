/*
 * Implementa métodos para extração e validação de campos de
 * formulário HTML, com a criação da notificação em caso de erro.
 *
 */


#ifndef VALFORMHTML_H
#define VALFORMHTML_H


#include "../../../bibcgi/formhtmlcgi.h"
#include "../str/bibstring2.h"
#include "../notifica.h"

/*
 * Retorna valor do campo do formulário HTML form, checando se os caracteres fazem parte do gabarito.
 * Caso o campo não exista, ou haja algum erro na recuperação do valor do campo, ou os caracteres do campo
 * não sejam validados, retorna NULL, gerando o registro de notificação correspondente (pode utilizar desccampo
 * para construir a mensagem de erro da notificação).
 *
 *
 * Caso de uso:
 *
 *
 * RegNoti* rn = NULL;
 *
 * char* idTarefa = NULL;
 * if (!(idTarefa = obterCFHVal("idTarefa", form, "id da tarefa", CHARDIG, &rn))) {
 * 		// Erro na obtenção do valor do campo do formulário
 * 		...
 * 		return rn->numnoti;
 * }
 *
 *
 *
 *
 */

char* obterCFHVal(char* nomecampo, FormularioHTML* form, char* desccampo, char* gabarito, RegNoti** rn);

char* obterCFHTML(char* nomecampo, FormularioHTML* form);








char* obterCFHVal(char* nomecampo, FormularioHTML* form, char* desccampo, char* gabarito, RegNoti** rn) {


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, nomecampo);
	char* msg;

	if (cf) {

		// campo existe

		if (cf->valor) {

			// valor do campo recuperado

			if (gabarito) {

				if (utf8Val(cf->valor, gabarito, NULL)) {

					// caractere inválido

					if (rn) {
						msg = concatstr2("Caractere inválido no ", desccampo);
						*rn = criarRegNoti(1, msg);
					}

					return NULL;
				}

			}

			// campo obtido com sucesso

			if (rn) {
				*rn = NULL;
			}

			return cf->valor;
		}

		// erro ao recuperar valor do campo

		if (rn) {
			msg = concatstr2("Erro ao tentar obter valor do ", desccampo);
			*rn = criarRegNoti(2, msg);
		}

		return NULL;
	}

	// campo não existe

	if (rn) {
		msg = concatstr2("Campo não existe: ", concatstr2(nomecampo, "."));
		*rn = criarRegNoti(3, msg);
	}

	return NULL;
}


char* obterCFHTML(char* nomecampo, FormularioHTML* form) {

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, nomecampo);

	if (!cf)
		return NULL;
	
	return cf->valor;
}



#endif
