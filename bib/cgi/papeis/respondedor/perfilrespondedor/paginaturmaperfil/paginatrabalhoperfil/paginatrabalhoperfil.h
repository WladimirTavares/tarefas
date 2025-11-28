/* minhasturmas.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../../../../str/bibstring2.h"
#include "../../../../../../str/multilinhas.h"

#include "../../../../../../lugar.h"
#include "../../../../../../notifica.h"

#include "../../../../../sessaocgi.h"
#include "../../../../../htmlcgi.h"



int paginaTrabalhoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Trabalho* trab, ItemTarefa* itens, char** statusEtregas, int numItens, RegNoti* rn);

int carregarPaginaTrabalhoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn);

char* htmlFormPaginaItemTarefaPerfil(char* idPerfilRespondedor, ItemTarefa* it, char* idTrabalho, char* idTurma, char* idSessao, char* statusEntrega);



/*      Implementações      */




int paginaTrabalhoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Trabalho* trab, ItemTarefa* itens, char** statusEtregas, int numItens, RegNoti* rn){

    if (usu && sessao) {

        Multilinhas* ml = mlCriar();

        // carregar modelo

        char* caminho = concatstr(dirHtml, "/papeis/respondedor/paginaperfilrespondedor/paginaturmaperfil/paginatrabalhoperfil/paginatrabalhoperfil.html");

        mlCarregarArquivoTexto(caminho, ml);

        // instanciar dados de sessão, de sistema, etc.

        incluirDadosSessao(usu, sessao, form, ml);

        // colocar dados do perfil

        mlSubstituirTodos("$IDPERFILRESPONDEDOR$", idPerfilRespondedor, ml);

        // colocar mensagem

        char* msg = msgNotiHTML(rn);

        mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

        

        // Colocar dados do trabalho

        char infotrabalho[4097] = "";

        sprintf(infotrabalho,
                "%d - %s",
                *(trab->numTrabalho), trab->titulo);

        mlSubstituirTodos("$INFOTRABALHO$", infotrabalho, ml);

        char* idTrabalho = llistr(*(trab->idTrabalho));
        mlSubstituirTodos("$IDTRABALHO$", idTrabalho, ml);

         // Colocar dados da turma

        char turmastr[4097] = "";

        sprintf(turmastr,
                "Cod. %s - %s.%s - %s - %s (%s)",
                turma->codigo, turma->ano, turma->semestre, turma->disc->codigo, turma->disc->nome, turma->disc->inst->sigla);

        mlSubstituirTodos("$TURMA$", turmastr, ml);

        char* idturma = llistr(*(turma->idTurma));
        mlSubstituirTodos("$IDTURMA$", idturma, ml);

        // Obter id da sessão

        CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "ids");

        char* idSessao = cf->valor;

        // Colocar itens de tarefa

        if (itens) {

            NoLinha* nl = mlEncontrar("@Tarefas", ml);
            char* linha = NULL;

            for (int i = 0; i < numItens; i++) {

                linha = htmlFormPaginaItemTarefaPerfil(idPerfilRespondedor, &(itens[i]), idTrabalho, idturma, idSessao, statusEtregas[i]);
                mlInserirAcima(linha, nl, ml);
            }

        }
        
        // instanciar dados de sessão, de sistema, etc.

        incluirDadosSessao(usu, sessao, form, ml);

         mlImprimir(ml);
    }

}



char* htmlFormPaginaItemTarefaPerfil(char* idPerfilRespondedor, ItemTarefa* it, char* idTrabalho, char* idTurma, char* idSessao, char* statusEntrega) {

    Multilinhas* ml = mlCriar();

    char linha[500] = "";

    // imprimir formulário do respondedor
    mlAnexarLinha("<form method=\"post\">\n", ml);

    sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"$URLTAREFAS$\" value=\"exibiritemtarefa\">%d - %s</button> %s\n", *(it->numItemTarefa), it->tarefa->titulo, statusEntrega ? statusEntrega : "");
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idPerfilRespondedor\" value=\"%s\">\n", idPerfilRespondedor);
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idItemTarefa\" value=\"%lld\">\n", *(it->idItemTarefa));
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idTrabalho\" value=\"%s\">\n", idTrabalho);
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idTurma\" value=\"%s\">\n", idTurma);
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%s\">\n", idSessao);
    mlAnexarLinha(linha, ml);

    mlAnexarLinha("</form>", ml);

    return mlExtrairTexto(ml);

}



int carregarPaginaTrabalhoPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn) {

    RegNoti* rnaux = NULL;

    char* idPerfil = NULL;
    if ( !(idPerfil = obterCFHVal("idPerfilRespondedor", form, "identificador do perfil de respondedor", CHARDIG, &rnaux)) ) {
        carregarPaginaTurmaPerfil(usu, sessao, form, rnaux);
        return 1;
    }

    /* CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idPerfilRespondedor");
	char* idPerfil = cf ? cf->valor : copiastr("");

    if (cf && utf8Val(idPerfil, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		RegNoti* rn = criarRegNoti(1, "Caractere inválido no identificador de perfil.");

        carregarPaginaRespondedor(usu, sessao, rn);
        return 1;
	} */

    char* idTurma = NULL;
    if ( !(idTurma = obterCFHVal("idTurma", form, "identificador da turma", CHARDIG, &rnaux)) ) {
        minhasTurmas(usu, sessao, form, rnaux);
        return 1;
    }

    /* cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : ""; */

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        carregarPaginaPerfilRespondedor(usu, sessao, form, rnaux);
        return 1;

    }

    // Carregar trabalho

    char* idTrabalho = NULL;
    if ( !(idTrabalho = obterCFHVal("idTrabalho", form, "identificador do trabalho", CHARDIG, &rnaux)) ) {
        minhasTurmas(usu, sessao, form, rnaux);
        return 1;
    }

    /* cf = obterCampoFormularioHTML(form, "idTrabalho");
    char* idTrabalho = cf ? cf->valor : ""; */

    Trabalho* trab = NULL;
    int numtrabs = 0;

    ret = bdBuscarTrabalhoId(idTrabalho, &trab, &numtrabs);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar trabalho da turma.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTurmaPerfil(usu, sessao, form, rnaux);
        return 3;
    }

    // Carregar itens de tarefa

    ItemTarefa* itens = NULL;
    int numItens = 0;

    ret = bdBuscarItensTarefaIdTrabalho(idTrabalho, &itens, &numItens);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar tarefas do trabalho.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rnaux);
        return 3;
    }

    // Checar quais itens tem respostas enviadas

    //int* respostasEnv = NULL;
    char** statusEntregas = NULL;
    if (numItens > 0) {
        //respostasEnv = (int *) malloc(numItens * sizeof(int));
        statusEntregas = (char **) malloc(numItens * sizeof(char *));
    }

    /*
     *
     *
     *       Checar tipo de cada tarefa e tomar providências de acordo.
     *
     * 
     * 
     * 
     * */


    for (int i = 0; i < numItens; i++) {

        //char* caminhoarquivo = concatstr2(dirDadosPerfilItemTarefa(atoi(idTrabalho), *(itens[i].idItemTarefa), atoi(idPerfil)), "/resposta.pdf");

        if (*(itens[i].tarefa->tipo) == BD_TT_SUBMISSAOSIMPLES) {

            statusEntregas[i] = statusEntregaTarefaSubmissaoSimples(atoi(idTrabalho), *(itens[i].idItemTarefa), atoi(idPerfil));
        }
        else if (*(itens[i].tarefa->tipo) == BD_TT_CODIGOC) {

            statusEntregas[i] = statusEntregaTarefaCodigoC(atoi(idTrabalho), *(itens[i].idItemTarefa), atoi(idPerfil));
        }
        else {
            statusEntregas[i] = NULL;
        }

    }


    paginaTrabalhoPerfil(usu, sessao, form, idPerfil, turma, trab, itens, statusEntregas, numItens, rn);

    return 0;

}











