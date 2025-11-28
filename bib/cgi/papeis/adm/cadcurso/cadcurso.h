/* cadcurso.h
 *
 * implementa métodos para geração da página de adm
 */


#include "../../../../str/bibstring2.h"
#include "../../../../str/multilinhas.h"

#include "../../../../lugar.h"
#include "../../../../notifica.h"

#include "../../../sessaocgi.h"
#include "../../../htmlcgi.h"



typedef struct FormCurso {
	char* idCurso;	// usando na página de visualização
	char* codigo;
	char* nome;
	char* idInst;
	char* obs;
} FormCurso;


void extrairFormularioCurso(FormularioHTML* form, FormCurso** formcurso);

int validarFormularioCurso(FormCurso* formcurso, RegNoti** rn);
int validarDadosCurso(FormCurso* formcurso, RegNoti** rn);

int preencherFormularioCurso(char* idCurso, char* codigo, char* nome, char* obs, Multilinhas* ml);



int paginaCadCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormCurso* fc, RegNoti* rn, Curso* cursos, int numCursos);

char* htmlFormPaginaVisualizarCurso(Curso* curso, long long int idSessao);

int paginaNovoCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormCurso* formcurso, RegNoti* rn);

int paginaVisualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormCurso* formcurso, RegNoti* rn, Curso* curso, int editar);


int buscarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int visualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int salvarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int atualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form);




/*		Implementações		*/




void extrairFormularioCurso(FormularioHTML* form, FormCurso** formcurso){

	// extrair dados do formulário html

	FormCurso* fc = (FormCurso *) malloc( sizeof(FormCurso) );

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idCurso");
	fc->idCurso = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "codigo");
	fc->codigo = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "nome");
	fc->nome = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "idInst");
	fc->idInst = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "obs");
	fc->obs = cf ? cf->valor : copiastr("");

	*formcurso = fc;
}



int validarFormularioCurso(FormCurso* formcurso, RegNoti** rn) {

	// checar validade de caracteres

	if (utf8Val(formcurso->idCurso, CHARDIG, NULL)) {	// usado na página de visualização
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(1, "Caractere inválido no identificador do curso.");

		return 1;
	}
	else if (utf8Val(formcurso->codigo, CHARCODIGO, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(2, "Caractere inválido no código.");

		return 2;
	}
	else if (utf8Val(formcurso->nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(3, "Caractere inválido no nome.");

		return 3;
	}
	else if (utf8Val(formcurso->idInst, CHARDIG, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(4, "Caractere inválido no id da instituição.");

		return 4;
	}
	else if (utf8Val(formcurso->obs, ALFANUMEXT, NULL)) {
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


int validarDadosCurso(FormCurso* formcurso, RegNoti** rn) {

	// checar validade dos dados inseridos

	if (strlen(formcurso->codigo) == 0 || strlen(formcurso->nome) == 0 || strlen(formcurso->idInst) == 0) {
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


int preencherFormularioCurso(char* idCurso, char* codigo, char* nome, char* obs, Multilinhas* ml) {

	mlSubstituirTodos("$IDCURSO$", idCurso ? idCurso : "", ml);		// usado na página de visualização
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



int paginaCadCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormCurso* formcurso, RegNoti* rn, Curso* cursos, int numCursos) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadcurso/cadcurso.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// repetir campos formulário

	if (formcurso)
		preencherFormularioCurso("", formcurso->codigo, formcurso->nome, formcurso->obs, ml);
	else
		preencherFormularioCurso("", "", "", "", ml);

	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	long long idI = strtoll(formcurso ? formcurso->idInst : "", NULL, 10);

	char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

	mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	// listar resultados da busca

	if (cursos) {

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		mlInserirAcima("<p>Lista de Cursos</p>", nlResultadoBusca, ml);

		char* linha = NULL;

		for (int i = 0; i < numCursos; i++) {

			linha = htmlFormPaginaVisualizarCurso(&(cursos[i]), sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);

		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);

	}

	mlImprimir(ml);

}

char* htmlFormPaginaVisualizarCurso(Curso* curso, long long int idSessao) {

	Multilinhas* ml = mlCriar();

	char linha[500];

	mlInserirAbaixo("<form method=\"post\">", ml->ult, ml);

	sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"visucurso\">%s - %s - %s</button>\n", curso->codigo, curso->nome, curso->inst->sigla );
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"idCurso\" value=\"%lld\">\n", *(curso->idCurso));
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", idSessao);
	mlInserirAbaixo(linha, ml->ult, ml);
	mlInserirAbaixo("</form>", ml->ult, ml);

	return mlExtrairTexto(ml);
}


int paginaNovoCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormCurso* formcurso, RegNoti* rn) {


	Multilinhas* ml = mlCriar();

	int ret = 0;

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadcurso/novocurso.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// repetir valores dos campos

	if (formcurso)
		preencherFormularioCurso("", formcurso->codigo, formcurso->nome, formcurso->obs, ml);
	else
		preencherFormularioCurso("", "", "", "", ml);

	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	long long idI = strtoll(formcurso ? formcurso->idInst : "", NULL, 10);

	char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

	mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	mlImprimir(ml);

	return ret;

}


int paginaVisualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormCurso* formcurso, RegNoti* rn, Curso* curso, int editar) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadcurso/visucurso.html");

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

	if (curso) {

		// incluir dados do curso

		preencherFormularioCurso(llistr(*(curso->idCurso)), curso->codigo, curso->nome, curso->obs, ml);

		//mlSubstituirTodos("$EDITAR$", "", ml);

		// inserir opções de instituição, colocando como selecionada a instituição do curso visualizado

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		char* htmlOpcoes = htmlOpcoesInstituicoes(*(curso->inst->idInstituicao));

		mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	}
	else  {

		// repetir valores dos campos

		if (formcurso)
			preencherFormularioCurso(formcurso->idCurso, formcurso->codigo, formcurso->nome, formcurso->obs, ml);
		else
			preencherFormularioCurso("", "", "", "", ml);

		//mlSubstituirTodos("$EDITAR$", "checked", ml);

		// inserir opções de instituição, colocando como selecionada a instituição do curso visualizado

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		long long idI = strtoll(formcurso ? formcurso->idInst : "", NULL, 10);

		//char* htmlOpcoes = htmlOpcoesInstituicoes(*(curso->inst->idInstituicao));
		char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

		mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

	}

	// modo edição

	/*
	if (editar)
		mlSubstituirTodos("$EDITAR$", "checked", ml);
	else
		mlSubstituirTodos("$EDITAR$", "", ml);
*/

	mlImprimir(ml);

	return 0;

}


int buscarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar parâmetros de buscas

	FormCurso* fc = NULL;
	char* msg = NULL;

	extrairFormularioCurso(form, &fc);

	Curso* cursos = NULL;
	int numCursos = 0;

	// checar validade de caracteres

	int numerr = validarFormularioCurso(fc, &rn);

	if (!validarFormularioCurso(fc, &rn)) {

		// se os dados foram validados, buscar instituições no banco

		int ret = bdBuscarCurso(fc->codigo, fc->nome, fc->idInst, fc->obs, &cursos, &numCursos);

		if (ret) {
			rn = criarRegNoti(ret, "Não foi possível buscar os cursos.");

			cursos = NULL;
			numCursos = 0;
		}
	}

	paginaCadCurso(usu, sessao, form, fc, rn, cursos, numCursos);

}


int visualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idCurso = NULL;

    if ( !(idCurso = obterCFHVal("idCurso", form, "identificador do curso", CHARDIG, &rn)) ) {

        paginaCadCurso(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

    // buscar curso no banco

	Curso* curso = NULL;
	int num;

	int ret = bdBuscarCursoId(idCurso, &curso, &num);

	if (ret) {
		rn = criarRegNoti(1, "Erro ao tentar resgatar informações sobre o curso.");

		paginaCadCurso(usu, sessao, form, NULL, rn, NULL, 0);
		return 2;
	}
	else {
		paginaVisualizarCurso(usu, sessao, form, NULL, NULL, curso, 0);
		return 0;
	}

}


int salvarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// regatar valores dos campos do formulário

	FormCurso* fc = NULL;
	char* msg = NULL;

	extrairFormularioCurso(form, &fc);

	// checar validade de caracteres

	int ret = validarFormularioCurso(fc, &rn);

	if (!ret) {

		// salvar no banco

		fc->codigo = aparar(&(fc->codigo));
		fc->nome = aparar(&(fc->nome));
		fc->idInst = aparar(&(fc->idInst));
		fc->obs = aparar(&(fc->obs));


		//if (strlen(fc->codigo) != 0 && strlen(fc->nome) != 0 && strlen(fc->idInst) != 0) {

		if (!validarDadosCurso(fc, &rn)) {		// dados validados

			long long int idCurso = 0;

			// salvar no banco
			ret = bdCadastrarCurso (fc->codigo, fc->nome, fc->idInst, fc->obs, &idCurso);

			if (ret) {

				// erro na inserção
				rn = criarRegNoti(ret, "Erro na inserção do Curso. Cursos de uma mesma instituição não podem ter o mesmo código.");
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro

				rn = criarRegNoti(0, "Curso criado com sucesso.");

				paginaCadCurso(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
		}
	}

	paginaNovoCurso(usu, sessao, form, fc, rn);

	return ret;
}


int atualizarCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar dados do curso do formulário

	FormCurso* fc = NULL;
	char* msg = NULL;

	extrairFormularioCurso(form, &fc);

	// checar validade de caracteres

	int ret = validarFormularioCurso(fc, &rn);
	if (!ret) {

		ret = validarDadosCurso(fc, &rn);
		if (!ret) {

			ret = bdAtualizarCursoId(fc->idCurso, fc->codigo, fc->nome, fc->idInst, fc->obs);
			if (!ret) {

				RegNoti* rn = criarRegNoti(ret, "Curso atualizado com sucesso.");
				paginaCadCurso(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
			else {
				rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre o curso.");
			}
		}
	}

	paginaVisualizarCurso(usu, sessao, form, fc, rn, NULL, 1);
	return ret;
}


int removerCurso(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idCurso = NULL;

    if ( !(idCurso = obterCFHVal("idCurso", form, "identificador do curso", CHARDIG, &rn)) ) {

        paginaCadCurso(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }


	int ret = bdApagarCursoId(idCurso);

	if (ret) {

		rn = criarRegNoti(1, "Não foi possível remover o curso. Deve haver haver perfil ou disciplina associados ao curso.");

		// resgatar dados do curso do formulário

		FormCurso* fc = NULL;
		extrairFormularioCurso(form, &fc);

		// checar se botão editar está selecionado

		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "cbEditar");

		paginaVisualizarCurso(usu, sessao, form, fc, rn, NULL, (cf ? 1 : 0) );
		return ret;
	}
	else {

		rn = criarRegNoti(ret, "Curso removido com sucesso.");
		paginaCadCurso(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}
}
