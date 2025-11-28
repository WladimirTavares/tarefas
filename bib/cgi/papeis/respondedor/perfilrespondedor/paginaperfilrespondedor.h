/* minhasturmas.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../../str/bibstring2.h"
#include "../../../../str/multilinhas.h"

#include "../../../../lugar.h"
#include "../../../../notifica.h"

#include "../../../sessaocgi.h"
#include "../../../htmlcgi.h"



int paginaPerfilRespondedor(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turmas, int numturmas, RegNoti* rn);

int carregarPaginaPerfilRespondedor(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn);




/*      Implementações      */




int paginaPerfilRespondedor(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turmas, int numturmas, RegNoti* rn) {

    if (usu && sessao) {

        Multilinhas* ml = mlCriar();

        // carregar modelo

        char* caminho = concatstr(dirHtml, "/papeis/respondedor/paginaperfilrespondedor/paginaperfilrespondedor.html");

        mlCarregarArquivoTexto(caminho, ml);

        // instanciar dados de sessão, de sistema, etc.

        incluirDadosSessao(usu, sessao, form, ml);

        // colocar mensagem

        char* msg = msgNotiHTML(rn);

        mlSubstituirTodos("$MSG$", msg ? msg : "", ml);

        char linha[500];

        // Se foram passadas turmas, listar as turmas

        if (turmas) {

            NoLinha* nlTurmasAbertas = mlEncontrar("@TurmasAbertas", ml);

            NoLinha* nlTurmasEncerradas = mlEncontrar("@TurmasEncerradas", ml);

            NoLinha* nl = NULL;

            for (int i = 0; i < numturmas; i++) {

                if (*(turmas[i].encerrada))
                    nl = nlTurmasEncerradas;
                else
                    nl = nlTurmasAbertas;

                // imprimir formulário da turma
                mlInserirAcima("<form method=\"post\">", nl, ml);

                sprintf(linha, "<button type=\"submit\" class=\"botaoLink\" name=\"acao\" formaction=\"\" value=\"paginaturmaperfil\">Cod. %s - %s - %s - %s - %s - %s</button>\n", turmas[i].codigo, turmas[i].ano, turmas[i].semestre, turmas[i].disc->codigo, turmas[i].disc->nome,  turmas[i].disc->inst->sigla);
                mlInserirAcima(linha, nl, ml);

                sprintf(linha, "<input type=\"hidden\" name=\"idPerfilRespondedor\" value=\"%s\">\n", idPerfilRespondedor);
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

        mlImprimir(ml);
    }

}



int carregarPaginaPerfilRespondedor(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn) {


    //char* idUsuario = llistr(*(usu->idUsuario));

    CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idPerfilRespondedor");
	char* idPerfil = cf ? cf->valor : copiastr("");

    if (cf && utf8Val(idPerfil, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		RegNoti* rn = criarRegNoti(1, "Caractere inválido no identificador de perfil.");

        carregarPaginaRespondedor(usu, sessao, rn);
        return 1;
	}

    Turma* turmas = NULL;
    int numturmas = 0;

    int ret = bdTurmasPerfil(idPerfil, &turmas, &numturmas);

    if (ret) {

        RegNoti* rn = criarRegNoti(2, "Erro ao tentar resgatar turmas do banco.");

        carregarPaginaRespondedor(usu, sessao, rn);
        return 2;

    }

    paginaPerfilRespondedor(usu, sessao, form, idPerfil, turmas, numturmas, rn);

    return 0;

}











