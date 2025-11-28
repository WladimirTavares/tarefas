/* cadinst.h
 *
 * implementa métodos para geração das paginas de cadastro de instituição
 */


#include "../../../../str/bibstring2.h"
#include "../../../../str/multilinhas.h"

#include "../../../../lugar.h"
#include "../../../../notifica.h"

#include "../../../sessaocgi.h"
#include "../../../htmlcgi.h"


typedef struct FormInstituicao {
	char* idInstituicao;	// usado na página de visualização
	char* sigla;
	char* nome;
	char* obs;
} FormInstituicao;



// extrai informações do formulário html
void extrairFormularioInstituicao(FormularioHTML* form, FormInstituicao** forminst);

int validarFormularioInstituicao(FormInstituicao* forminst, RegNoti** rn);
int validarDadosInstituicao(FormInstituicao* forminst, RegNoti** rn);

int preencherFormularioInstituicao(char* idInst, char* sigla, char* nome, char* obs, Multilinhas* ml);



int buscarInst( Usuario* usu, Sessao* sessao, FormularioHTML* form);

int paginaCadInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* insts, int numInsts);

char* htmlFormPaginaVisualizarInstituicao(Instituicao* inst, long long int idSessao);

int salvarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int paginaNovaInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn);

int visualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int paginaVisualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* inst, int editar);

int atualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerInst(Usuario* usu, Sessao* sessao, FormularioHTML* form);




/*		Implementações		*/



void extrairFormularioInstituicao(FormularioHTML* form, FormInstituicao** forminst){

	// extrair dados do formulário html

	FormInstituicao* fi = (FormInstituicao *) malloc( sizeof(FormInstituicao) );

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idInst");		// usado na página de visualização
	fi->idInstituicao = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "sigla");
	fi->sigla = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "nome");
	fi->nome = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "obs");
	fi->obs = cf ? cf->valor : copiastr("");

	*forminst = fi;
}



int validarFormularioInstituicao(FormInstituicao* forminst, RegNoti** rn) {

	// checar validade de caracteres

	if (utf8Val(forminst->idInstituicao, CHARDIG, NULL)) {		// usado na página de visualização
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(1, "Caractere inválido no identificador da instituição.");

		return 1;
	}
	if (utf8Val(forminst->sigla, CHARSIGLA, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(2, "Caractere inválido na sigla.");

		return 2;
	}
	if (utf8Val(forminst->nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(3, "Caractere inválido no nome.");

		return 3;
	}
	if (utf8Val(forminst->obs, ALFANUMEXT, NULL)) {
		// caracteres inválidos na observação

		if (rn)
			*rn = criarRegNoti(4, "Caractere inválido na observação.");

		return 4;
	}
	else {

		if (rn)
			*rn = criarRegNoti(0, "");

		return 0;
	}
}

int validarDadosInstituicao(FormInstituicao* forminst, RegNoti** rn) {

	// checar validade dos dados inseridos

	if (strlen(forminst->sigla) == 0 || strlen(forminst->nome) == 0){
		if (rn)
			*rn = criarRegNoti(1, "Sigla ou nome inválidos.");

		return 1;
	}
	else {

		if (rn)
			*rn = criarRegNoti(0, "");

		return 0;
	}
}


int preencherFormularioInstituicao(char* idInst, char* sigla, char* nome, char* obs, Multilinhas* ml) {

	mlSubstituirTodos("$IDINST$", idInst ? idInst : "", ml);		// usado na página de visualização
	mlSubstituirTodos("$SIGLA$", sigla ? sigla : "", ml);
	mlSubstituirTodos("$NOME$", nome ? nome : "", ml);
	mlSubstituirTodos("$OBS$", obs ? obs : "", ml);

	return 0;
}





int buscarInst( Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	Instituicao* insts = NULL;
	int numInsts = 0;

	// resgatar parâmetros de buscas, caso hajam

	FormInstituicao* fi = NULL;
	extrairFormularioInstituicao(form, &fi);

	RegNoti* rn = NULL;
	int ret = validarFormularioInstituicao(fi, &rn);

	// se os dados foram validados, buscar instituições no banco

	if (!ret) {
		// buscar instituições no banco de dados

		ret = bdBuscarInstituicao(fi->sigla, fi->nome, fi->obs, &insts, &numInsts);

		if (ret) {
			rn = criarRegNoti(ret, "Não foi possível buscar as instituições no banco.");

			paginaCadInst(usu, sessao, form, fi, rn, NULL, 0);
		}

	}

	paginaCadInst(usu, sessao, form, fi, rn, insts, numInsts);

	return 0;
}


int paginaCadInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* insts, int numInsts) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadinst/cadinst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar notificação

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// repetir valores do formulário

	if (forminst)
		preencherFormularioInstituicao("", forminst->sigla, forminst->nome, forminst-> obs, ml);
	else
		preencherFormularioInstituicao("", "", "", "", ml);

	// listar resultado da busca

	NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

	if (insts) {

		char* linha = NULL;

		mlInserirAcima("<p>Lista de Instituições</p>", nlResultadoBusca, ml);

		for (int i = 0; i < numInsts; i++) {

			linha = htmlFormPaginaVisualizarInstituicao(&(insts[i]), sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);
		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);
	}

	mlImprimir(ml);
}


char* htmlFormPaginaVisualizarInstituicao(Instituicao* inst, long long int idSessao) {

	Multilinhas* ml = mlCriar();

	char linha[500];

	mlInserirAbaixo("<form method=\"post\">", ml->ult, ml);

	sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"visuinst\">%s - %s</button>\n", inst->sigla, inst->nome );
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"idInst\" value=\"%lld\">\n", *(inst->idInstituicao));
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", idSessao);
	mlInserirAbaixo(linha, ml->ult, ml);

	mlInserirAbaixo("</form>", ml->ult, ml);

	return mlExtrairTexto(ml);
}


int salvarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// resgatar valores dos campos, caso hajam
	FormInstituicao* fi = NULL;
	RegNoti* rn = NULL;

	extrairFormularioInstituicao(form, &fi);

	// checar validade de caracteres
	int ret = validarFormularioInstituicao(fi, &rn);

	if (!ret) {

		// remover espaços em branco das extremidades
		fi->sigla = aparar(&(fi->sigla));
		fi->nome = aparar(&(fi->nome));
		fi->obs = aparar(&(fi->obs));

		// checar validade dos dados
		ret = validarDadosInstituicao(fi, &rn);

		if (!ret) {

			// gravar dados no banco

			long long int idInst = 0;
			ret = bdCadastrarInstituicao (fi->sigla, fi->nome, fi->obs, &idInst);

			if (ret) {
				// erro na inserção
				rn = criarRegNoti(6, "Erro na inserção da Instituição. Instituições diferentes não podem ter o mesmo nome ou sigla.");
			}
			else {
				// inserção realizada com sucesso, volta para a página de cadastro
				rn = criarRegNoti(0, "Instituição criada com sucesso.");
				paginaCadInst(usu, sessao, form, NULL, rn, NULL, 0);
				return 0;
			}
		}
	}

	paginaNovaInst(usu, sessao, form, fi, rn);
	return ret;
}


int paginaNovaInst(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn) {


	// carregar modelo

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadinst/novainst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar notificação

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// repetir valores dos campo, caso hajam

	if (forminst)
		preencherFormularioInstituicao("", forminst->sigla, forminst->nome, forminst->obs, ml);
	else
		preencherFormularioInstituicao("", "", "", "", ml);

	mlImprimir(ml);

	return 0;
}



int visualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idInst = NULL;

    if ( !(idInst = obterCFHVal("idInst", form, "identificador da instituição", CHARDIG, &rn)) ) {

        paginaCadInst(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	Instituicao* inst = NULL;
	int num;

	int ret = bdBuscarInstituicaoId(idInst, &inst, &num);

	if (ret) {
		rn = criarRegNoti(1, "Erro ao tentar resgatar informações sobre a instituição.");
		paginaCadInst(usu, sessao, form, NULL, rn, NULL, 0);
		return 2;
	}
	else {
		rn = criarRegNoti(0,"");
		paginaVisualizarInst(usu, sessao, form, NULL, NULL, inst, 0);
		return 0;
	}
}


int paginaVisualizarInst (Usuario* usu, Sessao* sessao, FormularioHTML* form, FormInstituicao* forminst, RegNoti* rn, Instituicao* inst, int editar) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadinst/visuinst.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar notificação

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// checkbox editar

	if (editar)
		mlSubstituirTodos("$EDITAR$", "checked", ml);
	else
		mlSubstituirTodos("$EDITAR$", "", ml);

	if (inst) {

		// inlcuir dados da instituição

		preencherFormularioInstituicao(llistr(*(inst->idInstituicao)), inst->sigla, inst->nome, inst->obs, ml);


	}
	else {		// caso houve falha na atualização

		// repetir valores dos campos

		//if (forminst)
			preencherFormularioInstituicao(forminst->idInstituicao, forminst->sigla, forminst->nome, forminst->obs, ml);
		//else
		//	preencherFormularioInstituicao("", "", "", "", ml);


	}

	mlImprimir(ml);
}




int atualizarInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar dados da instituição

	FormInstituicao* fi = NULL;
	char* msg = NULL;

	extrairFormularioInstituicao(form, &fi);

	// checar validade de caracteres
	int ret = validarFormularioInstituicao(fi, &rn);
	if (!ret) {

		// checar validade de dados
		ret = validarDadosInstituicao(fi, &rn);
		if (!ret) {

			// realizar atualização no banco
			ret = bdAtualizarInstId(fi->idInstituicao, fi->sigla, fi->nome, fi->obs);

			if (!ret) {

				rn = criarRegNoti(0, "Instituição atualizada com sucesso.");
				paginaCadInst(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
			else {

				rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre a instituição.");
			}
		}
	}

	paginaVisualizarInst(usu, sessao, form, fi, rn, NULL, 1);
	return ret;

}


int removerInst(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;


	// obter id da instituição

    char* idInst = NULL;

    if ( !(idInst = obterCFHVal("idInst", form, "identificador da instituição", CHARDIG, &rn)) ) {

        paginaCadInst(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	// remover do banco

	int ret = bdApagarInstId(idInst);

	if (ret) {
		RegNoti* rn = criarRegNoti(ret, "Não foi possível remover a instituição. Deve haver Curso, Disciplina ou Respondedor associados a esta Instituição.");

		// resgatar dados da instituição no formulário

		FormInstituicao* fi = NULL;
		extrairFormularioInstituicao(form, &fi);

		// checar se botão editar está selecionado

		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "cbEditar");

		paginaVisualizarInst(usu, sessao, form, fi, rn, NULL, (cf ? 1 : 0) );
		return ret;
	}
	else {
		RegNoti* rn = criarRegNoti(ret, "Instituição removida com sucesso.");
		paginaCadInst(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}
}
