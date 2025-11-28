/* cadinst.h
 *
 * implementa métodos para geração das paginas de cadastro de instituição
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../global.h"



int buscarInst2( Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaCadinst2(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg, Instituicao* insts, int numInsts);

int salvarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaNovaInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaVisualizarInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg, Instituicao* inst);

int atualizarInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form);




/*		Implementações		*/


int buscarInst2( Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	// resgatar parâmetros de buscas, caso houver

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "buscaSiglaInstituicao");
	char* siglaBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaNomeInstituicao");
	char* nomeBusca = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "buscaObsInstituicao");
	char* obsBusca = cf ? cf->valor : "";


	Instituicao* insts = NULL;
	int numInsts = 0;


	// checar validade de caracteres

	if (utf8Val(siglaBusca, CHARNOME, NULL)) {
		// caracteres inválidos na sigla

		msg = copiastr("<font color=\"#ff0000\">Caractere inválido na sigla.</font>");
		//mlSubstituirTodos("$MSG$", "<font color=\"#ff0000\">Caractere inválido na sigla.</font>", ml);
		//mlImprimir(ml);
		//return 0;
	}
	else if (utf8Val(nomeBusca, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		msg = copiastr("<font color=\"#ff0000\">Caractere inválido no nome.</font>");
		//mlSubstituirTodos("$MSG$", "<font color=\"#ff0000\">Caractere inválido no nome.</font>", ml);
		//mlImprimir(ml);
		//return 0;
	}
	else if (utf8Val(obsBusca, ALFANUMEXT, NULL)) {
		// caracteres inválidos na observação

		msg = copiastr("<font color=\"#ff0000\">Caractere inválido na observação.</font>");
		//mlSubstituirTodos("$MSG$", "<font color=\"#ff0000\">Caractere inválido na observação.</font>", ml);
		//mlImprimir(ml);
		//return 0;
	}
	else {

		// buscar instituições no banco de dados

		int ret = bdBuscarInstituicao(siglaBusca, nomeBusca, obsBusca, &insts, &numInsts);

		if (ret) {
			msg = copiastr("<font color=\"#ff0000\">Não foi possível buscar as instituições.</font>");

			insts = NULL;
			numInsts = 0;
		}
	}

	paginaCadinst2(usu, sessao, form, msg, insts, numInsts);

	return 0;
}




int paginaCadinst2(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg, Instituicao* insts, int numInsts) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadinst/cadinst.html");

	mlCarregarArquivoTexto(caminho, ml);

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

	// colocar nome do usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// colocar numero da sessão

	cf = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cf->valor, ml);

	// colocar a url do site (botao sair)

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

	if (insts) {

		char linha[200];

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

int paginaCadinst2old(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

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


int salvarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	// resgatar valores dos campos, caso haja

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "siglaInstituicao");
	char* sigla = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "nomeInstituicao");
	char* nome = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "obsInstituicao");
	char* obs = cf ? cf->valor : "";

	int ret = 0;

	// checar validade de caracteres

	if (utf8Val(sigla, CHARNOME, NULL)) {
		// caracteres inválidos na sigla

		msg = copiastr("<font color=\"#ff0000\">Caractere inválido na sigla.</font>");
	}
	else if (utf8Val(nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		msg = copiastr("<font color=\"#ff0000\">Caractere inválido no nome.</font>");
	}
	else if (utf8Val(obs, ALFANUMEXT, NULL)) {
		// caracteres inválidos na observação

		msg = copiastr("<font color=\"#ff0000\">Caractere inválido na observação.</font>");
	}
	else {

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
			}
			else {
				// inserção realizada com sucesso, volta para a página de cadastro

				paginaCadinst2(usu, sessao, form, "<font color=\"#0000ff\">Instituição criada com sucesso.</font>", NULL, 0);
				return ret;
			}
		}
		else {

			//paginaNova(usu, sessao, form, "<font color=\"#ff0000\">Sigla ou Nome inválidos.</font>");
			msg = copiastr("<font color=\"#ff0000\">Sigla ou Nome inválidos.</font>");
			ret = 1;
		}
	}

	paginaNovaInst2(usu, sessao, form, msg);
	return ret;
}


int paginaNovaInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "siglaInstituicao");
	char* sigla = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "nomeInstituicao");
	char* nome = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "obsInstituicao");
	char* obs = cf ? cf->valor : "";


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

	return 0;
}


int paginaNovaInst2old(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

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

				paginaCadinst2(usu, sessao, form, "<font color=\"#0000ff\">Instituição criada com sucesso.</font>", NULL, 0);
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


int visualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");

	if (cfIdInst) {

		char* idInst = cfIdInst->valor;

		if (utf8Val(idInst, CHARDIG, NULL)) {
			// caracteres inválidos na sigla

			paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Caractere inválido no identificador de instituição.</font>", NULL, 0);
			return 1;
		}

		Instituicao* inst = NULL;
		int num;

		int ret = bdBuscarInstituicaoId(cfIdInst->valor, &inst, &num);

		if (ret) {
			paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar resgatar informações sobre a instituição.</font>", NULL, 0);
			return 2;
		}
		else {
			paginaVisualizarInst2(usu, sessao, form, msg, inst);
			return 0;
		}
	}
	else {
		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar receber instituição do formulário.</font>", NULL, 0);
		return 3;
	}

}


int paginaVisualizarInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg, Instituicao* inst) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/adm/cadinst/visuinst.html");

	mlCarregarArquivoTexto(caminho, ml);


	// Instanciar caminhos de sistema e de páginas

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar mensagem

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// copiar parâmetros nas caixas de texto

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// colocar id da sessao

	CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cfIds->valor, ml);


	if (inst) {
		CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");

		mlSubstituirTodos("$IDINST$", cfIdInst ? cfIdInst->valor : "", ml);
		mlSubstituirTodos("$SIGLA$", inst ? inst->sigla : "", ml);
		mlSubstituirTodos("$NOME$", inst ? inst->nome : "", ml);
		mlSubstituirTodos("$OBS$", inst ? inst->obs : "", ml);
	}
	else {		// caso houve falha na atualização

		// repetir valores dos campos

		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idInst");
		char* idInst = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "siglaInstituicao");
		char* sigla = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "nomeInstituicao");
		char* nome = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "obsInstituicao");
		char* obs = cf ? cf->valor : "";

		mlSubstituirTodos("$IDINST$", idInst, ml);
		mlSubstituirTodos("$SIGLA$", sigla, ml);
		mlSubstituirTodos("$NOME$", nome, ml);
		mlSubstituirTodos("$OBS$", obs, ml);

	}

	mlImprimir(ml);
}


int paginaVisualizarInst2old(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	Multilinhas* ml = mlCriar();


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "acao");

	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");

	Instituicao* inst = NULL;
	int num;

	int ret = bdBuscarInstituicaoId(cfIdInst->valor, &inst, &num);


	if (ret) {

		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar resgatar informações sobre a instituição.</font>", NULL, 0);
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


int atualizarInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form) {


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idInst");
	char* idInst = cf ? cf->valor : "";

	if (utf8Val(idInst, CHARDIG, NULL)) {
		// caracteres inválidos no id da instituição

		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Caractere inválido no identificador de instituição.</font>", NULL, 0);
		return 1;
	}

	cf = obterCampoFormularioHTML(form, "siglaInstituicao");
	char* sigla = cf ? cf->valor : "";

	if (utf8Val(sigla, CHARNOME, NULL)) {
		// caracteres inválidos na sigla

		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Caractere inválido na sigla.</font>", NULL, 0);
		return 1;
	}

	cf = obterCampoFormularioHTML(form, "nomeInstituicao");
	char* nome = cf ? cf->valor : "";

	if (utf8Val(nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Caractere inválido no nome.</font>", NULL, 0);
		return 1;
	}

	cf = obterCampoFormularioHTML(form, "obsInstituicao");
	char* obs = cf ? cf->valor : "";

	if (utf8Val(obs, CARVALSML, NULL)) {
		// caracteres inválidos na observação

		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Caractere inválido na observação.</font>", NULL, 0);
		return 1;
	}


	int ret = bdAtualizarInstId(idInst, sigla, nome, obs);

	if (ret) {
		paginaVisualizarInst2(usu, sessao, form, "<font color=\"#ff0000\">Erro ao tentar atualizar informações sobre a instituição.</font>", NULL);
		return ret;
	}
	else {
		paginaCadinst2(usu, sessao, form, "<font color=\"#0000ff\">Instituição atualizada com sucesso.</font>", NULL, 0);
		return ret;
	}

}


int removerInst2(Usuario* usu, Sessao* sessao, FormularioHTML* form) {


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idInst");
	char* idInst = cf ? cf->valor : "";

	if (utf8Val(idInst, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		paginaCadinst2(usu, sessao, form, "<font color=\"#ff0000\">Caractere inválido no identificador de instituição.</font>", NULL, 0);
		return 1;
	}


	int ret = bdApagarInstId(cf->valor);

	if (ret) {
		paginaVisualizarInst2(usu, sessao, form, "<font color=\"#ff0000\">Não foi possível remover a instituição.<br> Deve haver Curso, Disciplina ou Respondedor associados a esta Instituição.</font>", NULL);
		return ret;
	}
	else {
		paginaCadinst2(usu, sessao, form, "<font color=\"#0000ff\">Instituição removida com sucesso.</font>", NULL, 0);
		return ret;
	}
}
