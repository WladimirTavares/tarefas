#include "feedback.c"

int main(int argc, char** argv) {

    //Extrair numero do caso de teste, diretório de dados do caso de teste e diretório da saída gerada pela resposta
    
    int ncts = 0;
    char* supdirct = NULL;
    char* supdirctresp = NULL;

    if (argc != 4) {
        // erro
    }

    ncts = atoi(argv[1]);
    supdirct = argv[2];
    supdirctresp = argv[3];

    //Executar resposta enviada
    char* html = htmlFeedBack(ncts, supdirct, supdirctresp);

    char caminho[4097] = "";
    sprintf(caminho, "%s/feedback.htm", supdirctresp);
    FILE* f = fopen(caminho, "w");
    fprintf(f, "%s", html);
    fclose(f);
}