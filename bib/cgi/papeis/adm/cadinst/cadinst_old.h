/* cadinst.h
 *
 * implementa métodos para geração das paginas de cadastro de instituição
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../global.h"



int paginaCadinst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaNovaInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaVisualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int atualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);




/*		Implementações		*/





int paginaCadinst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadinst/cadinst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// colocar nome do usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// resgatar parâmetros de buscas, caso houver

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "buscaSiglaInstituicao");
	char* siglaBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaNomeInstituicao");
	char* nomeBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaObsInstituicao");
	char* obsBusca = cf ? cf->valor : "";

	// copiar parâmetros nas caixas de texto

	mlSubstituirTodos("$SIGLABUSCA$", siglaBusca ? siglaBusca : "", ml);
	mlSubstituirTodos("$NOMEBUSCA$", nomeBusca ? nomeBusca : "", ml);
	mlSubstituirTodos("$OBSBUSCA$", obsBusca ? obsBusca : "", ml);

	// colocar numero da sessão

	cf = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cf->valor, ml);

	// colocar a url do site (botao sair)

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	char linha[200];

	// checar se houve solicitação de busca

	CampoFormularioHTML* cfAcao = obterCampoFormularioHTML(form, "acao");

	if (!strcmp(cfAcao->valor, "buscarinst")) {

		// checar validade de caracteres

		if (utf8Val(siglaBusca, CHARNOME, NULL)) {
			// caracteres inválidos na sigla

			//msg = copiastr("<font color=\"#0000ff\">Caractere inválido na sigla.</font>");
			mlSubstituirTodos("$MSG$", "<font color=\"#ff0000\">Caractere inválido na sigla.</font>", ml);
			mlImprimir(ml);
			return 0;
		}
		else if (utf8Val(nomeBusca, CHARNOME, NULL)) {
			// caracteres inválidos no nome

			//msg = copiastr("<font color=\"#0000ff\">Caractere inválido no nome.</font>");
			mlSubstituirTodos("$MSG$", "<font color=\"#ff0000\">Caractere inválido no nome.</font>", ml);
			mlImprimir(ml);
			return 0;
		}
		else if (utf8Val(obsBusca, ALFANUMEXT, NULL)) {
			// caracteres inválidos na observação

			//msg = copiastr("<font color=\"#0000ff\">Caractere inválido na observação.</font>");
			mlSubstituirTodos("$MSG$", "<font color=\"#ff0000\">Caractere inválido na observação.</font>", ml);
			mlImprimir(ml);
			return 0;
		}


		// buscar instituições no banco de dados

		Instituicao* insts = NULL;
		int numInsts = 0;

		int ret = bdBuscarInstituicao(siglaBusca, nomeBusca, obsBusca, &insts, &numInsts);

		// montar lista de instituições resultado da busca

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		//char linha[200];
		sprintf(linha, "<p>Lista de Instituições</p>");
		mlInserirAcima(linha, nlResultadoBusca, ml);

		for (int i = 0; i < numInsts; i++) {

			mlInserirAcima("<form method=\"post\">", nlResultadoBusca, ml);

			sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"./cadinst\" value=\"visuinst\">%s - %s</button>\n", insts[i].sigla, insts[i].nome );
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"idInst\" value=\"%lld\">\n", *(insts[i].idInstituicao));
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);
			mlInserirAcima("</form>", nlResultadoBusca, ml);
			//mlInserirAcima("<br>\n", nlCorpoMenuAdm, ml);
		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);

	}

	// colocar mensagem

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	mlImprimir(ml);

}


int paginaNovaInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();

	CampoFormularioHTML* cfAcao = obterCampoFormularioHTML(form, "acao");

	int ret = 0;

	char* formaction = NULL;

	// resgatar valores dos campos, caso haja

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "siglaInstituicao");
	char* sigla = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "nomeInstituicao");
	char* nome = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "obsInstituicao");
	char* obs = cf ? cf->valor : "";

	if (!strcmp(cfAcao->valor, "salvarinst")) {

		// gravar dados no banco

		sigla = aparar(&sigla);
		nome = aparar(&nome);
		obs = aparar(&obs);

		if (strlen(sigla) != 0 && strlen(nome) != 0) {
			long long int idInst = 0;

			ret = bdCadastrarInstituicao (sigla, nome, obs, &idInst);

			if (ret) {

				// erro na inserção

				msg = copiastr("<font color=\"#ff0000\">Erro na inserção da Instituição. Instituições diferentes não podem ter o mesmo nome ou sigla.</font>");

				//paginaNovaInst(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível inserir instituição.</font>");
				//return ret;
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro

				paginaCadinst(usu, sessao, form, "<font color=\"#0000ff\">Instituição criada com sucesso.</font>");
				return ret;
			}
		}
		else {

			//paginaNova(usu, sessao, form, "<font color=\"#ff0000\">Sigla ou Nome inválidos.</font>");
			msg = copiastr("<font color=\"#ff0000\">Sigla ou Nome inválidos.</font>");
			ret = 1;
		}

	}

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadinst/novainst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// Instanciar caminhos de sistema e de páginas

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar mensagem

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// colocar usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// repetir valores dos campo, caso haja

	mlSubstituirTodos("$SIGLA$", sigla, ml);
	mlSubstituirTodos("$NOME$", nome, ml);
	mlSubstituirTodos("$OBS$", obs, ml);

	CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cfIds->valor, ml);


	mlImprimir(ml);

	return ret;

}


int paginaVisualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "acao");

	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");

	Instituicao* inst = NULL;
	int num;

	int ret = bdBuscarInstituicaoId(cfIdInst->valor, &inst, &num);


	if (ret) {

		paginaCadinst(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar resgatar informações sobre a instituição.</font>");
		return ret;
	}
	else {

		char* caminho = concatstr(dirHtml, "/adm/cadinst/visuinst.html");

		mlCarregarArquivoTexto(caminho, ml);

		// Instanciar caminhos de sistema e de páginas

		mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

		// colocar mensagem

		mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

		// copiar parâmetros nas caixas de texto

		mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

		mlSubstituirTodos("$IDINST$", cfIdInst ? cfIdInst->valor : "", ml);
		mlSubstituirTodos("$SIGLA$", inst ? inst->sigla : "", ml);
		mlSubstituirTodos("$NOME$", inst ? inst->nome : "", ml);
		mlSubstituirTodos("$OBS$", inst ? inst->obs : "", ml);

		CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
		mlSubstituirTodos("$IDSESSAO$", cfIds->valor, ml);

		mlImprimir(ml);

		return ret;
	}
}


int atualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");
	CampoFormularioHTML* cfSiglaInst = obterCampoFormularioHTML(form, "siglaInstituicao");
	CampoFormularioHTML* cfNomeInst = obterCampoFormularioHTML(form, "nomeInstituicao");
	CampoFormularioHTML* cfObsInst = obterCampoFormularioHTML(form, "obsInstituicao");

	int ret = bdAtualizarInstId(cfIdInst->valor, cfSiglaInst->valor, cfNomeInst->valor, cfObsInst->valor);

	if (ret) {
		paginaVisualizarInst(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar atualizar informações sobre a instituição.</font>");
		return ret;
	}
	else {
		paginaCadinst(usu, sessao, form, "<font color=\"#0000ff\">Instituição atualizada com sucesso.</font>");
		return ret;
	}

}


int removerInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");

	int ret = bdApagarInstId(cfIdInst->valor);

	if (ret) {
		paginaVisualizarInst(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível remover a instituição.<br> Deve haver Curso, Disciplina ou Respondedor associados a esta Instituição.</font>");
		return ret;
	}
	else {
		paginaCadinst(usu, sessao, form, "<font color=\"#0000ff\">Instituição removida com sucesso.</font>");
		return ret;
	}
}
