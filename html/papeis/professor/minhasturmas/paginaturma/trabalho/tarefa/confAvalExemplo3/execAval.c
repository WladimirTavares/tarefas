#include "avalEstat.c"

int main(int argc, char** argv) {

    //Extrair numero do caso de teste, diretório de dados do caso de teste e diretório da saída gerada pela resposta
    
    int ct = 0;
    char* dirct = NULL;
    char* dirctresp = NULL;

    if (argc != 4) {
        // erro
    }

    ct = atoi(argv[1]);
    dirct = argv[2];
    dirctresp = argv[3];

    //Executar resposta enviada
    avaliacaoCT(ct, dirct, dirctresp);

}