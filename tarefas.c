/*
 * tarefas.c
 *
 * Script cgi principal do sistema Tarefas.
 *
 */



#include <stdlib.h>
#include <stdio.h>


#include "bib/str/bibstring2.h"
#include "bib/str/multilinhas.h"


// Incluir bibliotecas cgi

#include "../bibcgi/formhtmlcgi.h"


// Incluir bibliotecas de sistema

#include "bib/lugar.h"
#include "bib/bd/tarefasbd.h"
#include "bib/diretorio.h"
#include "bib/imagem.h"

#include "bib/cgi/controlesessao.h"

#include "bib/cgi/login/login.h"
#include "bib/cgi/papeis/papeis.h"


#include "bib/cgi/valformhtml.h"


// Incluir bibliotecas de perfis

// Perfil Adm

#include "bib/cgi/papeis/adm/adm.h"
//#include "bib/cgi/adm/cadinst/cadinst.h"
#include "bib/cgi/papeis/adm/cadinst/cadinst.h"
#include "bib/cgi/papeis/adm/cadcurso/cadcurso.h"
#include "bib/cgi/papeis/adm/caddisc/caddisc.h"
#include "bib/cgi/papeis/adm/cadusu/cadusu.h"
#include "bib/cgi/papeis/adm/cadperfil/cadperfil.h"


// Perfil Professor

#include "bib/cgi/papeis/professor/professor.h"
#include "bib/cgi/papeis/professor/cadturma/cadturma.h"
#include "bib/cgi/papeis/professor/minhasturmas/minhasturmas.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/paginaturma.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/respondedoresturma/respondedoresturma.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/respondedoresturma/incluirrespondedorturma/incluirrespondedorturma.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/respondedoresturma/incluirrespondedorturma/incluirrespondedoresloteturma.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/respondedoresturma/respondedorturma/respondedorturma.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/criartrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/paginatrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/paginaconfigurartrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/removertrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/paginaitemtarefa.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/novatarefatrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/incluirtarefatrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/duplicartarefatrabalho.h"

#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/atualizartarefatrabalho.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/removertarefatrabalho.h"
#include "bib/dwldr/dwldr.h"
#include "bib/visu/visu.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/entregastarefa.h"
#include "bib/cgi/papeis/professor/minhasturmas/paginaturma/trabalho/tarefa/visualizadorentrega/visualizadorentrega.h"


// Perfil Respondedor


#include "bib/cgi/papeis/respondedor/respondedor.h"
#include "bib/cgi/papeis/respondedor/perfilrespondedor/paginaperfilrespondedor.h"
#include "bib/cgi/papeis/respondedor/perfilrespondedor/paginaturmaperfil/paginaturmaperfil.h"
#include "bib/cgi/papeis/respondedor/perfilrespondedor/paginaturmaperfil/paginatrabalhoperfil/paginatrabalhoperfil.h"
#include "bib/cgi/papeis/respondedor/perfilrespondedor/paginaturmaperfil/paginatrabalhoperfil/exibiritemtarefa/exibiritemtarefa.h"





int main() {

	/*
	* 
	* CUIDADO!!!!!!!!!!!
	*
	* CORRIGIR ISSO!!!!!
	* 
	*/

	caminho_banco = caminhoTarefasBD;



	//printf("Tarefas\n");


	DadosCGI* dcgi = carregarDadosCGI();

	FormularioHTML* form = formularioHTMLDeDadosCGI(dcgi);


	// Checar se o recurso/página solicidada é válido

	// Se a página existir, checar autenticação

		// Checar autenticação de sessão

		// Se a sessão for válida, direcionar para o recurso/página solicitada

		// Caso a sessão não seja válida, direcionar para a página de login, mantendo a memória do recurso solicitado

	// Se a página não existir, página de erro e redirecionamento para página de login inicial


	// Checa se o sistema está sendo acessado modo download
	// Nesse caso, não é impresso o cabeçalho de conteúdo html
	CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "modo");
	if (!cf || !(cf->valor) || strcmp(cf->valor, "download")) {
		printf("Content-Type: text/html; charset: utf-8\n\n");
	}
	//printf("Content-Type: text/html; charset: utf-8\n\n");
	

	//printf("Tarefas!\n");

	CampoFormularioHTML* cfAcao;

	if (cfAcao = obterCampoFormularioHTML(form, "acao")) {		// caso esteja acessando o sistema a partir do próprio sistema (botão)

		if (!strcmp(cfAcao->valor, "entrar")) {		// caso seja tentativa de login

			CampoFormularioHTML* cfSenha = obterCampoFormularioHTML(form, "senha");
			CampoFormularioHTML* cfLogin = obterCampoFormularioHTML(form, "login");

			if ( cfLogin && cfSenha ) {		// checa se os campos "login" e "senha" foram resgatados corretamente

				// checar caracteres válidos no login e na senha
				if ( utf8Val(cfLogin->valor, CHARLOGIN, NULL) || utf8Val(cfSenha->valor, CHARSENHA, NULL) ) {

					RegNoti* rn = criarRegNoti(1, "usuário ou senha inválidos!");
					paginaLogin(dcgi->PATH_INFO, dcgi->QUERY_STRING, rn);
					return 0;
				}

				// autentica usuario

				Usuario* usu;
				bdAutenticaUsuario(cfLogin->valor, cfSenha->valor, &usu);

				// encerra sessões vencidas


				if (usu) {		// caso usuario autenticado
					// cria sessão
					Sessao* sessao = criarSessao(*(usu->idUsuario), 0, 6000, 60000);

					// checar se há string de consulta direcionando para trabalho

					if (dcgi->QUERY_STRING && dcgi->QUERY_STRING[0] != '\0') {
						FormularioHTML* formStrConsulta = formularioHTMLDeURLEnc(criarSegmento(dcgi->QUERY_STRING, (dcgi->QUERY_STRING + strlen(dcgi->QUERY_STRING) - 1)));
						
						// checar se foi enviado o identificador do trabalho
						//CampoFormularioHTML* cfT = obterCampoFormularioHTML(formStrConsulta, "t");
						RegNoti* rn = NULL;
						char* idTrabalho = obterCFHVal("t", formStrConsulta, "", CHARDIG, &rn);
						//if (cfT && cfT->valor && cfT->valor[0] != '\0') {
						if (idTrabalho && idTrabalho[0] != '\0') {
						       // checar se trabalho existe e se usuário tem acesso
						       // caso positivo, retornar id da turma
						       
							Trabalho* trabalho = NULL;
							long long int idPerfil = 0;
							char strIdPerfil[21]  = "";
							char strIdUsuario[21] = "";
							sprintf(strIdUsuario, "%lld", *(usu->idUsuario));
							int num = 0;
						        bdBuscarTrabalhoIdUsuario(idTrabalho, strIdUsuario , &trabalho, &idPerfil, &num);
							sprintf(strIdPerfil, "%lld", idPerfil);


							if (num > 0) {
								// trabalho existe e usuário tem acesso
								// nesse caso, inserir dados no formulário html

								char strIdTurma[22] = "";
								sprintf(strIdTurma, "%lld", *(trabalho->idTurma));
								
								//lltoa(*(trabalho->idTurma), strIdTurma, 10);

								CampoFormularioHTML* cfIdPerfil = criarCampoFormularioHTML("idPerfilRespondedor", strIdPerfil, NULL, NULL);

								CampoFormularioHTML* cfIdTurma = criarCampoFormularioHTML("idTurma", strIdTurma, NULL, NULL);

								char strIdSessao[22] = "";
								sprintf(strIdSessao, "%lld", sessao->idSessao); 
								CampoFormularioHTML* cfIds = criarCampoFormularioHTML("ids", strIdSessao, NULL, NULL);
								CampoFormularioHTML* cfIdTrabalho = criarCampoFormularioHTML("idTrabalho", idTrabalho, NULL, NULL);

								inserirCampoFormularioHTML(form, cfIdPerfil);
								inserirCampoFormularioHTML(form, cfIdTurma);
								inserirCampoFormularioHTML(form, cfIdTrabalho);
								inserirCampoFormularioHTML(form, cfIds);

								// chamar página do trabalho
								carregarPaginaTrabalhoPerfil(usu, sessao, form, NULL);
								return 0;

							}
						}

						// checar se foi enviado o identificador do trabalho
						//CampoFormularioHTML* cfTar = obterCampoFormularioHTML(formStrConsulta, "tar");
						char* idTarefa = obterCFHVal("tar", formStrConsulta, "", CHARDIG, &rn);
						if (idTarefa && idTarefa[0] != '\0') {


							char strIdUsuario[21] = "";
							sprintf(strIdUsuario, "%lld", *(usu->idUsuario));

							Usuario* usuperfil = NULL;

							bdPerfisTarefa(strIdUsuario, idTarefa, &usuperfil);

							if (usuperfil->numPerfis > 0) {
							

								char strIdPerfil[21] = "";
								
								sprintf(strIdPerfil, "%lld", *(usu->perfis[0].idPerfilRespondedor));

								Turma* turmas = NULL;
								int num = 0;

								bdTurmasPerfilTarefa(strIdPerfil, idTarefa, &turmas, &num);
							

								if (num > 0) {
									Trabalho* trabs = NULL;
									int numtrabs = 0;

									char strIdTurma[21] = "";
									sprintf(strIdTurma, "%lld", *(turmas[0].idTurma));

									bdBuscarTrabalhosTurmaTarefa(strIdTurma, idTarefa, &trabs, &numtrabs);

									if (numtrabs > 0) {

										ItemTarefa* itens = NULL;
										int numitens = 0;

										char strIdTrab[21] = "";
										sprintf(strIdTrab, "%lld", *(trabs[0].idTrabalho));

										bdBuscarItensTarefaIdTrabalhoTarefa(strIdTrab, idTarefa, &itens, &numitens);

										if (numitens > 0) {

											CampoFormularioHTML* cfIdPerfil = criarCampoFormularioHTML("idPerfilRespondedor", strIdPerfil, NULL, NULL);
											CampoFormularioHTML* cfIdTurma = criarCampoFormularioHTML("idTurma", strIdTurma, NULL, NULL);

											char strIdSessao[22] = "";
											sprintf(strIdSessao, "%lld", sessao->idSessao); 
											CampoFormularioHTML* cfIds = criarCampoFormularioHTML("ids", strIdSessao, NULL, NULL);
											CampoFormularioHTML* cfIdTrabalho = criarCampoFormularioHTML("idTrabalho", strIdTrab, NULL, NULL);

											char strIdItemTarefa[22] = "";
											sprintf(strIdItemTarefa, "%lld", *(itens[0].idItemTarefa));
											CampoFormularioHTML* cfIdItemTarefa = criarCampoFormularioHTML("idItemTarefa", strIdItemTarefa, NULL, NULL);

											inserirCampoFormularioHTML(form, cfIdPerfil);
											inserirCampoFormularioHTML(form, cfIdTurma);
											inserirCampoFormularioHTML(form, cfIdTrabalho);
											inserirCampoFormularioHTML(form, cfIdItemTarefa);
											inserirCampoFormularioHTML(form, cfIds);

											// carregar página do item de tarefa
											carregarPaginaExibirItemTarefa(usu, sessao, form, NULL);

											return 0;
										}
									}
								}
							}
						}
					}
					//printf("QUERY_STRING: %s", dcgi->QUERY_STRING);
					paginaPapeis(usu, sessao);
				}
				else {		// caso contrário, vai para página de login
					RegNoti* rn = criarRegNoti(2, "usuário ou senha iv�lido!");
					paginaLogin(dcgi->PATH_INFO, dcgi->QUERY_STRING, rn);
				}
			}
			else {
				RegNoti* rn = criarRegNoti(3, "");
				paginaLogin(dcgi->PATH_INFO, dcgi->QUERY_STRING, rn);
			}
		}
		else {		// caso já tenha logado

			// checar se a sessão é válida

			//		1. obter número da sessão

			CampoFormularioHTML* cfIds = obterCampoFormularioHTML(form, "ids");
			Sessao* sessao = NULL;

			if (cfIds && bdBuscarSessao(cfIds->valor, &sessao)) {
				// Sessão inexistente ou erro na consulta, ir para página de login


			}
			else {

				if (!strcmp(cfAcao->valor, "sair")) {

					// sair do sistema

					RegNoti* rn = criarRegNoti(0, "saída realizada com sucesso.");
					sairTarefas(sessao, rn);

					return 0;

				}
				else {



					// checar se a sessão está vencida

					if (sessaoValida(sessao) == 0) {

						atualizarHoraSessao(sessao);

						// resgatar usuário da sessão

						Usuario* usu;
						bdUsuarioIdUsuario(sessao->idUsuario, &usu);

						//printf("QUERY_STRING: %s", dcgi->QUERY_STRING);

						// identificar página a ser acessada e carregar, caso a sessao seja válida


						/* * * * * * * * * * * * * * * * * * * * * * * * * *
						 *
						 *		Papel ADMINISTRADOR
						 *
						 * * * * * * * * * * * * * * * * * * * * * * * * * */



						if (!strcmp(cfAcao->valor, "administrador")) {

							paginaAdm(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "voltarAdministrador")) {

							paginaPapeis(usu, sessao);
						}


						/* Cadastro de Instituições */

						else if (!strcmp(cfAcao->valor, "cadinst")) {

							paginaCadInst(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "buscarinst")) {

							buscarInst(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcadinst")) {

							paginaAdm(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "novainst")) {

							paginaNovaInst(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarnovainst")) {

							paginaCadInst(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "salvarinst")) {

							salvarInst(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "visuinst")) {

							visualizarInst(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisuinst")) {

							paginaCadInst(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "atualizarinst")) {

							atualizarInst(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removerinst")) {

							removerInst(usu, sessao, form);
						}


						/* Cadastro de Curso */

						else if (!strcmp(cfAcao->valor, "cadcurso")) {

							paginaCadCurso(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "buscarcurso")) {

							buscarCurso(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcadcurso")) {

							paginaAdm(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "novocurso")) {

							paginaNovoCurso(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "salvarcurso")) {

							salvarCurso(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarnovocurso")) {

							paginaCadCurso(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "visucurso")) {

							visualizarCurso(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "atualizarcurso")) {

							atualizarCurso(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removercurso")) {

							removerCurso(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisucurso")) {

							paginaCadCurso(usu, sessao, form, NULL, NULL, NULL, 0);
						}


						/* Cadastro de Disciplina */

						else if (!strcmp(cfAcao->valor, "caddisc")) {

							paginaCadDisc(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "buscardisc")) {

							buscarDisc(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcaddisc")) {

							paginaAdm(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "novadisc")) {

							paginaNovaDisc(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "salvardisc")) {

							salvarDisc(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarnovadisc")) {

							paginaCadDisc(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "visudisc")) {

							visualizarDisc(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "atualizardisc")) {

							atualizarDisc(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removerdisc")) {

							removerDisc(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisudisc")) {

							paginaCadDisc(usu, sessao, form, NULL, NULL, NULL, 0);
						}


						/* Cadastro de Usuário */

						else if (!strcmp(cfAcao->valor, "cadusu")) {

							paginaCadUsu(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "buscarusu")) {

							buscarUsu(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcadusu")) {

							paginaAdm(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "novousu")) {

							paginaNovoUsu(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarnovousu")) {

							paginaCadUsu(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "salvarusu")) {

							salvarUsu(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "visuusu")) {

							visualizarUsu(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "atualizarusu")) {

							atualizarUsu(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removerusu")) {

							removerUsu(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisuusu")) {

							paginaCadUsu(usu, sessao, form, NULL, NULL, NULL, 0);
						}


						/* Cadastro de Perfil */

						else if (!strcmp(cfAcao->valor, "cadperfil")) {

							paginaCadPerfil(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "buscarpr")) {

							buscarPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcadperfil")) {

							paginaAdm(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaobuscapr")) {

							//paginaCadPerfil(usu, sessao, form, NULL, NULL, NULL, 0);
							selInstituicaoCursoCadperfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "novoperfil")) {

							paginaNovoPerfil(usu, sessao, form, NULL, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaonovopr")) {

							selInstituicaoCursoNovoPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "buscarusuarionovopr")) {

							buscarUsuarioNovoPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarnovoperfil")) {

							paginaCadPerfil(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "salvarpr")) {

							salvarPerfil(usu, sessao, form);
						}


						else if (!strcmp(cfAcao->valor, "cadloteperfis")) {

							CAMINHO_PAGINA_ENVIAR_LOTE = "/papeis/adm/cadperfil/enviarperfis.html";
							paginaEnviarLotePerfis(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "enviarloteperfis")) {

							enviarLotePerfis(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "checardadosloteperfis")) {

							checarDadosLotePerfis(usu, sessao, form);
						}

						else if (!strcmp(cfAcao->valor, "cadastrarloteperfis")) {

							cadastrarLotePerfis(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarenviarperfis")) {

							paginaCadPerfil(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "voltarchecarperfis")) {

							CAMINHO_PAGINA_ENVIAR_LOTE = "/papeis/adm/cadperfil/enviarperfis.html";
							paginaEnviarLotePerfis(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "encerrarcadastroloteperfis")) {

							paginaCadPerfil(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "visuperfil")) {

							visualizarPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaoatualizarpr")) {

							selInstituicaoCursoVisualizarPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "atualizarpr")) {

							atualizarPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removerperfil")) {

							removerPerfil(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisuperfil")) {

							paginaCadPerfil(usu, sessao, form, NULL, NULL, NULL, 0);
						}


						/* * * * * * * * * * * * * * * * * * * * * * * * * *
						 *
						 *		Papel PROFESSOR
						 *
						 * * * * * * * * * * * * * * * * * * * * * * * * * */


						else if (!strcmp(cfAcao->valor, "professor")) {

							paginaProfessor(usu, sessao, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarprofessor")) {

							paginaPapeis(usu, sessao);
						}

						/* Cadastro de Turma */

						else if (!strcmp(cfAcao->valor, "cadtur")) {

							paginaCadTurma(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "voltarcadturma")) {

							paginaProfessor(usu, sessao, NULL);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaobuscaturma")) {

							selInstituicaoDisciplinaCadturma(usu, sessao, form);
						}
						/*else if (!strcmp(cfAcao->valor, "seldisciplinabuscaturma")) {

							selInstituicaoDisciplinaCadturma(usu, sessao, form);
						}*/
						else if (!strcmp(cfAcao->valor, "buscarturma")) {

							buscarTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "novaturma")) {

							paginaNovaTurma(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarnovaturma")) {

							paginaCadTurma(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaonovaturma")) {

							selInstituicaoDisciplinaNovaTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "salvarturma")) {

							salvarTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "visuturma")) {

							visualizarTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisuturma")) {

							paginaCadTurma(usu, sessao, form, NULL, NULL, NULL, 0);
						}
						else if (!strcmp(cfAcao->valor, "atualizarturma")) {

							atualizarTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "buscarprofvisuturma")) {

							buscarProfTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "incluirnovoprofturma")) {

							incluirNovoProf(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removerprofturma")) {

							removerProfTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaoatualizarturma")) {

							selInstituicaoVisualizarTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "removerturma")) {

							removerTurma(usu, sessao, form);
						}


						/* Minhas Turmas */


						else if (!strcmp(cfAcao->valor, "minhasturmas")) {

							minhasTurmas(usu, sessao, form, NULL);

						}
						else if (!strcmp(cfAcao->valor, "voltarminhasturmas")) {

							paginaProfessor(usu, sessao, NULL);

						}
						else if (!strcmp(cfAcao->valor, "paginaturma")) {

							carregarPaginaTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginaturma")) {

							minhasTurmas(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "respondedoresturma")) {

							carregarRespondedoresTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarrespondedoresturma")) {

							carregarPaginaTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "incluirrespondedorturma")) {

							carregarIncluirRespondedorTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "selinstituicaoincluirrespondedorturma")) {

							selInstituicaoIncluirRespondedorTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarincluirrespondedorturma")) {

							carregarRespondedoresTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "buscarperfilincluirrespondedor")) {

							buscarPerfilIncluirRespondedorTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "salvarrespondedorturma")) {

							incluirRespondedorTurma(usu, sessao, form);
						}
						/*else if (!strcmp(cfAcao->valor, "incluirrespondedoresloteturma")) {

							carregarPaginaIncluirRespLoteTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "cadastrarrespondedoreslote")) {

							cadastrarRespondedoresLote(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarincluirrespondedoreslote")) {

							carregarRespondedoresTurma(usu, sessao, form, NULL);
						}*/
						else if (!strcmp(cfAcao->valor, "cadloterespondedores")) {

							paginaEnviarLoteRespondedores(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "enviarloterespondedores")) {

							enviarLoteRespondedores(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "checardadosloterespondedores")) {

							checarDadosLoteRespondedores(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "cadastrarloteperfisrespondedores")) {

							cadastrarLotePerfisRespondedores(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "cadastrarrespondedores")) {

							cadastrarRespondedores(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "encerrarcadastrorespondedores")) {

							carregarRespondedoresTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarchecarrespondedores")) {

							paginaEnviarLoteRespondedores(usu, sessao, form, NULL, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarenviarrespondedores")) {

							carregarRespondedoresTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "retornarpaginarespondedores")) {

							carregarRespondedoresTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "paginarespondedorturma")) {

							carregarRespondedorTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "removerrespondedorturma")) {

							removerRespondedorTurma(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "criartrabalho")) {

							carregarPaginaCriarTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "salvartrabalho")) {

							salvarTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "configurartrabalho")) {
							
							carregarPaginaConfigurarTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarconfigurartrabalho")) {

							carregarPaginaTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "atualizartrabalho")) {

							atualizarTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcriartrabalho")) {

							carregarPaginaTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "paginatrabalho")) {

							carregarPaginaTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "removertrabalho")) {

							removerTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginatrabalho")) {

							carregarPaginaTurma(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "escolhertipotarefa")) {

							escolherTipoTarefa(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarescolhertipotarefa")) {

							carregarPaginaTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "paginacadastrartarefa")) {

							carregarPaginaCadastrarTarefa(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarcadastrartarefa")) {

							escolherTipoTarefa(usu, sessao, form, NULL);
						}
						/*
						else if (!strcmp(cfAcao->valor, "montartarefasubmissaosimples")) {

							montarTarefaSubmissaoSimples(usu, sessao, form);
						}
						*/
						else if (!strcmp(cfAcao->valor, "cadastrartarefa")) {

							cadastrarTarefa(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "checarconfavaliacaocodigoc")) {

							checarArqsAvaliacaoCodigoC(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "enviarconfavaliacaostdin")) {

							salvarArqsAvaliacaoCodigoCSTDIN(usu, sessao, form, "paginatrabalho");
						}
						else if (!strcmp(cfAcao->valor, "enviarconfavaliacaoestatica")) {

							enviarArqsAvaliacaoCodigoC(usu, sessao, form, "paginatrabalho");
						}
						else if (!strcmp(cfAcao->valor, "configuraravaliacaocodigoc")) {

							editarConfiguracaoCodigoC(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "atualizarconfiguracaocodigoc")) {

							//salvarArqsAvaliacaoCodigoC(usu, sessao, form, "paginaitemtarefa");
							atualizarArqsAvaliacaoCodigoC(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "paginaincluirtarefatrabalho")) {

							carregarPaginaIncluirTarefaTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarincluirtarefatrabalho")) {

							carregarPaginaTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "incluirtarefatrabalho")) {

							incluirTarefaTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "duplicartarefatrabalho")) {

							carregarPaginaDuplicarTarefaTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "montarduplicartarefatrabalho")) {

							duplicarTarefaTrabalho(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "voltarduplicartarefatrabalho")) {

							carregarPaginaTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "paginaitemtarefa")) {

							carregarPaginaItemTarefa(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginaitemtarefa")) {

							carregarPaginaTrabalho(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "removeritemtarefa")) {

							removerItemTarefa(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "editaritemtarefa")) {

							atualizarItemTarefa(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "paginaentregas")) {

							carregarPaginaEntregasTarefa(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "visualizarentrega")) {

							visualizarEntrega(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarvisualizadorentrega")) {

							carregarPaginaEntregasTarefa(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarentregastarefa")) {

							carregarPaginaItemTarefa(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "downloadentrega")) {

							//printf("Content-Type: text/html; charset: utf-8\n\n");
							//printf("xxx");
							//return 0;
							dwldr(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "downloadvisualizarentrega")) {
													//   visualizarentrega

							//printf("Content-Type: text/html; charset: utf-8\n\n");
							//printf("xxx");
							//return 0;

							dwldr(usu, sessao, form);
						}






						/* * * * * * * * * * * * * * * * * * * * * * * * * *
						 *
						 *		Papel RESPONDEDOR
						 *
						 * * * * * * * * * * * * * * * * * * * * * * * * * */



						else if (!strcmp(cfAcao->valor, "respondedor")) {

							//printf("Pagina de Respondedor");
							carregarPaginaRespondedor(usu, sessao, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarrespondedor")) {

							//printf("Pagina de Respondedor");
							paginaPapeis(usu, sessao);
						}
						else if (!strcmp(cfAcao->valor, "paginaperfilrespondedor")) {

							//printf("Pagina de Respondedor");
							carregarPaginaPerfilRespondedor(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginaperfilrespondedor")) {

							//printf("Pagina de Respondedor");
							carregarPaginaRespondedor(usu, sessao, NULL);
						}
						else if (!strcmp(cfAcao->valor, "paginaturmaperfil")) {

							//printf("Pagina de Respondedor");
							carregarPaginaTurmaPerfil(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginaturmaperfil")) {

							//printf("Pagina de Respondedor");
							carregarPaginaPerfilRespondedor(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "paginatrabalhoperfil")) {

							//printf("Pagina de Respondedor");
							carregarPaginaTrabalhoPerfil(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginatrabalhoperfil")) {

							//printf("Pagina de Respondedor");
							carregarPaginaTurmaPerfil(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "exibiritemtarefa")) {

							//printf("Pagina de Respondedor");
							carregarPaginaExibirItemTarefa(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "voltarpaginaexibiritemtarefa")) {

							//printf("Pagina de Respondedor");
							carregarPaginaTrabalhoPerfil(usu, sessao, form, NULL);
						}
						else if (!strcmp(cfAcao->valor, "submeterresposta")) {

							//printf("Pagina de Respondedor");
							salvarRespostaItemTarefa(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "salvarrespostacodigoc")) {

							//printf("Pagina de Respondedor");
							salvarRespostaItemTarefaCodigoC(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "avaliarrespostacodigoc")) {

							//printf("Pagina de Respondedor");
							avaliarRespostaItemTarefaCodigoC(usu, sessao, form);
						}
						else if (!strcmp(cfAcao->valor, "executarrespostacodigocstdin")) {

							//printf("Pagina de Respondedor");
							executarRespostaItemTarefaCodigoCSTDIN(usu, sessao, form);
						}
						
					}
					else {

						// caso sessão esteja vencida, redirecionar para página de login

						printf("Sessão inválida.");
					}

				}

			}

		}
	}
	else {		// caso esteja acessando o sistema a partir de url

		RegNoti* rn = criarRegNoti(0, "");
		//printf("QUERY_STRING: %s<br>", dcgi->QUERY_STRING);
		//printf("PATH_INFO: %s", dcgi->PATH_INFO);
		
		//char* destino = concatstr2(dcgi->PATH_INFO ? dcgi->PATH_INFO : "", concatstr2("?", dcgi->QUERY_STRING));
                paginaLogin(dcgi->PATH_INFO, dcgi->QUERY_STRING, rn);
	}



}
