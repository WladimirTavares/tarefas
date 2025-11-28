#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


#include "../str/bibstring2.h"
#include "../str/multilinhas.h"

#include "../lugar.h"
#include "../notifica.h"

#include "../cgi/sessaocgi.h"
#include "../cgi/htmlcgi.h"




int dwldr(Usuario* usu, Sessao* sessao, FormularioHTML* form);





/*      Implementações      */





int dwldr(Usuario* usu, Sessao* sessao, FormularioHTML* form) {

    

    char* acao = obterCFHTML("acao", form);

    if (!strcmp(acao, "downloadvisualizarentrega")) {
                    // visualizarentrega

        char* idTrabalho = obterCFHTML("idTrabalho", form);
        char* idItemTarefa = obterCFHTML("idItemTarefa", form);
        char* idPerfilRespondedor = obterCFHTML("idPerfilRespondedor", form);

        long long int idT = atoll(idTrabalho);
        long long int idIT = atoll(idItemTarefa);
        long long int idPR = atoll(idPerfilRespondedor);

        Tarefa* tarefa = NULL;
        int numlins = 0;

        int ret = bdBuscarTarefaIdItemTarefa(idItemTarefa, &tarefa, &numlins);

        if (*(tarefa->tipo) == BD_TT_SUBMISSAOSIMPLES) {

            char* extensao = extensaoArqResposta(idT, idIT, idPR);
            char* nomearq = nomeArqResposta(idT, idIT, idPR);
            char* caminho = caminhoArqResposta(idT, idIT, idPR);
            
            // abrir arquivo
            FILE* f = fopen(caminho, "rb");

            // tamanho do arquivo
            struct stat st;
            stat(caminho, &st);
            size_t size = st.st_size;

            if (f) {

                printf("Content-Type: application/octet-stream\n");
                //printf("Content-Type: application/x-download\n");
                //printf("Content-Type: application/force-download\n");

                if (!strcmp(extensao, "pdf")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
                else if (!strcmp(extensao, "txt")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
                else if (!strcmp(extensao, "jpg") || !strcmp(extensao, "png") || !strcmp(extensao, "gif")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
                else if (!strcmp(extensao, "c")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }

                char* ct = (char *) malloc(size * sizeof(char));
                fread(ct, 1, size, f);

                char hd[100];
                sprintf(hd, "Content-Length: %ld\n\n", size);
                printf("%s", hd);

                fwrite(ct, 1, size, stdout);

                return 0;
            }

        }
        else if (*(tarefa->tipo) == BD_TT_CODIGOC) {

            char* extensao = extensaoArqResposta(idT, idIT, idPR);
            char* nomearq = nomeArqResposta(idT, idIT, idPR);
            char* caminho = caminhoArqResposta(idT, idIT, idPR);
            
            // abrir arquivo
            FILE* f = fopen(caminho, "rb");

            // tamanho do arquivo
            struct stat st;
            stat(caminho, &st);
            size_t size = st.st_size;

            if (f) {
                printf("Content-Type: application/octet-stream\n");
                //printf("Content-Type: application/x-download\n");
                //printf("Content-Type: application/force-download\n");

                if (!strcmp(extensao, "c")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
            }

            char* ct = (char *) malloc(size * sizeof(char));
            fread(ct, 1, size, f);

            char hd[100];
            sprintf(hd, "Content-Length: %ld\n\n", size);
            printf("%s", hd);

            fwrite(ct, 1, size, stdout);

            return 0;
        }
        else if (*(tarefa->tipo) == BD_TT_CODIGOCSTDIN) {

            char* extensao = extensaoArqResposta(idT, idIT, idPR);
            char* nomearq = nomeArqResposta(idT, idIT, idPR);
            char* caminho = caminhoArqResposta(idT, idIT, idPR);
            
            // abrir arquivo
            FILE* f = fopen(caminho, "rb");

            // tamanho do arquivo
            struct stat st;
            stat(caminho, &st);
            size_t size = st.st_size;

            if (f) {
                printf("Content-Type: application/octet-stream\n");
                //printf("Content-Type: application/x-download\n");
                //printf("Content-Type: application/force-download\n");

                if (!strcmp(extensao, "c")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
            }

            char* ct = (char *) malloc(size * sizeof(char));
            fread(ct, 1, size, f);

            char hd[100];
            sprintf(hd, "Content-Length: %ld\n\n", size);
            printf("%s", hd);

            fwrite(ct, 1, size, stdout);

            return 0;
        }

        return 1;
    }
    else if (!strcmp(acao, "downloadentrega")) {

        char* idTrabalho = obterCFHTML("idTrabalho", form);
        char* idItemTarefa = obterCFHTML("idItemTarefa", form);
        char* idPerfilRespondedor = obterCFHTML("idPerfilRespondedor", form);

        long long int idT = atoll(idTrabalho);
        long long int idIT = atoll(idItemTarefa);
        long long int idPR = atoll(idPerfilRespondedor);

        Tarefa* tarefa = NULL;
        int numlins = 0;

        int ret = bdBuscarTarefaIdItemTarefa(idItemTarefa, &tarefa, &numlins);

        if (*(tarefa->tipo) == BD_TT_SUBMISSAOSIMPLES) {

            char* extensao = extensaoArqResposta(idT, idIT, idPR);
            char* nomearq = nomeArqResposta(idT, idIT, idPR);
            char* caminho = caminhoArqResposta(idT, idIT, idPR);
            
            // abrir arquivo
            FILE* f = fopen(caminho, "rb");

            // tamanho do arquivo
            struct stat st;
            stat(caminho, &st);
            size_t size = st.st_size;

            if (f) {

                printf("Content-Type: application/octet-stream\n");
                //printf("Content-Type: application/x-download\n");
                //printf("Content-Type: application/force-download\n");

                if (!strcmp(extensao, "pdf")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
                else if (!strcmp(extensao, "txt")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
                else if (!strcmp(extensao, "jpg") || !strcmp(extensao, "png") || !strcmp(extensao, "gif")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }

                char* ct = (char *) malloc(size * sizeof(char));
                fread(ct, 1, size, f);

                char hd[100];
                sprintf(hd, "Content-Length: %ld\n\n", size);
                printf("%s", hd);

                fwrite(ct, 1, size, stdout);

                return 0;
            }

        }
        else if (*(tarefa->tipo) == BD_TT_CODIGOC) {
            char* extensao = extensaoArqResposta(idT, idIT, idPR);
            char* nomearq = nomeArqResposta(idT, idIT, idPR);
            char* caminho = caminhoArqResposta(idT, idIT, idPR);
            
            // abrir arquivo
            FILE* f = fopen(caminho, "rb");

            // tamanho do arquivo
            struct stat st;
            stat(caminho, &st);
            size_t size = st.st_size;

            if (f) {
                printf("Content-Type: application/octet-stream\n");
                //printf("Content-Type: application/x-download\n");
                //printf("Content-Type: application/force-download\n");

                if (!strcmp(extensao, "c")) {

                    printf("Content-Disposition: inline; filename=\"%s\"\n", nomearq);
                    printf("Content-Transfer-Encoding: binary\n");
                }
            }

            char* ct = (char *) malloc(size * sizeof(char));
            fread(ct, 1, size, f);

            char hd[100];
            sprintf(hd, "Content-Length: %ld\n\n", size);
            printf("%s", hd);

            fwrite(ct, 1, size, stdout);

            return 0;
        }

        return 2;
    }
    
}
