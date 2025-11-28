#include "cab.c"
#include "respostaprep.c"
#include "carregarCt.c"
#include "salvarSaida.c"

int main(int argc, char** argv) {

    //Extrair numero do caso de teste, diretório de dados do caso de teste e diretório da saída gerada pela resposta
    
    int __ct = 0;
    char* __dirct = NULL;
    char* __dirctresp = NULL;

    if (argc != 4) {
        // erro
    }

    __ct = atoi(argv[1]);
    __dirct = argv[2];
    __dirctresp = argv[3];

    //Carregar valores das variáveis globais de entrada e saída
    __carregar_dados_casoteste(__ct, __dirct, __dirctresp);

    //Executar resposta enviada
    __main();

    //Salvar saída gerada pela resposta
    __salvar_saida_casoteste(__ct, __dirctresp);

}