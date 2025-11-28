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

#include "cadperfillistas.h"



// Cadastro em lote


char* CAMINHO_PAGINA_ENVIAR_LOTE = NULL;
char* CAMINHO_PAGINA_CHECAR_LOTE = NULL;
char* CAMINHO_PAGINA_RELATORIO_LOTE = NULL;

char* HTML_BOTAO_PROXIMO_PAGINA_CHECAR = NULL;
char* HTML_BOTAO_CHECAR_PAGINA_CHECAR = NULL;


int paginaEnviarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadPerfil* rel, RegNoti* rn);

int enviarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int extrairListaPerfis(Multilinhas* ml, ListaPerfilLote* lista, RelatorioCadPerfil* rel);



// exibe o conteúdo do arquivo e mensagens de erro de tipos de caracteres ou campos vazios
int paginaConteudoLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, ListaPerfilLote* lista, RelatorioCadPerfil* rel, RegNoti* rn);

	char* htmlLinhaPerfilLote(LinhaPerfilLote* lpl, int i, int cadastrar);

	int checarDadosLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form);

		int extrairPerfisFormulario(ListaPerfilLote* lista, FormularioHTML* form);

		int bateriaValidacoesListaPerfis(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

			int validarDadosListaPerfis(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

				int validarDadosPerfilLote(LinhaPerfilLote* lpl, char** msg);

			int checarCursos (ListaPerfilLote* lista, RelatorioCadPerfil* rel);

			// verifica se há perfis duplicados entre os que serão criados
			int checarPerfisRepetidos(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

			int buscarPerfisExistentes(ListaPerfilLote* lista);

			// valida os dados para a criação de novo usuário, se for o caso
			int validarDadosNovoUsuario(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

			// verifica se há logins duplicados entre os que serão criados
			int checarNovosLoginsDuplicados(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

			int buscarLoginsExistentes(ListaPerfilLote* lista);

	// extrai dados do formulário, valida os dados e cadastra
	int cadastrarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form);

		int cadastrarListaPerfis(ListaPerfilLote* lista, RelatorioCadPerfil* rel);



int paginaRelatorioLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, ListaPerfilLote* lista, RelatorioCadPerfil* rel, RegNoti* rn);

	char* htmlLinhaPerfilLote2(LinhaPerfilLote* lpl, int i, int loginperfilExistente);









/*		Cadastro de perfis em lote		*/



int paginaEnviarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadPerfil* rel, RegNoti* rn) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	//char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/enviarperfis.html");
	char* caminho = concatstr(dirHtml, CAMINHO_PAGINA_ENVIAR_LOTE);

	mlCarregarArquivoTexto(caminho, ml);

	// colocar mensagem

	char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// caso haja id de turma disponível, colocar na página

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idTurma");

	if (cf && cf->valor) mlSubstituirTodos("$IDTURMA$", cf->valor, ml);

	// imprimir relatório

	if (rel) {

		NoLinha* nl = mlEncontrar("@linhasRelatorioCadastro", ml);

		char linhaHTML[500] = "";


		mlInserirAcima("<table>\n", nl, ml);

		NoLinhaRelCadPerfil* nolr = rel->prim;

		while (nolr) {

			sprintf(linhaHTML, "<p>%s</p>", nolr->linha->msg);

			mlInserirAcima(linhaHTML, nl, ml);

			nolr = nolr->prox;

		}

		mlInserirAcima("</table>\n", nl, ml);

	}

	mlImprimir(ml);

	//printf("%d - %p", tamrelc, relcl);return 0;
}


int enviarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	CAMINHO_PAGINA_ENVIAR_LOTE = "/papeis/adm/cadperfil/enviarperfis.html";
	CAMINHO_PAGINA_CHECAR_LOTE = "/papeis/adm/cadperfil/checarperfis.html";
	CAMINHO_PAGINA_RELATORIO_LOTE = "/papeis/adm/cadperfil/relatoriocadastroperfis.html";

	HTML_BOTAO_CHECAR_PAGINA_CHECAR = "<br>\n<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"checardadosloteperfis\">checar perfis</button>\n";
	HTML_BOTAO_PROXIMO_PAGINA_CHECAR = "<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"cadastrarloteperfis\">cadastrar perfis</button>";

	// acessar arquivo

	CampoFormularioHTML* arqListaPerfis = obterCampoFormularioHTML(form, "listaperfis");

	// checa se foi enviado arquivo e se o nome não é vazio
	if (arqListaPerfis && arqListaPerfis->nomeArquivo && strlen(arqListaPerfis->nomeArquivo)) {

		char* texto = segtostr(arqListaPerfis->conteudoArquivo);

		Multilinhas* ml = mlCriar();

		mlAnexarTexto(texto, ml);

		// Extrair dados dos perfis a serem criados
		//
		// primeiro é feita uma checagem do número de campos em cada linha
		// essa checagem gera um relatório indicando quais linhas possuem a quantidade errada de campos
		//
		// caso nao haja linhas com quantidade errada de campos, é feita a extração dos dados com a construção
		// de uma lista de registros de perfis (ListaPerfilLote)

		ListaPerfilLote* lista = lplCriarLista();
		RelatorioCadPerfil* rel = rcpCriar();

		int nlpls = 0;
		RegNoti* rn = NULL;

		int ret = extrairListaPerfis(ml, lista, rel);

		// Em caso de erro imprimir relatório

		if (ret) {

			paginaEnviarLotePerfis(usu, sessao, form, rel, rn);

			return 1;

		}

		// exibir o conteúdo do arquivo lote

		paginaConteudoLotePerfis(usu, sessao, form, lista, NULL, NULL);

		return 0;


	}
	else {
		RegNoti* rn = criarRegNoti(12, "Nenhum arquivo foi selecionado.");

		paginaEnviarLotePerfis(usu, sessao, form, NULL, rn);

		return 4;
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

int extrairListaPerfis(Multilinhas* ml, ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	if (ml) {

		// remove linhas em branco

		mlRemoverLinhasEmBranco(ml);

		//
		NoLinha* nl;

		// checar número de campos em cada linha, para cada linha com o número errado de campo
		// gera uma linha de relatório indicando erro

		if (lplNumCamposListaPerfis(ml, rel))
			return 1;

		char msg[500] = "";

		int i = 0;
		nl = ml->prim;

		int ret = 0;
		while (nl && nl->linha) {

			// array de segmentos
			char** segs = NULL;
			int nsegs = 0;

			// dividir linha em segmentos separados por ','

			if (!fragstr(nl->linha, ',', &segs, &nsegs)){

				// criar registro de perfil
				LinhaPerfilLote* linha = (LinhaPerfilLote *) malloc (sizeof(LinhaPerfilLote));

				linha->nome = aparar(&(segs[0]));
				linha->email = aparar(&(segs[1]));
				linha->login = aparar(&(segs[2]));
				linha->senha = aparar(&(segs[3]));
				linha->matricula = aparar(&(segs[4]));
				linha->codigoCurso = aparar(&(segs[5]));
				linha->siglaInst = aparar(&(segs[6]));

				//linha->perfilExiste = 0;
				linha->perfilExistente = NULL;

				lplInserirLinha(linha, lista);

			}
			else {

				rel->status = 3;

                sprintf(msg, "A linha %d é inválida. Verifique se o arquivo está corrompido.", i + 1);

                LinhaRelCadPerfil* linha = rcpConstruirLinha(3, msg, NULL);

                rcpInserirLinha(linha, rel);

				ret = 2;
			}

			i++;
			nl = nl->prox;
		}

		return ret;
	}

	return 3;
}



int paginaConteudoLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, ListaPerfilLote* lista, RelatorioCadPerfil* rel, RegNoti* rn) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	//char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/checarperfis.html");
	char* caminho = concatstr(dirHtml, CAMINHO_PAGINA_CHECAR_LOTE);

	mlCarregarArquivoTexto(caminho, ml);

	// colocar mensagem

	//char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", "", ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// caso haja id de turma disponível, colocar na página

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idTurma");

	if (cf && cf->valor) mlSubstituirTodos("$IDTURMA$", cf->valor, ml);


	// imprimir relatório de perfis existentes

	// encontrar posição do relatório no html
	NoLinha* nl = mlEncontrar("@listaPerfisSubmetidos", ml);

	char linha[1000] = "";

	if (lista) {

		sprintf(linha,
				"<input type=\"hidden\" name=\"numPerfis\" value=\"%d\">\n",
				lista->numlins);
		mlInserirAcima(linha, nl, ml);

		mlInserirAcima("<table>\n", nl, ml);

		// cabeçalho da tabela
		mlInserirAcima("	<tr>\n"
						"		<td></td>\n"
						"		<td><b>nome</b></td>\n"
						"		<td><b>email</b></td>\n"
						"		<td><b>login</b></td>\n"
						"		<td><b>senha</b></td>\n"
						"		<td><b>matricula</b></td>\n"
						"		<td><b>codigo curso</b></td>\n"
						"		<td><b>sigla instituição</b></td>\n"
						"	</tr>\n",
				 nl, ml);

		NoLinhaPerfilLote* nolp = lista->prim;

		char* html = NULL;

		int i = 1;

		while (nolp) {

			html = htmlLinhaPerfilLote(nolp->linha, i, 0);

			mlInserirAcima(html, nl, ml);

			nolp = nolp->prox;
			i++;
		}

		mlInserirAcima("</table>\n", nl, ml);

		mlInserirAbaixo(HTML_BOTAO_CHECAR_PAGINA_CHECAR, nl, ml);
	}
	else if (rel) {

		sprintf(linha,
				"<input type=\"hidden\" name=\"numPerfis\" value=\"%d\">\n",
				rel->numlins);

		mlInserirAcima(linha, nl, ml);

		mlInserirAcima("<table>\n", nl, ml);

		// cabeçalho da tabela
		mlInserirAcima("	<tr>\n"
						"		<td></td>\n"
						"		<td><b>nome</b></td>\n"
						"		<td><b>email</b></td>\n"
						"		<td><b>login</b></td>\n"
						"		<td><b>senha</b></td>\n"
						"		<td><b>matricula</b></td>\n"
						"		<td><b>codigo curso</b></td>\n"
						"		<td><b>sigla instituição</b></td>\n"
						"		<td><b>cadastrar</b></td>\n"
						"	</tr>\n",
				 nl, ml);

		NoLinhaRelCadPerfil* nolr = rel->prim;

		char* html = NULL;

		int i = 1;

		while (nolr) {

			int cadastrar = 0;

			if (rel->status == 0) {
				if (!(nolr->linha->lpl->perfilExistente)) {
					if (nolr->linha->lpl->loginExistente) cadastrar = 1;
					else cadastrar = 2;
				}
			}


			html = htmlLinhaPerfilLote(nolr->linha->lpl, i, cadastrar);
			mlInserirAcima(html, nl, ml);

			// imprimir mensagem do relatório
			char linhaHTML[1000] = "";

			if (nolr->linha->numerr) {
				sprintf(linhaHTML,
					"	<tr>\n"
					"		<td colspan=\"8\">%s</td>\n"
					"	</tr>\n",
					nolr->linha->msg);
			}
			else if (nolr->linha->lpl->perfilExistente) {

				LinhaPerfilLote* lpl = nolr->linha->lpl;
				sprintf(linhaHTML,
					"	<tr>\n"
					"		<td colspan=\"8\">Perfil já existe no sistema vinculado ao usuario: Nome: %s, Email: %s, Login: %s, Senha: %s. (Isso não impede a conclusão dos demais cadastros.)</td>\n"
					"	</tr>\n",
					lpl->perfilExistente->nome, lpl->perfilExistente->email, lpl->perfilExistente->login, lpl->perfilExistente->senha);
			}
			else if (nolr->linha->lpl->loginExistente) {

				LinhaPerfilLote* lpl = nolr->linha->lpl;

				sprintf(linhaHTML,
						"	<tr>\n"
						"		<td colspan=\"8\"><div>Login já existe no sistema vinculado ao usuário:</div><div>Nome: %s, Email: %s, Login: %s, Senha: %s. Se o usuário existente for o correto, selecione \"cadastrar\" ao lado. Ou escolha outro login para criar novo usuário.</div></td>\n"
						"	</tr>",
						lpl->loginExistente->nome, lpl->loginExistente->email, lpl->loginExistente->login, lpl->loginExistente->senha);

			}


			mlInserirAcima(linhaHTML, nl, ml);
			mlInserirAcima("<tr><td>&nbsp;</td></tr>", nl, ml);

			nolr = nolr->prox;
			i++;
		}

		mlInserirAcima("</table>\n", nl, ml);

		NoLinha* nl = mlEncontrar("@listaPerfisSubmetidos", ml);

		mlInserirAcima(HTML_BOTAO_CHECAR_PAGINA_CHECAR, nl, ml);

		if (rel->status == 0) {
			mlInserirAcima(HTML_BOTAO_PROXIMO_PAGINA_CHECAR, nl, ml);
		}

	}

	mlImprimir(ml);

	return 0;

}



char* htmlLinhaPerfilLote(LinhaPerfilLote* lpl, int i, int cadastrar) {

	/*
	 * cadastrar:	0 - não imprime checkbox
	 * 				1 - imprime checkbox não selecionada
	 * 				2 - imprime checkbox selecionada
	 */

	char* html = (char *) malloc( 2000 * sizeof(char));

	char aux[100] = "";
	if (cadastrar == 1) {
		sprintf(aux, "		<td><input type=\"checkbox\" name=\"cadastrar%d\"/></td>\n", i);
	}
	else if (cadastrar == 2) {
		sprintf(aux, "		<td><input type=\"checkbox\" name=\"cadastrar%d\" checked /></td>\n", i);
	}

	sprintf(html,
			"	<tr>\n"
			"		<td>%i.</td>"
			"		<td><input type=\"text\" name=\"nomePerfil%d\" value=\"%s\" %s/></td>\n"
			"		<td><input type=\"text\" name=\"emailPerfil%d\" value=\"%s\" %s/></td>\n"
			"		<td><input type=\"text\" name=\"loginPerfil%d\" value=\"%s\" %s/></td>\n"
			"		<td><input type=\"text\" name=\"senhaPerfil%d\" value=\"%s\" %s/></td>\n"
			"		<td><input type=\"text\" name=\"matriculaPerfil%d\" value=\"%s\"/></td>\n"
			"		<td><input type=\"text\" name=\"codigoCursoPerfil%d\" value=\"%s\"/></td>\n"
			"		<td><input type=\"text\" name=\"siglaInstPerfil%d\" value=\"%s\"/></td>\n"
			"		<td>%s</td>"
			"	</tr>\n",
			i,
			i, lpl->nome, (lpl->perfilExistente ? "style=\"text-decoration: line-through\" readonly" : ""),
			i, lpl->email, lpl->perfilExistente ? "style=\"text-decoration: line-through\" readonly" : "",
			i, lpl->login, lpl->perfilExistente ? "style=\"text-decoration: line-through\" readonly" : "",
			i, lpl->senha, lpl->perfilExistente ? "style=\"text-decoration: line-through\" readonly" : "",
			i, lpl->matricula,
			i, lpl->codigoCurso,
			i, lpl->siglaInst,
			aux);

	return html;
}



int checarDadosLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// extrai dados de perfis do formulário
	ListaPerfilLote* lista = lplCriarLista();
	extrairPerfisFormulario(lista, form);

	// executar bateria de validações
	RelatorioCadPerfil* rel = rcpCriar();
	int ret = bateriaValidacoesListaPerfis(lista, rel);


	CAMINHO_PAGINA_CHECAR_LOTE = "/papeis/adm/cadperfil/checarperfis.html";

	HTML_BOTAO_CHECAR_PAGINA_CHECAR = "<br>\n<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"checardadosloteperfis\">checar perfis</button>\n";
	HTML_BOTAO_PROXIMO_PAGINA_CHECAR = "<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"cadastrarloteperfis\">cadastrar perfis</button>";

	paginaConteudoLotePerfis(usu, sessao, form, NULL, rel, NULL);

	return 0;
}




int extrairPerfisFormulario(ListaPerfilLote* lista, FormularioHTML* form) {

	int numPerfis = 0;
	sscanf(obterCampoFormularioHTML(form, "numPerfis")->valor, "%d", &numPerfis);

	char nomeCampo[1000] = "";

	for (int i = 1; i <= numPerfis; i++) {

		sprintf(nomeCampo, "nomePerfil%d", i);
		char* nome = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		sprintf(nomeCampo, "emailPerfil%d", i);
		char* email = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		sprintf(nomeCampo, "loginPerfil%d", i);
		char* login = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		sprintf(nomeCampo, "senhaPerfil%d", i);
		char* senha = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		sprintf(nomeCampo, "matriculaPerfil%d", i);
		char* matricula = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		sprintf(nomeCampo, "codigoCursoPerfil%d", i);
		char* codigoCurso = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		sprintf(nomeCampo, "siglaInstPerfil%d", i);
		char* siglaInst = aparar(&(obterCampoFormularioHTML(form, nomeCampo)->valor));

		LinhaPerfilLote* lpl = lplConstruirLinha(nome, email, login, senha, matricula, codigoCurso, siglaInst);

		sprintf(nomeCampo, "cadastrar%d", i);
		CampoFormularioHTML* cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) {
			lpl->cadastrar = 1;
		}

		sprintf(nomeCampo, "incluirRespondedor%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) {
			lpl->incluirRespondedor = 1;
		}

		/*
		sprintf(nomeCampo, "ignorado%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) {
			lpl->ignorado = 1;
		}
		*/

		sprintf(nomeCampo, "perfilPreExistente%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) {
			lpl->perfilPreExistente = 1;
		}

		sprintf(nomeCampo, "loginPreExistente%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) {
			lpl->loginPreExistente = 1;
		}

		lplInserirLinha(lpl, lista);
	}
}



int bateriaValidacoesListaPerfis(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	// validar dados (caracteres)
	//RelatorioCadPerfil* rel1 = rcpCriar();
	rcpEsvaziarRelatorio(rel);
	if (validarDadosListaPerfis(lista, rel)) {

		return 1;
	}

	// checar cursos no banco
	//RelatorioCadPerfil* rel2 = rcpCriar();
	rcpEsvaziarRelatorio(rel);
	if (checarCursos(lista, rel)) {

		return 2;
	}

	// checar perfis repetidos no formulário
	//RelatorioCadPerfil* rel3 = rcpCriar();
	rcpEsvaziarRelatorio(rel);
	if(checarPerfisRepetidos(lista, rel)) {

		return 3;
	}

	// checar perfis existentes
	buscarPerfisExistentes(lista);

	// validar dados para criação de usuário
	//RelatorioCadPerfil* rel4 = rcpCriar();
	rcpEsvaziarRelatorio(rel);
	if (validarDadosNovoUsuario(lista, rel)) {

		return 4;
	}

	// checar logins repetidos no formulário
	//RelatorioCadPerfil* rel5 = rcpCriar();
	rcpEsvaziarRelatorio(rel);
	if (checarNovosLoginsDuplicados(lista, rel)) {

		return 5;
	}

	// checar logins existentes
	buscarLoginsExistentes(lista);

	return 0;
}




int validarDadosListaPerfis(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	rel->status = 0;
	int ret = 0;

	if (lista) {

		if (lista->prim) {

			// percorrer lista de linhas perfis a serem cadastrados

			NoLinhaPerfilLote* nolp = lista->prim;
			LinhaRelCadPerfil* linha = NULL;

			int i = 0;

			while (nolp) {

				char* msg = NULL;

				// validar dados

				// Checa se houve algum erro de validação, antes que todas as linhas sejam validadas não haverá tentativa de inserção no banco

				char msgaux[500] = "";
				if (validarDadosPerfilLote( nolp->linha, &msg)) {

					sprintf(msgaux, "Linha %d inválida. ", i+1);
					msg = concatstr2(msgaux, msg);

					linha = rcpConstruirLinha(91, msg, nolp->linha);

					// inserir linha no relatório
					rcpInserirLinha(linha, rel);
					rel->status = 4;
					ret = 1;
				}
				else {
					//sprintf(msgaux, "Linha %d válida. ", i+1);
					//msg = concatstr2(msgaux, msg);

					linha = rcpConstruirLinha(0, "", nolp->linha);

					// inserir linha no relatório
					rcpInserirLinha(linha, rel);
				}

				nolp = nolp->prox;
				i++;
			}

			return ret;
		}

		// lista vazia
		return 0;
	}

	return 2;

}



int validarDadosPerfilLote(LinhaPerfilLote* lpl, char** msg) {

	if (utf8Val(lpl->nome, CHARNOME, NULL)) {

		*msg = copiastr("Caractere inválido no nome do usuário.");

		return 11;
	}
	/*else if (lpl->nome && strlen(lpl->nome) == 0) {

		*msg = copiastr("Nome não pode ser vazio.");

		return 12;
	}*/
	else if (utf8Val(lpl->email, CHAREMAIL, NULL)) {

		*msg = copiastr("Caractere inválido no email do usuário.");

		return 13;
	}

	else if (lpl->login && utf8Val(lpl->login, CHARLOGIN, NULL)) {

		*msg = copiastr("Caractere inválido no login.");

		return 14;
	}
	/*else if (lpl->login && strlen(lpl->login) == 0) {

		*msg = copiastr("Login não pode ser vazio.");

		return 15;
	}*/
	else if (lpl->senha && utf8Val(lpl->senha, CHARSENHA, NULL)) {

		*msg = copiastr("Caractere inválido na senha.");

		return 16;
	}
	/*else if (lpl->senha && strlen(lpl->senha) == 0) {

		*msg = copiastr("Senha não pode ser vazia.");

		return 17;
	}*/
	else if (utf8Val(lpl->matricula, CHARMAT, NULL)) {

		*msg = copiastr("Caractere inválido na matrícula.");

		return 18;
	}
	else if (lpl->matricula && strlen(lpl->matricula) == 0) {

		*msg = copiastr("Matrícula não pode ser vazia.");

		return 19;
	}
	else if (utf8Val(lpl->codigoCurso, CHARCODIGO, NULL)) {

		*msg = copiastr("Caractere inválido no código do curso.");

		return 20;
	}
	else if (lpl->codigoCurso && strlen(lpl->codigoCurso) == 0) {

		*msg = copiastr("Código de curso não pode ser vazio.");

		return 21;
	}
	else if (utf8Val(lpl->siglaInst, CHARSIGLA, NULL)) {

		*msg = copiastr("Caractere inválido na sigla da instituição.");

		return 22;
	}
	else if (lpl->siglaInst && strlen(lpl->siglaInst) == 0) {

		*msg = copiastr("Sigla não pode ser vazia.");

		return 23;
	}
	else{

		*msg = copiastr("Dados válidos. Perfil pronto para cadastro.");

		return 0;
	}
}



int checarCursos (ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	rel->status = 0;
	int ret = 0;

	Curso* curso = NULL;
	int nc = 0;

	LinhaPerfilLote* linha = NULL;
	LinhaRelCadPerfil* linhar = NULL;

	NoLinhaPerfilLote* nolp = lista->prim;
	while (nolp) {

		linha = nolp->linha;

		if (!bdBuscarCursoCodigoSiglaInst(linha->codigoCurso, linha->siglaInst, &curso, &nc)) {

			if (nc) {		// curso existe

				linha->curso = curso;
				linhar = rcpConstruirLinha(0, "", linha);
			}
			else {

				// curso não existe

				char msg[500] = "";

				sprintf(msg, "Curso não existe. Verifique se o código (%s) e a sigla da instituição (%s) estão corretos.", linha->codigoCurso, linha->siglaInst);

				linhar = rcpConstruirLinha(70, msg, linha);

				rel->status = 7;
				ret = 1;
			}

		}
		else {

			linhar = rcpConstruirLinha(71, "Erro ao tentar pesquisar curso no banco.", linha);

			rel->status = 7;
			ret = 1;
		}

		rcpInserirLinha(linhar, rel);
		nolp = nolp->prox;
	}

	return ret;

}



int checarPerfisRepetidos(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	int numlins = lista->numlins;

	NoLinhaPerfilLote* nolp1 = lista->prim;
	int i = 1;
	while (nolp1) {

		LinhaPerfilLote* lpl1 = nolp1->linha;

		int flag = 1;

		// buscar por linha com o mesmo perfil
		NoLinhaPerfilLote* nolp2 = lista->prim;
		int j = 1;
		while (nolp2) {

			if (nolp1 != nolp2) {

				LinhaPerfilLote* lpl2 = nolp2->linha;

				if ( ! ( strcmp(lpl1->matricula, lpl2->matricula) || strcmp(lpl1->codigoCurso, lpl2->codigoCurso) || strcmp(lpl1->siglaInst, lpl2->siglaInst) ) ) {

					char msg[500] = "";
					sprintf(msg, "Perfil (matrícula, código curso, sigla instituição) igual ao da linha %d", j);
					LinhaRelCadPerfil* lrel = rcpConstruirLinha(31, msg, lpl1);

					rcpInserirLinha(lrel, rel);

					rel->status = 9;
					flag = 0;
					break;
				}
			}

			nolp2 = nolp2->prox;
			j++;
		}

		if (flag) {		// perfil único

			LinhaRelCadPerfil* lrel = rcpConstruirLinha(0, "", lpl1);

			rcpInserirLinha(lrel, rel);
		}

		nolp1 = nolp1->prox;
		i++;
	}

	return rel->status;
}




int buscarPerfisExistentes (ListaPerfilLote* lista) {

	int ret = 1;		// valor que indica que todos os perfis já existem
						// deve passar direto para a página de relatório

	Usuario* up = NULL;
	int nup = 0;

	LinhaPerfilLote* linha = NULL;

	NoLinhaPerfilLote* nolp = lista->prim;
	while (nolp) {

		linha = nolp->linha;

		int retbd = bdBuscarUsuarioPerfilMatriculaCodCursoSiglaInst2(linha->matricula, linha->codigoCurso, linha->siglaInst, &up, &nup);

		if (up && ( *(up->adm) || *(up->professor) ) ) {
			up->senha = copiastr("***");
		}

		if (!retbd) {

			if (nup) {		// perfil existe

				linha->perfilExistente = up;
				//linha->perfilExiste = 1;
				ret = 0;

			}

		}
		else return 2;		// valor indica erro de acesso ao banco

		nolp = nolp->prox;
	}

	return ret;

}




int validarDadosNovoUsuario(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	int ret = 0;

	LinhaPerfilLote* linha = NULL;

	LinhaRelCadPerfil* linhar = NULL;

	NoLinhaPerfilLote* nolp = lista->prim;
	while (nolp) {

		linha = nolp->linha;

		if (!(linha->perfilExistente)) {

			if (eBranco(linha->nome) || eBranco(linha->login) || eBranco(linha->senha)) {

				linhar = rcpConstruirLinha(41, "Nome, login ou senha não podem ser vazios para criação de novo usuário.", linha);
				rel->status = 10;

				ret = 1;
			}
			else {

				linhar = rcpConstruirLinha(0, "", linha);
			}
		}
		else {

			linhar = rcpConstruirLinha(0, "", linha);
		}

		rcpInserirLinha(linhar, rel);

		nolp = nolp->prox;
	}

	return ret;
}



int checarNovosLoginsDuplicados(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	int ret = 0;

	if (lista && rel) {

		LinhaRelCadPerfil* lr = NULL;

		int i = 1;
		NoLinhaPerfilLote* nolpi = lista->prim;
		while (nolpi) {

			if (nolpi->linha->login && !(nolpi->linha->perfilExistente)) {

				int flag = 0;

				int j = 1;
				NoLinhaPerfilLote* nolpj = lista->prim;
				while (nolpj) {

					if (nolpi != nolpj && nolpj->linha->login && !(nolpj->linha->perfilExistente)) {

						if (!strcmp(nolpi->linha->login, nolpj->linha->login)) {

							char msg[100] = "";
							sprintf(msg, "Login repetido na linha %d.", j);
							lr = rcpConstruirLinha(80, msg, nolpi->linha);

							rel->status = 8;

							flag = 1;
							ret = 1;
							break;
						}
					}

					nolpj = nolpj->prox;
					j++;
				}

				if (!flag) {

					lr = rcpConstruirLinha(0, "", nolpi->linha);
				}
			}
			else {

				lr = rcpConstruirLinha(0, "", nolpi->linha);
			}

			rcpInserirLinha(lr, rel);

			nolpi = nolpi->prox;
			i++;
		}

		return ret;
	}
	else {
		return 1;
	}
}




int buscarLoginsExistentes(ListaPerfilLote* lista) {

	int ret = 1;		// valor que indica que todos os perfis já existem
						// deve passar direto para a página de relatório

	Usuario* up = NULL;
	int nup = 0;

	LinhaPerfilLote* linha = NULL;
	LinhaRelCadPerfil* linhar = NULL;

	NoLinhaPerfilLote* nolp = lista->prim;
	while (nolp) {

		linha = nolp->linha;

		int retbd = 0;
		retbd = bdBuscarUsuarioLogin(linha->login, &up);

		if (up && ( *(up->adm) || *(up->professor) ) ) {
			up->senha = copiastr("***");
		}

		if (!retbd) {

			//if (up && !(linha->perfilExistente)) {		// perfil não existe
			if (up) {		// perfil não existe

				linha->loginExistente = up;
			}

		}

		nolp = nolp->prox;
	}

	return ret;
}






int cadastrarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form) {


	CAMINHO_PAGINA_ENVIAR_LOTE = "/papeis/adm/cadperfil/enviarperfis.html";
	CAMINHO_PAGINA_CHECAR_LOTE = "/papeis/adm/cadperfil/checarperfis.html";
	CAMINHO_PAGINA_RELATORIO_LOTE = "/papeis/adm/cadperfil/relatoriocadastroperfis.html";

	HTML_BOTAO_CHECAR_PAGINA_CHECAR = "<br>\n<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"checardadosloteperfis\">checar perfis</button>\n";
	HTML_BOTAO_PROXIMO_PAGINA_CHECAR = "<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"cadastrarloteperfis\">cadastrar perfis</button>";


	// extrai dados de perfis do formulário
	ListaPerfilLote* lista = lplCriarLista();
	extrairPerfisFormulario(lista, form);

	// executar bateria de validações
	RelatorioCadPerfil* rel = rcpCriar();
	int ret = bateriaValidacoesListaPerfis(lista, rel);

	if (ret) {

		paginaConteudoLotePerfis(usu, sessao, form, NULL, rel, NULL);
		return 1;
	}
	else {

		RelatorioCadPerfil* rel2 = rcpCriar();

		cadastrarListaPerfis(lista, rel2);

		// carregar relatório

		paginaRelatorioLotePerfis(usu, sessao, form, lista, rel2, NULL);

	}

	return 0;
}



int cadastrarListaPerfis(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	rel->status = 0;
	LinhaRelCadPerfil* linhar = NULL;

	// cadastrar

	NoLinhaPerfilLote* nolp = lista->prim;

	while (nolp) {

		LinhaPerfilLote* lpl = nolp->linha;

		if (lpl->cadastrar) {

			int ret = 0;
			long long int idUsuario = 0;

			if (lpl->loginExistente) {
				idUsuario = *(lpl->loginExistente->idUsuario);
			}
			else {
				// incluir usuário

				ret = bdCadastrarUsuario(lpl->nome, lpl->login, lpl->senha, lpl->email, "0", "0", "1", &idUsuario);

				if (ret) {

					linhar = rcpConstruirLinha(111, "Erro ao tentar criar usuário no banco.", lpl);
					rcpInserirLinha(linhar, rel);
					rel->status = 11;
					continue;
				}
			}

			// incluir perfil

			char* strIdUsuario = llistr(idUsuario);
			char* strIdCurso = llistr(*(lpl->curso->idCurso));

			long long int idPerfilRespondedor = 0;
			ret = bdCadastrarPerfilRespondedor(strIdUsuario, lpl->matricula, strIdCurso, "1", "", &idPerfilRespondedor);

			if (ret) {
				linhar = rcpConstruirLinha(112, "Erro ao tentar criar perfil no banco.", lpl);
				rel->status = 11;
			}
			else {
				linhar = rcpConstruirLinha(0, "Perfil criado com sucesso.", lpl);
			}

		}
		else {
			linhar = rcpConstruirLinha(0, "Perfil ignorado.", lpl);
		}

		rcpInserirLinha(linhar, rel);

		nolp = nolp->prox;
	}

	return 0;

}



int paginaRelatorioLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, ListaPerfilLote* lista, RelatorioCadPerfil* rel, RegNoti* rn) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	//char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/checarperfis.html");
	char* caminho = concatstr(dirHtml, CAMINHO_PAGINA_CHECAR_LOTE);

	mlCarregarArquivoTexto(caminho, ml);

	// colocar mensagem

	//char* msg = msgNotiHTML(rn);

	mlSubstituirTodos("$MSG$", "", ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// caso haja id de turma disponível, colocar na página

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idTurma");

	if (cf && cf->valor) mlSubstituirTodos("$IDTURMA$", cf->valor, ml);


	// imprimir relatório de perfis existentes

	// encontrar posição do relatório no html
	NoLinha* nl = mlEncontrar("@listaPerfisSubmetidos", ml);

	char linha[1000] = "";

	if (rel) {

		// cabeçalho da tabela

		sprintf(linha,
				"<input type=\"hidden\" name=\"numPerfis\" value=\"%d\">\n",
				rel->numlins);

		mlInserirAcima(linha, nl, ml);

		mlInserirAcima("<table>\n", nl, ml);

		// cabeçalho da tabela
		mlInserirAcima("	<tr>\n"
						"		<td></td>\n"
						"		<td><b>nome</b></td>\n"
						"		<td><b>email</b></td>\n"
						"		<td><b>login</b></td>\n"
						"		<td><b>senha</b></td>\n"
						"		<td><b>matricula</b></td>\n"
						"		<td><b>codigo curso</b></td>\n"
						"		<td><b>sigla instituição</b></td>\n"
						"	</tr>\n",
				 nl, ml);


		// linhas do relatório

		NoLinhaRelCadPerfil* nolr 	= rel->prim;
		char* html 					= NULL;
		int i 						= 1;

		while (nolr) {

			int loginperfilExistente = (nolr->linha->lpl->loginExistente && nolr->linha->lpl->cadastrar)
										|| nolr->linha->lpl->perfilExistente
										?
										1 : 0;

			html = htmlLinhaPerfilLote2(nolr->linha->lpl, i, loginperfilExistente);
			mlInserirAcima(html, nl, ml);

			// imprimir mensagem do relatório
			char linhaHTML[1000] = "";

			if (nolr->linha->lpl->perfilExistente) {

				LinhaPerfilLote* lpl = nolr->linha->lpl;
				sprintf(linhaHTML,
					"	<tr>\n"
					"		<td colspan=\"8\">%s Perfil já existe no sistema vinculado ao usuário: Nome: %s, Email: %s, Login: %s, Senha: %s.</td>\n"
					"	</tr>\n",
					nolr->linha->msg,
					lpl->perfilExistente->nome, lpl->perfilExistente->email,
					lpl->perfilExistente->login, lpl->perfilExistente->senha);
			}
			else if (!(nolr->linha->lpl->cadastrar)) {

				LinhaPerfilLote* lpl = nolr->linha->lpl;
				sprintf(linhaHTML,
					"	<tr>\n"
					"		<td colspan=\"8\">%s</td>\n"
					"	</tr>\n",
					nolr->linha->msg);
			}
			else if (nolr->linha->lpl->loginExistente) {

				LinhaPerfilLote* lpl = nolr->linha->lpl;

				sprintf(linhaHTML,
						"	<tr>\n"
						"		<td colspan=\"8\"><div>%s. Perfil criado no usuário:</div><div>Nome: %s, Email: %s, Login: %s, Senha: %s.</div></td>\n"
						"	</tr>\n",
						nolr->linha->msg,
						lpl->loginExistente->nome, lpl->loginExistente->email,
						lpl->loginExistente->login, lpl->loginExistente->senha);

			}
			else {

				LinhaPerfilLote* lpl = nolr->linha->lpl;

				sprintf(linhaHTML,
						"	<tr>\n"
						"		<td colspan=\"8\">%s</td>\n"
						"	</tr>\n",
						nolr->linha->msg);
			}


			mlInserirAcima(linhaHTML, nl, ml);
			mlInserirAcima("<tr><td>&nbsp;</td></tr>", nl, ml);

			nolr = nolr->prox;
			i++;
		}

		mlInserirAcima("</table>\n", nl, ml);

		NoLinha* nl = mlEncontrar("@listaPerfisSubmetidos", ml);

		mlInserirAcima("<br>\n<button type=\"submit\" name=\"acao\" id=\"enviarperfis\" formaction=\"\" value=\"encerrarcadastroloteperfis\">encerrar cadastro lote</button>\n", nl, ml);

	}

	mlImprimir(ml);

	return 0;

}



char* htmlLinhaPerfilLote2(LinhaPerfilLote* lpl, int i, int loginperfilExistente) {

	/*
	 * cadastrar:	0 - não imprime checkbox
	 * 				1 - imprime checkbox não selecionada
	 * 				2 - imprime checkbox selecionada
	 */

	char* html = (char *) malloc( 2000 * sizeof(char));

	sprintf(html,
			"	<tr>\n"
			"		<td>%i.</td>\n"
			"		<td %s><input type=\"hidden\" name=\"nomePerfil%d\" value=\"%s\"/>%s</td>\n"
			"		<td %s><input type=\"hidden\" name=\"emailPerfil%d\" value=\"%s\"/>%s</td>\n"
			"		<td %s><input type=\"hidden\" name=\"loginPerfil%d\" value=\"%s\"/>%s</td>\n"
			"		<td %s><input type=\"hidden\" name=\"senhaPerfil%d\" value=\"%s\"/>%s</td>\n"
			"		<td ><input type=\"hidden\" name=\"matriculaPerfil%d\" value=\"%s\"/>%s</td>\n"
			"		<td ><input type=\"hidden\" name=\"codigoCursoPerfil%d\" value=\"%s\"/>%s</td>\n"
			"		<td ><input type=\"hidden\" name=\"siglaInstPerfil%d\" value=\"%s\"/>%s</td>\n"
			"	</tr>\n",
			i,
			loginperfilExistente ? "style=\"text-decoration: line-through\"" : "", i, lpl->nome, lpl->nome,
			loginperfilExistente ? "style=\"text-decoration: line-through\"" : "", i, lpl->email, lpl->email,
			loginperfilExistente ? "style=\"text-decoration: line-through\"" : "", i, lpl->login, lpl->login,
			loginperfilExistente ? "style=\"text-decoration: line-through\"" : "", i, lpl->senha, lpl->senha,
			i, lpl->matricula, lpl->matricula,
			i, lpl->codigoCurso, lpl->codigoCurso,
			i, lpl->siglaInst, lpl->siglaInst);

	return html;
}
