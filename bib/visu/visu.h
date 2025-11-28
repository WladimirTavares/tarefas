/*
 * visu.h
 *
 * Provê código html para um visualizador de arquivos.
 * 
 * Três parâmetros devem ser providos: 1) o tipo do arquivo (extensão sem o '.')
 *                                     2) a url de onde o arquivo pode ser obtido
 *                                     3) a url onde se encontra o bundle do codemirror (para abrir código C com syntax highlighting) 
 *
*/


#include <stdlib.h>
#include <stdio.h>


#include "../../bib/str/multilinhas.h"
#include "../../../bibcgi/formhtmlcgi.h"



char* htmlVisualizador(char* tipo, char* url, char* urlbundlecm) {

    // escolher tipo de visualizador

    Multilinhas* mlvisu = mlCriar();

    if (!strcmp(tipo, "png") || !strcmp(tipo, "jpg") || !strcmp(tipo, "gif")) {
            // carregar código do visualizador
            
            char* caminho = concatstr(dirHtml, "/visu/visuImg.htm");
            mlCarregarArquivoTexto(caminho, mlvisu);
    }
    else if (!strcmp(tipo, "pdf")) {
        //

        char* caminho = concatstr(dirHtml, "/visu/visuPdf.htm");
        mlCarregarArquivoTexto(caminho, mlvisu);
    }
    else if (!strcmp(tipo, "txt")) {

        char* caminho = concatstr(dirHtml, "/visu/visuTxt.htm");
        mlCarregarArquivoTexto(caminho, mlvisu);
    }
    else if (!strcmp(tipo, "c")) {

        char* caminho = concatstr(dirHtml, "/visu/visuCodC.htm");
        mlCarregarArquivoTexto(caminho, mlvisu);

        // colocar endereço do bundle codemirror
        mlSubstituirTodos("$URLDWLTAREFAS$", urlbundlecm, mlvisu);
        
    }

    mlSubstituirTodos("$VISUURLARQ$", url, mlvisu);

    return mlExtrairTexto(mlvisu);
}