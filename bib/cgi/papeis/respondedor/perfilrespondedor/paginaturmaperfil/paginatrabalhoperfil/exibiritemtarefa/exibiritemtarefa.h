/* minhasturmas.h
 *
 * implementa métodos para geração da página de cadastro de usuários
 */


#include "../../../../../../../str/bibstring2.h"
#include "../../../../../../../str/multilinhas.h"

#include "../../../../../../../lugar.h"
#include "../../../../../../../notifica.h"

#include "../../../../../../sessaocgi.h"
#include "../../../../../../htmlcgi.h"



int paginaExibirItemTarefaSubmissaoSimples(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor,Turma* turma, Trabalho* trab, ItemTarefa* item, char* statusEntrega, RegNoti* rn);

int paginaExibirItemTarefaCodigoC(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor,Turma* turma, Trabalho* trab, ItemTarefa* item, char* statusEntrega, char* resposta, int palavrares, char* palavraresmsg, int falhaAval, int gccrespostaexit, char* gccrespostalog, int gccexecctexit, char* gccexecctlog, int gccexecavalexit, char* gccexecavallog, char* feedback, RegNoti* rn);

int carregarPaginaExibirItemTarefa(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn);

int salvarRespostaItemTarefa(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int salvarRespostaItemTarefaCodigoC(Usuario* usu, Sessao* sessao, FormularioHTML* form);

int avaliarRespostaItemTarefaCodigoC(Usuario* usu, Sessao* sessao, FormularioHTML* form);

char* caminhoCompiladoResposta(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor);


// char* htmlFormPaginaItemTarefa(ItemTarefa* it, char* idTrabalho, char* idTurma, char* idSessao);



/*      Implementações      */




int paginaExibirItemTarefaSubmissaoSimples(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Trabalho* trab, ItemTarefa* item, char* statusEntrega, RegNoti* rn){

    if (usu && sessao) {

        Multilinhas* ml = mlCriar();

        // carregar modelo

        char* caminho = concatstr(dirHtml, "/papeis/respondedor/paginaperfilrespondedor/paginaturmaperfil/paginatrabalhoperfil/exibiritemtarefa/exibiritemtarefa.html");

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


        char* iditemtarefa = llistr(*(item->idItemTarefa));
        mlSubstituirTodos("$IDITEMTAREFA$", iditemtarefa, ml);

        //char* iditemtarefa = llistr(*(item->iditemtarefa));
        //mlSubstituirTodos("$IDITEMTAREFA$", iditemtarefa, ml);

        // Colocar link para a imagem do enunciado
        // A imagem do enunciado fica no diretório de downloads

        //char* urlimg = "http://127.0.0.1/tarefasdwl/0/113";
        char* urlimg = urlEnunciadoPNG(*(item->idTarefa));

        mlSubstituirTodos("$ENUNCIADOTAREFA$", urlimg, ml);

        unsigned int ap = 0;

        imgAlturaPadraoPNG(caminhoEnunciadoPNG(*(item->idTarefa)), 0.3426, &ap);

        char strap[13] = "";
        sprintf(strap, "%upx", ap);

        mlSubstituirTodos("$ALTURAENUN$", strap, ml);

        mlSubstituirTodos("$RESPOSTAENVIADA$", statusEntrega, ml);

/* 
        if (respostaEnviada)
            mlSubstituirTodos("$RESPOSTAENVIADA$", "Resposta enviada!", ml);
        else
            mlSubstituirTodos("$RESPOSTAENVIADA$", "", ml);
 */

         mlImprimir(ml);
    }



}



int paginaExibirItemTarefaCodigoC(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Trabalho* trab, ItemTarefa* item, char* statusEntrega, char* resposta, int palavrares, char* palavraresmsg, int falhaAval, int gccrespostaexit, char* gccrespostalog, int gccexecctexit, char* gccexecctlog, int gccexecavalexit, char* gccexecavallog, char* feedback, RegNoti* rn){

    if (usu && sessao) {

        Multilinhas* ml = mlCriar();

        // carregar modelo

        char* caminho = concatstr(dirHtml, "/papeis/respondedor/paginaperfilrespondedor/paginaturmaperfil/paginatrabalhoperfil/exibiritemtarefa/exibiritemtarefacodigoc.html");

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


        char* iditemtarefa = llistr(*(item->idItemTarefa));
        mlSubstituirTodos("$IDITEMTAREFA$", iditemtarefa, ml);

        //char* iditemtarefa = llistr(*(item->iditemtarefa));
        //mlSubstituirTodos("$IDITEMTAREFA$", iditemtarefa, ml);

        // Colocar link para a imagem do enunciado
        // A imagem do enunciado fica no diretório de downloads

        //char* urlimg = "http://127.0.0.1/tarefasdwl/0/113";
        char* urlimg = urlEnunciadoPNG(*(item->idTarefa));

        mlSubstituirTodos("$ENUNCIADOTAREFA$", urlimg, ml);

        unsigned int ap = 0;

        imgAlturaPadraoPNG(caminhoEnunciadoPNG(*(item->idTarefa)), 0.3426, &ap);

        char strap[13] = "";
        sprintf(strap, "%upx", ap);


        // colocar dicas
        NoLinha* nl = mlEncontrar("@dicas", ml);
        // int len = strlen(item->tarefa->descricao);
        // len = len + 200;
        char* dicas = NULL;

        dicas = concatstr2("<details> <summary>Dicas</summary> ", item->tarefa->obs);
        dicas = concatstr2(dicas, "</details>");
        mlInserirAbaixo(dicas, nl, ml);

        // colocar endereço do bundle codemirror
        mlSubstituirTodos("$URLDWLTAREFAS$", urlTarefasDwl, ml);

        mlSubstituirTodos("$ALTURAENUN$", strap, ml);

        mlSubstituirTodos("$RESPOSTAENVIADA$", statusEntrega, ml);

        // colocar resposta
        mlSubstituirTodos("$RESPOSTA$", resposta, ml);



	// remove botão de envio, caso trabalho já tenha encerrado
        nl = mlEncontrar("@btavaliar", ml);
        time_t agora = time(NULL);
        if (agora > *(trab->segHoraFim)) {
                mlRemoverNoLinha(nl, ml);
        }




        // checar se não houve envio
        if (!strcmp(statusEntrega, "")) {
            mlSubstituirTodos("$PALAVRASRESERVADAS$", "", ml);
            mlSubstituirTodos("$GCCRESPOSTAEXIT$", "", ml);
            mlSubstituirTodos("$GCCRESPOSTALOG$", "", ml);
            mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        // Checar palavra reservada
        if (palavrares) {
            mlSubstituirTodos("$PALAVRASRESERVADAS$", palavraresmsg, ml);
            mlSubstituirTodos("$GCCRESPOSTAEXIT$", "", ml);
            mlSubstituirTodos("$GCCRESPOSTALOG$", "", ml);
            mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        mlSubstituirTodos("$PALAVRASRESERVADAS$", "", ml);


        // checar erro de compilação da resposta submetida
        if (gccrespostaexit) {

            char* html = "<div>Erro de compilação</div>";
            mlSubstituirTodos("$GCCRESPOSTAEXIT$", html, ml);
            mlSubstituirTodos("$GCCRESPOSTALOG$", gccrespostalog ? gccrespostalog : "", ml);
            mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }
        
        mlSubstituirTodos("$GCCRESPOSTAEXIT$", "Compilação bem sucedida.", ml);
        mlSubstituirTodos("$GCCRESPOSTALOG$", gccrespostalog, ml);

        // checar erro de compilação do código de execução de caso de teste
        if (gccexecctexit) {

            char* html = "<div>Erro de compilação do código de execução de caso de teste.</div>";
            mlSubstituirTodos("$GCCEXECCTEXIT$", html, ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", gccexecctlog, ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
        mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
        
        //mlSubstituirTodos("$GCCEXECCTEXIT$", "Compilação bem sucedida.", ml);
        //mlSubstituirTodos("$GCCEXECCTLOG$", gccrespostalog, ml);


        // checar erro de compilação do códigp de avaliação
        if (gccexecavalexit) {

            char* html = "<div>Erro de compilação do código de avaliação.</div>";
            mlSubstituirTodos("$GCCEXECAVALEXIT$", html, ml);
            //mlSubstituirTodos("$GCCEXECAVALLOG$", gccexecavallog, ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
        mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);

        //mlSubstituirTodos("$GCCEXECAVALEXIT$", "Compilação bem sucedida.", ml);
        //mlSubstituirTodos("$GCCEXECAVALLOG$", gccexecavallog, ml);

        // colocar feedback
        mlSubstituirTodos("$FEEDBACK$", feedback, ml);

/* 
        if (respostaEnviada)
            mlSubstituirTodos("$RESPOSTAENVIADA$", "Resposta enviada!", ml);
        else
            mlSubstituirTodos("$RESPOSTAENVIADA$", "", ml);
 */

         mlImprimir(ml);
    }



}



int paginaExibirItemTarefaCodigoCSTDIN(Usuario* usu, Sessao* sessao, FormularioHTML* form, char* idPerfilRespondedor, Turma* turma, Trabalho* trab, ItemTarefa* item, char* statusEntrega, char* resposta, int palavrares, char* palavraresmsg, int falhaAval, int gccrespostaexit, char* gccrespostalog, int gccexecctexit, char* gccexecctlog, int gccexecavalexit, char* gccexecavallog, char* feedback, RegNoti* rn){

    if (usu && sessao) {

        Multilinhas* ml = mlCriar();

        // carregar modelo

        char* caminho = concatstr(dirHtml, "/papeis/respondedor/paginaperfilrespondedor/paginaturmaperfil/paginatrabalhoperfil/exibiritemtarefa/exibiritemtarefacodigocstdin.html");

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


        char* iditemtarefa = llistr(*(item->idItemTarefa));
        mlSubstituirTodos("$IDITEMTAREFA$", iditemtarefa, ml);

        //char* iditemtarefa = llistr(*(item->iditemtarefa));
        //mlSubstituirTodos("$IDITEMTAREFA$", iditemtarefa, ml);

        // Colocar link para a imagem do enunciado
        // A imagem do enunciado fica no diretório de downloads

        //char* urlimg = "http://127.0.0.1/tarefasdwl/0/113";
        char* urlimg = urlEnunciadoPNG(*(item->idTarefa));

        mlSubstituirTodos("$ENUNCIADOTAREFA$", urlimg, ml);

        unsigned int ap = 0;

        imgAlturaPadraoPNG(caminhoEnunciadoPNG(*(item->idTarefa)), 0.3426, &ap);

        char strap[13] = "";
        sprintf(strap, "%upx", ap);

        // colocar dicas
        NoLinha* nl = mlEncontrar("@dicas", ml);
        // int len = strlen(item->tarefa->descricao);
        // len = len + 200;
        char* dicas = NULL;

        dicas = concatstr2("<details> <summary>Dicas</summary> ", item->tarefa->obs);
        dicas = concatstr2(dicas, "</details>");
        mlInserirAbaixo(dicas, nl, ml);

        // colocar endereço do bundle codemirror
        mlSubstituirTodos("$URLDWLTAREFAS$", urlTarefasDwl, ml);

        mlSubstituirTodos("$ALTURAENUN$", strap, ml);

        mlSubstituirTodos("$RESPOSTAENVIADA$", statusEntrega, ml);

        // colocar resposta
        mlSubstituirTodos("$RESPOSTA$", resposta, ml);


        // colocar endereço do bundle codemirror
        mlSubstituirTodos("$URLDWLTAREFAS$", urlTarefasDwl, ml);

        mlSubstituirTodos("$ALTURAENUN$", strap, ml);

        mlSubstituirTodos("$RESPOSTAENVIADA$", statusEntrega, ml);

        // colocar resposta
        mlSubstituirTodos("$RESPOSTA$", resposta, ml);



	// remove botão de envio, caso trabalho já tenha encerrado
        nl = mlEncontrar("@btavaliar", ml);
        time_t agora = time(NULL);
        if (agora > *(trab->segHoraFim)) {
                mlRemoverNoLinha(nl, ml);
        }



        // checar se não houve envio
        if (!strcmp(statusEntrega, "")) {
            mlSubstituirTodos("$PALAVRASRESERVADAS$", "", ml);
            mlSubstituirTodos("$GCCRESPOSTAEXIT$", "", ml);
            mlSubstituirTodos("$GCCRESPOSTALOG$", "", ml);
            mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        // Checar palavra reservada
        if (palavrares) {
            mlSubstituirTodos("$PALAVRASRESERVADAS$", palavraresmsg, ml);
            mlSubstituirTodos("$GCCRESPOSTAEXIT$", "", ml);
            mlSubstituirTodos("$GCCRESPOSTALOG$", "", ml);
            mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        mlSubstituirTodos("$PALAVRASRESERVADAS$", "", ml);


        // checar erro de compilação da resposta submetida
        if (gccrespostaexit) {

            char* html = "<div>Erro de compilação</div>";
            mlSubstituirTodos("$GCCRESPOSTAEXIT$", html, ml);
            mlSubstituirTodos("$GCCRESPOSTALOG$", gccrespostalog ? gccrespostalog : "", ml);
            mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }
        
        mlSubstituirTodos("$GCCRESPOSTAEXIT$", "Compilação bem sucedida.", ml);
        mlSubstituirTodos("$GCCRESPOSTALOG$", gccrespostalog, ml);

        // checar erro de compilação do código de execução de caso de teste
        if (gccexecctexit) {

            char* html = "<div>Erro de compilação do código de execução de caso de teste.</div>";
            mlSubstituirTodos("$GCCEXECCTEXIT$", html, ml);
            mlSubstituirTodos("$GCCEXECCTLOG$", gccexecctlog, ml);
            mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
            mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        mlSubstituirTodos("$GCCEXECCTEXIT$", "", ml);
        mlSubstituirTodos("$GCCEXECCTLOG$", "", ml);
        
        //mlSubstituirTodos("$GCCEXECCTEXIT$", "Compilação bem sucedida.", ml);
        //mlSubstituirTodos("$GCCEXECCTLOG$", gccrespostalog, ml);


        // checar erro de compilação do códigp de avaliação
        if (gccexecavalexit) {

            char* html = "<div>Erro de compilação do código de avaliação.</div>";
            mlSubstituirTodos("$GCCEXECAVALEXIT$", html, ml);
            //mlSubstituirTodos("$GCCEXECAVALLOG$", gccexecavallog, ml);
            mlSubstituirTodos("$FEEDBACK$", "", ml);
            mlImprimir(ml);
            return 0;
        }

        mlSubstituirTodos("$GCCEXECAVALEXIT$", "", ml);
        mlSubstituirTodos("$GCCEXECAVALLOG$", "", ml);

        //mlSubstituirTodos("$GCCEXECAVALEXIT$", "Compilação bem sucedida.", ml);
        //mlSubstituirTodos("$GCCEXECAVALLOG$", gccexecavallog, ml);

        // colocar feedback
        mlSubstituirTodos("$FEEDBACK$", feedback, ml);

/* 
        if (respostaEnviada)
            mlSubstituirTodos("$RESPOSTAENVIADA$", "Resposta enviada!", ml);
        else
            mlSubstituirTodos("$RESPOSTAENVIADA$", "", ml);
 */

         mlImprimir(ml);
    }



}



int carregarPaginaExibirItemTarefa(Usuario* usu, Sessao* sessao, FormularioHTML* form, RegNoti* rn) {


    char* idPerfil = NULL;
    if ( !(idPerfil = obterCFHVal("idPerfilRespondedor", form, "identificador do perfil de respondedor", CHARDIG, &rn)) ) {
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);
        return 1;
    }

    /*
    CampoFormularioHTML* cf = obterCampoFormularioHTML(form, "idPerfilRespondedor");
	char* idPerfil = cf ? cf->valor : copiastr("");

    if (cf && utf8Val(idPerfil, CHARDIG, NULL)) {
		// caracteres inválidos na sigla

		RegNoti* rn = criarRegNoti(1, "Caractere inválido no identificador de perfil.");

        carregarPaginaRespondedor(usu, sessao, rn);
        return 1;
	}
    */

    char* idTurma = NULL;
    if ( !(idTurma = obterCFHVal("idTurma", form, "identificador da turma", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }

/* 
    cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : "";
 */

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        carregarPaginaPerfilRespondedor(usu, sessao, form, rn);
        return 1;

    }

    // Carregar trabalho

    char* idTrabalho = NULL;
    if ( !(idTrabalho = obterCFHVal("idTrabalho", form, "identificador do trabalho", CHARDIG, &rn)) ) {
        printf("%s", idTrabalho);
        carregarPaginaTurmaPerfil(usu, sessao, form, rn);
        return 1;
    }

/* 
    cf = obterCampoFormularioHTML(form, "idTrabalho");
    char* idTrabalho = cf ? cf->valor : "";
     */

    Trabalho* trab = NULL;
    int numtrabs = 0;

    ret = bdBuscarTrabalhoId(idTrabalho, &trab, &numtrabs);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar trabalho da turma.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTurma(usu, sessao, form, rn);
        return 3;
    }

    // Carregar item de tarefa

    char* idItemTarefa = NULL;
    if ( !(idItemTarefa = obterCFHVal("idItemTarefa", form, "identificador di item de tarefa", CHARDIG, &rn)) ) {
        carregarPaginaTurmaPerfil(usu, sessao, form, rn);
        return 1;
    }

/* 
    cf = obterCampoFormularioHTML(form, "idItemTarefa");
    char* idItemTarefa = cf ? cf->valor : "";
 */

    ItemTarefa* item = NULL;
    int numItens = 0;

    ret = bdBuscarItensTarefaId(idItemTarefa, &item, &numItens);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar tarefa.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);
        return 3;
    }

    // Checar se existe resposta enviada anteriormente

    long long int idTrab = 0, idIT = 0, idPR = 0;

    sscanf(idTrabalho, "%lld", &idTrab);
    sscanf(idItemTarefa, "%lld", &idIT);
    sscanf(idPerfil, "%lld", &idPR);

    //char* camArqResp = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/resposta.pdf");

    char* statusEntrega = statusEntregaTarefaSubmissaoSimples(idTrab, idIT, idPR);

/* 
    int respenv = 0;

    if (!access(camArqResp, F_OK))
        respenv = 1;
 */

    if (*(item->tarefa->tipo) == BD_TT_SUBMISSAOSIMPLES) {
        return paginaExibirItemTarefaSubmissaoSimples(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, rn);
    }
    else if (*(item->tarefa->tipo) == BD_TT_CODIGOC) {


        // Carregar resposta submetida, caso haja

        char* resposta = NULL;
        char* feedback = NULL;

        if (tarefaEntregue(idTrab, idIT, idPR)) {

            FILE* f = NULL;

            char* caminho = caminhoArqResposta(idTrab, idIT, idPR);

            //printf("%s", caminho);

            
            
            if (!access(caminho, F_OK)) {
                struct stat st;
                stat(caminho, &st);
                size_t tam = st.st_size;

                if (tam) {
                    resposta = (char *) malloc((tam + 1) * sizeof(char));

                    if (f = fopen(caminho, "r")) {
                        fread(resposta, 1, tam,f);
                        fclose(f);
                    }

                    resposta[tam] = '\0';
		    subststr("\\n", "\\\\n", &(resposta));
                    subststr("\n", "\\n", &(resposta));
                    subststr("\"", "\\\"", &(resposta));
                }
            }
        }
        else {

            // carregar modelo

            FILE* f = NULL;

            char* caminho = dirAvaliacaoTarefa(*(item->tarefa->idTarefa));
            caminho = concatstr2(caminho, "/cabMod.c");

            if (!access(caminho, F_OK)) {
                struct stat st;
                stat(caminho, &st);
                size_t tam = st.st_size;

                if (tam) {
                    resposta = (char *) malloc((tam + 1) * sizeof(char));

                    if (f = fopen(caminho, "r")) {
                        fread(resposta, 1, tam,f);
                        fclose(f);
                    }

                    resposta[tam] = '\0';
		    subststr("\\n", "\\\\n", &(resposta));
                    subststr("\n", "\\n", &(resposta));
                    subststr("\"", "\\\"", &(resposta));
                }
            }

        }

        // carregar feedback, caso haja
        FILE* f = NULL;
        char* caminho = dirAreaDeTestesITPerfil(idTrab, idIT, idPR);
        caminho = concatstr2(caminho, "/feedback.htm");

        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            //if (tam) {
                feedback = (char *) malloc((tam + 1) * sizeof(char));

                if (f = fopen(caminho, "r")) {
                    fread(feedback, 1, tam,f);
                    fclose(f);
                }

                feedback[tam] = '\0';
            //}
        }


        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        * 
        *   Checar palavras reservadas
        * 
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        char* caminhoDadosIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);

        char caminhopalavrareservada[4097] = "";
        sprintf(caminhopalavrareservada, "%s/palres.txt", caminhoDadosIT);

        FILE* fpr = fopen(caminhopalavrareservada, "r");

        if (fpr) {
            int palavrares = 0;
            char palavraresmsg[5000] = "";

            fscanf(fpr, "%d", &palavrares);
            fgets(palavraresmsg, 5000, fpr);

            return paginaExibirItemTarefaCodigoC(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, palavrares, palavraresmsg,  0, -1, "", -1, "", -1, "", "", rn);
        }
        


        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        * 
        *   Checar resultado da rotina de avaliação
        * 
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


        // Indica se houve falha durante o processo de avaliação e qual foi a falha

        int falhaAval = 0;


        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        * 
        *   Checar se já houve envio
        * 
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        
        caminho = caminhoArqResposta(idTrab, idIT, idPR);

        if (access(caminho, F_OK)) {

            return paginaExibirItemTarefaCodigoC(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", falhaAval, -1, "", -1, "", -1, "", "", rn);
        }





        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        *   Checar resultado da compilação da resposta
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


        
        //printf("%s", caminho);
        int gccrespostaexit = 100;

        caminho = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/gccresposta.exit");
        
        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            //printf("xxxx");

            if (tam) {
                if (f = fopen(caminho, "r")) {
                    fscanf(f, "%d", &gccrespostaexit);
                    //printf("%d", gccrespostaexit);
                    fclose(f);
                }
                
            }
            else {
                // Compilação não retornou valor
                falhaAval = 1;
            }
        }
        else {
            // Compilação terminou inesperadamente ou não foi submetida tarefa
            //falhaAval = 2;
        }

        // carregar log da compilação da resposta

        caminho = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/gccresposta.log");
        //printf("%s", caminho);
        char* gccrespostalog = NULL;

        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            //if (tam) {
                gccrespostalog = (char *) malloc((tam + 1) * sizeof(char));

                if (f = fopen(caminho, "r")) {
                    fread(gccrespostalog, 1, tam,f);
                    fclose(f);
                }

                gccrespostalog[tam] = '\0';
            //}
        }

        if (gccrespostaexit && tarefaEntregue(idTrab, idIT, idPR)) {
            return paginaExibirItemTarefaCodigoC(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", falhaAval, gccrespostaexit, gccrespostalog, -1, "", -1, "", feedback, rn);
        }


        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        *   Checar resultado da compilação do código de execução de caso de teste
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        caminho = concatstr2(dirAreaDeTestesITPerfil(idTrab, idIT, idPR), "/gccexecCt.exit");
        int gccexecctexit = 100;
        
        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            if (tam) {
                if (f = fopen(caminho, "r")) {
                    fscanf(f, "%d", &gccexecctexit);
                    fclose(f);
                }
                
            }
            else {
                // Compilação não retornou valor
                falhaAval = 3;
            }
        }
        else {
            // Compilação terminou inesperadamente
            falhaAval = 4;
        }

        // carregar log da compilação da rotina de execução de caso de teste

        caminho = concatstr2(dirAreaDeTestesITPerfil(idTrab, idIT, idPR), "/gccexecCt.log");
        char* gccexecctlog = NULL;

        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            if (tam) {
                gccexecctlog = (char *) malloc((tam + 1) * sizeof(char));

                if (f = fopen(caminho, "r")) {
                    fread(gccexecctlog, 1, tam,f);
                    fclose(f);
                }

                gccexecctlog[tam] = '\0';
            }
        }

        if (falhaAval) {
            return paginaExibirItemTarefaCodigoC(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", falhaAval, gccrespostaexit, gccrespostalog, gccexecctexit, gccexecctlog, -1, "", feedback, rn);
        }


        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        *   Checar resultado da compilação do código de avaliação de caso de teste
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        // Checar resultado da compilação

        caminho = concatstr2(dirAreaDeTestesITPerfil(idTrab, idIT, idPR), "/gccexecAval.exit");
        int gccexecavalexit = 0;
        
        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            if (tam) {
                if (f = fopen(caminho, "r")) {
                    fscanf(f, "%d", &gccexecavalexit);
                    fclose(f);
                }
                
            }
            else {
                // Compilação não retornou valor
                falhaAval = 5;
            }
        }
        else {
            // Compilação terminou inesperadamente
            falhaAval = 6;
        }

        // carregar log da compilação da rotina de avaliação

        caminho = concatstr2(dirAreaDeTestesITPerfil(idTrab, idIT, idPR), "/gccexecAval.log");
        char* gccexecavallog = NULL;

        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            if (tam) {
                gccexecavallog = (char *) malloc((tam + 1) * sizeof(char));

                if (f = fopen(caminho, "r")) {
                    fread(gccexecavallog, 1, tam,f);
                    fclose(f);
                }

                gccexecavallog[tam] = '\0';
            }
        }


        //if (falhaAval) {
            return paginaExibirItemTarefaCodigoC(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", falhaAval, gccrespostaexit, gccrespostalog, gccexecctexit, gccexecctlog, gccexecavalexit, gccexecavallog, feedback, rn);
        //}
        
    }


    else if (*(item->tarefa->tipo) == BD_TT_CODIGOCSTDIN) {


        // Carregar resposta submetida, caso haja

        char* resposta = NULL;
        char* feedback = NULL;

        if (tarefaEntregue(idTrab, idIT, idPR)) {

            FILE* f = NULL;

            char* caminho = caminhoArqResposta(idTrab, idIT, idPR);

            //printf("%s", caminho);

            
            
            if (!access(caminho, F_OK)) {
                struct stat st;
                stat(caminho, &st);
                size_t tam = st.st_size;

                if (tam) {
                    resposta = (char *) malloc((tam + 1) * sizeof(char));

                    if (f = fopen(caminho, "r")) {
                        fread(resposta, 1, tam,f);
                        fclose(f);
                    }

                    resposta[tam] = '\0';
		    subststr("\\n", "\\\\n", &(resposta));
                    subststr("\n", "\\n", &(resposta));
                    subststr("\"", "\\\"", &(resposta));
                }
            }
        }
        else {

            // carregar modelo

            FILE* f = NULL;

            char* caminho = dirAvaliacaoTarefa(*(item->tarefa->idTarefa));
            caminho = concatstr2(caminho, "/cabMod.c");

            if (!access(caminho, F_OK)) {
                struct stat st;
                stat(caminho, &st);
                size_t tam = st.st_size;

                if (tam) {
                    resposta = (char *) malloc((tam + 1) * sizeof(char));

                    if (f = fopen(caminho, "r")) {
                        fread(resposta, 1, tam,f);
                        fclose(f);
                    }

                    resposta[tam] = '\0';
		    subststr("\\n", "\\\\n", &(resposta));
                    subststr("\n", "\\n", &(resposta));
                    subststr("\"", "\\\"", &(resposta));
                }
            }

        }

        // carregar feedback, caso haja
        FILE* f = NULL;
	char* caminho = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);
        caminho = concatstr2(caminho, "/exec.log");

        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            //if (tam) {
                feedback = (char *) malloc((tam + 1) * sizeof(char));

                if (f = fopen(caminho, "r")) {
                    fread(feedback, 1, tam,f);
                    fclose(f);
                }

                feedback[tam] = '\0';
            //}
        }


        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        * 
        *   Checar palavras reservadas
        * 
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        char* caminhoDadosIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);

        char caminhopalavrareservada[4097] = "";
        sprintf(caminhopalavrareservada, "%s/palres.txt", caminhoDadosIT);

        FILE* fpr = fopen(caminhopalavrareservada, "r");

        if (fpr) {
            int palavrares = 0;
            char palavraresmsg[5000] = "";

            fscanf(fpr, "%d", &palavrares);
            fgets(palavraresmsg, 5000, fpr);

            return paginaExibirItemTarefaCodigoCSTDIN(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, palavrares, palavraresmsg,  0, -1, "", -1, "", -1, "", "", rn);
        }
        

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        * 
        *   Checar se já houve envio
        * 
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        
        caminho = caminhoArqResposta(idTrab, idIT, idPR);

        if (access(caminho, F_OK)) {

            return paginaExibirItemTarefaCodigoCSTDIN(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", 0, -1, "", -1, "", -1, "", "", rn);
        }





        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        * 
        *   Checar resultado da compilação da resposta
        * 
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


        
        //printf("%s", caminho);
        int gccrespostaexit = 100;

        caminho = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/gccresposta.exit");
        
        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            //printf("xxxx");

            if (tam) {
                if (f = fopen(caminho, "r")) {
                    fscanf(f, "%d", &gccrespostaexit);
                    //printf("%d", gccrespostaexit);
                    fclose(f);
                }
                
            }
            else {
                // Compilação não retornou valor
                //falhaAval = 1;
            }
        }
        else {
            // Compilação terminou inesperadamente ou não foi submetida tarefa
            //falhaAval = 2;
        }

        // carregar log da compilação da resposta

        caminho = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/gccresposta.log");
        //printf("%s", caminho);
        char* gccrespostalog = NULL;

        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            //if (tam) {
                gccrespostalog = (char *) malloc((tam + 1) * sizeof(char));

                if (f = fopen(caminho, "r")) {
                    fread(gccrespostalog, 1, tam,f);
                    fclose(f);
                }

                gccrespostalog[tam] = '\0';
            //}
        }

        if (gccrespostaexit && tarefaEntregue(idTrab, idIT, idPR)) {
            return paginaExibirItemTarefaCodigoCSTDIN(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", 0, gccrespostaexit, gccrespostalog, -1, "", -1, "", feedback, rn);
        }



        //if (falhaAval) {
            return paginaExibirItemTarefaCodigoCSTDIN(usu, sessao, form, idPerfil, turma, trab, item, statusEntrega, resposta, 0, "", 0, gccrespostaexit, gccrespostalog, 0, "", 0, "", feedback, rn);
        //}
        
    }

    return 0;

}


int salvarRespostaItemTarefa(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

    RegNoti* rn = NULL;

    char* idPerfil = NULL;
    if ( !(idPerfil = obterCFHVal("idPerfilRespondedor", form, "identificador do perfil de respondedor", CHARDIG, &rn)) ) {
        paginaPapeis(usu, sessao);
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
    if ( !(idTurma = obterCFHVal("idTurma", form, "identificador da turma", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }
    
    /* cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : ""; */

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        carregarPaginaPerfilRespondedor(usu, sessao, form, rn);
        return 1;

    }

    // Carregar trabalho

    char* idTrabalho = NULL;
    if ( !(idTrabalho = obterCFHVal("idTrabalho", form, "identificador do traballho.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
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
        carregarPaginaTurma(usu, sessao, form, rn);
        return 3;
    }

    // Carregar item de tarefa

    char* idItemTarefa = NULL;
    if ( !(idItemTarefa = obterCFHVal("idItemTarefa", form, "identificador do item de tarefa.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }

    /* cf = obterCampoFormularioHTML(form, "idItemTarefa");
    char* idItemTarefa = cf ? cf->valor : ""; */

    ItemTarefa* item = NULL;
    int numItens = 0;

    ret = bdBuscarItensTarefaId(idItemTarefa, &item, &numItens);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar tarefa.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);
        return 3;
    }

    // checar se diretório do perfil para a este item de tarefa já existe

    long long int idTrab = 0, idIT = 0, idPR = 0;

    sscanf(idTrabalho, "%lld", &idTrab);
    sscanf(idItemTarefa, "%lld", &idIT);
    sscanf(idPerfil, "%lld", &idPR);

    char* dirDPIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);

    if (dirDPIT == NULL) {

        // erro ao tentar construir caminho do diretório do perfil no item de tarefa

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar construir caminho do diretório do perfil.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 4;

    }

    if (access(dirDPIT, F_OK)) {

        printf("%s", dirDPIT);

        // diretório não existe

        ret = dirCriarDirDadosPerfilItemTarefa(idTrab, idIT, idPR);

        if (ret) {

            // erro ao tentar criar diretório do perfil no item de tarefa

            RegNoti* rn = criarRegNoti(1, "Erro ao tentar criar diretório do perfil.");

            carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

            return 5;
        }
    }

    // A partir deste ponto o diretório do perfil já existe

    CampoFormularioHTML* cfResposta = obterCampoFormularioHTML(form, "resposta");

    if (cfResposta == NULL) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar resposta do formulário.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 6;
    }

    if (cfResposta->nomeArquivo == NULL) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Campo do formulário não é arquivo.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 7;
    }

    if (!strcmp(cfResposta->nomeArquivo, "")) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Não foi selecionado arquivo de resposta.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 8;
    }

    // Checa arquivo vazio

    if (cfResposta->conteudoArquivo->fim < cfResposta->conteudoArquivo->ini) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Problema com o arquivo de enunciado. Não há dados associado ao arquivo.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 8;

    }

    size_t tamArq = cfResposta->conteudoArquivo->fim - cfResposta->conteudoArquivo->ini + 1;

    // obtem extensão do arquivo

    char* nomeArq = NULL;
   
    if (strstr(cfResposta->nomeArquivo, ".txt")) {nomeArq = "resposta.txt"; }
    else if (strstr(cfResposta->nomeArquivo, ".pdf")) {nomeArq = "resposta.pdf"; }
    else if (strstr(cfResposta->nomeArquivo, ".png")) {nomeArq = "resposta.png"; }
    else if (strstr(cfResposta->nomeArquivo, ".jpg")) {nomeArq = "resposta.jpg"; }
    else if (strstr(cfResposta->nomeArquivo, ".gif")) {nomeArq = "resposta.gif"; }


    char* caminhoarquivo = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), concatstr2("/", nomeArq));

    FILE* f = fopen(caminhoarquivo, "wb");

    if (f) {

        size_t salvos = fwrite(cfResposta->conteudoArquivo->ini, tamArq, 1, f);


        if (salvos * tamArq != tamArq) {

            // não foram salvos todos os bytes recebidos

            fclose(f);

            // remover diretório do perfil no item de tarefa

             RegNoti* rn = criarRegNoti(1, "Não foi possível salvar corretamente o arquivo de resposta no disco.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 9;

        }
        else {

            // Arquivo de resposta salvo com sucesso

            fclose(f);


            /*
             *  Criar .png
             *
             *
             */

            char* dirDadosResp = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);
            char* dirDownloadsResp = dirDownloadsPerfilItemTarefa(idTrab, idIT, idPR);

            char comando[1000] = "";

            sprintf(comando, "convert -density 300 -quality 20 -background white -alpha remove -alpha off %s/resposta.pdf %s/resposta.png", dirDadosResp, dirDownloadsResp);

            //printf("%s", comando);

            system(comando);

            RegNoti* rn = criarRegNoti(0, "Tarefa enviada com sucesso.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 0;

        }

    }
    else {


        RegNoti* rn = criarRegNoti(1, "Não foi possível salvar arquivo no disco.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 9;

    }

}


int salvarRespostaItemTarefaCodigoC(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

    RegNoti* rn = NULL;

    char* idPerfil = NULL;
    if ( !(idPerfil = obterCFHVal("idPerfilRespondedor", form, "identificador do perfil de respondedor", CHARDIG, &rn)) ) {
        paginaPapeis(usu, sessao);
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
    if ( !(idTurma = obterCFHVal("idTurma", form, "identificador da turma", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }
    
    /* cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : ""; */

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        carregarPaginaPerfilRespondedor(usu, sessao, form, rn);
        return 1;

    }

    // Carregar trabalho

    char* idTrabalho = NULL;
    if ( !(idTrabalho = obterCFHVal("idTrabalho", form, "identificador do traballho.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
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
        carregarPaginaTurma(usu, sessao, form, rn);
        return 3;
    }

    // Carregar item de tarefa

    char* idItemTarefa = NULL;
    if ( !(idItemTarefa = obterCFHVal("idItemTarefa", form, "identificador do item de tarefa.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }

    /* cf = obterCampoFormularioHTML(form, "idItemTarefa");
    char* idItemTarefa = cf ? cf->valor : ""; */

    ItemTarefa* item = NULL;
    int numItens = 0;

    ret = bdBuscarItensTarefaId(idItemTarefa, &item, &numItens);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar tarefa.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);
        return 3;
    }

    // checar se diretório do perfil para a este item de tarefa já existe

    long long int idTrab = 0, idIT = 0, idPR = 0;

    sscanf(idTrabalho, "%lld", &idTrab);
    sscanf(idItemTarefa, "%lld", &idIT);
    sscanf(idPerfil, "%lld", &idPR);

    char* dirDPIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);

    if (dirDPIT == NULL) {

        // erro ao tentar construir caminho do diretório do perfil no item de tarefa

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar construir caminho do diretório do perfil.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 4;

    }

    if (access(dirDPIT, F_OK)) {

        //printf("%s", dirDPIT);

        // diretório não existe

        ret = dirCriarDirDadosPerfilItemTarefa(idTrab, idIT, idPR);

        if (ret) {

            // erro ao tentar criar diretório do perfil no item de tarefa

            RegNoti* rn = criarRegNoti(1, "Erro ao tentar criar diretório do perfil.");

            carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

            return 5;
        }
    }

    // A partir deste ponto o diretório do perfil já existe

    CampoFormularioHTML* cfResposta = obterCampoFormularioHTML(form, "taResposta");

    if (cfResposta == NULL) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar resposta do formulário.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 6;
    }

    char* caminhoarquivo = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/resposta.c");

    FILE* f = fopen(caminhoarquivo, "w");

    if (f) {

        subststr("\r", "", &(cfResposta->valor));
        size_t salvos = fprintf(f, "%s", cfResposta->valor);

        if (salvos < 0) {

            // não foram salvos todos os bytes recebidos

            fclose(f);

            // remover diretório do perfil no item de tarefa

             RegNoti* rn = criarRegNoti(1, "Não foi possível salvar corretamente o arquivo de resposta no disco.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 9;

        }
        else {

            // Arquivo de resposta salvo com sucesso

            fclose(f);

            RegNoti* rn = criarRegNoti(0, "Tarefa enviada com sucesso.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 0;
        }

    }
    else {


        RegNoti* rn = criarRegNoti(1, "Não foi possível salvar arquivo no disco.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 9;

    }

}



int avaliarRespostaItemTarefaCodigoC(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Salvar Resposta
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    RegNoti* rn = NULL;

    char* idPerfil = NULL;
    if ( !(idPerfil = obterCFHVal("idPerfilRespondedor", form, "identificador do perfil de respondedor", CHARDIG, &rn)) ) {
        paginaPapeis(usu, sessao);
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
    if ( !(idTurma = obterCFHVal("idTurma", form, "identificador da turma", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }
    
    /* cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : ""; */

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        carregarPaginaPerfilRespondedor(usu, sessao, form, rn);
        return 1;

    }

    // Carregar trabalho

    char* idTrabalho = NULL;
    if ( !(idTrabalho = obterCFHVal("idTrabalho", form, "identificador do traballho.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
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
        carregarPaginaTurma(usu, sessao, form, rn);
        return 3;
    }

    // Carregar item de tarefa

    char* idItemTarefa = NULL;
    if ( !(idItemTarefa = obterCFHVal("idItemTarefa", form, "identificador do item de tarefa.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }

    /* cf = obterCampoFormularioHTML(form, "idItemTarefa");
    char* idItemTarefa = cf ? cf->valor : ""; */

    ItemTarefa* item = NULL;
    int numItens = 0;

    ret = bdBuscarItensTarefaId(idItemTarefa, &item, &numItens);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar tarefa.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);
        return 3;
    }

    // checar se diretório do perfil para a este item de tarefa já existe

    long long int idTrab = 0, idIT = 0, idPR = 0;

    sscanf(idTrabalho, "%lld", &idTrab);
    sscanf(idItemTarefa, "%lld", &idIT);
    sscanf(idPerfil, "%lld", &idPR);

    char* dirDPIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);

    if (dirDPIT == NULL) {

        // erro ao tentar construir caminho do diretório do perfil no item de tarefa

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar construir caminho do diretório do perfil.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 4;

    }

    if (access(dirDPIT, F_OK)) {

        //printf("%s", dirDPIT);

        // diretório não existe

        ret = dirCriarDirDadosPerfilItemTarefa(idTrab, idIT, idPR);

        if (ret) {

            // erro ao tentar criar diretório do perfil no item de tarefa

            RegNoti* rn = criarRegNoti(1, "Erro ao tentar criar diretório do perfil.");

            carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

            return 5;
        }
    }

    // A partir deste ponto o diretório do perfil já existe

    CampoFormularioHTML* cfResposta = obterCampoFormularioHTML(form, "taResposta");

    if (cfResposta == NULL) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar resposta do formulário.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 6;
    }

    char* caminhoarquivo = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/resposta.c");

    FILE* f = fopen(caminhoarquivo, "w");

    if (f) {

        subststr("\r", "", &(cfResposta->valor));
        size_t salvos = fprintf(f, "%s", cfResposta->valor);

        if (salvos < 0) {

            // não foram salvos todos os bytes recebidos

            fclose(f);

            // remover diretório do perfil no item de tarefa

             RegNoti* rn = criarRegNoti(1, "Não foi possível salvar corretamente o arquivo de resposta no disco.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 9;

        }
        else {

            // Arquivo de resposta salvo com sucesso

            fclose(f);

            RegNoti* rn = criarRegNoti(0, "Tarefa enviada com sucesso.");

            //carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            //return 0;
        }

    }
    else {


        RegNoti* rn = criarRegNoti(1, "Não foi possível salvar arquivo no disco.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 9;

    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Rotinas de avaliação
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


    // Indica se houve falha durante o processo de avaliação e qual foi a falha

    int falhaAval = 0;



    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Palavras reservadas
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    
    char* caminhoResposta = caminhoArqResposta(idTrab, idIT, idPR);
    char* caminhoDadosIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);


    Multilinhas* mlresp = mlCriar();
    mlCarregarArquivoTexto(caminhoResposta, mlresp);
    RegNoti* rnpr = NULL;
    palavrasReservadasCodigoC(mlresp, &rnpr);

    char caminhopalavrareservada[4097] = "";
    sprintf(caminhopalavrareservada, "%s/palres.txt", caminhoDadosIT);
    remove(caminhopalavrareservada);

    if (rnpr && rnpr->numnoti) {
        
        FILE* fpr = fopen(caminhopalavrareservada, "w");
        fprintf(fpr, "%d %s", rnpr->numnoti, rnpr->msg);
        fclose(fpr);
        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);
        return 0;
    }

        

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Compilar Resposta
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


    // Montar linha de compilação
    char cmd[25000] = "";

    
    char* caminhoAreaTestes = dirAreaDeTestesITPerfil(idTrab, idIT, idPR);
    char* caminhoCompilado = caminhoCompiladoResposta(idTrab, idIT, idPR);
    

    // Apagar arquivos de status da execução do gcc
    char caminhoGccRespostaLog[4097] = "";
    sprintf(caminhoGccRespostaLog, "%s/gccresposta.log", caminhoDadosIT);
    
    char caminhoGccRespostaExit[4097] = "";
    sprintf(caminhoGccRespostaExit, "%s/gccresposta.exit", caminhoDadosIT);
    
    remove(caminhoGccRespostaLog);
    remove(caminhoGccRespostaExit);
    remove(caminhoCompilado);

    // Montar comando de compilação
    //sprintf(cmd, "gcc %s -o %s -lm 1> %s/gccresposta.log 2>&1; echo $? > %s/gccresposta.exit", caminhoResposta, caminhoCompilado, caminhoDadosIT, caminhoDadosIT);
    //printf("%s", cmd);
    chdir(caminhoDadosIT);
    sprintf(cmd, "gcc resposta.c -o respcomp -lm 1> gccresposta.log 2>&1; echo $? > gccresposta.exit");
    //printf("%s", cmd);
    system(cmd);

    // Checar resultado da compilação

    char* caminho = concatstr2(caminhoAreaTestes, "/gccresposta.exit");
    int gccrespostaexit = 0;
    
    if (!access(caminho, F_OK)) {
        struct stat st;
        stat(caminho, &st);
        size_t tam = st.st_size;

        if (tam) {
            if (f = fopen(caminho, "r")) {
                fscanf(f, "%d", &gccrespostaexit);
                fclose(f);
            }
            
        }
        else {
            // Compilação não retornou valor
            falhaAval = 1;
        }
    }
    else {
        // Compilação terminou inesperadamente
        falhaAval = 2;
    }


    if (gccrespostaexit) {
        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);
        return 0;
    }
    



    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Preparar Execução de Caso de Teste
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // Obter número de casos de teste

    char* caminhoNcts = dirCaminhoNumCts(*(item->tarefa->idTarefa));

    f = fopen(caminhoNcts, "r");
    int ncts = 0;

    fscanf(f, "%d", &ncts);
    fclose(f);

    // Criar área de testes no diretório do perfil no item de tarefa

    dirEsvaziarAreaTestesITPerfil(idTrab, idIT, idPR);
    dirCriarDirAreaTestesITPerfil(idTrab, idIT, idPR, ncts);

    // Preparar resposta para executar caso de teste

    Multilinhas* respostaprep = mlCriar();
    mlCarregarArquivoTexto(caminhoResposta, respostaprep);
    prepRespostaParaAvaliacaoCodigoC(respostaprep);
    
    mlSalvarArquivoTexto(dirCaminhoRespostaPrepITPerfil(idTrab, idIT, idPR), respostaprep);

    // Copiar e compilar código de execução do caso de teste

    char* caminhoModeloExecCt = dirCaminhoModeloCExecCt();
    char* diraval = dirAvaliacaoTarefa(*(item->tarefa->idTarefa));
    

    sprintf(cmd, "cp %s/cab.c %s/", diraval, caminhoAreaTestes);
    //printf("%s", cmd);
    system(cmd);
    sprintf(cmd, "cp %s/carregarCt.c %s/", diraval, caminhoAreaTestes);
    system(cmd);
    sprintf(cmd, "cp %s/salvarSaida.c %s/", diraval, caminhoAreaTestes);
    system(cmd);
    //printf("%s", cmd);

    sprintf(cmd, "cp %s %s/", caminhoModeloExecCt, caminhoAreaTestes);

    system(cmd);

    //char* caminhoExecCtPR = concatstr2(caminhoAreaTestes, "/execCt.c");
    //char* caminhoExecCtPRComp = concatstr2(caminhoAreaTestes, "/execCt");

    char* caminhoGccExecCtExit = concatstr2(caminhoAreaTestes, "/gccexecCt.exit");
    char* caminhoGccExecCtLog = concatstr2(caminhoAreaTestes, "/gccexecCt.log");

    remove(caminhoGccExecCtExit);
    remove(caminhoGccExecCtLog);

    sprintf(cmd, "gcc %s/execCt.c -o %s/execCt -lm 1> %s/gccexecCt.log 2>&1; echo $? > %s/gccexecCt.exit", caminhoAreaTestes, caminhoAreaTestes, caminhoAreaTestes, caminhoAreaTestes);
    //printf("%s", cmd);

    system(cmd);

    // Checar resultado da compilação

    caminho = concatstr2(caminhoAreaTestes, "/gccexecCt.exit");
    int gccexecctexit = 100;
    
    if (!access(caminho, F_OK)) {
        struct stat st;
        stat(caminho, &st);
        size_t tam = st.st_size;

        if (tam) {
            if (f = fopen(caminho, "r")) {
                fscanf(f, "%d", &gccexecctexit);
                fclose(f);
            }
            
        }
        else {
            // Compilação não retornou valor
            falhaAval = 3;
        }
    }
    else {
        // Compilação terminou inesperadamente
        falhaAval = 4;
    }


    if (gccexecctexit) {
        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);
        return 0;
    }


    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Executar bateria de testes
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // Montar linha para execução de caso de teste

    int ct = 1;

    for (ct = 1; ct <= ncts; ct++) {
        //char* diraval = dirAvaliacaoTarefa(*(item->tarefa->idTarefa));
        char dirct[4097] = "";
        sprintf(dirct, "%s/%d", dirAvaliacaoTarefa(*(item->tarefa->idTarefa)), ct);


        //printf("%s", dirct);

        char dirctresp[4097] = "";
        sprintf(dirctresp, "%s/%d", caminhoAreaTestes, ct);

        //printf("------%s", dirctresp);

        /* -------------
        sprintf(cmd, "%s/execCt %d %s %s 1>%s/execCt.log 2>&1; echo $? > %s/execCt.exit", caminhoAreaTestes, ct, dirct, dirctresp, dirctresp, dirctresp);
        */
        
        //sprintf(cmd, "timeout -v 2s bash -c \'ulimit -v 20000; ulimit -f 248; %s/execCt %d %s %s 1> %s/execCtStdout.log 2> %s/execCtStderr.log\' 1> %s/timeout.log 2>&1; echo $? > %s/timeout.exit", caminhoAreaTestes, ct, dirct, dirctresp, dirctresp, dirctresp, dirctresp, dirctresp);
        sprintf(cmd, "timeout -v 2s bash -c \'ulimit -v 20000; ulimit -f 248; %s/execCt %d %s %s 1> %s/execCt.log 2>&1\' 1> %s/timeout.log 2>&1; echo $? > %s/timeout.exit", caminhoAreaTestes, ct, dirct, dirctresp, dirctresp, dirctresp, dirctresp);

        
        //printf("%s", cmd);
        system(cmd);


        caminho = concatstr2(caminhoAreaTestes, "/%d/saida.txt");
        
        if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;

            if (tam) {
                if (f = fopen(caminho, "r")) {
                    fscanf(f, "%d", &gccexecctexit);
                    fclose(f);
                }
                
            }
            else {
                // Execução de caso de teste não gerou saida
                // Sair do laço
                falhaAval = 5;
            }
        }
        else {
            // Execução de caso de teste terminou inesperadamente
            // Sair do laço
            falhaAval = 6;
        }



    }



    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Avaliar resultado dos testes
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // copiar e compilar código de avaliação
    sprintf(cmd, "cp %s/avalEstat.c %s/", diraval, caminhoAreaTestes);
    //printf("%s", cmd);
    system(cmd);

    char* caminhoModeloExecAval = dirCaminhoModeloCExecAval();
    //printf("-----%s-----", caminhoModeloExecAval);
    sprintf(cmd, "cp %s %s/", caminhoModeloExecAval, caminhoAreaTestes);
    system(cmd);
    sprintf(cmd, "gcc %s/execAval.c -o %s/execAval -lm 1> %s/gccexecAval.log 2>&1; echo $? > %s/gccexecAval.exit", caminhoAreaTestes, caminhoAreaTestes, caminhoAreaTestes, caminhoAreaTestes);
    //printf("%s", cmd);
    system(cmd);


    // Checar resultado da compilação

    caminho = concatstr2(caminhoAreaTestes, "/gccexecCt.exit");
    int gccexecavalexit = 100;
    
    if (!access(caminho, F_OK)) {
        struct stat st;
        stat(caminho, &st);
        size_t tam = st.st_size;

        if (tam) {
            if (f = fopen(caminho, "r")) {
                fscanf(f, "%d", &gccexecctexit);
                fclose(f);
            }
            
        }
        else {
            // Compilação não retornou valor
            falhaAval = 3;
        }
    }
    else {
        // Compilação terminou inesperadamente
        falhaAval = 4;
    }




    for (int ct = 1; ct <= ncts; ct++) {

		// avaliar cada caso de teste
		char dirct[4097] = "";
		char dirctresp[4097] = "";

		sprintf(dirct, "%s/%d", dirAvaliacaoTarefa(*(item->tarefa->idTarefa)), ct);
		sprintf(dirctresp, "%s/%d", caminhoAreaTestes, ct);


        sprintf(cmd, "%s/execAval %d %s %s", caminhoAreaTestes, ct, dirct, dirctresp);
        //printf("%s", cmd);
        system(cmd);

    }



    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Gerar Feedback
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    sprintf(cmd, "cp %s/feedback.c %s/", diraval, caminhoAreaTestes);
    system(cmd);
    char* caminhoModeloExecFeedback = dirCaminhoModeloCExecFeedback();
    //printf("-----%s-----", caminhoModeloExecAval);
    sprintf(cmd, "cp %s %s/", caminhoModeloExecFeedback, caminhoAreaTestes);
    //printf("%s", cmd);
    system(cmd);
    sprintf(cmd, "gcc %s/execFeedback.c -o %s/execFeedback -lm 1> %s/gccexecFeedback.log 2>&1; echo $? > %s/gccexecFeedback.exit", caminhoAreaTestes, caminhoAreaTestes, caminhoAreaTestes, caminhoAreaTestes);
    //printf("%s", cmd);
    system(cmd);
    sprintf(cmd, "%s/execFeedback %d %s %s", caminhoAreaTestes, ncts, dirAvaliacaoTarefa(*(item->tarefa->idTarefa)), caminhoAreaTestes);
    system(cmd);
    //printf("%s", cmd);

    carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

    return 0;

}



int executarRespostaItemTarefaCodigoCSTDIN(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Salvar Resposta
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    RegNoti* rn = NULL;

    char* idPerfil = NULL;
    if ( !(idPerfil = obterCFHVal("idPerfilRespondedor", form, "identificador do perfil de respondedor", CHARDIG, &rn)) ) {
        paginaPapeis(usu, sessao);
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
    if ( !(idTurma = obterCFHVal("idTurma", form, "identificador da turma", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }
    
    /* cf = obterCampoFormularioHTML(form, "idTurma");
    char* idTurma = cf ? cf->valor : ""; */

    // Carregar turma

    Turma* turma = NULL;

    int ret = bdBuscarTurmaId2(idTurma, &turma);

    if (ret) {

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar turma.");

        carregarPaginaPerfilRespondedor(usu, sessao, form, rn);
        return 1;

    }

    // Carregar trabalho

    char* idTrabalho = NULL;
    if ( !(idTrabalho = obterCFHVal("idTrabalho", form, "identificador do traballho.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
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
        carregarPaginaTurma(usu, sessao, form, rn);
        return 3;
    }

    // Carregar item de tarefa

    char* idItemTarefa = NULL;
    if ( !(idItemTarefa = obterCFHVal("idItemTarefa", form, "identificador do item de tarefa.", CHARDIG, &rn)) ) {
        minhasTurmas(usu, sessao, form, rn);
        return 1;
    }

    /* cf = obterCampoFormularioHTML(form, "idItemTarefa");
    char* idItemTarefa = cf ? cf->valor : ""; */

    ItemTarefa* item = NULL;
    int numItens = 0;

    ret = bdBuscarItensTarefaId(idItemTarefa, &item, &numItens);

    if (ret) {
        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar tarefa.");

        //minhasTurmas(usu, sessao, form, rn);
        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);
        return 3;
    }

    // checar se diretório do perfil para a este item de tarefa já existe

    long long int idTrab = 0, idIT = 0, idPR = 0;

    sscanf(idTrabalho, "%lld", &idTrab);
    sscanf(idItemTarefa, "%lld", &idIT);
    sscanf(idPerfil, "%lld", &idPR);

    char* dirDPIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);

    if (dirDPIT == NULL) {

        // erro ao tentar construir caminho do diretório do perfil no item de tarefa

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar construir caminho do diretório do perfil.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 4;

    }

    if (access(dirDPIT, F_OK)) {

        //printf("%s", dirDPIT);

        // diretório não existe

        ret = dirCriarDirDadosPerfilItemTarefa(idTrab, idIT, idPR);

        if (ret) {

            // erro ao tentar criar diretório do perfil no item de tarefa

            RegNoti* rn = criarRegNoti(1, "Erro ao tentar criar diretório do perfil.");

            carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

            return 5;
        }
    }

    // A partir deste ponto o diretório do perfil já existe

    CampoFormularioHTML* cfResposta = obterCampoFormularioHTML(form, "taResposta");

    if (cfResposta == NULL) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar resposta do formulário.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 6;
    }

    char* caminhoarquivo = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/resposta.c");

    FILE* f = fopen(caminhoarquivo, "w");

    if (f) {

        subststr("\r", "", &(cfResposta->valor));
        size_t salvos = fprintf(f, "%s", cfResposta->valor);

        if (salvos < 0) {

            // não foram salvos todos os bytes recebidos

            fclose(f);

            // remover diretório do perfil no item de tarefa

             RegNoti* rn = criarRegNoti(1, "Não foi possível salvar corretamente o arquivo de resposta no disco.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 9;

        }
        else {

            // Arquivo de resposta salvo com sucesso

            fclose(f);

            RegNoti* rn = criarRegNoti(0, "Tarefa enviada com sucesso.");

            //carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            //return 0;
        }

    }
    else {


        RegNoti* rn = criarRegNoti(1, "Não foi possível salvar arquivo no disco.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 9;

    }
    
    // A partir deste ponto o diretório do perfil já existe

    CampoFormularioHTML* cfStdin = obterCampoFormularioHTML(form, "taStdin");

    if (cfStdin == NULL) {

        // Erro ao tentar resgatar campo do formulário

        RegNoti* rn = criarRegNoti(1, "Erro ao tentar resgatar stdin do formulário.");

        carregarPaginaTrabalhoPerfil(usu, sessao, form, rn);

        return 6;
    }

    caminhoarquivo = concatstr2(dirDadosPerfilItemTarefa(idTrab, idIT, idPR), "/stdin.txt");

    f = fopen(caminhoarquivo, "w");

    if (f) {

        subststr("\r", "", &(cfStdin->valor));
        size_t salvos = fprintf(f, "%s", cfStdin->valor);

        if (salvos < 0) {

            // não foram salvos todos os bytes recebidos

            fclose(f);

            // remover diretório do perfil no item de tarefa

             RegNoti* rn = criarRegNoti(1, "Não foi possível salvar corretamente o arquivo stdin.txt no disco.");

            carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            return 9;

        }
        else {

            // Arquivo de resposta salvo com sucesso

            fclose(f);

            RegNoti* rn = criarRegNoti(0, "Tarefa enviada com sucesso.");

            //carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

            //return 0;
        }

    }
    else {


        RegNoti* rn = criarRegNoti(1, "Não foi possível salvar arquivo no disco.");

        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

        return 9;

    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Rotinas de avaliação
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


    // Indica se houve falha durante o processo de avaliação e qual foi a falha

    int falhaAval = 0;



    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Palavras reservadas
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    
    char* caminhoResposta = caminhoArqResposta(idTrab, idIT, idPR);
    char* caminhoDadosIT = dirDadosPerfilItemTarefa(idTrab, idIT, idPR);


    Multilinhas* mlresp = mlCriar();
    mlCarregarArquivoTexto(caminhoResposta, mlresp);
    RegNoti* rnpr = NULL;
    palavrasReservadasCodigoC(mlresp, &rnpr);

    char caminhopalavrareservada[4097] = "";
    sprintf(caminhopalavrareservada, "%s/palres.txt", caminhoDadosIT);
    remove(caminhopalavrareservada);

    if (rnpr && rnpr->numnoti) {
        
        FILE* fpr = fopen(caminhopalavrareservada, "w");
        fprintf(fpr, "%d %s", rnpr->numnoti, rnpr->msg);
        fclose(fpr);
        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);
        return 0;
    }

        

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Compilar Resposta
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


    // Montar linha de compilação
    char cmd[25000] = "";

    
    char* caminhoAreaTestes = dirAreaDeTestesITPerfil(idTrab, idIT, idPR);
    char* caminhoCompilado = caminhoCompiladoResposta(idTrab, idIT, idPR);
    

    // Apagar arquivos de status da execução do gcc
    char caminhoGccRespostaLog[4097] = "";
    sprintf(caminhoGccRespostaLog, "%s/gccresposta.log", caminhoDadosIT);
    
    char caminhoGccRespostaExit[4097] = "";
    sprintf(caminhoGccRespostaExit, "%s/gccresposta.exit", caminhoDadosIT);
    
    remove(caminhoGccRespostaLog);
    remove(caminhoGccRespostaExit);
    remove(caminhoCompilado);

    // Montar comando de compilação
    //sprintf(cmd, "gcc %s -o %s -lm 1> %s/gccresposta.log 2>&1; echo $? > %s/gccresposta.exit", caminhoResposta, caminhoCompilado, caminhoDadosIT, caminhoDadosIT);
    //printf("%s", cmd);
    chdir(caminhoDadosIT);
    sprintf(cmd, "gcc resposta.c -o respcomp -lm 1> gccresposta.log 2>&1; echo $? > gccresposta.exit");
    //printf("%s", cmd);
    system(cmd);

    // Checar resultado da compilação

    char* caminho = concatstr2(caminhoAreaTestes, "/gccresposta.exit");
    int gccrespostaexit = 0;
    
    if (!access(caminho, F_OK)) {
        struct stat st;
        stat(caminho, &st);
        size_t tam = st.st_size;

        if (tam) {
            if (f = fopen(caminho, "r")) {
                fscanf(f, "%d", &gccrespostaexit);
                fclose(f);
            }
            
        }
        else {
            // Compilação não retornou valor
            falhaAval = 1;
        }
    }
    else {
        // Compilação terminou inesperadamente
        falhaAval = 2;
    }


    if (gccrespostaexit) {
        carregarPaginaExibirItemTarefa(usu, sessao, form, rn);
        return 0;
    }
    

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * 
    *   Executar bateria de testes
    * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // Montar linha para execução de caso de teste

    //int ct = 1;

    //for (ct = 1; ct <= ncts; ct++) {
        //char* diraval = dirAvaliacaoTarefa(*(item->tarefa->idTarefa));
        //char dirct[4097] = "";
        //sprintf(dirct, "%s/%d", dirAvaliacaoTarefa(*(item->tarefa->idTarefa)), ct);


        //printf("%s", dirct);

        //char dirctresp[4097] = "";
        //sprintf(dirctresp, "%s/%d", caminhoAreaTestes, ct);

        //printf("------%s", dirctresp);

        /* -------------
        sprintf(cmd, "%s/execCt %d %s %s 1>%s/execCt.log 2>&1; echo $? > %s/execCt.exit", caminhoAreaTestes, ct, dirct, dirctresp, dirctresp, dirctresp);
        */
        
        //sprintf(cmd, "timeout -v 2s bash -c \'ulimit -v 20000; ulimit -f 248; %s/execCt %d %s %s 1> %s/execCtStdout.log 2> %s/execCtStderr.log\' 1> %s/timeout.log 2>&1; echo $? > %s/timeout.exit", caminhoAreaTestes, ct, dirct, dirctresp, dirctresp, dirctresp, dirctresp, dirctresp);
        sprintf(cmd, "timeout -v 2s bash -c \'ulimit -v 20000; ulimit -f 248; %s < %s/stdin.txt 1> %s/exec.log 2>&1\' 1> %s/timeout.log 2>&1; echo $? > %s/timeout.exit", caminhoCompilado, caminhoDadosIT, caminhoDadosIT, caminhoDadosIT, caminhoDadosIT);

        
        //printf("%s", cmd);
        system(cmd);


        //caminho = concatstr2(caminhoAreaTestes, "/%d/saida.txt");
        //
        //if (!access(caminho, F_OK)) {
        //    struct stat st;
        //    stat(caminho, &st);
        //  size_t tam = st.st_size;

        //  if (tam) {
        //      if (f = fopen(caminho, "r")) {
        //          fscanf(f, "%d", &gccexecctexit);
        //          fclose(f);
        //      }
        //      
        //  }
        //  else {
        //      // Execução de caso de teste não gerou saida
        //      // Sair do laço
        //      falhaAval = 5;
        //  }
        //}
        //else {
        //    // Execução de caso de teste terminou inesperadamente
        //    // Sair do laço
        //     falhaAval = 6;
        //}



    //}


    carregarPaginaExibirItemTarefa(usu, sessao, form, rn);

    return 0;

}


char* caminhoCompiladoResposta(long long int idTrabalho, long long int idItemTarefa, long long int idPerfilRepondedor) {

    char* dirResp = dirDadosPerfilItemTarefa(idTrabalho, idItemTarefa, idPerfilRepondedor);

    char* caminho = concatstr2(dirResp, "/respcomp");

    return caminho;
}








