/* adm.h
 *
 * implementa métodos para geração da página de adm
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../lugar.h"
#include "../../../notifica.h"




int paginaRespondedor(Usuario* usu, Sessao* sessao, Usuario* usuPerfis, RegNoti* rn);

char* htmlFormPerfilRespondedor(Usuario* respondedor, PerfilRespondedor* perfil, char* idSessao);


int carregarPaginaRespondedor(Usuario* usu, Sessao* sessao, RegNoti* rn);



/*		Implementações		*/



int paginaRespondedor(Usuario* usu, Sessao* sessao, Usuario* usuPerfis, RegNoti* rn) {

	if (usu && sessao) {

		Multilinhas* ml = mlCriar();

		char* caminho = concatstr(dirHtml, "/papeis/respondedor/respondedor.html");

		mlCarregarArquivoTexto(caminho, ml);

		// Instanciar caminhos de sistema e de páginas

		mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

		mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

		char ids[21];
		sprintf(ids, "%lld", sessao->idSessao);
		mlSubstituirTodos("$IDSESSAO$", ids, ml);

		// colocar mensagem

        char* msg = msgNotiHTML(rn);

        mlSubstituirTodos("$MSG$", msg ? msg : "", ml);


		// listar perfis

		NoLinha* nlListaPerfis = mlEncontrar("@perfisRespondedor", ml);

		char* html = NULL;

		for (int i = 0; i < usuPerfis->numPerfis; i++) {

			//mlInserirAcima(llistr(*(usuPerfis->perfis[i].idPerfilRespondedor)), nlListaPerfis, ml);
			//mlInserirAcima("<br>", nlListaPerfis, ml);

			html = htmlFormPerfilRespondedor(usuPerfis, &(usuPerfis->perfis[i]), ids);

			mlInserirAcima(html, nlListaPerfis, ml);
			//mlInserirAcima("<br>", nlListaPerfis, ml);

		}

		mlImprimir(ml);

		return 0;

	}

	return 1;

}




char* htmlFormPerfilRespondedor(Usuario* respondedor, PerfilRespondedor* perfil, char* idSessao) {

    Multilinhas* ml = mlCriar();

    char linha[500] = "";

    // imprimir formulário do respondedor
    mlAnexarLinha("<form method=\"post\">\n", ml);

    sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"paginaperfilrespondedor\">%s - %s - (%s, %s, %s)</button>\n", respondedor->nome, respondedor->email, perfil->matricula, perfil->curso->codigo, perfil->curso->inst->sigla);
    mlAnexarLinha(linha, ml);

    char* idPerfilRespondedor = llistr(*(perfil->idPerfilRespondedor));

    sprintf(linha, "<input type=\"hidden\" name=\"idPerfilRespondedor\" value=\"%s\">\n", idPerfilRespondedor);
    mlAnexarLinha(linha, ml);

    //sprintf(linha, "<input type=\"hidden\" name=\"idTurma\" value=\"%s\">\n", idTurma);
    //mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%s\">\n", idSessao);
    mlAnexarLinha(linha, ml);

    mlAnexarLinha("</form>", ml);

    return mlExtrairTexto(ml);

}




int carregarPaginaRespondedor(Usuario* usu, Sessao* sessao, RegNoti* rn) {


	// resgatar id do usuário

	char* idUsuario = (char *) malloc(21 * sizeof(char));
	idUsuario[0] = '\0';

	if (usu->idUsuario) {
		sprintf(idUsuario, "%lld", *(usu->idUsuario));
	}
	else {
		sprintf(idUsuario, "%d", 0);
	}


	// buscar perfis no banco

	Usuario* perfisUsu = NULL;
	int numUsuarios = 0;

	int ret = bdBuscarUsuarioPerfilIdUsu(idUsuario, &perfisUsu, &numUsuarios);

	if (ret) {

		// erro ao tentar buscar perfis no banco

		RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar perfis do banco.");

        paginaPapeis(usu, sessao);
	}

	if (numUsuarios) {

		paginaRespondedor(usu, sessao, perfisUsu, NULL);

	}
	else {

		// não foram encontrados perfis associados a esse usuário

		RegNoti* rn = criarRegNoti(2, "Não há perfis associados a este usuário.");

        paginaPapeis(usu, sessao);
	}


}




