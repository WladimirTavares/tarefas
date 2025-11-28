#include "avalEstat.c"

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
    avaliacaoEstaticaTarefa(ncts, supdirct, supdirctresp);

}