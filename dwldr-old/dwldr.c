#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Incluir bibliotecas do sistema

#include "../bib/lugar.h"
#include "../bib/str/bibstring2.h"
#include "../bib/cgi/valformhtml.h"

// Incluir bibliotecas cgi

#include "../../bibcgi/formhtmlcgi.h"

int main() {

	DadosCGI* dcgi = carregarDadosCGI();

	FormularioHTML* form = formularioHTMLDeDadosCGI(dcgi);


	//printf("Content-Type: text/html; charset: utf-8\n\n");

    // obter dados para a construir o caminho até o arquivo

    char* idTrabalho = obterCFHTML("idTrabalho", form);
    
    char* idItemTarefa = obterCFHTML("idItemTarefa", form);

    char* idPerfilRespondedor = obterCFHTML("idPerfilRespondedor", form);

    //printf("idTrabalho: %s,\n idItemTarefa: %s,\n idPerfilRespondedor: %s\n", idTrabalho, idItemTarefa, idPerfilRespondedor);



    // montar caminho do arquivo

    char* caminho = dirDadosPerfilItemTarefaStr(idTrabalho, idItemTarefa, idPerfilRespondedor);
    caminho = concatstr2(caminho, "/resposta.pdf");
    //caminho = concatstr2(dirDadosTarefas, concatstr2("/", caminho));

    // obter tamanho do arquivo em bytes
    struct stat st;
    stat(caminho, &st);
    size_t size = st.st_size;


	//printf("%s, %ld", caminho, size);

    //return 0;

    // abrir arquivo

    FILE* f = fopen(caminho, "rb");

    if (f) {

        char* ct = (char *) malloc(size * sizeof(char));

        fread(ct, 1, size, f);

        // enviar arquivo

        printf("Content-Type: application/octet-stream\n");
        //printf("Content-Type: application/x-download\n");
        //printf("Content-Type: application/force-download\n");
        printf("Content-Disposition: attachment; filename=\"resposta.pdf\"\n");
        printf("Content-Transfer-Encoding: binary\n");
        
        char hd[100];
        sprintf(hd, "Content-Length: %ld\n\n", size);
        printf("%s", hd);
        

        fwrite(ct, 1, size, stdout);
    }

    printf("Content-Type: text/html; charset: utf-8\n\n");

    return 0;
}