/* cadusu.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../../str/bibstring2.h"
#include "../../../../str/multilinhas.h"

#include "../../../../lugar.h"
#include "../../../../notifica.h"

#include "../../../sessaocgi.h"
#include "../../../htmlcgi.h"



typedef struct FormUsuario {
	char* idUsuario;
	char* nome;
	char* login;
	char* email;
	char* senha;
	char* professor;
	char* administrador;
	char* habilitado;
} FormUsuario;


void extrairFormularioUsuario(FormularioHTML* form, FormUsuario** formusu);

int validarFormularioUsuario(FormUsuario* formusu, RegNoti** rn);
int validarDadosUsuario(FormUsuario* formusu, RegNoti** rn);

int preencherFormularioUsuario(char* idUsuario, char* nome, char* login, char* email, char* senha, char* professor, char* administrador, char* habilitado, Multilinhas* ml);



int paginaCadUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormUsuario* formusu, RegNoti* rn, Usuario* usuarios, int numUsus);

char* htmlFormPaginaVisualizarUsuario(Usuario* usu, long long int idSessao);

int paginaNovoUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormUsuario* formusu, RegNoti* rn);

int paginaVisualizarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormUsuario* formusu, RegNoti* rn, Usuario* usuario, int editar);


int buscarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int visualizarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int salvarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int atualizarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int removerUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form);





/*		Implementações		*/




void extrairFormularioUsuario(FormularioHTML* form, FormUsuario** formusu){

	// extrair dados do formulário html

	FormUsuario* fu = (FormUsuario *) malloc( sizeof(FormUsuario) );

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idUsuario");
	fu->idUsuario = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "nome");
	fu->nome = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "login");
	fu->login = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "email");
	fu->email = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "senha");
	fu->senha = cf ? cf->valor : copiastr("");

	cf = obterCampoFormularioHTML(form, "professor");
	fu->professor = cf ? copiastr("1") : copiastr("0");

	cf = obterCampoFormularioHTML(form, "administrador");
	fu->administrador = cf ? copiastr("1") : copiastr("0");

	cf = obterCampoFormularioHTML(form, "habilitado");
	fu->habilitado = cf ? copiastr("1") : copiastr("0");

	*formusu = fu;
}



int validarFormularioUsuario(FormUsuario* formusu, RegNoti** rn) {

	// checar validade de caracteres

	if (utf8Val(formusu->idUsuario, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(1, "Caractere inválido no nome.");

		return 1;
	}
	else if (utf8Val(formusu->nome, CHARNOME, NULL)) {
		// caracteres inválidos na sigla

		if (rn)
			*rn = criarRegNoti(2, "Caractere inválido no nome.");

		return 2;
	}
	else if (utf8Val(formusu->login, CHARLOGIN, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(3, "Caractere inválido no login.");

		return 3;
	}
	else if (utf8Val(formusu->email, CHAREMAIL, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(4, "Caractere inválido no email.");

		return 4;
	}
	else if (utf8Val(formusu->senha, CHARSENHA, NULL)) {
		// caracteres inválidos no nome

		if (rn)
			*rn = criarRegNoti(5, "Caractere inválido na senha.");

		return 5;
	}
	else if (formusu->professor && utf8Val(formusu->professor, CHARDIG, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(6, "Caractere inválido no campo professor.");

		return 6;
	}
	else if (formusu->administrador && utf8Val(formusu->administrador, CHARDIG, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(7, "Caractere inválido no campo administrador.");

		return 7;
	}
	else if (formusu->habilitado && utf8Val(formusu->habilitado, CHARDIG, NULL)) {
		// caracteres inválidos

		if (rn)
			*rn = criarRegNoti(8, "Caractere inválido no campo habilitado.");

		return 8;
	}
	else{

		if (rn)
			*rn = NULL;

		return 0;
	}
}


int validarDadosUsuario(FormUsuario* formusu, RegNoti** rn) {

	if (strlen(formusu->nome) == 0 || strlen(formusu->login) == 0 || strlen(formusu->senha) == 0) {

		if (rn)
			*rn = criarRegNoti(1, "Nome, login ou senha inválidos.");

		return 1;
	}
	else {

		if (rn)
			*rn = criarRegNoti(0, "");

		return 0;
	}
}


int preencherFormularioUsuario(char* idUsuario, char* nome, char* login, char* email, char* senha, char* professor, char* administrador, char* habilitado, Multilinhas* ml) {

	mlSubstituirTodos("$IDUSUARIO$", idUsuario ? idUsuario : "", ml);
	mlSubstituirTodos("$NOME$", nome ? nome : "", ml);
	mlSubstituirTodos("$LOGIN$", login ? login : "", ml);
	mlSubstituirTodos("$EMAIL$", email ? email : "", ml);
	mlSubstituirTodos("$SENHA$", senha ? senha : "", ml);
	mlSubstituirTodos("$PROFESSOR$", professor && !strcmp(professor, "1") ? "checked" : "", ml);
	mlSubstituirTodos("$ADMINISTRADOR$", administrador && !strcmp(administrador, "1") ? "checked" : "", ml);
	mlSubstituirTodos("$HABILITADO$", habilitado && !strcmp(habilitado, "1") ? "checked" : "", ml);

	return 0;
}




int paginaCadUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormUsuario* formusu, RegNoti* rn, Usuario* usuarios, int numUsuarios) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadusu/cadusu.html");

	mlCarregarArquivoTexto(caminho, ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// copiar parâmetros nas caixas de texto

	if (formusu)
		preencherFormularioUsuario("", formusu->nome, formusu->login, formusu->email, "", formusu->professor, formusu->administrador, formusu->habilitado, ml);
	else
		preencherFormularioUsuario("", "", "", "", "",  "", "", "1", ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	if (usuarios) {

		char* linha;

		// montar lista de usuarios resultado da busca

		NoLinha* nlResultadoBusca = mlEncontrar("@resultadoBusca", ml);

		mlInserirAcima("<p>Lista de Usuários</p>", nlResultadoBusca, ml);

		for (int i = 0; i < numUsuarios; i++) {

			linha = htmlFormPaginaVisualizarUsuario(&(usuarios[i]), sessao->idSessao);
			mlInserirAcima(linha, nlResultadoBusca, ml);

		}

		nlResultadoBusca = mlEncontrar("@antesDivVoltar", ml);
		mlInserirAbaixo("<hr>", nlResultadoBusca, ml);

	}

	mlImprimir(ml);

}


char* htmlFormPaginaVisualizarUsuario(Usuario* usu, long long int idSessao) {

	Multilinhas* ml = mlCriar();

	char linha[500];

	mlInserirAbaixo("<form method=\"post\">", ml->ult, ml);

	sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"visuusu\">%s - %s - %s</button>\n", usu->login, usu->nome, usu->email );
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"idUsuario\" value=\"%lld\">\n", *(usu->idUsuario));
	mlInserirAbaixo(linha, ml->ult, ml);

	sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", idSessao);
	mlInserirAbaixo(linha, ml->ult, ml);
	mlInserirAbaixo("</form>", ml->ult, ml);

	return mlExtrairTexto(ml);

}


int paginaNovoUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormUsuario* formusu, RegNoti* rn) {


	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadusu/novousu.html");

	mlCarregarArquivoTexto(caminho, ml);

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// copiar parâmetros nas caixas de texto

	if (formusu)
		preencherFormularioUsuario("", formusu->nome, formusu->login, formusu->email, formusu->senha, formusu->professor, formusu->administrador, formusu->habilitado, ml);
	else
		preencherFormularioUsuario("", "", "", "", "",  "", "", "", ml);

	mlImprimir(ml);

	return 0;

}


int paginaVisualizarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form, FormUsuario* formusu, RegNoti* rn, Usuario* usuario, int editar) {

	Multilinhas* ml = mlCriar();

	char* caminho = concatstr(dirHtml, "/papeis/adm/cadusu/visuusu.html");

	mlCarregarArquivoTexto(caminho, ml);

	incluirDadosSessao(usu, sessao, form, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// checkbox editar

	if (editar)
		mlSubstituirTodos("$EDITAR$", "checked", ml);
	else
		mlSubstituirTodos("$EDITAR$", "", ml);

	if (usuario) {

		// colocar dados do usuario a ser visualizado no formulário

		preencherFormularioUsuario(llistr(*(usuario->idUsuario)), usuario->nome, usuario->login, usuario->email, "", *(usuario->professor) == 1 ? "1" : "0", *(usuario->adm) == 1 ? "1" : "0", *(usuario->habilitado) == 1 ? "1" : "0", ml);

	}
	else {

		// repetir valores dos campos

		if (formusu)
			preencherFormularioUsuario(formusu->idUsuario, formusu->nome, formusu->login, formusu->email, formusu->senha, formusu->professor, formusu->administrador, formusu->habilitado, ml);
		else
			preencherFormularioUsuario("", "", "", "", "", "", "", "", ml);

	//mlSubstituirTodos("$EDITAR$", "checked", ml);
	}

	mlImprimir(ml);

	return 0;
}



int buscarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar parâmetros de buscas

	FormUsuario* fu = NULL;
	char* msg = NULL;

	extrairFormularioUsuario(form, &fu);

	Usuario* usus = NULL;
	int numUsus = 0;

	// checar validade de caracteres

	int ret = validarFormularioUsuario(fu, &rn);

	if (!ret) {

		// buscar instituições no banco de dados

		int ret = bdBuscarUsuario(fu->nome, fu->login, fu->email, fu->administrador, fu->professor, fu->habilitado, &usus, &numUsus);

		if (ret) {
			rn = criarRegNoti(1, "Não foi possível buscar os usuários.");

			usus = NULL;
			numUsus = 0;

		}

	}

	paginaCadUsu(usu, sessao, form, fu, rn, usus, numUsus);

	return ret;
}


int visualizarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idUsuario = NULL;

    if ( !(idUsuario = obterCFHVal("idUsuario", form, "identificador do usuário", CHARDIG, &rn)) ) {

        paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

    Usuario* usuario = NULL;
	int num;

	int ret = bdBuscarUsuarioId(idUsuario, &usuario, &num);

	if (ret) {

		RegNoti* rn = criarRegNoti(2, "Erro ao tentar resgatar informações sobre o usuário.");
		paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
		return 2;
	}
	else {

		paginaVisualizarUsu(usu, sessao, form, NULL, NULL, usuario, 0);
		return 0;
	}

}


int salvarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

	// resgatar valores dos campos do formulário

	FormUsuario* fu = NULL;
	char* msg = NULL;

	extrairFormularioUsuario(form, &fu);

	// checar validade de caracteres

	int ret = validarFormularioUsuario(fu, &rn);

	if (!ret) {

		// salvar no banco

		fu->nome = aparar(&(fu->nome));
		fu->email = aparar(&(fu->email));
		fu->login = aparar(&(fu->login));
		fu->senha = aparar(&(fu->senha));

		ret = validarDadosUsuario(fu, &rn);
		if (!ret) {
			long long int idUsu = 0;

			ret = bdCadastrarUsuario (fu->nome, fu->login, fu->senha, fu->email, fu->administrador, fu->professor, fu->habilitado, &idUsu);

			if (ret) {

				// erro na inserção

				rn = criarRegNoti(ret, "Erro na inserção do Usuário. Tente outro login.");
			}
			else {

				// inserção realizada com sucesso, volta para a página de cadastro

				rn = criarRegNoti(ret, "Usuário criado com sucesso.");

				paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
				return ret;
			}
		}
	}

	paginaNovoUsu(usu, sessao, form, fu, rn);

	return ret;

}


int atualizarUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idUsuario = NULL;

    if ( !(idUsuario = obterCFHVal("idUsuario", form, "identificador do usuário", CHARDIG, &rn)) ) {

        paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	// resgatar valores dos campos do formulário

	FormUsuario* fu = NULL;
	char* msg = NULL;

	extrairFormularioUsuario(form, &fu);

	// checar validade de caracteres

	int ret = validarFormularioUsuario(fu, &rn);

	if (!ret) {

		if (strlen(fu->senha) != 0) {

			ret = validarDadosUsuario(fu, &rn);

			if (!ret) {

				ret = bdAtualizarUsuarioIdSenha(idUsuario, fu->nome, fu->login, fu->senha, fu->email, fu->administrador, fu->professor, fu->habilitado);

				if (!ret) {

					rn = criarRegNoti(0, "Usuário atualizado com sucesso.");

					paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
					return 0;
				}
				else {

					rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre o usuário.");
				}
			}

		}
		else {

			if (strlen(fu->nome) != 0 && strlen(fu->login) != 0) {

				ret = bdAtualizarUsuarioId(idUsuario, fu->nome, fu->login, fu->email, fu->administrador, fu->professor, fu->habilitado);

				if (!ret) {

					rn = criarRegNoti(ret, "Usuário atualizado com sucesso.");

					paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
					return 0;
				}
				else {

					rn = criarRegNoti(ret, "Erro ao tentar atualizar informações sobre o usuário.");
				}
			}
			else {

				rn = criarRegNoti(1, "Nome ou login inválidos.");
			}

		}

	}

	paginaVisualizarUsu(usu, sessao, form, fu, rn, NULL, 1);
	return ret;

}


int removerUsu(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	RegNoti* rn = NULL;

    // obter id da instituição

    char* idUsuario = NULL;

    if ( !(idUsuario = obterCFHVal("idUsuario", form, "identificador do usuário", CHARDIG, &rn)) ) {

        paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
        return 1;
    }

	int ret = bdApagarUsuarioId(idUsuario);

	if (ret) {

		RegNoti* rn = criarRegNoti(ret, "Não foi possível remover o usuário.");

		// resgatar dados do curso do formulário

		FormUsuario* fu = NULL;
		extrairFormularioUsuario(form, &fu);

		// checar se botão editar está selecionado

		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "cbEditar");

		paginaVisualizarUsu(usu, sessao, form, fu, rn, NULL, (cf ? 1 : 0) );
		return ret;
	}
	else {

		RegNoti* rn = criarRegNoti(ret, "Usuário removido com sucesso.");

		paginaCadUsu(usu, sessao, form, NULL, rn, NULL, 0);
		return ret;
	}
}
