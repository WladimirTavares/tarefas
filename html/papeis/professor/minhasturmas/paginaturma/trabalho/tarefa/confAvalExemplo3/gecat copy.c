#include "cab.c"
#include "sol.c"
#include "gerCt.c"
#include "salvarCt.c"



int main(int argc, char* argv[]) {

        int ct = 0;
        sscanf(argv[1], "%d", &ct);
        char dirct[4097];
        sprintf(dirct, "%s/%d", argv[2], ct);

		iniRand();
        gerarArquivosCasoTeste(ct, dirct);

}