/* minhasturmas.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../../../str/bibstring2.h"
#include "../../../../../str/multilinhas.h"

#include "../../../../../lugar.h"
#include "../../../../../notifica.h"

#include "../../../../sessaocgi.h"
#include "../../../../htmlcgi.h"



int paginaTurmaPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Usuario* profs, int numprofs, Trabalho* trabalhos, int numtrabs, RegNoti* rn);

int carregarPaginaTurmaPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn);

char* htmlFormPaginaTrabalhoPerfil(char* idPerfilRespondedor, Trabalho* trabalho, char* idTurma, char* idSessao);



/*      Implementações      */




int paginaTurmaPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Usuario* profs, int numprofs, Trabalho* trabalhos, int numtrabs, RegNoti* rn) {

    if (usu && sessao) {

        Multilinhas* ml = mlCriar();

        // carregar modelo

        char* caminho = concatstr(dirHtml, "/papeis/respondedor/paginaperfilrespondedor/paginaturmaperfil/paginaturmaperfil.html");

        mlCarregarArquivoTexto(caminho, ml);

        // instanciar dados de sessão, de sistema, etc.

        incluirDadosSessao(usu, sessao, form, ml);

        // colocar dados do perfil

        mlSubstituirTodos("$IDPERFILRESPONDEDOR$", idPerfilRespondedor, ml);

        // colocar mensagem

        char* msg = msgNotiHTML(rn);

        mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

        // Colocar dados da turma

        char turmastr[4097] = "";

        sprintf(turmastr,
                "Cod. %s - %s.%s - %s - %s (%s)",
                turma->codigo, turma->ano, turma->semestre, turma->disc->codigo, turma->disc->nome, turma->disc->inst->sigla);

        mlSubstituirTodos("$TURMA$", turmastr, ml);

        char* idturma = llistr(*(turma->idTurma));
        mlSubstituirTodos("$IDTURMA$", idturma, ml);

        // Colocar professores

        if (profs) {

            char linha[500];

            NoLinha* nl = mlEncontrar("@Professores", ml);

            for (int i = 0; i < numprofs; i++) {

                sprintf(linha, "%s - %s<br>", profs[i].nome, profs[i].email);

                mlInserirAcima(linha, nl, ml);
            }

            mlInserirAcima("<br>\n", nl, ml);

        }

        // Obter id da sessão

        CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "ids");

        char* idSessao = cf->valor;


        // Colocar trabalhos

        if (trabalhos) {

            //char linha[500];

            NoLinha* nl = mlEncontrar("@Trabalhos", ml);

            for (int i = 0; i < numtrabs; i++) {

                //sprintf(linha, "T%lld - %s<br>", *(trabalhos[i].idTrabalho), trabalhos[i].titulo);

                char* linha = htmlFormPaginaTrabalhoPerfil(idPerfilRespondedor, &(trabalhos[i]), idturma, idSessao);

                mlInserirAcima(linha, nl, ml);
            }
        }

        // Se foram passados trabalhos, listá-los

        // OBS.: O código do botão para acessar a página do trabalho inclui código javascript para
        //		 definir o valor do input idTrabalho que guarda o id do trabalho a ser selecionado
        //		 Quando o botão é clicado esse campo do fórmulário é definido.

        /*
        if (trabs) {

            NoLinha* nl = mlEncontrar("@Trabalhos", ml);

            for (int i = 0; i < numtrabs; i++) {

                // imprimir formulário da turma
                mlInserirAcima("<form method=\"post\">", nl, ml);

                sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"./cadturma\" value=\"paginatrabalho\">Cod. %s - %s - %s - %s - %s - %s</button>\n", turmas[i].codigo, turmas[i].ano, turmas[i].semestre, turmas[i].disc->codigo, turmas[i].disc->nome,  turmas[i].disc->inst->sigla);
                mlInserirAcima(linha, nl, ml);

                sprintf(linha, "<input type=\"hidden\" name=\"idDisciplina\" value=\"%lld\">\n", *(turmas[i].idDisciplina));
                mlInserirAcima(linha, nl, ml);
                sprintf(linha, "<input type=\"hidden\" name=\"idTurma\" value=\"%lld\">\n", *(turmas[i].idTurma));
                mlInserirAcima(linha, nl, ml);

                sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%lld\">\n", sessao->idSessao);
                mlInserirAcima(linha, nl, ml);
                mlInserirAcima("</form>", nl, ml);

            }

        }
        */

         mlImprimir(ml);
    }



}



char* htmlFormPaginaTrabalhoPerfil(char* idPerfilRespondedor, Trabalho* trabalho, char* idTurma, char* idSessao) {

    Multilinhas* ml = mlCriar();

    char linha[500] = "";

    // imprimir formulário do respondedor
    mlAnexarLinha("<form method=\"post\">\n", ml);

    sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"paginatrabalhoperfil\">%d - %s</button>\n", *(trabalho->numTrabalho), trabalho->titulo);
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idTrabalho\" value=\"%lld\">\n", *(trabalho->idTrabalho));
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idPerfilRespondedor\" value=\"%s\">\n", idPerfilRespondedor);
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"idTurma\" value=\"%s\">\n", idTurma);
    mlAnexarLinha(linha, ml);

    sprintf(linha, "<input type=\"hidden\" name=\"ids\" value=\"%s\">\n", idSessao);
    mlAnexarLinha(linha, ml);

    mlAnexarLinha("</form>", ml);

    return mlExtrairTexto(ml);

}



int carregarPaginaTurmaPerfil(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn) {


    CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idPerfilRespondedor");
	char* idPerfil = cf ? cf->valor : copiastr("");

    if (cf && utf8Val(idPerfil, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		RegNoti* rn = criarRegNoti(1, "Caractere inválido no identificador de perfil.");

        carregarPaginaRespondedor(usu, sessao, rn);
        return 1;
	}


    cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : "";

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        minhasTurmas(usu, sessao, form, rn);
        return 1;

    }

    // Carregar professores

    char* idprofcriador = llistr(*(turma->idProfCriador));
    char* idturma = llistr(*(turma->idTurma));

    Usuario* profs = NULL;
    int numprofs = 0;

    ret = bdBuscarProfsTurmaId(idturma, idprofcriador, &profs, &numprofs);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar professores da turma.");

        minhasTurmas(usu, sessao, form, rn);
        return 2;
    }

    // Carregar trabalhos da turma

    Trabalho* trabs = NULL;
    int numtrabs = 0;

    ret = bdBuscarTrabalhosTurmaId(idTurma, &trabs, &numtrabs);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar trabalhos da turma.");

        //minhasTurmas(usu, sessao, form, rn);
        paginaTurmaPerfil(usu, sessao, form, idPerfil, turma, profs, numprofs, NULL, 0, rn);
        return 3;
    }


    paginaTurmaPerfil(usu, sessao, form, idPerfil, turma, profs, numprofs, trabs, numtrabs, rn);

    return 0;

}











