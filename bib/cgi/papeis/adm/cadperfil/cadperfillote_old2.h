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


int paginaEnviarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadPerfil* rel, RegNoti* rn);

int enviarLotePerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int extrairListaPerfis(Multilinhas* ml, ListaPerfilLote* lista, RelatorioCadPerfil* rel);

int validarLinhasPerfisLote(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

int validarLinhaPerfilLote(LinhaPerfilLote* lpl, char** msg);

int checarCursos (ListaPerfilLote* lista, RelatorioCadPerfil* rel);

int checarPerfisExistentes (ListaPerfilLote* lista, RelatorioCadPerfil* rel);



int paginaChecarPerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadPerfil* rel);

int cadastrarPerfisLote(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int checarUsuariosExistentes(ListaPerfilLote* lista, RelatorioCadPerfil* rel);

int checarNovosLoginsDuplicados(ListaPerfilLote* lista, RelatorioCadPerfil* rel);



int paginaRelatorioCadastroPerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, ListaPerfilLote* lista);








int extrairListaPerfisML(Multilinhas* ml, ListaPerfilLote* lista, RegNoti** rn);









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

	// acessar arquivo

	CampoFormularioHTML* arqListaPerfis = obterCampoFormularioHTML(form, "listaperfis");

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

		// Checar se o arquivo submetido estava vazio

		if (lista->numlins == 0) {		// lista vazia

			rn = criarRegNoti(1, "Lista de perfis vazia.");
			paginaEnviarLotePerfis(usu, sessao, form, NULL, rn);

			return 1;
		}

		// Validar campos dos registros de perfis
		//
		// é gerado um relatório para cada linha indicando a presenção de caracteres ou valores inválidos

		ret = validarLinhasPerfisLote(lista, rel);

		if (ret) {		// houve falha de validação de dos dados de perfis

			paginaEnviarLotePerfis(usu, sessao, form, rel, NULL);

			return 2;
		}

		// Checar se cursos existem
		//
		// verifica se o código de curso e a instituição se referem a um curso cadastrado no banco
		// é gerado relatório informando caso o curso não exista

		RelatorioCadPerfil* rel2 = rcpCriar();
		ret = checarCursos(lista, rel2);

		if (ret) {		// houve falha de validação de dos dados de perfis

			paginaEnviarLotePerfis(usu, sessao, form, rel2, NULL);

			return 3;
		}

		// Checar perfis existentes
		//
		// verifica se os perfis (matrícula, curso) já existem
		// é gerado relatório com o nome, email, login e senha do usuário do perfil

		RelatorioCadPerfil* rel3 = rcpCriar();

		ret = checarPerfisExistentes(lista, rel3);

		if (ret) {

			paginaRelatorioCadastroPerfis(usu, sessao, form, lista);

			return 0;
		}

		// após a checagem de perfis existentes, é construida a página informando os dados
		// dos usuários dos perfis existentes e com campos para a definição de login e senha
		// dos novos usuários que serão criados para os novos perfis
		// as informações para a construção da página vem do último relatório gerado na checagem de perfis existentes

		return paginaChecarPerfis(usu, sessao, form, rel3);

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

		// checar número de campos em cada linha

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
				linha->login = NULL;
				linha->senha = NULL;
				linha->matricula = aparar(&(segs[2]));
				linha->codigoCurso = aparar(&(segs[3]));
				linha->siglaInst = aparar(&(segs[4]));

				linha->usuExistente = NULL;

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




int validarLinhasPerfisLote(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

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
				if (validarLinhaPerfilLote( nolp->linha, &msg)) {

					sprintf(msgaux, "Linha %d inválida. ", i+1);
					msg = concatstr2(msgaux, msg);

					linha = rcpConstruirLinha(91, msg, nolp->linha);

					// inserir linha no relatório
					rcpInserirLinha(linha, rel);
					rel->status = 4;
					ret = 1;
				}
				else {
					sprintf(msgaux, "Linha %d válida. ", i+1);
					msg = concatstr2(msgaux, msg);

					linha = rcpConstruirLinha(0, msg, nolp->linha);

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





int validarLinhaPerfilLote(LinhaPerfilLote* lpl, char** msg) {

	if (utf8Val(lpl->nome, CHARNOME, NULL)) {

		*msg = copiastr("Caractere inválido no nome do usuário.");

		return 11;
	}
	else if (lpl->nome && strlen(lpl->nome) == 0) {

		*msg = copiastr("Nome não pode ser vazio.");

		return 12;
	}
	else if (utf8Val(lpl->email, CHAREMAIL, NULL)) {

		*msg = copiastr("Caractere inválido no email do usuário.");

		return 13;
	}

	else if (lpl->login && utf8Val(lpl->login, CHARLOGIN, NULL)) {

		*msg = copiastr("Caractere inválido no login.");

		return 14;
	}
	else if (lpl->login && strlen(lpl->login) == 0) {

		*msg = copiastr("Login não pode ser vazio.");

		return 15;
	}
	else if (lpl->senha && utf8Val(lpl->senha, CHARSENHA, NULL)) {

		*msg = copiastr("Caractere inválido na senha.");

		return 16;
	}
	else if (lpl->senha && strlen(lpl->senha) == 0) {

		*msg = copiastr("Senha não pode ser vazia.");

		return 17;
	}

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




int checarPerfisExistentes (ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

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
		retbd = bdBuscarUsuarioPerfilMatriculaCodCursoSiglaInst(linha->matricula, linha->codigoCurso, linha->siglaInst, &up, &nup);

		if (!retbd) {

			if (nup) {		// perfil existe

				linha->usuExistente = up;
				linhar = rcpConstruirLinha(0, "", linha);
			}
			else {

				// perfil novo

				linhar = rcpConstruirLinha(0, "", linha);
				ret = 0;	// indica que é necessário inlcusão de login e senha para novo usuário.
			}

		}

		rcpInserirLinha(linhar, rel);

		nolp = nolp->prox;
	}

	return ret;

}





int paginaChecarPerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, RelatorioCadPerfil* rel) {


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

	if (rel) {

		// encontrar posição do relatório no html
		NoLinha* nl = mlEncontrar("@listaPerfisSubmetidos", ml);

		char linhaHTML[1000] = "";

		sprintf(linhaHTML,
				"<input type=\"hidden\" name=\"numPerfis\" value=\"%d\">\n",
				rel->numlins);
		mlInserirAcima(linhaHTML, nl, ml);

		NoLinhaRelCadPerfil* nolr = rel->prim;

		int i = 1;

		while (nolr) {

			LinhaRelCadPerfil* linha = nolr->linha;
			LinhaPerfilLote* lpl = linha->lpl;
			Usuario* usuExistente = linha->lpl->usuExistente;

			if (linha->lpl->usuExistente) {		// perfil existe

				sprintf(linhaHTML, "<p>[%d] %s, %s, %s, %s, %s<br>"
									"<input type=\"hidden\" name=\"nomePerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"emailPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"matriculaPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"codCursoPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"siglaInstPerfil%d\" value=\"%s\">"
									"Perfil já existe vinculado ao usuário: Nome: %s - Email: %s - Login: %s - Senha: %s</p>"
									"<input type=\"hidden\" name=\"nomeExistente%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"emailExistente%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"loginExistente%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"senhaExistente%d\" value=\"%s\">",
									i, lpl->nome, lpl->email, lpl->matricula, lpl->codigoCurso, lpl->siglaInst,
									i, lpl->nome,
									i, lpl->email,
									i, lpl->matricula,
									i, lpl->codigoCurso,
									i, lpl->siglaInst,
									usuExistente->nome, usuExistente->email, usuExistente->login, usuExistente->senha,
									i, usuExistente->nome,
									i, usuExistente->email,
									i, usuExistente->login,
									i, usuExistente->senha);
			}
			else {

				//printf("%d-",linha->numerr);
				char* msg = NULL;
				if (linha->numerr) {
					msg = concatstr2("<br>\n", linha->msg);
					//printf("%d-",i);
				}

				sprintf(linhaHTML, "<p>[%d] %s, %s, %s, %s, %s<br>\n"
									"<input type=\"hidden\" name=\"nomePerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"emailPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"matriculaPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"codCursoPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"siglaInstPerfil%d\" value=\"%s\">"
									"Perfil novo: "
									"Login: <input type=\"text\" name=\"loginNovoUsu%d\" value=\"%s\"> - "
									"Senha: <input type=\"text\" name=\"senhaNovoUsu%d\" value=\"%s\">"
									"%s"
									"</p>",
									i, lpl->nome, lpl->email, lpl->matricula, lpl->codigoCurso, lpl->siglaInst,
									i, lpl->nome,
									i, lpl->email,
									i, lpl->matricula,
									i, lpl->codigoCurso,
									i, lpl->siglaInst,
									i, lpl->login ? lpl->login : "",
									i, lpl->senha ? lpl->senha : "",
									msg ? msg : "");
			}

			mlInserirAcima(linhaHTML, nl, ml);

			nolr = nolr->prox;
			i++;
		}
	}

	mlImprimir(ml);

	return 0;
}


int cadastrarPerfisLote(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

	// Extrair dados do formulário

	int numPerfis = 0;
	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "numPerfis");
	if (cf && cf->valor) {
		sscanf(cf->valor, "%d", &numPerfis);
	}

	ListaPerfilLote* lista = lplCriarLista();
	//RelatorioCadPerfil* rel = rcpCriar();

	for (int i = 1; i <= numPerfis; i++) {

		LinhaPerfilLote* lpl = lplCriarLinha();
		LinhaRelCadPerfil* linha = NULL;

		char nomeCampo[30];

		// resgatar informações do perfil/usuário
		sprintf(nomeCampo, "nomePerfil%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) lpl->nome = cf->valor;

		sprintf(nomeCampo, "emailPerfil%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) lpl->email = cf->valor;

		sprintf(nomeCampo, "matriculaPerfil%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) lpl->matricula = cf->valor;

		sprintf(nomeCampo, "codCursoPerfil%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) lpl->codigoCurso = cf->valor;

		sprintf(nomeCampo, "siglaInstPerfil%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);
		if (cf) lpl->siglaInst = cf->valor;



		// Checar se o perfil i já existe
		sprintf(nomeCampo, "nomeExistente%d", i);
		cf = obterCampoFormularioHTML(form, nomeCampo);

		if (cf) {		// perfil existe

			lpl->login = NULL;
			lpl->senha = NULL;

			Usuario* usuExistente = (Usuario *) malloc(sizeof(Usuario));

			sprintf(nomeCampo, "nomeExistente%d", i);
			cf = obterCampoFormularioHTML(form, nomeCampo);
			if (cf) usuExistente->nome = cf->valor;

			sprintf(nomeCampo, "emailExistente%d", i);
			cf = obterCampoFormularioHTML(form, nomeCampo);
			if (cf) usuExistente->email = cf->valor;

			sprintf(nomeCampo, "loginExistente%d", i);
			cf = obterCampoFormularioHTML(form, nomeCampo);
			if (cf) usuExistente->login = cf->valor;

			sprintf(nomeCampo, "senhaExistente%d", i);
			cf = obterCampoFormularioHTML(form, nomeCampo);
			if (cf) usuExistente->senha = cf->valor;

			lpl->usuExistente = usuExistente;
			linha = rcpConstruirLinha(0, NULL, lpl);

		}
		else {

			Usuario* usuExistente = NULL;

			sprintf(nomeCampo, "loginNovoUsu%d", i);
			cf = obterCampoFormularioHTML(form, nomeCampo);
			if (cf) lpl->login = cf->valor;

			sprintf(nomeCampo, "senhaNovoUsu%d", i);
			cf = obterCampoFormularioHTML(form, nomeCampo);
			if (cf) lpl->senha = cf->valor;

			linha = rcpConstruirLinha(0, NULL, lpl);
		}

		lplInserirLinha(lpl, lista);

	}

	// verificar caracteres e dados dos campos login e senha
	// essa verificação é feita novamente por questão de segurança

	RelatorioCadPerfil* rel = rcpCriar();
	int ret = validarLinhasPerfisLote(lista, rel);

	if (ret) {		// em caso de erro reportar relatório indicando as linhas inválidas
		paginaChecarPerfis(usu, sessao, form, rel);
		return 1;
	}

	// checar se novos usuários já existem

	RelatorioCadPerfil* rel2 = rcpCriar();
	ret = checarUsuariosExistentes(lista, rel2);

	if (ret) {		// caso novo login sugerido já seja utilizado por outro usuário, reportar

		paginaChecarPerfis(usu, sessao, form, rel2);
		return 1;
	}

	// checar se novos logins são diferentes entre si

	RelatorioCadPerfil* rel3 = rcpCriar();
	ret = checarNovosLoginsDuplicados(lista, rel3);

	if (ret) {		// caso novo login sugerido já seja utilizado por outro usuário, reportar

		paginaChecarPerfis(usu, sessao, form, rel3);
		return 1;
	}

	// cadastrar novos usuários e perfis

	NoLinhaPerfilLote* nolp = lista->prim;
	LinhaPerfilLote* linha = NULL;

	while (nolp) {

		linha = nolp->linha;

		if (linha->login) {

			// criar usuário

			long long int idUsuario;
			ret = bdCadastrarUsuario(linha->nome, linha->login, linha->senha, linha->email, "0", "0", "1", &idUsuario);

			// buscar id do curso

			Curso* curso = NULL;
			int nc = 0;

			ret = bdBuscarCursoCodigoSiglaInst(linha->codigoCurso, linha->siglaInst, &curso, &nc);

			// criar perfil

			char* strIdUsuario = llistr(idUsuario);
			char* strIdCurso = llistr(*(curso->idCurso));

			long long int idPerfilRespondedor = 0;
			ret = bdCadastrarPerfilRespondedor(strIdUsuario, linha->matricula, strIdCurso, "1", "", &idPerfilRespondedor);

		}

		nolp = nolp->prox;
	}

	// imprimir página com o relatório de cadastro

	paginaRelatorioCadastroPerfis(usu, sessao, form, lista);

	return 0;
}



int paginaRelatorioCadastroPerfis(Usuario* usu, Sessao* sessao, FormularioHTML* form, ListaPerfilLote* lista) {

	Multilinhas* ml = mlCriar();

	// carregar modelo

	//char* caminho = concatstr(dirHtml, "/papeis/adm/cadperfil/relatoriocadastroperfis.html");
	char* caminho = concatstr(dirHtml, CAMINHO_PAGINA_RELATORIO_LOTE);

	mlCarregarArquivoTexto(caminho, ml);

	// colocar mensagem

	mlSubstituirTodos("$MSG$", "", ml);

	// instanciar dados de sessão, de sistema, etc.

	incluirDadosSessao(usu, sessao, form, ml);

	// caso haja id de turma disponível, colocar na página

	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idTurma");

	if (cf && cf->valor) mlSubstituirTodos("$IDTURMA$", cf->valor, ml);

	// imprimir relatório de perfis existentes

	if (lista) {

		NoLinha* nl = mlEncontrar("@listaPerfisSubmetidos", ml);

		char linhaHTML[1000] = "";

		sprintf(linhaHTML,
				"<input type=\"hidden\" name=\"numPerfis\" value=\"%d\">\n",
				lista->numlins);
		mlInserirAcima(linhaHTML, nl, ml);

		NoLinhaPerfilLote* nolp = lista->prim;
		LinhaPerfilLote* lpl = NULL;
		Usuario* usuExistente = NULL;

		int i = 1;

		while (nolp) {

			lpl = nolp->linha;
			usuExistente = lpl->usuExistente;

			if (usuExistente) {		// perfil já existia

				sprintf(linhaHTML, "<p>[%d] %s, %s, %s, %s, %s<br>"
									"<input type=\"hidden\" name=\"nomePerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"emailPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"matriculaPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"codCursoPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"siglaInstPerfil%d\" value=\"%s\">"
									"Perfil já existe vinculado ao usuário: Nome: %s - Email: %s - Login: %s - Senha: %s</p>"
									"<input type=\"hidden\" name=\"nomeExistente%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"emailExistente%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"loginExistente%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"senhaExistente%d\" value=\"%s\">",
									i, lpl->nome, lpl->email, lpl->matricula, lpl->codigoCurso, lpl->siglaInst,
									i, lpl->nome,
									i, lpl->email,
									i, lpl->matricula,
									i, lpl->codigoCurso,
									i, lpl->siglaInst,
									usuExistente->nome, usuExistente->email, usuExistente->login, usuExistente->senha,
									i, usuExistente->nome,
									i, usuExistente->email,
									i, usuExistente->login,
									i, usuExistente->senha);
			}
			else {

				sprintf(linhaHTML, "<p>[%d] %s, %s, %s, %s, %s<br>\n"
									"<input type=\"hidden\" name=\"nomePerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"emailPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"matriculaPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"codCursoPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"siglaInstPerfil%d\" value=\"%s\">"
									"<input type=\"hidden\" name=\"loginNovoUsu%d\" value=\"%s\"> - "
									"<input type=\"hidden\" name=\"senhaNovoUsu%d\" value=\"%s\">"
									"Cadastro de usuário e perfil realizado com sucesso: "
									"Login: %s - "
									"Senha: %s"
									"</p>",
									i, lpl->nome, lpl->email, lpl->matricula, lpl->codigoCurso, lpl->siglaInst,
									i, lpl->nome,
									i, lpl->email,
									i, lpl->matricula,
									i, lpl->codigoCurso,
									i, lpl->siglaInst,
									i, lpl->login ? lpl->login : "",
									i, lpl->senha ? lpl->senha : "",
									lpl->login ? lpl->login : "",
									lpl->senha ? lpl->senha : "");
			}

			mlInserirAcima(linhaHTML, nl, ml);

			nolp = nolp->prox;
			i++;
		}

	}

	mlImprimir(ml);
}



int checarUsuariosExistentes(ListaPerfilLote* lista, RelatorioCadPerfil* rel) {

	// checar se os novos logins já existem

	int ret = 0;
	rel->status = 0;

	NoLinhaPerfilLote* nolp = lista->prim;

	while(nolp) {

		LinhaRelCadPerfil* lr;

		if (nolp->linha->login) {

			Usuario* usuario = NULL;
			ret = bdBuscarUsuarioLogin(nolp->linha->login, &usuario);

			if (ret) {
				lr = rcpConstruirLinha(60, "Erro ao tentar pesquisar login no banco.", nolp->linha);
				rel->status = 5;
				ret = 1;
			}
			else {

				if (usuario) {

					lr = rcpConstruirLinha(61, "Login já é usado por outro usuário. Escolha outro ou inclua o perfil individualmente na página de cadastro de perfis (nesse caso, remova esse perfil do arquivo de perfis e repita a operação).", nolp->linha);
					rel->status = 6;
					ret = 1;
				}
				else {

					lr = rcpConstruirLinha(0, "", nolp->linha);
				}
			}
		}
		else {

			lr = rcpConstruirLinha(0, "", nolp->linha);
		}

		rcpInserirLinha(lr, rel);

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


			if (nolpi->linha->login) {

				int flag = 0;

				int j = 1;
				NoLinhaPerfilLote* nolpj = lista->prim;
				while (nolpj) {

					if (nolpi != nolpj && nolpj->linha->login) {

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



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////






/*
 * Layout do arquivo para inclusão de perfis em lote.
 *
 * Cada linha deve ter o seguinte padrão:
 *
 * <nome-respondedor>, <email-respondedor>, <login-respondedor>, <senha-respondedor>, <matricula-perfil>, <codigo-curso-perfil>, <sigla-instituição-perfil>
 *
 *
 */




int extrairListaPerfisML(Multilinhas* ml, ListaPerfilLote* lista, RegNoti** rn) {

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

				LinhaPerfilLote* linha = (LinhaPerfilLote *) malloc (sizeof(LinhaPerfilLote));

				linha->nome = aparar(&(segs[0]));
				linha->email = aparar(&(segs[1]));
				linha->login = aparar(&(segs[2]));
				linha->senha = aparar(&(segs[3]));
				linha->matricula = aparar(&(segs[4]));
				linha->codigoCurso = aparar(&(segs[5]));
				linha->siglaInst = aparar(&(segs[6]));

				lplInserirLinha(linha, lista);
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

