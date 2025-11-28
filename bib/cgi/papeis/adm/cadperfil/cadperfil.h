/* cadperfil.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../../str/bibstring2.h"
#include "../../../../str/multilinhas.h"

#include "../../../../lugar.h"
#include "../../../../notifica.h"

#include "../../../sessaocgi.h"
#include "../../../htmlcgi.h"

#include "cadperfillote.h"



typedef struct FormPerfil {

	char* idPerfil; 	// página de visualização
	char* idUsuario;	// página novo perfil
	char* nome;
	char* login;
	char* email;
	char* matricula;
	char* idInst;
	char* idCurso;
	char* habilitado;
	char* obs;

} FormPerfil;





void extrairFormularioPerfil(FormularioHTML* form, FormPerfil** formperfil);

int validarFormularioPerfil(FormPerfil* formperfil, RegNoti** rn);
int validarDadosPerfil(FormPerfil* formperfil, RegNoti** rn);

int preencherFormularioPerfil(char* idPerfil, char* idUsuario, char* nome, char* login, char* email, char* matricula, char* habilitado, char* obs, Multilinhas* ml);



int paginaCadPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormPerfil* formperfil, RegNoti* rn, Usuario* usus, int numUsus);

char* htmlFormPaginaVisualizarPerfil(Usuario* usu, PerfilRespondedor* perfil, long long int idSessao);

int paginaNovoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormPerfil* formperfil, RegNoti* rn, Usuario* usuPerfil);

int paginaVisualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormPerfil* formperfil, RegNoti* rn,  Usuario* usuPerfil, int editar);



int buscarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int visualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int buscarUsuarioNovoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int salvarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int atualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int selInstituicaoCursoCadperfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int selInstituicaoCursoNovoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int selInstituicaoCursoVisualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form);

//int cadastrarPerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form);





/*		Implementações		*/






void extrairFormularioPerfil(FormularioHTML* form, FormPerfil** formperfil) {

	// extrair dados do formulário html

	FormPerfil* fp = (FormPerfil *) malloc( sizeof(FormPerfil) );

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idPerfil");
	fp->idPerfil = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "idUsuarioPerfil");
	fp->idUsuario = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "nome");
	fp->nome = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "login");
	fp->login = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "email");
	fp->email = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "matricula");
	fp->matricula = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "idInst");
	fp->idInst = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "idCurso");
	fp->idCurso = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "habilitado");
	fp->habilitado = cf ? copiastr("1") : copiastr("0");

	cf = obterCampoFormularioHTML(form, "obs");
	fp->obs = cf ? cf->valor : copiastr("");

	*formperfil = fp;
}


int validarFormularioPerfil(FormPerfil* formperfil, RegNoti** rn) {

	// checar validade de caracteres

	if (utf8Val(formperfil->idPerfil, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(1, "Caractere inválido no identificador do usuário.");

		return 1;
	}
	else if (utf8Val(formperfil->idUsuario, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(2, "Caractere inválido no identificador do usuário.");

		return 2;
	}
	else if (utf8Val(formperfil->nome, CHARNOME, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(3, "Caractere inválido no nome.");

		return 3;
	}
	else if (utf8Val(formperfil->login, CHARLOGIN, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(4, "Caractere inválido no login.");

		return 4;
	}
	else if (utf8Val(formperfil->email, CHAREMAIL, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(5, "Caractere inválido no email.");

		return 5;
	}
	else if (utf8Val(formperfil->matricula, CHARMAT, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(6, "Caractere inválido na matrícula.");

		return 6;
	}
	else if (utf8Val(formperfil->idInst, CHARDIG, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(7, "Caractere inválido no identificador da instituição.");

		return 7;
	}
	else if (utf8Val(formperfil->idCurso, CHARDIG, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(8, "Caractere inválido no identificador do curso.");

		return 8;
	}
	else if (formperfil->habilitado && utf8Val(formperfil->habilitado, CHARDIG, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(9, "Caractere inválido no campo habilitado.");

		return 9;
	}
	else if (utf8Val(formperfil->obs, CARVALSMLEXT, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(10, "Caractere inválido na observação.");

		return 10;
	}
	else{

		if (rn)
			*rn = NULL;

		return 0;
	}

}


int validarDadosPerfil(FormPerfil* formperfil, RegNoti** rn) {

	if (strlen(formperfil->idUsuario) == 0 || strlen(formperfil->idCurso) == 0 || strlen(formperfil->matricula) == 0) {

		if (rn)
				*rn = criarRegNoti(1, "Usuário, curso ou matrícula inválidos.");

		return 1;
	}
	else {

		if (rn)
			*rn = criarRegNoti(0, "");

		return 0;
	}

}


int preencherFormularioPerfil(char* idPerfil, char* idUsuario, char* nome, char* login, char* email, char* matricula, char* habilitado, char* obs, Multilinhas* ml) {

	mlSubstituirTodos("$IDPERFIL$", idPerfil ? idPerfil : "", ml);				// página visualização
	mlSubstituirTodos("$IDUSUARIOPERFIL$", idUsuario ? idUsuario : "", ml);		// página novo perfil
	mlSubstituirTodos("$NOME$", nome ? nome : "", ml);
	mlSubstituirTodos("$LOGIN$", login ? login : "", ml);
	mlSubstituirTodos("$EMAIL$", email ? email : "", ml);
	mlSubstituirTodos("$MATRICULA$", matricula ? matricula : "", ml);
	mlSubstituirTodos("$HABILITADO$", habilitado && !strcmp(habilitado, "1") ? "checked" : "", ml);
	mlSubstituirTodos("$OBS$", obs ? obs : "", ml);

	return 0;
}




int paginaCadPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormPerfil* formperfil, RegNoti* rn, Usuario* usus, int numUsus){

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/cadperfil.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// apenas repete os valores nos campos

	if (formperfil)
		preencherFormularioPerfil("", "", formperfil->nome, formperfil->login, formperfil->email, formperfil->matricula, formperfil->habilitado, formperfil->obs, ml);
	else
		preencherFormularioPerfil("", "", "", "", "", "", "", "", ml);

	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	long long idI = strtoll(formperfil ? formperfil->idInst : "", NULL, 10);

	char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

	mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);


	// inserir opções de curso

	if (formperfil && formperfil->idInst && strcmp(formperfil->idInst, "")) {		// se foi selecionado id de instituição

		NoLinha* nl = mlEncontrar("@OpcoesCurso", ml);

		long long int idC = strtoll(formperfil->idCurso ? formperfil->idCurso : "", NULL, 10);

		htmlOpcoes = htmlOpcoesCursos(formperfil->idInst, idC);

		mlSubstituirTodosEmLinha("@OpcoesCurso", htmlOpcoes, nl);

	}


	// Se foram passados perfis (como listas de usuários), listar os perfis

	if (usus) {

		// montar lista de perfis resultado da busca

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		mlInserirAcima("<p>Lista de Perfis</p>", nlResultadoBusca, ml);

		char* linha;

		for (int i = 0; i < numUsus; i++) {

			// acessar perfis do usuário
			PerfilRespondedor* perfis = usus[i].perfis;

			for (int j = 0; j < usus[i].numPerfis; j++) {

				linha = htmlFormPaginaVisualizarPerfil(&(usus[i]), &(perfis[j]), sessao->idSessao);
				mlInserirAcima(linha, nlResultadoBusca, ml);

			}

		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);

	}

	mlImprimir(ml);

}



char* htmlFormPaginaVisualizarPerfil(Usuario* usu, PerfilRespondedor* perfil, long long int idSessao) {

	Multilinhas* ml = mlCriar();

	char linha[500];

	mlInserirAbaixo("<form method=\"post\">", ml->ult, ml);

	sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"visuperfil\">%s - %s - %s - %s - %s - %s</button>\n", usu->login, perfil->matricula, perfil->curso->inst->sigla, perfil->curso->codigo, perfil->curso->nome, usu->nome);
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"idPerfil\" value=\"%lld\">\n", *(perfil->idPerfilRespondedor));
	mlInserirAbaixo(linha, ml->ult, ml);
	sprintf(linha, "<input type=\"hidden\" name=\"idUsuarioPerfil\" value=\"%lld\">\n", *(usu->idUsuario));
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", idSessao);
	mlInserirAbaixo(linha, ml->ult, ml);
	mlInserirAbaixo("</form>", ml->ult, ml);

	return mlExtrairTexto(ml);
}


int paginaNovoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormPerfil* formperfil, RegNoti* rn, Usuario* usuPerfil) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/novoperfil.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);


	int ret = 0;

	// preencher campos do formulário

	if (usuPerfil) {	// caso tenha sido selecionado um usuário para o perfil

		char* idUsuario = llistr(*(usuPerfil->idUsuario));
		char* habilitado = *(usuPerfil->habilitado) == 1 ? "1" : "0";

		preencherFormularioPerfil("", idUsuario, usuPerfil->nome, usuPerfil->login, usuPerfil->email, formperfil ? formperfil->matricula : "", formperfil ? formperfil->habilitado : "", formperfil ? formperfil->obs : "", ml);

	}
	else {

		if (formperfil)
			preencherFormularioPerfil("", formperfil->idUsuario, formperfil->nome, formperfil->login, formperfil->email, formperfil->matricula, formperfil->habilitado, formperfil->obs, ml);
		else
			preencherFormularioPerfil("", "", "", "", "", "", "", "", ml);

	}


	// inserir opções de instituição

	NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

	long long idI = strtoll(formperfil && formperfil->idInst ? formperfil->idInst : "", NULL, 10);

	char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

	mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);


	// inserir opções de curso

	if (formperfil && formperfil->idInst && strcmp(formperfil->idInst, "")) {		// se foi selecionado id de instituição

		NoLinha* nl = mlEncontrar("@OpcoesCurso", ml);

		long long int idC = strtoll(formperfil->idCurso ? formperfil->idCurso : "", NULL, 10);

		htmlOpcoes = htmlOpcoesCursos(formperfil->idInst, idC);

		mlSubstituirTodosEmLinha("@OpcoesCurso", htmlOpcoes, nl);
	}

	mlImprimir(ml);

	return ret;

}


int paginaVisualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormPerfil* formperfil, RegNoti* rn, Usuario* usuPerfil, int editar){

	Multilinhas* ml = mlCriar();


	//if (usu) {

		//CampoFormularioHTML* cfIdUsu = obterCampoFormularioHTML(form, "idUsuarioPerfil");

		char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/visuperfil.html");

		mlCarregarArquivoTexto(caminho, ml);

		// instanciar dados de sessão, de sistema, etc.

		incluirDadosSessao(usu, sessao, form, ml);


		// colocar mensagem

		char* msg = msgNotiHTML(rn);

		mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

		long long int idI = 0;
		char* idIstr = NULL;
		long long int idC = 0;

		if (usuPerfil) {
			// colocar dados do perfil a ser visualizado no formulário

			char* idPerfil = llistr(*(usuPerfil->perfis->idPerfilRespondedor));
			char* idUsuario = llistr(*(usuPerfil->idUsuario));
			char* habilitado = *(usuPerfil->perfis->habilitado) == 1 ? "1" : "0";
			preencherFormularioPerfil(idPerfil, idUsuario, usuPerfil->nome, usuPerfil->login, usuPerfil->email, usuPerfil->perfis->matricula, habilitado, usuPerfil->perfis->obs, ml);

			idC = *(usuPerfil->perfis->curso->idCurso);
			idI = *(usuPerfil->perfis->curso->inst->idInstituicao);
			idIstr = llistr(idI);

		}
		else {
			// repetir valores dos campos do formulário

			if (formperfil)
				preencherFormularioPerfil(formperfil->idPerfil, formperfil->idUsuario, formperfil->nome, formperfil->login, formperfil->email, formperfil->matricula, formperfil->habilitado, formperfil->obs, ml);
			else
				preencherFormularioPerfil("", "", "", "", "", "", "", "", ml);

			idI = strtoll(formperfil && formperfil->idInst ? formperfil->idInst : "", NULL, 10);
			idIstr = formperfil && formperfil->idInst ? formperfil->idInst : "";
			idC = strtoll(formperfil && formperfil->idCurso ? formperfil->idCurso : "", NULL, 10);

		}



		// colocar as opções de instituições

		NoLinha* nl = mlEncontrar("@OpcoesInst", ml);

		char* htmlOpcoes = htmlOpcoesInstituicoes(idI);

		mlSubstituirTodosEmLinha("@OpcoesInst", htmlOpcoes, nl);

		// colocar as opções dos cursos

		nl = mlEncontrar("@OpcoesCurso", ml);

		htmlOpcoes = htmlOpcoesCursos(idIstr, idC);

		mlSubstituirTodosEmLinha("@OpcoesCurso", htmlOpcoes, nl);

		// modo edição

		if (editar)
			mlSubstituirTodos("$EDITAR$", "checked", ml);
		else
			mlSubstituirTodos("$EDITAR$", "", ml);

		mlImprimir(ml);

		return 0;
	//}
	//else {

	//	RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar informações sobre o usuário.");

	//	paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
	//	return 1;
	//}
}



int buscarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar parâmetros de buscas (campos do formulário)

	FormPerfil* fp = NULL;
	char* msg = NULL;

	extrairFormularioPerfil(form, &fp);

	Usuario* usus = NULL;
	int numUsus = 0;

	int ret = validarFormularioPerfil(fp, &rn);

	if (!ret) {

		// buscar instituições no banco de dados

		ret = bdBuscarUsuarioPerfil(fp->nome, fp->login, fp->email, fp->matricula, fp->idCurso, fp->idInst, &usus, &numUsus);

		if (ret) {
			rn = criarRegNoti(1, "Não foi possível buscar os usuários.");

			usus = NULL;
			numUsus = 0;
		}
	}

	paginaCadPerfil(usu, sessao, form, fp, rn, usus, numUsus);

	return ret;


}


int visualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id do usuário do perfil

    char* idUsuarioPerfil = NULL;

    if ( !(idUsuarioPerfil = obterCFHVal("idUsuarioPerfil", form, "identificador do usuário do perfil", CHARDIG, &rn)) ) {

        paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

    // obter id do perfil

    char* idPerfil = NULL;

    if ( !(idPerfil = obterCFHVal("idPerfil", form, "identificador do usuário do perfil", CHARDIG, &rn)) ) {

        paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

    // buscar usuário/perfil no banco

    Usuario* usuPerfil = NULL;

	int num;

	int ret = bdBuscarUsuarioPerfilId(idUsuarioPerfil, idPerfil, &usuPerfil, &num);

	if (ret) {

		RegNoti* rn = criarRegNoti(2, "Erro ao tentar resgatar informações sobre o perfil.");

		paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
		return 2;
	}
	else {
		paginaVisualizarPerfil(usu, sessao, form, NULL, NULL, usuPerfil, 0);
		return 0;
	}

}


int buscarUsuarioNovoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id do usuário do perfil

    char* login = NULL;

    if ( !(login = obterCFHVal("login", form, "login do usuário do perfil", CHARLOGIN, &rn)) ) {

		FormPerfil* fp = NULL;
		extrairFormularioPerfil(form, &fp);
        paginaNovoPerfil(usu, sessao, form, fp, rn, NULL);
        return 1;
    }

    Usuario* usuPerfil = NULL;
	int ret = bdBuscarUsuarioLogin(login, &usuPerfil);

	if (ret) {
		RegNoti* rn = criarRegNoti(1, "Login não encontrado.");

		paginaNovoPerfil(usu, sessao, form, NULL, rn, NULL);
	}
	else {
		paginaNovoPerfil(usu, sessao, form, NULL, NULL, usuPerfil);
	}

}


int salvarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar parâmetros de buscas (campos do formulário)

	FormPerfil* fp = NULL;

	extrairFormularioPerfil(form, &fp);

	// checar validade de caracteres

	int ret = validarFormularioPerfil(fp, &rn);

	// checar validade de caracteres

	if (!ret) {

		// salvar no banco

		fp->obs = aparar(&(fp->obs));

		ret = validarDadosPerfil(fp, &rn);

		if (!ret) {
			long long int idPR = 0;

			ret = bdCadastrarPerfilRespondedor(fp->idUsuario, fp->matricula, fp->idCurso, fp->habilitado, fp->obs, &idPR);

			if (ret) {

				// erro na inserção

				rn = criarRegNoti(1, "Erro na inserção do Usuário. Só pode haver um perfil para a mesma matrícula e o mesmo curso.");
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro

				rn = criarRegNoti(ret, "Perfil criado com sucesso.");

				paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
		}
	}

	paginaNovoPerfil(usu, sessao, form, fp, rn, NULL);

	return ret;

}


int atualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar os valores dos campos dos formulário

	char* idPerfil = NULL;

    if ( !(idPerfil = obterCFHVal("idPerfil", form, "identificador do usuário do perfil", CHARDIG, &rn)) ) {

        paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	// resgatar os valores dos campos dos formulário

	FormPerfil* fp = NULL;
	char* msg = NULL;

	extrairFormularioPerfil(form, &fp);

	fp->matricula = aparar(&(fp->matricula));
	fp->obs = aparar(&(fp->obs));

	// checar validade de caracteres

	int ret = validarFormularioPerfil(fp, &rn);

	if (!ret) {

		if (strlen(fp->matricula) != 0) {

			ret = bdAtualizarPerfilRespondedorId(idPerfil, fp->matricula, fp->idCurso, fp->habilitado, fp->obs);

			if (!ret) {
				RegNoti* rn = criarRegNoti(ret, "Perfil atualizado com sucesso.");

				paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
				return 0;
			}
			else {
				RegNoti* rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre o perfil.");
			}
		}
	}

	paginaVisualizarPerfil(usu, sessao, form, fp, rn, NULL, 1);
	return ret;
}


int removerPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar os valores dos campos dos formulário

	char* idPerfil = NULL;

    if ( !(idPerfil = obterCFHVal("idPerfil", form, "identificador do perfil", CHARDIG, &rn)) ) {

        paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	int ret = bdApagarPerfilRespondedorId(idPerfil);

	if (ret) {
		RegNoti* rn = criarRegNoti(ret, "Não foi possível remover o perfil. Perfil pode estar incluído em alguma turma.");

		FormPerfil* fp = NULL;
		extrairFormularioPerfil(form, &fp);

		// checar se botão editar está selecionado

		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "cbEditar");

		paginaVisualizarPerfil(usu, sessao, form, fp, rn, NULL, (cf ? 1 : 0) );
		return ret;
	}
	else {
		RegNoti* rn = criarRegNoti(ret, "Perfil removido com sucesso.");

		paginaCadPerfil(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}
}


int selInstituicaoCursoCadperfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	FormPerfil* fp = NULL;
	char* msg = NULL;

	extrairFormularioPerfil(form, &fp);

	paginaCadPerfil(usu, sessao, form, fp, NULL, NULL, 0);
}


int selInstituicaoCursoVisualizarPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	FormPerfil* fp = NULL;
	char* msg = NULL;

	extrairFormularioPerfil(form, &fp);

	paginaVisualizarPerfil(usu, sessao, form, fp, NULL, NULL, 1);
}


int selInstituicaoCursoNovoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	FormPerfil* fp = NULL;
	char* msg = NULL;

	extrairFormularioPerfil(form, &fp);

	paginaNovoPerfil(usu, sessao, form, fp, NULL, NULL);
}
