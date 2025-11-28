/*
 * Implementa métodos para a geração de páginas html pelos scripst cgi principalmente visando a colocação dados refentes à sessão nas páginas
 *
 */


#ifndef SESSAOCGI_H
#define SESSAOCGI_H


#include "../str/bibstring2.h"
#include "../str/multilinhas.h"

#include "../lugar.h"



int incluirDadosSessao(Usuario* usu, Sessao* sessao, FormularioHTML* form,  Multilinhas* ml);



/*      Implementações      */



int incluirDadosSessao(Usuario* usu, Sessao* sessao, FormularioHTML* form,  Multilinhas* ml) {

    // colocar nome do usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// colocar numero da sessão

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cf->valor, ml);

	// colocar a url do site (botao sair)

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

    return 0;
}





#endif
