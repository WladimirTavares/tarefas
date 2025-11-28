#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// função que gera o código html de feedback sobre o resultado da avaliação do caso de teste

char* htmlFeedBack(int ncts, char* supdirct, char* supdirctresp) {

    // gere código html exibir as informações sobre o caso de teste
    // que você quiser (entrada, gabarito, saída, resultado da avaliação, ...)

    char* html = (char *) malloc(10000*sizeof(char));
    html[0] = '\0';
    //char html[10000] = "";
    char linha[4000] = "";

    char dirct[4097] = "";
    char dirctresp[4097] = "";


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

        if (resultado < 0) {    // execução do caso de testes terminou inesperadamente
            sprintf(linha, "<div>caso de teste %d<br>\n entrada<br>\n x: %d<br>\n y: %d<br>\n gabarito<br>\n z: %d<br>\n saída<br>\n z: <br>\n resultado: <b>Falha na execução do caso de testes. (Erro de execução.)</b><br></div><br>", i, x, y, gabz, z);
            strcat(html, linha);
            break;
        }


        // abrir arquivo de gabarito e entrada (caso necessário)
        
        sprintf(caminho, "%s/entrada.txt", dirct);
        FILE* fe = fopen(caminho, "r");
        sprintf(caminho, "%s/gabarito.txt", dirct);
        FILE* fg = fopen(caminho, "r");

        int x, y;
        fscanf(fe, "%d", &x);
        fscanf(fe, "%d", &y);

        int gabz;
        fscanf(fg, "%d", &gabz);

        // caso tenha sido gerado caso de teste dinâmico
        //sprintf(caminho, "%s/entradadinamica.txt", dirctresp);
        //FILE* fd = fopen(caminho, "r");

        // abrir arquivo de saída
        sprintf(caminho, "%s/saida.txt", dirctresp);
        FILE* fs = fopen(caminho, "r");

        int z;
        fscanf(fs, "%d", &z);

        

        // monte o código html do resultado da avaliação do caso de teste
        sprintf(linha, "<div>entrada<br>\n x: %d<br>\n y: %d<br>\n gabarito<br>\n z: %d<br>\n saída<br>\n z: %d<br>\n resultado: %s<br></div><br>", x, y, gabz, z, resultado ? "acertou!" : "resposta errada");
        strcat(html, linha);


        // feche os arquivos
        fclose(fe);
        fclose(fg);
        fclose(fs);
        fclose(fa);
    }
    
    return html;
}