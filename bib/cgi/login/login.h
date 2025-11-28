/* login.h
 *
 * implementa métodos para geração da página de login
 */


#include "../../str/bibstring2.h"
#include "../../str/multilinhas.h"

#include "../../lugar.h"
#include "../../notifica.h"




int paginaLogin(char* destino, char* strConsulta, RegNoti* rn);


// Encerra a sessão
int sairTarefas(Sessao* sessao, RegNoti* rn);




/* Implemantações */



int paginaLogin(char* destino, char* strConsulta, RegNoti* rn) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/login/login.html");

	mlCarregarArquivoTexto(caminho ? caminho : "", ml);

	// Instanciar caminhos de sistema e de páginas

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	/*if (msg)
		mlSubstituirTodos("$MSG$", msg, ml);
	else
		mlSubstituirTodos("$MSG$", "", ml);
	*/

	char* caminhopagina = concatstr2(destino ? destino : "", strConsulta && strConsulta[0] != '\0' ? concatstr2("?", strConsulta) : "");
	if (caminhopagina)
		mlSubstituirTodos("$CAMINHOPAGINA$", caminhopagina, ml);
	else
		mlSubstituirTodos("$CAMINHOPAGINA$", "", ml);

	mlImprimir(ml);
}



int sairTarefas(Sessao* sessao, RegNoti* rn) {

	encerrarSessao(sessao);

	if (rn) {

		paginaLogin("", "", rn);

		return 1;
	}

	rn = criarRegNoti(0, "");

	paginaLogin("", "", rn);
}

