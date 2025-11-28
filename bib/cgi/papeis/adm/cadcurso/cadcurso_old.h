/* cadcurso.h
 *
 * implementa métodos para geração da página de adm
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../global.h"



int paginaCadcurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaNovoCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaVisualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int atualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);




/*		Implementações		*/




int paginaCadcurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

		Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadcurso/cadcurso.html");

	mlCarregarArquivoTexto(caminho, ml);

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// resgatar parâmetros de buscas

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "buscaCodigoCurso");
	char* codigoBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaNomeCurso");
	char* nomeBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaIdInst");
	char* idInstBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaObsCurso");
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

	if (!strcmp(cfAcao->valor, "buscarcurso")) {

		// buscar instituições no banco de dados

		Curso* cursos = NULL;
		int numCursos = 0;

		int ret = bdBuscarCurso(codigoBusca, nomeBusca, idInstBusca, obsBusca, &cursos, &numCursos);

		// montar lista de instituições resultado da busca

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		//char linha[200];
		sprintf(linha, "<p>Lista de Cursos</p>");
		mlInserirAcima(linha, nlResultadoBusca, ml);

		for (int i = 0; i < numCursos; i++) {

			mlInserirAcima("<form method=\"post\">", nlResultadoBusca, ml);

			sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"./cadcurso\" value=\"visucurso\">%s - %s - %s</button>\n", cursos[i].codigo, cursos[i].nome, cursos[i].inst->sigla );
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"idCurso\" value=\"%lld\">\n", *(cursos[i].idCurso));
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


int paginaNovoCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {


	Multilinhas* ml = mlCriar();

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "acao");

	int ret = 0;

	char* formaction = NULL;

	if (!strcmp(cf->valor, "salvarcurso")) {

		// gravar dados no banco

		cf = obterCampoFormularioHTML(form, "codigoCurso");
		char* codigo = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "nomeCurso");
		char* nome = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "idInstituicao");
		char* idInst = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "obsCurso");
		char* obs = cf ? cf->valor : "";

		codigo = aparar(&codigo);
		nome = aparar(&nome);
		idInst = aparar(&idInst);
		obs = aparar(&obs);

		if (strlen(codigo) != 0 && strlen(nome) != 0 && strlen(idInst) != 0) {
			long long int idCurso = 0;

			ret = bdCadastrarCurso (codigo, nome, idInst, obs, &idCurso);

			if (ret) {

				// erro na inserção

				msg = copiastr("<font color=\"#ff0000\">Erro na inserção do Curso.</font>");

				//paginaNovaInst(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível inserir instituição.</font>");
				//return ret;
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro

				paginaCadcurso(usu, sessao, form, "<font color=\"#0000ff\">Curso criado com sucesso.</font>");
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

	char* caminho = concatstr(dirHtml, "/adm/cadcurso/novocurso.html");

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


int paginaVisualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "acao");

	CampoFormularioHTML* cfIdCurso = obterCampoFormularioHTML(form, "idCurso");

	Curso* curso = NULL;
	int num;

	int ret = bdBuscarCursoId(cfIdCurso->valor, &curso, &num);

	if (ret) {

		paginaCadcurso(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar resgatar informações sobre o curso.</font>");
		return ret;
	}
	else {

		char* caminho = concatstr(dirHtml, "/adm/cadcurso/visucurso.html");

		mlCarregarArquivoTexto(caminho, ml);

		// Instanciar caminhos de sistema e de páginas

		mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

		// colocar mensagem

		mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

		// colocar dados do curso a ser visualizado no formulário

		mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

		mlSubstituirTodos("$IDCURSO$", cfIdCurso ? cfIdCurso->valor : "", ml);
		mlSubstituirTodos("$CODIGO$", curso ? curso->codigo : "", ml);
		mlSubstituirTodos("$NOME$", curso ? curso->nome : "", ml);
		//mlSubstituirTodos("$IDINSTITUICAO$", curso ? *(curso->inst->idInstituicao) : "", ml);
		mlSubstituirTodos("$OBS$", curso ? curso->obs : "", ml);

		// inserir opções de instituição, colocando como selecionada a instituição do curso visualizado

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		Instituicao* insts = NULL;
		int numInsts = 0;

		bdTodasInstituicoes(&insts, &numInsts);

		char elHtml[200];

		for (int i = 0; i < numInsts; i++) {
			if (*(curso->inst->idInstituicao) == *(insts[i].idInstituicao))
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


int atualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cfIdCurso = obterCampoFormularioHTML(form, "idCurso");
	CampoFormularioHTML* cfCodigoCurso = obterCampoFormularioHTML(form, "codigoCurso");
	CampoFormularioHTML* cfNomeCurso = obterCampoFormularioHTML(form, "nomeCurso");
	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInstituicao");
	CampoFormularioHTML* cfObsCurso = obterCampoFormularioHTML(form, "obsCurso");

	int ret = bdAtualizarCursoId(cfIdCurso->valor, cfCodigoCurso->valor, cfNomeCurso->valor, cfIdInst->valor, cfObsCurso->valor);

	if (ret) {
		paginaVisualizarCurso(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar atualizar informações sobre o curso.</font>");
		return ret;
	}
	else {
		paginaCadcurso(usu, sessao, form, "<font color=\"#0000ff\">Curso atualizado com sucesso.</font>");
		return ret;
	}

}


int removerCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cfIdCurso = obterCampoFormularioHTML(form, "idCurso");

	int ret = bdApagarCursoId(cfIdCurso->valor);

	if (ret) {
		paginaVisualizarCurso(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível remover o curso.</font>");
		return ret;
	}
	else {
		paginaCadcurso(usu, sessao, form, "<font color=\"#0000ff\">Curso removido com sucesso.</font>");
		return ret;
	}
}
