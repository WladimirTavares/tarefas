/* caddisc.h
 *
 * implementa métodos para geração da página de cadastro de disciplinas
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../global.h"





int paginaCaddisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaNovaDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaVisualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int atualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);





/*		Implementações		*/





int paginaCaddisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/caddisc/caddisc.html");

	mlCarregarArquivoTexto(caminho, ml);

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// resgatar parâmetros de buscas

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "buscaCodigoDisciplina");
	char* codigoBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaNomeDisciplina");
	char* nomeBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaIdInst");
	char* idInstBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaObsDisciplina");
	char* obsBusca = cf ? cf->valor : "";

	// copiar parâmetros nas caixas de texto

	mlSubstituirTodos("$CODIGOBUSCA$", codigoBusca ? codigoBusca : "", ml);
	mlSubstituirTodos("$NOMEBUSCA$", nomeBusca ? nomeBusca : "", ml);
	mlSubstituirTodos("$IDINSTBUSCA$", idInstBusca ? idInstBusca : "", ml);
	mlSubstituirTodos("$OBSBUSCA$", obsBusca ? obsBusca : "", ml);

	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	Instituicao* insts = NULL;
	int numInsts = 0;

	bdTodasInstituicoes(&insts, &numInsts);

	char elHtml[200];

	sprintf(elHtml, "<option value=\"\">-</option>@OpcoesInst");
	mlSubstituirTodosEmLinha("@OpcoesInst", elHtml, nl);
	for (int i = 0; i < numInsts; i++) {
		sprintf(elHtml, "<option value=%lld>%s</option>@OpcoesInst", *(insts[i].idInstituicao), insts[i].sigla);
		mlSubstituirTodosEmLinha("@OpcoesInst", elHtml, nl);
	}

	mlSubstituirTodosEmLinha("@OpcoesInst", "", nl);

	// colocar numero da sessão

	cf = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cf->valor, ml);

	// colocar mensagem

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// colocar a url do site
	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	char linha[200];

	// checar se houve solicitação de busca

	CampoFormularioHTML* cfAcao = obterCampoFormularioHTML(form, "acao");

	if (!strcmp(cfAcao->valor, "buscardisc")) {

		// buscar instituições no banco de dados

		Disciplina* disciplinas = NULL;
		int numDisciplinas = 0;

		int ret = bdBuscarDisciplina(codigoBusca, nomeBusca, idInstBusca, obsBusca, &disciplinas, &numDisciplinas);

		// montar lista de instituições resultado da busca

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		//char linha[200];
		sprintf(linha, "<p>Lista de Disciplinas</p>");
		mlInserirAcima(linha, nlResultadoBusca, ml);

		for (int i = 0; i < numDisciplinas; i++) {

			mlInserirAcima("<form method=\"post\">", nlResultadoBusca, ml);

			sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"./caddisc\" value=\"visudisc\">%s - %s - %s</button>\n", disciplinas[i].codigo, disciplinas[i].nome, disciplinas[i].inst->sigla );
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"idDisciplina\" value=\"%lld\">\n", *(disciplinas[i].idDisciplina));
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);
			mlInserirAcima("</form>", nlResultadoBusca, ml);
			//mlInserirAcima("<br>\n", nlCorpoMenuAdm, ml);
		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);

	}

	mlImprimir(ml);

}


int paginaNovaDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {


	Multilinhas* ml = mlCriar();

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "acao");

	int ret = 0;

	char* formaction = NULL;

	if (!strcmp(cf->valor, "salvardisc")) {

		// gravar dados no banco

		cf = obterCampoFormularioHTML(form, "codigoDisciplina");
		char* codigo = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "nomeDisciplina");
		char* nome = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "idInstituicao");
		char* idInst = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "obsDisciplina");
		char* obs = cf ? cf->valor : "";

		codigo = aparar(&codigo);
		nome = aparar(&nome);
		idInst = aparar(&idInst);
		obs = aparar(&obs);

		if (strlen(codigo) != 0 && strlen(nome) != 0 && strlen(idInst) != 0) {
			long long int idDisciplina = 0;

			ret = bdCadastrarDisciplina (codigo, nome, idInst, obs, &idDisciplina);

			if (ret) {

				// erro na inserção

				msg = copiastr("<font color=\"#ff0000\">Erro na inserção da Disciplina.</font>");

				//paginaNovaInst(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível inserir instituição.</font>");
				//return ret;
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro

				paginaCaddisc(usu, sessao, form, "<font color=\"#0000ff\">Disciplina criada com sucesso.</font>");
				return ret;
			}
		}
		else {

			//paginaNova(usu, sessao, form, "<font color=\"#ff0000\">Sigla ou Nome inválidos.</font>");
			msg = copiastr("<font color=\"#ff0000\">Código, Nome ou Instituição inválidos.</font>");
			ret = 1;
		}

	}

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/caddisc/novadisc.html");

	mlCarregarArquivoTexto(caminho, ml);

	// Instanciar caminhos de sistema e de páginas

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar mensagem

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// colocar usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cfIds->valor, ml);


	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	Instituicao* insts = NULL;
	int numInsts = 0;

	bdTodasInstituicoes(&insts, &numInsts);

	char elHtml[200];

	for (int i = 0; i < numInsts; i++) {
		sprintf(elHtml, "<option value=%lld>%s</option>@OpcoesInst", *(insts[i].idInstituicao), insts[i].sigla);
		mlSubstituirTodosEmLinha("@OpcoesInst", elHtml, nl);
	}

	mlSubstituirTodosEmLinha("@OpcoesInst", "", nl);

	mlImprimir(ml);

	return ret;

}


int paginaVisualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "acao");

	CampoFormularioHTML* cfIdDisc = obterCampoFormularioHTML(form, "idDisciplina");

	Disciplina* disciplina = NULL;
	int num;

	int ret = bdBuscarDisciplinaId(cfIdDisc->valor, &disciplina, &num);

	if (ret) {

		paginaCaddisc(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar resgatar informações sobre o curso.</font>");
		return ret;
	}
	else {

		char* caminho = concatstr(dirHtml, "/adm/caddisc/visudisc.html");

		mlCarregarArquivoTexto(caminho, ml);

		// Instanciar caminhos de sistema e de páginas

		mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

		// colocar mensagem

		mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

		// colocar dados do curso a ser visualizado no formulário

		mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

		mlSubstituirTodos("$IDDISCIPLINA$", cfIdDisc ? cfIdDisc->valor : "", ml);
		mlSubstituirTodos("$CODIGO$", disciplina ? disciplina->codigo : "", ml);
		mlSubstituirTodos("$NOME$", disciplina ? disciplina->nome : "", ml);
		//mlSubstituirTodos("$IDINSTITUICAO$", curso ? *(curso->inst->idInstituicao) : "", ml);
		mlSubstituirTodos("$OBS$", disciplina ? disciplina->obs : "", ml);

		// inserir opções de instituição, colocando como selecionada a instituição do curso visualizado

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		Instituicao* insts = NULL;
		int numInsts = 0;

		bdTodasInstituicoes(&insts, &numInsts);

		char elHtml[200];

		for (int i = 0; i < numInsts; i++) {
			if (*(disciplina->inst->idInstituicao) == *(insts[i].idInstituicao))
				sprintf(elHtml, "<option value=%lld selected>%s</option>@OpcoesInst", *(insts[i].idInstituicao), insts[i].sigla);
			else
				sprintf(elHtml, "<option value=%lld>%s</option>@OpcoesInst", *(insts[i].idInstituicao), insts[i].sigla);
			mlSubstituirTodosEmLinha("@OpcoesInst", elHtml, nl);
		}

		mlSubstituirTodosEmLinha("@OpcoesInst", "", nl);

		// colocar id da sessão

		CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
		mlSubstituirTodos("$IDSESSAO$", cfIds->valor, ml);

		mlImprimir(ml);

		return ret;
	}
}


int atualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cfIdDisc = obterCampoFormularioHTML(form, "idDisciplina");
	CampoFormularioHTML* cfCodigoDisc = obterCampoFormularioHTML(form, "codigoDisciplina");
	CampoFormularioHTML* cfNomeDisc = obterCampoFormularioHTML(form, "nomeDisciplina");
	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInstituicao");
	CampoFormularioHTML* cfObsDisc = obterCampoFormularioHTML(form, "obsDisciplina");

	int ret = bdAtualizarDisciplinaId(cfIdDisc->valor, cfCodigoDisc->valor, cfNomeDisc->valor, cfIdInst->valor, cfObsDisc->valor);

	if (ret) {
		paginaVisualizarDisc(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar atualizar informações sobre a disciplina.</font>");
		return ret;
	}
	else {
		paginaCaddisc(usu, sessao, form, "<font color=\"#0000ff\">Disciplina atualizada com sucesso.</font>");
		return ret;
	}

}


int removerDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cfIdDisc = obterCampoFormularioHTML(form, "idDisciplina");

	int ret = bdApagarDisciplinaId(cfIdDisc->valor);

	if (ret) {
		paginaVisualizarDisc(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível remover a disciplina.</font>");
		return ret;
	}
	else {
		paginaCaddisc(usu, sessao, form, "<font color=\"#0000ff\">Disciplina removida com sucesso.</font>");
		return ret;
	}
}
