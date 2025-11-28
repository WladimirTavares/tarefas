/* cadperfil.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../str/bibstring2.h"
#include "../../../str/multilinhas.h"

#include "../../../global.h"
#include "../../../notifica.h"

#include "../../sessaocgi.h"
#include "../../htmlcgi.h"

#include "cadperfillistas.h"



// Cadastro em lote

int paginaPerfilLote(Usuario* usu, Sessao* sessao, FormularioHTML* form, LinhaRelatorioCadastroLote* relcl, int tamrelc, RegNoti* rn);

int paginaPerfilLote2(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadastroLote* relcl, RegNoti* rn);

//int paginaPerfilLote2(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadastroLote* relcl, RegNoti* rn);

int validarLinhaPerfilLote(LinhaPerfilLote* lpl, char** msg);

// gera um relatório da validação dos dados
int validarLinhasPerfisLote(LinhaPerfilLote** lpls, int numLPL, LinhaRelatorioCadastroLote** relcl);

int validarLinhasPerfisLote2(ListaPerfilLote* listaPL, RelatorioCadastroLote* relcl);

int cadastrarPerfilDeLote(LinhaPerfilLote* lpl, Usuario** usuExistente, char** msg);

//int extrairPerfisML(Multilinhas* ml, LinhaPerfilLote** linhasPL, int* numLPL, RegNoti** rn);

int extrairListaPerfisML(Multilinhas* ml, ListaPerfilLote* listaPL, RegNoti** rn);

/*
char* htmlLinhaRelatorioCadastroLote(LinhaRelatorioCadastroLote* lrcl);

char* htmlLinhaRelatorioCadastroLote2(LinhaRelatorioCadastroLote* lrcl);
*/

char* htmlLinhaRelatorioCadastroLote3(LinhaRelatorioCadastroLote* lrcl);





/*		Cadstro de perfis em lote		*/



/*
int paginaPerfilLote(Usuario* usu, Sessao* sessao, FormularioHTML* form, LinhaRelatorioCadastroLote* relcl, int tamrelc, RegNoti* rn) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadperfil/loteperfil.html");

	mlCarregarArquivoTexto(caminho, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	if (relcl) {

		NoLinha* nl = mlEncontrar("@linhasPerfis", ml);

		char* linhaHTML = NULL;

		linhaHTML = copiastr("<table>\n");
		mlInserirAbaixo(linhaHTML, nl, ml);

		for (int i = 0; i < tamrelc; i++) {

			// gera a linha do código HTML

			linhaHTML = htmlLinhaRelatorioCadastroLote3(&(relcl[i]));

			mlInserirAbaixo(linhaHTML, nl, ml);

			free(linhaHTML);

			linhaHTML = NULL;

		}

		linhaHTML = copiastr("</table>\n");
		mlInserirAbaixo(linhaHTML, nl, ml);


	}

	mlImprimir(ml);

	//printf("%d - %p", tamrelc, relcl);return 0;
}
*/


int paginaPerfilLote2(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadastroLote* relcl, RegNoti* rn) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	char* caminho = concatstr(dirHtml, "/adm/cadperfil/loteperfil.html");

	mlCarregarArquivoTexto(caminho, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	if (relcl) {

		printf("vdc");

		NoLinha* nl = mlEncontrar("@linhasPerfis", ml);

		char* linhaHTML = NULL;

		linhaHTML = copiastr("<table>\n");
		mlInserirAbaixo(linhaHTML, nl, ml);

		NoLinhaRelatorioCadastroLote* nolinharcl = relcl->prim;

		if (nolinharcl) printf("ea");

		while (nolinharcl) {

			linhaHTML = htmlLinhaRelatorioCadastroLote3(nolinharcl->lrcl);

			printf("%s", linhaHTML);

			mlInserirAbaixo(linhaHTML, nl, ml);

			free(linhaHTML);

			linhaHTML = NULL;

			nolinharcl = nolinharcl->prox;
		}

		linhaHTML = copiastr("</table>\n");
		mlInserirAbaixo(linhaHTML, nl, ml);


	}

	mlImprimir(ml);

	//printf("%d - %p", tamrelc, relcl);return 0;
}


char* htmlLinhaRelatorioCadastroLote(LinhaRelatorioCadastroLote* lrcl) {

	char* linhaHTML = NULL;

	if (lrcl) {

		linhaHTML = concatstr("", lrcl->lpl->matricula);
			linhaHTML = concatstr(linhaHTML, ", ");
			linhaHTML = concatstr(linhaHTML, lrcl->lpl->codigoCurso);
			linhaHTML = concatstr(linhaHTML, ", ");
			linhaHTML = concatstr(linhaHTML, lrcl->lpl->siglaInst);
			linhaHTML = concatstr(linhaHTML, ", ");
			linhaHTML = concatstr(linhaHTML, lrcl->lpl->nome);
			linhaHTML = concatstr(linhaHTML, ", ");
			linhaHTML = concatstr(linhaHTML, lrcl->lpl->email);
			linhaHTML = concatstr(linhaHTML, ": ");
			linhaHTML = concatstr(linhaHTML, lrcl->msg);

		if (lrcl->numerr == 1) {		// perfil já existe


			linhaHTML = concatstr(linhaHTML, " Perfil já foi cadastrado no seguinte usuário: login: ");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->login);
			linhaHTML = concatstr(linhaHTML, ", nome: ");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->nome);
		}
		else if (lrcl->numerr == 2) {		// usuário já existe

			linhaHTML = concatstr(linhaHTML, " (Usuario: login: ");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->login);
			linhaHTML = concatstr(linhaHTML, ", nome: ");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->nome);
			linhaHTML = concatstr(linhaHTML, ")");
		}
		else if (lrcl->numerr != 0) {

			linhaHTML = concatstr(linhaHTML, " Não foi possível cadastrar perfil.");

		}

		linhaHTML = concatstr(linhaHTML, "<br>");
	}

	return linhaHTML;
}


char* htmlLinhaRelatorioCadastroLote2(LinhaRelatorioCadastroLote* lrcl) {

	char* linhaHTML = NULL;

	if (lrcl) {

		linhaHTML = copiastr("<tr><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->nome);
		linhaHTML = concatstr(linhaHTML, "</td><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->email);
		linhaHTML = concatstr(linhaHTML, "</td><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->login);
		linhaHTML = concatstr(linhaHTML, "</td><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->matricula);
		linhaHTML = concatstr(linhaHTML, "</td><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->codigoCurso);
		linhaHTML = concatstr(linhaHTML, "</td><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->siglaInst);
		linhaHTML = concatstr(linhaHTML, "</td><td>");
		linhaHTML = concatstr(linhaHTML, "</tr><tr><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->msg);
		linhaHTML = concatstr(linhaHTML, "</td>");

		if (lrcl->numerr == 1) {		// perfil já existe


			linhaHTML = concatstr(linhaHTML, "<td>Perfil já foi cadastrado no seguinte usuário:</td>");
			linhaHTML = concatstr(linhaHTML, "<td>login:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->login);
			linhaHTML = concatstr(linhaHTML, "</td><td>nome:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->nome);
			linhaHTML = concatstr(linhaHTML, "</td><td>email:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->email);
			linhaHTML = concatstr(linhaHTML, "</td>");
		}
		else if (lrcl->numerr == 2) {		// usuário já existe

			linhaHTML = concatstr(linhaHTML, "<td> Inclusão de perfil deve ser feita de forma manual no seguinte usuário:</td><td>login:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->login);
			linhaHTML = concatstr(linhaHTML, "</td><td>nome:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->nome);
			linhaHTML = concatstr(linhaHTML, "</td><td>email:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->email);
			linhaHTML = concatstr(linhaHTML, "</td>");
		}
		else if (lrcl->numerr != 0) {

			linhaHTML = concatstr(linhaHTML, "<td>Não foi possível cadastrar perfil.</td><td></td><td></td><td></td><td></td><td></td><td></td>");

		}

		linhaHTML = concatstr(linhaHTML, "</tr>\n");
	}

	return linhaHTML;
}



char* htmlLinhaRelatorioCadastroLote3(LinhaRelatorioCadastroLote* lrcl) {

	char* linhaHTML = NULL;

	if (lrcl) {

		printf("KKK");

		linhaHTML = copiastr("<tr><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->nome);
		linhaHTML = concatstr(linhaHTML, ",");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->email);
		linhaHTML = concatstr(linhaHTML, ",");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->login);
		linhaHTML = concatstr(linhaHTML, ",");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->matricula);
		linhaHTML = concatstr(linhaHTML, ",");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->codigoCurso);
		linhaHTML = concatstr(linhaHTML, ",");
		linhaHTML = concatstr(linhaHTML, lrcl->lpl->siglaInst);
		linhaHTML = concatstr(linhaHTML, "</td>");
		linhaHTML = concatstr(linhaHTML, "</tr><tr><td>");
		linhaHTML = concatstr(linhaHTML, lrcl->msg);
		//linhaHTML = concatstr(linhaHTML, "</td>");

		if (lrcl->numerr == 1) {		// perfil já existe


			linhaHTML = concatstr(linhaHTML, " Perfil já foi cadastrado no seguinte usuário:</td>");
			linhaHTML = concatstr(linhaHTML, "<td>login:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->login);
			linhaHTML = concatstr(linhaHTML, "</td><td>nome:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->nome);
			linhaHTML = concatstr(linhaHTML, "</td><td>email:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->email);
			//linhaHTML = concatstr(linhaHTML, "</td>");
		}
		else if (lrcl->numerr == 2) {		// usuário já existe

			linhaHTML = concatstr(linhaHTML, " Inclusão de perfil deve ser feita de forma <br>manual no seguinte usuário:</td><td>login:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->login);
			linhaHTML = concatstr(linhaHTML, "</td><td>nome:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->nome);
			linhaHTML = concatstr(linhaHTML, "</td><td>email:</td><td>");
			linhaHTML = concatstr(linhaHTML, lrcl->usuExistente->email);
			//linhaHTML = concatstr(linhaHTML, "</td>");
		}
		else if (lrcl->numerr != 0) {

			linhaHTML = concatstr(linhaHTML, " Não foi possível cadastrar perfil.</td><td></td><td></td><td></td><td></td><td></td><td></td>");

		}

		linhaHTML = concatstr(linhaHTML, "</td></tr><tr><td class=\"espacoVertical\"></td></tr>\n");
	}

	return linhaHTML;
}





int validarLinhaPerfilLote(LinhaPerfilLote* lpl, char** msg) {

	// checar validade de caracteres

	if (utf8Val(lpl->nome, CHARNOME, NULL)) {
		// caracteres inválidos na sigla

		*msg = copiastr("Caractere inválido no nome do usuário.");

		return 1;
	}
	else if (lpl->nome && strlen(lpl->nome) == 0) {
		// nome não pode ser vazio

		*msg = copiastr("Nome não pode ser vazio.");

		return 2;
	}
	else if (utf8Val(lpl->email, CHAREMAIL, NULL)) {
		// caracteres inválidos na sigla

		*msg = copiastr("Caractere inválido no email do usuário.");

		return 3;
	}
	else if (utf8Val(lpl->login, CHARLOGIN, NULL)) {
		// caracteres inválidos no nome

		*msg = copiastr("Caractere inválido no login.");

		return 4;
	}
	else if (lpl->login && strlen(lpl->login) == 0) {
		// nome não pode ser vazio

		*msg = copiastr("Login não pode ser vazio.");

		return 5;
	}
	else if (utf8Val(lpl->senha, CHARSENHA, NULL)) {
		// caracteres inválidos no nome

		*msg = copiastr("Caractere inválido na senha.");

		return 6;
	}
	else if (lpl->senha && strlen(lpl->senha) == 0) {
		// nome não pode ser vazio

		*msg = copiastr("Senha não pode ser vazia.");

		return 7;
	}
	else if (utf8Val(lpl->matricula, CHARMAT, NULL)) {
		// caracteres inválidos no nome

		*msg = copiastr("Caractere inválido na matrícula.");

		return 8;
	}
	else if (lpl->matricula && strlen(lpl->matricula) == 0) {
		// nome não pode ser vazio

		*msg = copiastr("Matrícula não pode ser vazia.");

		return 9;
	}
	else if (utf8Val(lpl->codigoCurso, CHARCODIGO, NULL)) {
		// caracteres inválidos no nome

		*msg = copiastr("Caractere inválido no código do curso.");

		return 10;
	}
	else if (lpl->codigoCurso && strlen(lpl->codigoCurso) == 0) {
		// nome não pode ser vazio

		*msg = copiastr("Código de curso não pode ser vazio.");

		return 11;
	}
	else if (utf8Val(lpl->siglaInst, CHARSIGLA, NULL)) {
		// caracteres inválidos

		*msg = copiastr("Caractere inválido na sigla da instituição.");

		return 12;
	}
	else if (lpl->siglaInst && strlen(lpl->siglaInst) == 0) {
		// nome não pode ser vazio

		*msg = copiastr("Sigla não pode ser vazia.");

		return 13;
	}
	else{

		*msg = copiastr("Dados válidos. Perfil pronto para cadastro.");

		return 0;
	}

}

/*
int validarLinhasPerfisLote(LinhaPerfilLote** lpls, int numLPL, LinhaRelatorioCadastroLote** relcl) {

	int flag = 0;

	if (lpls && *lpls) {

		if (numLPL > 0) {

			*relcl = (LinhaRelatorioCadastroLote *) malloc(numLPL * sizeof(LinhaRelatorioCadastroLote));

			for (int i = 0; i < numLPL; i++) {

				char* msg = NULL;

				int ret = validarLinhaPerfilLote( &((*lpls)[i]), &msg);

				(*relcl)[i].numerr = ret;

				if (ret)
					flag = 1;

				(*relcl)[i].msg = msg;
				(*relcl)[i].lpl = &((*lpls)[i]);
				(*relcl)[i].usuExistente = NULL;

			}

			return flag;
		}
	}

	*relcl = NULL;

	return 1;
}
*/

/*
int validarLinhasPerfisLote2(ListaPerfilLote* listaPL, RelatorioCadastroLote* relcl) {

	int flag = 0;

	if (listaPL) {

		if (listaPL->numlpls > 0) {

			NoLinhaPerfilLote* nolpl = listaPL->prim;

			while (nolpl) {

				char* msg  = NULL;

				int ret = validarLinhaPerfilLote(nolpl->linhapl, &msg);

				if (ret)
					flag = 1;

				LinhaRelatorioCadastroLote* linharelcl = rclConstruirLRCL(ret, msg, nolpl->linhapl, NULL);

				rclInserirLinhaRelatorioCadastroLote(linharelcl, relcl);

				nolpl = nolpl->prox;
			}

			return flag;
		}
	}

	return 1;
}
*/

int validarLinhasPerfisLote2(ListaPerfilLote* listaPL, RelatorioCadastroLote* rcl) {

	int flag = 0;

	if (listaPL) {

		if (listaPL->prim) {

			// percorrer lista de linhas perfis a serem cadastrados

			NoLinhaPerfilLote* nlpl = listaPL->prim;

			while (nlpl) {

				char* msg = NULL;

				// validar dados

				int ret = validarLinhaPerfilLote( nlpl->linhapl, &msg);

				// construir linha do relatório de tentativa cadastro em lote

				LinhaRelatorioCadastroLote* lrcl = rclConstruirLRCL(ret, msg, nlpl->linhapl, NULL);

				// Checa se houve algum erro de validação, antes que todas as linhas sejam validadas não haverá tentativa de inserção no banco

				if (ret)
					flag = 1;

				// inserir linha do relatório
				rclInserirLinhaRelatorioCadastroLote(lrcl, rcl);

				nlpl = nlpl->prox;
			}

			return flag;
		}
	}

	return 1;
}


/*
int cadastrarPerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// acessar arquivo

	CampoFormularioHTML* arqListaPerfis = obterCampoFormularioHTML(form, "listaperfis");

	if (arqListaPerfis && arqListaPerfis->nomeArquivo && strlen(arqListaPerfis->nomeArquivo)) {

		char* texto = segtostr(arqListaPerfis->conteudoArquivo);

		Multilinhas* ml = mlCriar();

		mlAnexarTexto(texto, ml);

		// extrair dados dos perfis a serem criados

		//LinhaPerfilLote* lpls = NULL;
		ListaPerfilLote* listaPL = lplCriarListaPL();

		int nlpls = 0;
		RegNoti* rn = NULL;

		int ret = extrairListaPerfisML(ml, listaPL, &rn);

		if (ret) {		// erro ao tentar extrair perfis da lista

			paginaPerfilLote2(usu, sessao, form, NULL, rn);
			return 0;
		}
		else {

			if (nlpls == 0) {		// lista vazia

				rn = criarRegNoti(1, "Lista de perfis vazia.");
				paginaPerfilLote2(usu, sessao, form, NULL, rn);
				return 0;
			}

			// validar dados

			//LinhaRelatorioCadastroLote* relcl = NULL;
			RelatorioCadastroLote* relcl = rclCriarRCL();

			//ret = validarLinhasPerfisLote(&lpls, nlpls, &relcl);
			ret = validarLinhasPerfisLote2(listaPL, relcl);

			if (ret) {		// houve falha de validação de dos dados de perfis

				paginaPerfilLote2(usu, sessao, form, relcl, NULL);

				return 1;
			}

			// cadastrar perfis e criar relatório de cadastro em lote

			//relcl = (LinhaRelatorioCadastroLote *) malloc(nlpls * sizeof(LinhaRelatorioCadastroLote));

			NoLinhaPerfilLote* nolpl = listaPL->prim;

			while (nolpl) {

				Usuario* usuExistente = NULL;
				char* msg = NULL;

				ret = cadastrarPerfilDeLote(nolpl->linhapl, &usuExistente, &msg);

				LinhaRelatorioCadastroLote* lrcl = rclConstruirLRCL(ret, msg, nolpl->linhapl, usuExistente);

				rclInserirLinhaRelatorioCadastroLote(lrcl, relcl);

				nolpl = nolpl->prox;
			}

			paginaPerfilLote2(usu, sessao, form, relcl, rn);

		}

	}
	else {
		RegNoti* rn = criarRegNoti(12, "Nenhum arquivo foi selecionado.");

		paginaPerfilLote(usu, sessao, form, NULL, 0, rn);
	}

}
*/


int cadastrarPerfisLote(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// acessar arquivo

	CampoFormularioHTML* arqListaPerfis = obterCampoFormularioHTML(form, "listaperfis");

	if (arqListaPerfis && arqListaPerfis->nomeArquivo && strlen(arqListaPerfis->nomeArquivo)) {

		char* texto = segtostr(arqListaPerfis->conteudoArquivo);

		Multilinhas* ml = mlCriar();

		mlAnexarTexto(texto, ml);

		// extrair dados dos perfis a serem criados

		ListaPerfilLote* listaPL = lplCriarListaPL();

		int nlpls = 0;
		RegNoti* rn = NULL;

		int ret = extrairListaPerfisML(ml, listaPL, &rn);

		// checar extração da lista de perfis

		if (ret) {		// erro ao tentar extrair perfis da lista

			paginaPerfilLote2(usu, sessao, form, NULL, rn);
			return 0;
		}

		// checar se há perfis a serem cadastradps

		if (listaPL->numlpls == 0) {		// lista vazia

			rn = criarRegNoti(1, "Lista de perfis vazia.");
			paginaPerfilLote2(usu, sessao, form, NULL, rn);
			return 0;
		}

		// validar dados

		RelatorioCadastroLote* relcl = rclCriarRCL();		// criar relatório

		//ret = validarLinhasPerfisLote2(listaPL, relcl);

		// checar se dados foram validados

		if (ret) {		// houve falha de validação de dos dados de perfis

			paginaPerfilLote2(usu, sessao, form, relcl, NULL);

			return 1;
		}

		// cadastrar perfis e criar relatório de cadastro em lote

		// relcl = (LinhaRelatorioCadastroLote *) malloc(nlpls * sizeof(LinhaRelatorioCadastroLote));

		NoLinhaPerfilLote* noLPL = listaPL->prim;

		while (noLPL) {

			// cadastrar perfil i

			Usuario* usuExistente = NULL;
			char* msg = NULL;

			ret = cadastrarPerfilDeLote(noLPL->linhapl, &usuExistente, &msg);

			LinhaRelatorioCadastroLote* linhaRPL = rclConstruirLRCL(ret, msg, noLPL->linhapl, usuExistente);

			rclInserirLinhaRelatorioCadastroLote(linhaRPL, relcl);

			noLPL = noLPL->prox;

			printf("sss");
		}

		printf("fffff");
		paginaPerfilLote2(usu, sessao, form, relcl, rn);



	}
	else {
		RegNoti* rn = criarRegNoti(12, "Nenhum arquivo foi selecionado.");

		paginaPerfilLote2(usu, sessao, form, NULL, rn);
	}

}


int cadastrarPerfilDeLote(LinhaPerfilLote* lpl, Usuario** usuExistente, char** msg) {

	// checar se perfil existe a partir da matrícula, do curso e da instituição

	Usuario* up = NULL;
	int nup = 0;

	*usuExistente = NULL;

	int ret = bdBuscarUsuarioPerfilMatriculaCodCursoSiglaInst(lpl->matricula, lpl->codigoCurso, lpl->siglaInst, &up, &nup);

	if(!ret) {

		if (nup) {

			// perfil existe

			*usuExistente = up;
			*msg = copiastr("Perfil já existe.");

			return 1;
		}
		else {

			// perfil novo

			// checar se usuario existe

			Usuario* usu = NULL;

			int ret = bdBuscarUsuarioLogin(lpl->login, &usu);

			if (usu) {		// usuário existe

				// inclusão de perfil em usuário existente deve ser feita de forma manual

				*usuExistente = usu;
				*msg = copiastr("Usuário já existe.");

				return 2;
			}
			else {

				// criar usuário

				long long int idUsuario;
				//ret = bdCadastrarUsuario(lpl->nome, lpl->login, lpl->senha, lpl->email, "0", "0", "1", &idUsuario);

				if (ret) {		// erro ao tentar cadastrar usuário no banco

					*msg = copiastr("Erro ao tentar cadastrar usuário no banco.");

					return 6;

				}
				else {

					// cadastrar perfil

					// checar se curso existe

					Curso* curso = NULL;
					int nc = 0;

					ret = bdBuscarCursoCodigoSiglaInst(lpl->codigoCurso, lpl->siglaInst, &curso, &nc);

					if (curso == 0) {

						// curso não existe

						*msg = copiastr("Curso não existe.");

						return 7;
					}

					char* strIdUsuario = llistr(idUsuario);
					char* strIdCurso = llistr(*(curso->idCurso));
					long long int idPerfilRespondedor = 0;

					//ret = bdCadastrarPerfilRespondedor(strIdUsuario, lpl->matricula, strIdCurso, "1", "", &idPerfilRespondedor);

					if (ret) {

						// erro ao cadastrar perfil no banco

						*msg = copiastr("Erro ao tentar cadastrar perfil no banco.");

						return 8;
					}
					else {

						// perfil criado com sucesso

						*msg = copiastr("Perfil criado com sucesso.");

						return 0;
					}
				}

			}
		}
	}
	else {

		// erro ao tentar verificar existência do perfil no banco

		*msg = copiastr("Erro ao tentar checar perfil no banco.");

	}


}


/*
 * Layout do arquivo para inclusão de perfis em lote.
 *
 * Cada linha deve ter o seguinte padrão:
 *
 * <nome-respondedor>, <email-respondedor>, <login-respondedor>, <senha-respondedor>, <matricula-perfil>, <codigo-curso-perfil>, <sigla-instituição-perfil>
 *
 *
 */

/*
int extrairPerfisML(Multilinhas* ml, LinhaPerfilLote** linhasPL, int* numLPL, RegNoti** rn) {

	if (ml) {

		// remove linhas em branco

		mlRemoverLinhasEmBranco(ml);

		// checar número de campos em cada linha

		NoLinha* nl = ml->prim;
		int nlin = 0;
		int nc = 0;

		while (nl) {

			if (nl->linha) {

				nc = contacar(nl->linha, ',');

				if (nc != 6) {		// número de campos errado

					char msg[21+41] = "";

					sprintf(msg, "A linha %d possui número errado de campos: %d campos.", nlin + 1, nc);
					*rn = criarRegNoti(1, msg);

					return 1;
				}
			}
			else {
				char msg[14 + 21] = "";

				sprintf(msg, "Linha %d nula.", nc);
				*rn = criarRegNoti(2, msg);

				return 2;
			}

			nl = nl->prox;
			nlin++;
		}

		// Criar perfis. Será uma lista de usuários com um perfil cada

		*linhasPL = NULL;

		int i = 0;

		nl = ml->prim;

		while (nl && nl->linha) {

			// mais uma linha
			*linhasPL = (LinhaPerfilLote *) realloc(*linhasPL, (i + 1) * sizeof(LinhaPerfilLote));

			char** segs = NULL;
			int nsegs = 0;

			// dividir linha em segmentos separados por ','

			int ret = fragstr(nl->linha, ',', &segs, &nsegs);

			if (!ret){
				(*linhasPL)[i].nome = aparar(&(segs[0]));
				(*linhasPL)[i].email = aparar(&(segs[1]));
				(*linhasPL)[i].login = aparar(&(segs[2]));
				(*linhasPL)[i].senha = aparar(&(segs[3]));
				(*linhasPL)[i].matricula = aparar(&(segs[4]));
				(*linhasPL)[i].codigoCurso = aparar(&(segs[5]));
				(*linhasPL)[i].siglaInst = aparar(&(segs[6]));

				//printf("%s.", (*linhasPL)[i].siglaInst);

			}
			else {

				char* msg = NULL;

				if (ret == 1)
					msg = copiastr("Caractere delimitador inválido.");
				else if (ret == 2)
					msg = copiastr("String inválida.");

				*rn = criarRegNoti(ret, msg);

				return ret;
			}

			i++;
			nl = nl->prox;
		}

		*numLPL = i;


		*rn = criarRegNoti(0, "");

		return 0;
	}

	*rn = criarRegNoti(3, "Problem na lista de perfis.");

	return 3;
}
*/



int extrairListaPerfisML(Multilinhas* ml, ListaPerfilLote* listaPL, RegNoti** rn) {

	if (ml) {

		// remove linhas em branco

		mlRemoverLinhasEmBranco(ml);

		// checar número de campos em cada linha

		NoLinha* nl = ml->prim;
		int nlin = 0;
		int nc = 0;

		while (nl) {

			if (nl->linha) {

				nc = contacar(nl->linha, ',');

				if (nc != 6) {		// número de campos errado

					char msg[21+41] = "";

					sprintf(msg, "A linha %d possui número errado de campos: %d campos.", nlin + 1, nc);
					*rn = criarRegNoti(1, msg);

					return 1;
				}
			}
			else {
				char msg[14 + 21] = "";

				sprintf(msg, "Linha %d nula.", nc);
				*rn = criarRegNoti(2, msg);

				return 2;
			}

			nl = nl->prox;
			nlin++;
		}

		// Criar perfis. Será uma lista de usuários com um perfil cada

		int i = 0;

		nl = ml->prim;

		while (nl && nl->linha) {

			// mais uma linha
			///*linhasPL = (LinhaPerfilLote *) realloc(*linhasPL, (i + 1) * sizeof(LinhaPerfilLote));

			char** segs = NULL;
			int nsegs = 0;

			// dividir linha em segmentos separados por ','

			int ret = fragstr(nl->linha, ',', &segs, &nsegs);

			if (!ret){

				LinhaPerfilLote* linhapl = (LinhaPerfilLote *) malloc (sizeof(LinhaPerfilLote));

				linhapl->nome = aparar(&(segs[0]));
				linhapl->email = aparar(&(segs[1]));
				linhapl->login = aparar(&(segs[2]));
				linhapl->senha = aparar(&(segs[3]));
				linhapl->matricula = aparar(&(segs[4]));
				linhapl->codigoCurso = aparar(&(segs[5]));
				linhapl->siglaInst = aparar(&(segs[6]));

				lplInserirLinhaPerfilLote(linhapl, listaPL);
				printf("yyy");
			}
			else {

				char* msg = NULL;

				if (ret == 1)
					msg = copiastr("Caractere delimitador inválido.");
				else if (ret == 2)
					msg = copiastr("String inválida.");

				*rn = criarRegNoti(ret, msg);

				return ret;
			}

			i++;
			nl = nl->prox;
		}

		*rn = criarRegNoti(0, "");

		return 0;
	}

	*rn = criarRegNoti(3, "Problem na lista de perfis.");

	return 3;
}

