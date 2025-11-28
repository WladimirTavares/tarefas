/* papeis.h
 *
 * implementa métodos para geração da página inicial de escolha de papeis
 */


#include "../../str/bibstring2.h"
#include "../../str/multilinhas.h"

#include "../../lugar.h"



int paginaPapeis(Usuario* usu, Sessao* sessao);




/* Implemantações */



int paginaPapeis(Usuario* usu, Sessao* sessao) {

	if (usu && sessao) {
		Multilinhas* ml = mlCriar();

		char* caminho = concatstr(dirHtml, "/papeis/papeis.html");

		mlCarregarArquivoTexto(caminho, ml);

		// Instanciar caminhos de sistema e de páginas

		mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

		mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

		// Construir página

		NoLinha* nlCorpoPapeis = mlEncontrar("@corpoPapeis", ml);

		mlInserirAcima("<form method=\"post\">\n", nlCorpoPapeis, ml);

		// Checar as permissões do usuário e carregar os papeis disponíveis de acordo

		if (*(usu->habilitado)) {
			if (*(usu->adm)) {

				mlInserirAcima("<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"administrador\">Administrador</button>\n", nlCorpoPapeis, ml);
				mlInserirAcima("<br>\n", nlCorpoPapeis, ml);
			}

			if (*(usu->professor)) {

				mlInserirAcima("<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"professor\">Professor</button>\n", nlCorpoPapeis, ml);
				mlInserirAcima("<br>\n", nlCorpoPapeis, ml);
			}

			if (usu->numPerfis) {

				mlInserirAcima("<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"respondedor\">Respondedor</button>\n", nlCorpoPapeis, ml);
				mlInserirAcima("<br>\n", nlCorpoPapeis, ml);
			}

			if (*(usu->adm) == 0 && *(usu->professor) == 0 && usu->numPerfis == 0) {

				mlInserirAcima("<p>Não há recursos do sistema disponíveis para este usuário.<p>", nlCorpoPapeis, ml);
			}
		}
		else {

			// sair do sistema

			RegNoti* rn = criarRegNoti(1, "usuário não habilitado.");

			sairTarefas(sessao, rn);

			return 0;
		}


		char linhaIds[200];
		sprintf(linhaIds, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">", sessao->idSessao);
		mlInserirAcima(linhaIds, nlCorpoPapeis, ml);
		mlInserirAcima("</form>\n", nlCorpoPapeis, ml);

		char ids[21];
		sprintf(ids, "%lld", sessao->idSessao);
		mlSubstituirTodos("$IDSESSAO$", ids, ml);

		mlImprimir(ml);

		return 0;
	}

	return 1;
}
