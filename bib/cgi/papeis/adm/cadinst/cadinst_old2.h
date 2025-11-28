/* cadinst.h
 *
 * implementa métodos para geração das paginas de cadastro de instituição
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../global.h"
#include "../../../notifica.h"


typedef struct FormInstituicao {
	char* sigla;
	char* nome;
	char* obs;
} FormInstituicao;



// extrai informações do formulário html
void extrairFormularioInstituicao(FormularioHTML* form, FormInstituicao** forminst);

int validarFormularioInstituicao(FormInstituicao* forminst, char** msg);

int buscarInst( Usuario* usu, Sessao* sessao, FormularioHTML* form);

/*
int buscarInst_old( Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaCadinst_old(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg, Instituicao* insts, int numInsts);
*/

int paginaCadinst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* insts, int numInsts);

int salvarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int paginaNovaInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn);

int visualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg);

int paginaVisualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* inst);

int atualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);




/*		Implementações		*/



void extrairFormularioInstituicao(FormularioHTML* form, FormInstituicao** forminst){

	// extrair dados do formulário html

	FormInstituicao* fi = (FormInstituicao *) malloc( sizeof(FormInstituicao) );

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "sigla");
	fi->sigla = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "nome");
	fi->nome = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "obs");
	fi->obs = cf ? cf->valor : copiastr("");

	*forminst = fi;
}


int validarFormularioInstituicao(FormInstituicao* forminst, char** msg) {

	// checar validade de caracteres

	if (utf8Val(forminst->sigla, CHARNOME, NULL)) {
		// caracteres inválidos na sigla

		if (msg)
			*msg = copiastr("Caractere inválido na sigla.");

		return 1;
	}
	else if (utf8Val(forminst->nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		if (msg)
			*msg = copiastr("Caractere inválido no nome.");

		return 2;
	}
	else if (utf8Val(forminst->obs, ALFANUMEXT, NULL)) {
		// caracteres inválidos na observação

		if (msg)
			*msg = copiastr("Caractere inválido na observação.");

		return 3;
	}
	else {

		if (msg)
			*msg = NULL;

		return 0;
	}
}






/*
int buscarInst_old( Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

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

	paginaCadinst_old(usu, sessao, form, msg, insts, numInsts);

	return 0;
}
*/



int buscarInst( Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// resgatar parâmetros de buscas, caso hajam

	FormInstituicao* fi = NULL;
	char* msg = NULL;

	extrairFormularioInstituicao(form, &fi);

	int numerr = validarFormularioInstituicao(fi, &msg);

	// se os dados foram validados, buscar instituições no banco

	Instituicao* insts = NULL;
	int numInsts = 0;

	if (!numerr) {
		// buscar instituições no banco de dados

		int ret = bdBuscarInstituicao(fi->sigla, fi->nome, fi->obs, &insts, &numInsts);

		if (ret) {
			msg = copiastr("Não foi possível buscar as instituições.");

			insts = NULL;
			numInsts = 0;

			numerr = ret;
		}

	}

	RegNoti* rn = criarRegNoti(numerr, msg);

	paginaCadinst(usu, sessao, form, fi, rn, insts, numInsts);

	return 0;
}


/*
int paginaCadinst_old(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg, Instituicao* insts, int numInsts) {

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
*/




int paginaCadinst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* insts, int numInsts) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadinst/cadinst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// colocar nome do usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// colocar numero da sessão

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cf->valor, ml);

	// colocar a url do site (botao sair)

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar notificação

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// resgatar parâmetros de buscas, caso necessário

	if (forminst == NULL)
		extrairFormularioInstituicao(form, &forminst);

	// copiar parâmetros nas caixas de texto

	mlSubstituirTodos("$SIGLABUSCA$", forminst->sigla, ml);
	mlSubstituirTodos("$NOMEBUSCA$", forminst->nome, ml);
	mlSubstituirTodos("$OBSBUSCA$", forminst->obs, ml);

	// listar resultado da busca

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

	mlImprimir(ml);
}


int salvarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// resgatar valores dos campos, caso hajam

	FormInstituicao* fi = NULL;
	char* msg = NULL;

	extrairFormularioInstituicao(form, &fi);

	// checar validade de caracteres

	int ret = validarFormularioInstituicao(fi, &msg);

	if (!ret) {

		// gravar dados no banco

		fi->sigla = aparar(&(fi->sigla));
		fi->nome = aparar(&(fi->nome));
		fi->obs = aparar(&(fi->obs));

		if (strlen(fi->sigla) != 0 && strlen(fi->nome) != 0) {
			long long int idInst = 0;

			ret = bdCadastrarInstituicao (fi->sigla, fi->nome, fi->obs, &idInst);

			if (ret) {
				// erro na inserção

				msg = copiastr("Erro na inserção da Instituição. Instituições diferentes não podem ter o mesmo nome ou sigla.");
			}
			else {
				// inserção realizada com sucesso, volta para a página de cadastro

				msg = copiastr("Instituição criada com sucesso.");
				RegNoti* rn = criarRegNoti(0, msg);

				paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
				return 0;
			}
		}
		else {

			//paginaNova(usu, sessao, form, "<font color=\"#ff0000\">Sigla ou Nome inválidos.</font>");
			msg = copiastr("Sigla ou Nome inválidos.");
			ret = 1;
		}
	}

	RegNoti* rn = criarRegNoti(ret, msg);

	paginaNovaInst(usu, sessao, form, fi, rn);
	return ret;
}


int paginaNovaInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn) {


	// carregar modelo

	Multilinhas* ml = mlCriar();

	/*
	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "siglaInstituicao");
	char* sigla = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "nomeInstituicao");
	char* nome = cf ? cf->valor : "";

	cf = obterCampoFormularioHTML(form, "obsInstituicao");
	char* obs = cf ? cf->valor : "";
	*/

	char* caminho = concatstr(dirHtml, "/adm/cadinst/novainst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// Instanciar caminhos de sistema e de páginas

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar notificação

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// colocar usuário

	mlSubstituirTodos("$USUARIOLOGIN$", usu->login, ml);

	// colocar id da sessão

	CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
	mlSubstituirTodos("$IDSESSAO$", cfIds->valor, ml);

	// resgatar dados dos formulário html, caso necessário

	if (!forminst)
		extrairFormularioInstituicao(form, &forminst);

	// repetir valores dos campo, caso haja

	mlSubstituirTodos("$SIGLA$", forminst->sigla, ml);
	mlSubstituirTodos("$NOME$", forminst->nome, ml);
	mlSubstituirTodos("$OBS$", forminst->obs, ml);


	mlImprimir(ml);

	return 0;
}



int visualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* msg) {

	CampoFormularioHTML* cfIdInst = obterCampoFormularioHTML(form, "idInst");

	RegNoti* rn = NULL;

	if (cfIdInst) {

		char* idInst = cfIdInst->valor;

		if (utf8Val(idInst, CHARDIG, NULL)) {
			// caracteres inválidos na sigla

			rn = criarRegNoti(1, "Caractere inválido no identificador de instituição.");

			paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
			return 1;
		}

		Instituicao* inst = NULL;
		int num;

		int ret = bdBuscarInstituicaoId(cfIdInst->valor, &inst, &num);

		if (ret) {
			rn = criarRegNoti(1, "Erro ao tentar resgatar informações sobre a instituição.");
			paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
			return 2;
		}
		else {
			rn = criarRegNoti(0,"");
			paginaVisualizarInst(usu, sessao, form, NULL, NULL, inst);
			return 0;
		}
	}
	else {
		rn = criarRegNoti(3, "Erro ao tentar receber instituição do formulário.");
		paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
		return 3;
	}

}


int paginaVisualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* inst) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/adm/cadinst/visuinst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// Instanciar caminhos de sistema e de páginas

	mlSubstituirTodos("$URLTAREFAS$", urlTarefas, ml);

	// colocar notificação

	char* msg = msgNotiHTML(rn);

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

		/*
		cf = obterCampoFormularioHTML(form, "siglaInstituicao");
		char* sigla = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "nomeInstituicao");
		char* nome = cf ? cf->valor : "";

		cf = obterCampoFormularioHTML(form, "obsInstituicao");
		char* obs = cf ? cf->valor : "";
		*/

		if (forminst)
			extrairFormularioInstituicao(form, &forminst);

		mlSubstituirTodos("$IDINST$", idInst, ml);
		mlSubstituirTodos("$SIGLA$", forminst->sigla, ml);
		mlSubstituirTodos("$NOME$", forminst->nome, ml);
		mlSubstituirTodos("$OBS$", forminst->obs, ml);

	}

	mlImprimir(ml);
}




int atualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idInst");
	char* idInst = cf ? cf->valor : "";

	RegNoti* rn = NULL;

	if (utf8Val(idInst, CHARDIG, NULL)) {
		// caracteres inválidos no id da instituição

		rn = criarRegNoti(1, "Caractere inválido no identificador de instituição.");
		paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
		return 1;
	}


	// resgatar dados da instituição

	FormInstituicao* fi = NULL;
	char* msg = NULL;

	extrairFormularioInstituicao(form, &fi);

	// checar validade de caracteres

	int ret = validarFormularioInstituicao(fi, &msg);

	if (ret) {

		RegNoti* rn = criarRegNoti(ret, msg);
		paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}

	// realizar atualização no banco

	ret = bdAtualizarInstId(idInst, fi->sigla, fi->nome, fi->obs);

	if (ret) {
		RegNoti* rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre a instituição.");
		paginaVisualizarInst(usu, sessao, form, fi, rn, NULL);
		return ret;
	}
	else {
		RegNoti* rn = criarRegNoti(0, "Instituição atualizada com sucesso.");
		paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}

}


int removerInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {


	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idInst");
	char* idInst = cf ? cf->valor : "";

	// checar validade dos campos do formulário

	if (utf8Val(idInst, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		RegNoti* rn = criarRegNoti(1, "Caractere inválido no identificador de instituição.");
		paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
		return 1;
	}

	// remover do banco

	int ret = bdApagarInstId(cf->valor);

	if (ret) {
		RegNoti* rn = criarRegNoti(ret, "Não foi possível remover a instituição.<br> Deve haver Curso, Disciplina ou Respondedor associados a esta Instituição.");
		paginaVisualizarInst(usu, sessao, form, NULL, rn, NULL);
		return ret;
	}
	else {
		RegNoti* rn = criarRegNoti(ret, "Instituição removida com sucesso.");
		//printf("%s", rn->msg);
		paginaCadinst(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}
}
