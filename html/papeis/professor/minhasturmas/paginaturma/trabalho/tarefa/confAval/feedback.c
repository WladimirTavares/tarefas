// função que gera o código html de feedback sobre o resultado da avaliação do caso de teste

char* htmlFeedBack(int ncts, char* supdirct, char* supdirctresp) {

    // gere código html exibir as informações sobre o caso de teste
    // que você quiser (entrada, gabarito, saída, resultado da avaliação, ...)

    char* html = (char *) malloc(10000*sizeof(char));

    char dirct[4097] = "";
    char dirctresp[4097] = "";

    for (int i = 1; i < ncts; i++) {

        // montar caminho dos diretórios de caso de teste
        sprintf(dirct, "%s/%d", supdirct, i);
        sprintf(dirctresp, "%s/%d", supdirctresp, i);

        // abrir arquivo de gabarito e entrada (caso necessário)
        char caminho[4097];
        sprintf(caminho, "%s/entrada.txt", dirct);
        FILE* fe = fopen(caminho, "r");
        sprintf(caminho, "%s/gabarito.txt", dirct);
        FILE* fg = fopen(caminho, "r");

        // caso tenha sido gerado caso de teste dinâmico
        //sprintf(caminho, "%s/entradadinamica.txt", dirctresp);
        //FILE* fd = fopen(caminho, "r");

        // abrir arquivo de saída
        sprintf(caminho, "%s/saida.txt", dirctresp);
        FILE* fs = fopen(caminho, "r");

        // abrir resultado da avaliação
        sprintf(caminho, "%s/avalct.txt", dirctresp);
        FILE* fa = fopen(caminho, "r");

        // monte o código html do resultado da avaliação do caso de teste


        // feche os arquivos
        fclose(fe);
        fclose(fg);
        fclose(fs);
        fclose(fa);
    }

    // criar arquivo de avaliação global da tarefa
    char* caminho[4097] = "";
    sprintf(caminho, "%s/avaltarefa.txt", supdirctresp);
    FILE* fat = fopen(caminho, "r");

    // escreva o resultado da avaliação global da tarefa


    fclose(fat);
}