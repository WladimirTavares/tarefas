#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// funções que geram o código html de feedback sobre o resultado da avaliação do caso de teste

char* htmlEstilo();

char* htmlFeedBack(int ncts, char* supdirct, char* supdirctresp) {

    // gere código html exibir as informações sobre o caso de teste
    // que você quiser (entrada, gabarito, saída, resultado da avaliação, ...)

    char* html = (char *) malloc(10000*sizeof(char));
    html[0] = '\0';
    //char html[10000] = "";
    char linha[4000] = "";

    char dirct[4097] = "";
    char dirctresp[4097] = "";


    // definir estilos css

    // sprintf(html, "<style>\n"
    //   				"	.cabct {font-family: Palatino; font-size: 16pt; font-weight: bold; text-decoration: #333333 underline}\n"
    //   				"	.secct {font-family: sans-serif; font-size: 12pt; font-weight: bold}\n"
    //   				"	.varnome {font-family: sans-serif; font-size: 12pt}\n"
    //   				"	.varval {font-family: Courier New, Courier; font-size: 12pt}\n"
    //   				"	.rescor {color: #0000ff}\n"
    //   				"	.reserr {color: #ff0000}\n"
    //   			"</style>\n\n");

    sprintf(html, htmlEstilo());


    for (int i = 1; i <= ncts; i++) {

        // montar caminho dos diretórios de caso de teste
        sprintf(dirct, "%s/%d", supdirct, i);
        sprintf(dirctresp, "%s/%d", supdirctresp, i);


        // abrir resultado da avaliação
        char caminho[4097];
        sprintf(caminho, "%s/avalct.txt", dirctresp);
        FILE* fa = fopen(caminho, "r");

        int resultado;
        fscanf(fa, "%d", &resultado);

        // abrir arquivo de gabarito e entrada (caso necessário)
        
        sprintf(caminho, "%s/entrada.txt", dirct);
        FILE* fe = fopen(caminho, "r");
        sprintf(caminho, "%s/gabarito.txt", dirct);
        FILE* fg = fopen(caminho, "r");

        int N;
        char L[400] = "";
        fscanf(fe, "%d", &N);
        fgets(L, 400, fe);

        int gabmaior;
        fscanf(fg, "%d", &gabmaior);

        // caso tenha sido gerado caso de teste dinâmico
        //sprintf(caminho, "%s/entradadinamica.txt", dirctresp);
        //FILE* fd = fopen(caminho, "r");

        if (resultado < 0) {    // execução do caso de testes terminou inesperadamente

            if (resultado == -2) {  // tempo limite excedido
                sprintf(linha, "<div>caso de teste %d<br>\n entrada<br>\n N: %d<br>\n L: %s<br>\n gabarito<br>\n z: %d<br>\n saída<br>\n z: <br>\n resultado: <b>Tempo limite excedido.</b><br></div><br>", i, N, L, gabmaior);
                strcat(html, linha);
                break;
            }

            sprintf(linha, "<div>caso de teste %d<br>\n entrada<br>\n N: %d<br>\n L: %s<br>\n gabarito<br>\n z: %d<br>\n saída<br>\n z: <br>\n resultado: <b>Falha na execução do caso de testes. (Erro de execução.)</b><br></div><br>", i, N, L, gabmaior);
            strcat(html, linha);
            break;
        }

        // abrir saida do terminal
		FILE* fterm = NULL;
      	char* terminal = NULL;
      	sprintf(caminho, "%s/execCt.log", dirctresp);
      
      	if (!access(caminho, F_OK)) {
            struct stat st;
            stat(caminho, &st);
            size_t tam = st.st_size;
    
            if (tam) {
              	terminal = (char *) malloc((tam + 1) * sizeof(char));
                if (fterm = fopen(caminho, "r")) {
                    fread(terminal, 1, tam, fterm);
                    terminal[tam] = '\0';
                    fclose(fterm);
                }
              	else terminal[0] = '\0';
                
            }
            else {
                terminal = "";
            }
        }
        else terminal = "Erro ao tentar obter saida do terminal";

        // abrir arquivo de saída
        sprintf(caminho, "%s/saida.txt", dirctresp);
        FILE* fs = fopen(caminho, "r");

        int maior;
        fscanf(fs, "%d", &maior);

        

        // monte o código html do resultado da avaliação do caso de teste
        sprintf(linha, "<div>caso de teste %d<br>\n entrada<br>\n N: %d<br>\n L: %s<br>\n gabarito<br>\n maior: %d<br>\n saída<br>\n maior: %d<br>\n resultado: %s<br>\n terminal: <pre style=\"background-color: #000000; color: #00ff00\">%s</pre><br></div><br>", i, N, L, gabmaior, maior, resultado ? "acertou!" : "resposta errada", terminal);
        
        sprintf(linha, "<div>"
          			   "	<span class=\"cabct\">caso de teste %d</span><br>\n"
          			   "	<span class=\"secct\">entrada</span><br>\n"
          			   "		<span class=\"varnome\">N:</span> <span class=\"varval\">%d</span><br>\n"
          			   "		<span class=\"varnome\">L:</span> <span class=\"varval\">%s</span><br>\n"
          			   "	<span class=\"secct\">gabarito</span><br>\n"
          			   "		<span class=\"varnome\">maior:</span> <span class=\"varval\">%d</span><br>\n"
          			   "	<span class=\"secct\">saída</span><br>\n"
          			   "		<span class=\"varnome\">maior:</span> <span class=\"varval\">%d</span><br>\n"
          			   "	<span class=\"secct\">resultado:</span> <span class=\"varval\">%s</span><br>\n"
          			   "	<span class=\"secct\">terminal:</span> <pre style=\"background-color: #000000; color: #00ff00\">%s</pre><br>\n"
          			   "</div><br>",
          				i,
          				N,
          				L,
          				gabmaior,
          				maior,
          				resultado ? "<span class=\"rescor\">acertou!</span>" : "<span class=\"reserr\">resposta errada</span>",
          				terminal);
        
        strcat(html, linha);


        // feche os arquivos
        fclose(fe);
        fclose(fg);
        fclose(fs);
        fclose(fa);
    }
    
    return html;
}

char* htmlEstilo() {

    return "<style>\n"
      				"	.cabct {font-family: Palatino; font-size: 16pt; font-weight: bold; text-decoration: #333333 underline}\n"
      				"	.secct {font-family: sans-serif; font-size: 12pt; font-weight: bold}\n"
      				"	.varnome {font-family: sans-serif; font-size: 12pt}\n"
      				"	.varval {font-family: Courier New, Courier; font-size: 12pt}\n"
      				"	.rescor {color: #0000ff}\n"
      				"	.reserr {color: #ff0000}\n"
      			"</style>\n\n";
}