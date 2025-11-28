/* adm.h
 *
 * implementa métodos para geração da página de adm
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../lugar.h"




int paginaAdm(Usuario* usu, Sessao* sessao);



/*		Implementações		*/



int paginaAdm(Usuario* usu, Sessao* sessao) {

	if (usu && sessao) {

		Multilinhas* ml = mlCriar();

		char* caminho = concatstr(dirHtml, "/papeis/adm/adm.html");

		mlCarregarArquivoTexto(caminho, ml);

		// Instanciar caminhos de sistema e de páginas

		mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

		mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

		char ids[21];
		sprintf(ids, "%lld", sessao->idSessao);
		mlSubstituirTodos("$IDSESSAO$", ids, ml);

		mlImprimir(ml);

		return 0;

	}

	return 1;

}
