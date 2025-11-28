/*
 * imagem.h
 *
 * rotinas de manipulação e extração de dados de imagens
 *
 */



void imgDimensoesPNG(char* nomearqpng, unsigned int* largura, unsigned int* altura);


//int converterPDFPNG(char* camihoarqpdg, char* caminhoarqpng);



/*		Implementações		*/



void imgDimensoesPNG(char* nomearqpng, unsigned int* largura, unsigned int* altura){

    FILE* f = fopen(nomearqpng, "r");

    if (f){

        char* cabecalho = (char *) malloc(25 * sizeof(char));
        fread(cabecalho, 24, 1, f);
        cabecalho[24] = '\0';

        unsigned int* a = (unsigned int *) (cabecalho + 16);
        unsigned int* l = (unsigned int *) (cabecalho + 20);

        *largura = ((*l>>24)&0xff) | // move byte 3 to byte 0
                        ((*l<<8)&0xff0000) | // move byte 1 to byte 2
                        ((*l>>8)&0xff00) | // move byte 2 to byte 1
                        ((*l<<24)&0xff000000); // byte 0 to byte 3

        *altura = ((*a>>24)&0xff) | // move byte 3 to byte 0
                        ((*a<<8)&0xff0000) | // move byte 1 to byte 2
                        ((*a>>8)&0xff00) | // move byte 2 to byte 1
                        ((*a<<24)&0xff000000); // byte 0 to byte 3

        fclose(f);

    }
    else {
        *largura = 0;
        *altura = 0;
    }

}


void imgAlturaPadraoPNG(char* nomearqpng, double fator, unsigned int* a) {

    // valor padrão do fator = 0.3426

	unsigned int l = 0;

	imgDimensoesPNG(nomearqpng, a, &l);

	*a = (int) (fator * (*a));

}


/*
 * https://unix.stackexchange.com/questions/75635/shell-command-to-get-pixel-size-of-an-image
 *
 *
 *
 *
 *
 *
 */
