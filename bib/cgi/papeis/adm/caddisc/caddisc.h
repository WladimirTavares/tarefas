/* caddisc.h
 *
 * implementa métodos para geração da página de cadastro de disciplinas
 */


#include "../../../../str/bibstring2.h"
#include "../../../../str/multilinhas.h"

#include "../../../../lugar.h"
#include "../../../../notifica.h"

#include "../../../sessaocgi.h"
#include "../../../htmlcgi.h"



typedef struct FormDisciplina {
	char* idDisc;		// página de visualização
	char* codigo;
	char* nome;
	char* idInst;
	char* obs;
} FormDisciplina;


void extrairFormularioDisciplina(FormularioHTML* form, FormDisciplina** formdisc);

int validarFormularioDisciplina(FormDisciplina* formdisc, RegNoti** rn);
int validarDadosDisciplina(FormDisciplina* formdisc, RegNoti** rn);

int preencherFormularioDisciplina(char* idDisc, char* codigo, char* nome, char* obs, Multilinhas* ml);



int paginaCadDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormDisciplina* formdisc, RegNoti* rn, Disciplina* discs, int numDiscs);

char* htmlFormPaginaVisualizarDisciplina(Disciplina* disc, long long int idSessao);

int paginaNovaDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormDisciplina* formdisc, RegNoti* rn);

int paginaVisualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormDisciplina* formdisc, RegNoti* rn, Disciplina* disc, int editar);


int buscarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int visualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int salvarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int atualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form);





/*		Implementações		*/




void extrairFormularioDisciplina(FormularioHTML* form, FormDisciplina** formdisc){

	// extrair dados do formulário html

	FormDisciplina* fd = (FormDisciplina *) malloc( sizeof(FormDisciplina) );

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idDisciplina");
	fd->idDisc = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "codigo");
	fd->codigo = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "nome");
	fd->nome = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "idInst");
	fd->idInst = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "obs");
	fd->obs = cf ? cf->valor : copiastr("");

	*formdisc = fd;
}



int validarFormularioDisciplina(FormDisciplina* formdisc, RegNoti** rn) {

	// checar validade de caracteres

	if (utf8Val(formdisc->idDisc, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(1, "Caractere inválido no id da disciplina.");

		return 1;
	}
	else if (utf8Val(formdisc->codigo, CHARCODIGO, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(2, "Caractere inválido no código.");

		return 2;
	}
	else if (utf8Val(formdisc->nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(3, "Caractere inválido no nome.");

		return 3;
	}
	else if (utf8Val(formdisc->idInst, CHARDIG, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(4, "Caractere inválido no id da instituição.");

		return 4;
	}
	else if (utf8Val(formdisc->obs, ALFANUMEXT, NULL)) {
		// caracteres inválidos na observação

		if (rn)
			*rn = criarRegNoti(5, "Caractere inválido na observação.");

		return 5;
	}
	else{

		if (rn)
			*rn = NULL;

		return 0;
	}

}



int validarDadosDisciplina(FormDisciplina* formdisc, RegNoti** rn) {

	// checar validade dos dados inseridos

	if (strlen(formdisc->codigo) == 0 || strlen(formdisc->nome) == 0 || strlen(formdisc->idInst) == 0) {
		if (rn)
			*rn = criarRegNoti(1, "Código, nome ou instituição inválidos.");

		return 1;
	}
	else {

		if (rn)
			*rn = criarRegNoti(0, "");

		return 0;
	}
}


int preencherFormularioDisciplina(char* idDisc, char* codigo, char* nome, char* obs, Multilinhas* ml) {

	mlSubstituirTodos("$IDDISCIPLINA$", idDisc ? idDisc : "", ml);
	mlSubstituirTodos("$CODIGO$", codigo ? codigo : "", ml);
	mlSubstituirTodos("$NOME$", nome ? nome : "", ml);
	//mlSubstituirTodos("$IDINST$", idInst ? idInst : "", ml);		// a instituição aparece em um elemento select
																	// isso significa que o valor padrão deve ser indicado
																	// quando forem colocadas as opções
																	//
																	// até o momento, $IDINST$ não é usado
	mlSubstituirTodos("$OBS$", obs ? obs : "", ml);

	return 0;
}



int paginaCadDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormDisciplina* formdisc, RegNoti* rn, Disciplina* discs, int numDiscs) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/caddisc/caddisc.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// repetir valores campos

	if (formdisc)
		preencherFormularioDisciplina("", formdisc->codigo, formdisc->nome, formdisc->obs, ml);
	else
		preencherFormularioDisciplina("", "", "", "", ml);

	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	long long idI = strtoll(formdisc ? formdisc->idInst : "", NULL, 10);

	char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

	mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// checar se houve solicitação de busca

	if (discs) {

		// montar lista de disciplinas resultado da busca

		char* linha;

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		mlInserirAcima("<p>Lista de Disciplinas</p>", nlResultadoBusca, ml);

		for (int i = 0; i < numDiscs; i++) {

			linha = htmlFormPaginaVisualizarDisciplina(&(discs[i]), sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);


			/*
			mlInserirAcima("<form method=\"post\">", nlResultadoBusca, ml);

			sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"./caddisc\" value=\"visudisc\">%s - %s - %s</button>\n", discs[i].codigo, discs[i].nome, discs[i].inst->sigla );
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"idDisciplina\" value=\"%lld\">\n", *(discs[i].idDisciplina));
			mlInserirAcima(linha, nlResultadoBusca, ml);

			sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);
			mlInserirAcima("</form>", nlResultadoBusca, ml);
			//mlInserirAcima("<br>\n", nlCorpoMenuAdm, ml);
			*/
		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);

	}

	mlImprimir(ml);

}


char* htmlFormPaginaVisualizarDisciplina(Disciplina* disc, long long int idSessao) {

	Multilinhas* ml = mlCriar();

	char linha[500];

	mlInserirAbaixo("<form method=\"post\">", ml->ult, ml);

	sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"visudisc\">%s - %s - %s</button>\n", disc->codigo, disc->nome, disc->inst->sigla );
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"idDisciplina\" value=\"%lld\">\n", *(disc->idDisciplina));
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", idSessao);
	mlInserirAbaixo(linha, ml->ult, ml);
	mlInserirAbaixo("</form>", ml->ult, ml);

	return mlExtrairTexto(ml);
}


int buscarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar parâmetros de buscas

	FormDisciplina* fd = NULL;
	char* msg = NULL;

	extrairFormularioDisciplina(form, &fd);

	Disciplina* discs = NULL;
	int numDiscs = 0;

	// checar validade de caracteres

	int numerr = validarFormularioDisciplina(fd, &rn);

	if (!validarFormularioDisciplina(fd, &rn)) {

		// buscar instituições no banco de dados

		int ret = bdBuscarDisciplina(fd->codigo, fd->nome, fd->idInst, fd->obs, &discs, &numDiscs);
		if (ret) {

			rn = criarRegNoti(ret, "Não foi possível buscar os cursos.");

		}
	}

	paginaCadDisc(usu, sessao, form, fd, rn, discs, numDiscs);

	return 0;
}


int paginaNovaDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormDisciplina* formdisc, RegNoti* rn) {


	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/caddisc/novadisc.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// repetir parâmetros nas caixas de texto

	if (formdisc)
		preencherFormularioDisciplina("", formdisc->codigo, formdisc->nome, formdisc->obs, ml);
	else
		preencherFormularioDisciplina("", "", "", "", ml);

	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	long long idI = strtoll(formdisc ? formdisc->idInst : "", NULL, 10);

	char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

	mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	mlImprimir(ml);

	return 0;
}


int salvarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar valores dos campos do formulário

	FormDisciplina* fd = NULL;
	char* msg = NULL;

	extrairFormularioDisciplina(form, &fd);

	// checar validade de caracteres

	int ret = validarFormularioDisciplina(fd, &rn);

	if (!ret) {

		// salvar no banco

		fd->codigo = aparar(&(fd->codigo));
		fd->nome = aparar(&(fd->nome));
		fd->idInst = aparar(&(fd->idInst));
		fd->obs = aparar(&(fd->obs));


		ret = validarDadosDisciplina(fd, &rn);
		if (!ret) {
			long long int idDisc = 0;

			ret = bdCadastrarDisciplina (fd->codigo, fd->nome, fd->idInst, fd->obs, &idDisc);

			if (ret) {

				// erro na inserção

				rn = criarRegNoti(ret, "Erro na inserção da Disciplina. Não pode haver disciplinas com o mesmo código em uma mesma instituição.");
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro
				RegNoti* rn = criarRegNoti(ret, "Disciplina criado com sucesso.");

				paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
		}
	}

	paginaNovaDisc(usu, sessao, form, fd, rn);

	return ret;
}


int paginaVisualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormDisciplina* formdisc, RegNoti* rn, Disciplina* disc, int editar) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/papeis/adm/caddisc/visudisc.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// checkbox editar

	if (editar)
		mlSubstituirTodos("$EDITAR$", "checked", ml);
	else
		mlSubstituirTodos("$EDITAR$", "", ml);

	if (disc) {

		// incluir dados da disciplina

		preencherFormularioDisciplina(llistr(*(disc->idDisciplina)), disc->codigo, disc->nome, disc->obs, ml);

		//mlSubstituirTodos("$EDITAR$", "", ml);

		// inserir opções de instituição, colocando como selecionada a instituição do curso visualizado

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		char* htmlOpcoes = htmlOpcoesInstituicoes(*(disc->inst->idInstituicao));

		mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	}
	else {

		// repetir valores dos campos

		if (formdisc)
			preencherFormularioDisciplina(formdisc->idDisc, formdisc->codigo, formdisc->nome, formdisc->obs, ml);
		else
			preencherFormularioDisciplina("", "", "", "", ml);

		//mlSubstituirTodos("$EDITAR$", "checked", ml);

		// inserir opções de instituição, colocando como selecionada a instituição do curso visualizado

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		long long idI = strtoll(formdisc ? formdisc->idInst : "", NULL, 10);

		char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

		mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	}

	mlImprimir(ml);

	return 0;
}


int visualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idDisc = NULL;

    if ( !(idDisc = obterCFHVal("idDisciplina", form, "identificador da disciplina", CHARDIG, &rn)) ) {

        paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

    Disciplina* disc = NULL;
	int num;

	int ret = bdBuscarDisciplinaId(idDisc, &disc, &num);

	if (ret) {
		rn = criarRegNoti(1, "Erro ao tentar resgatar informações sobre a disciplina.");

		paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
		return 2;
	}
	else {
		paginaVisualizarDisc(usu, sessao, form, NULL, NULL, disc, 0);
		return 0;
	}

}


int atualizarDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idDisc = NULL;

    if ( !(idDisc = obterCFHVal("idDisciplina", form, "identificador da disciplina", CHARDIG, &rn)) ) {

        paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	// resgatar dados do curso do formulário

	FormDisciplina* fd = NULL;
	char* msg = NULL;

	extrairFormularioDisciplina(form, &fd);

	// checar validade de caracteres

	int ret = validarFormularioDisciplina(fd, &rn);

	if (!ret) {

		ret = validarDadosDisciplina(fd, &rn);
		if (!ret) {

			ret = bdAtualizarDisciplinaId(idDisc, fd->codigo, fd->nome, fd->idInst, fd->obs);
			if (!ret) {

				rn = criarRegNoti(ret, "Curso atualizado com sucesso.");
				paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
			else {
				rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre a disciplina. Código, Nome e Instituição não podem ser vazios.");
			}
		}
	}

	paginaVisualizarDisc(usu, sessao, form, fd, rn, NULL, 1);
	return ret;

}


int removerDisc(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idDisc = NULL;

    if ( !(idDisc = obterCFHVal("idDisciplina", form, "identificador da disciplina", CHARDIG, &rn)) ) {

        paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	int ret = bdApagarDisciplinaId(idDisc);

	if (ret) {
		RegNoti* rn = criarRegNoti(ret, "Não foi possível remover a disciplina.");

		// resgatar dados do curso do formulário

		FormDisciplina* fd = NULL;
		extrairFormularioDisciplina(form, &fd);

		// checar se botão editar está selecionado

		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "cbEditar");

		paginaVisualizarDisc(usu, sessao, form, fd, rn, NULL, (cf ? 1 : 0) );
		return ret;
	}
	else {
		RegNoti* rn = criarRegNoti(ret, "Disciplina removida com sucesso.");

		paginaCadDisc(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}
}
