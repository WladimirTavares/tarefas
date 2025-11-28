#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// Para organizar a contrução do feedback, declare aqui as variáveis globais
// contendo a entrada do problema, o gabarito e a saida

// variáveis contendo a entrada
int N;
char L[400];

// variáveis contendo o gabarito
int gabmaior;

// variáveis contendo a saída (caso a saída seja alguma variável de entrada modificada, escolha um nome de variável diferente)
int maior;

// variável(eis) contendo o resultado da avaliação
int resultado;

// variável contendo o stdout da resposta
char* terminal;

// carrega os dados

int carregarEntrada(char* dirct);
int carregarGabarito(char* dirct);
int carregarSaida(char* dirctresp);
int carregarResultado(char* dirctresp);
int carregarTerminal(char* dirctresp);



// funções que geram o código html de feedback sobre o resultado da avaliação do caso de teste

// gera os estilos css usados no html de feedback
char* htmlEstilo();

char* htmlEntrada();
char* htmlGabarito();
char* htmlSaida();
char* htmlResultado();
char* htmlTerminal();       // stdout da resposta

// gera o html de cada caso de teste
char* htmlCasoTeste();

/* * * * * * * * * * * * * * * * * * * * * * * * *
 * função principal que gera o html do feedback
 * * * * * * * * * * * * * * * * * * * * * * * * */

char* htmlFeedBack(int ncts, char* supdirct, char* supdirctresp) {

    // gera código html exibir as informações sobre o caso de teste
    // que você quiser (entrada, gabarito, saída, resultado da avaliação, ...)

    size_t tam = 0;
    char* html = (char *) malloc((tam + 1) * sizeof(char));
    html[0] = '\0';
    
    char linha[4000] = "";

    char dirct[4097] = "";
    char dirctresp[4097] = "";

    for (int i = 1; i <= ncts; i++) {

        // montar caminho dos diretórios de caso de teste
        sprintf(dirct, "%s/%d", supdirct, i);
        sprintf(dirctresp, "%s/%d", supdirctresp, i);

        // carregar dados do caso de teste
        carregarEntrada(dirct);
        carregarGabarito(dirct);
        carregarSaida(dirctresp);
        carregarResultado(dirctresp);
        carregarTerminal(dirctresp);

        // gerar html do caso de teste
        char* htmlct = htmlCasoTeste();

        // concatenar html do caso de teste
        tam = tam + strlen(htmlct);
        html = (char *) realloc(html, (tam + 1) * sizeof(char));
        strcat(html, htmlct);

        // se houver erro, encerra a construção do feedback
        if (resultado != 1) {
            break;
        }

    }

    return html;
}

int carregarEntrada(char* dirct) {

    char caminho[4097];
    sprintf(caminho, "%s/entrada.txt", dirct);
    FILE* fe = fopen(caminho, "r");

    fscanf(fe, "%d", &N);
    fgets(L, 400, fe);

    fclose(fe);
}

int carregarGabarito(char* dirct) {

    char caminho[4097];
    sprintf(caminho, "%s/gabarito.txt", dirct);
    FILE* fg = fopen(caminho, "r");

    fscanf(fg, "%d", &gabmaior);

    fclose(fg);
}

int carregarSaida(char* dirctresp) {

    char caminho[4097];
    sprintf(caminho, "%s/saida.txt", dirctresp);
    FILE* fs = fopen(caminho, "r");

    fscanf(fs, "%d", &maior);

    fclose(fs);
}

int carregarResultado(char* dirctresp) {

    char caminho[4097];
    sprintf(caminho, "%s/avalct.txt", dirctresp);
    FILE* fa = fopen(caminho, "r");

    fscanf(fa, "%d", &resultado);

    fclose(fa);
}

int carregarTerminal(char* dirctresp) {

    char caminho[4097];
    FILE* fterm = NULL;

    sprintf(caminho, "%s/execCt.log", dirctresp);

    if (!access(caminho, F_OK)) {   // foi gerado arquivo de log
        struct stat st;
        stat(caminho, &st);
        size_t tam = st.st_size;

        if (tam) {  // arquivo de log tem informação
            terminal = (char *) malloc((tam + 1) * sizeof(char));
            if (fterm = fopen(caminho, "r")) {  // arquivo de log aberto com sucesso
                fread(terminal, 1, tam, fterm);
                terminal[tam] = '\0';
                fclose(fterm);
            }
            else terminal = "Erro ao tentar abrir arquivo de log";    // erro ao tentar abrir arquivo de log
            
        }
        else {
            terminal = "";
        }
    }
    else terminal = "Erro ao tentar obter saida do terminal";
}

char* htmlEstilo() {

    char* linha = (char *) malloc(1000 * sizeof(char));

    sprintf(linha, "<style>\n"
      				"	.cabct {font-family: Palatino; font-size: 16pt; font-weight: bold; text-decoration: #333333 underline}\n"
      				"	.secct {font-family: sans-serif; font-size: 12pt; font-weight: bold}\n"
      				"	.varnome {font-family: sans-serif; font-size: 12pt}\n"
      				"	.varval {font-family: Courier New, Courier; font-size: 12pt}\n"
      				"	.rescor {color: #0000ff}\n"
      				"	.reserr {color: #ff0000}\n"
      			"</style>");

    return linha;
}

char* htmlEntrada() {

    char* linha = (char *) malloc(1000 * sizeof(char));

    sprintf(linha, "    <div>\n"
                   "	    <span class=\"secct\">entrada</span><br>\n"
          		   "		    <span class=\"varnome\">N:</span> <span class=\"varval\">%d</span><br>\n"
          		   "		    <span class=\"varnome\">L:</span> <span class=\"varval\">%s</span><br>\n"
                   "    </div>",
                   N,
                   L);
    
    return linha;
}

char* htmlGabarito() {

    char* linha = (char *) malloc(1000 * sizeof(char));

    sprintf(linha, "    <div>\n"
                   "	    <span class=\"secct\">gabarito</span><br>\n"
          		   "		    <span class=\"varnome\">maior:</span> <span class=\"varval\">%d</span><br>\n"
                   "    </div>",
                   gabmaior);
    
    return linha;
}

char* htmlSaida() {

    char* linha = (char *) malloc(1000 * sizeof(char));

    sprintf(linha, "    <div>\n"
                   "	    <span class=\"secct\">saída</span><br>\n"
          		   "		    <span class=\"varnome\">maior:</span> <span class=\"varval\">%d</span><br>\n"
                   "    </div>",
                   maior);
    
    return linha;
}

char* htmlResultado() {

    char* linha = (char *) malloc(150 * sizeof(char));
    char* strResultado = (char *) malloc(100 * sizeof(char));

    if (resultado < 0) {

        if (resultado == -2)
            sprintf(strResultado, "Tempo limite excedido.");
        else
            sprintf(strResultado, "Falha na execução do caso de testes. (Erro de execução.)");
    }
    else if (resultado) {
        sprintf(strResultado, "<span class=\"rescor\">acertou!</span>");
    }
    else {
        sprintf(strResultado, "<span class=\"reserr\">resposta errada</span>");
    }

    sprintf(linha, "    <div>\n"
                   "        %s\n"
                   "    </div>",
                   strResultado);
    
    return linha;
}

char* htmlTerminal() {

    char* linha = (char *) malloc((200 + strlen(terminal) + 1) * sizeof(char));

    sprintf(linha, "    <div>\n"
                   "	    <span class=\"secct\">terminal:</span> <pre style=\"background-color: #000000; color: #00ff00\">%s</pre><br>\n"
                   "    </div>",
                   terminal);
    
    return linha;
}

char* htmlCasoTeste() {

    char* htmlest = htmlEstilo();
    char* htmle = htmlEntrada();
    char* htmlg = htmlGabarito();
    char* htmls = htmlSaida();
    char* htmlr = htmlResultado();
    char* htmlt = htmlTerminal();

    size_t tamhtml = strlen(htmlest) + strlen(htmle) + strlen(htmlg) + strlen(htmls) + strlen(htmlr) + strlen(htmlt) + 100 + 1;

    char* html = (char *) malloc(tamhtml *sizeof(char));

    sprintf(html, "<div>\n%s\n%s\n%s\n%s\n%s\n%s\n"
                  "</div>\n",
                  htmlest,
                  htmle,
                  htmlg,
                  htmls,
                  htmlr,
                  htmlt);

    free(htmlest);
    free(htmle);
    free(htmlg);
    free(htmls);
    free(htmlr);
    free(htmlt);

    return html;
}