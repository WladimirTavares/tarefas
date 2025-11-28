#ifndef DIRETORIO_H
#define DIRETORIO_H




#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>



#include "./str/multilinhas.h"




int dirLs(char* nomedir, Multilinhas** ml);

int dirSubDirs(char* nomedir, Multilinhas** ml);

int dirNaoSubDirs(char* nomedir, Multilinhas** ml);

int dirEsvaziarDir(char* nomedir);





/*		Implementações		*/





int dirLs(char* nomedir, Multilinhas** ml) {

	DIR *dp;
    struct dirent *ep;

    dp = opendir (nomedir);

    if (dp != NULL){

		*ml = mlCriar();

        while (ep = readdir (dp)) {
			mlAnexarLinha(ep->d_name, *ml);

		}

        closedir(dp);
    }
    else {
        // não foi possível abrir o diretório

        *ml = NULL;
        return 1;
    }

}



int dirSubDirs(char* nomedir, Multilinhas** ml) {

	DIR *dp = NULL;
    struct dirent *ep;

    dp = opendir(nomedir);

    if (dp != NULL){

		*ml = mlCriar();

        while (ep = readdir (dp)) {
			if (ep->d_type == DT_DIR){

				//printf("%ld", strlen(ep->d_name));
                if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, "..")){
                    mlAnexarLinha(ep->d_name, *ml);
                }
            }
		}

        closedir(dp);
    }
    else {
        // não foi possível abrir o diretório

		*ml = NULL;
        return 1;
    }

}



int dirNaoSubDirs(char* nomedir, Multilinhas** ml) {

    DIR *dp;
    struct dirent *ep;

    dp = opendir (nomedir);

    if (dp != NULL){

		*ml = mlCriar();

        while (ep = readdir (dp)) {
			if (ep->d_type != DT_DIR){

				//printf("%ld", strlen(ep->d_name));
                if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, "..")){
                    mlAnexarLinha(ep->d_name, *ml);
                }
            }
		}

        closedir(dp);
    }
    else {
        // não foi possível abrir o diretório

		*ml = NULL;
        return 1;
    }
}



int dirEsvaziarDir(char* nomedir) {

    DIR *dp;
    struct dirent *ep;

    dp = opendir (nomedir);

    int ret = 0;

    if (dp != NULL){

        int nomeIrregular = 0;

        while (ep = readdir (dp)) {

            if (ep && strcmp(ep->d_name, ".") && strcmp(ep->d_name, "..") && strlen(ep->d_name) && !eBranco(ep->d_name)){

                // montar caminho para o arquivo/diretório
                char* caminho = concatstr2(nomedir, concatstr2("/", ep->d_name));

                if (ep->d_type != DT_DIR) {

                    ret = remove(caminho);

                    if (!ret) {       // erro ao tentar remover arquivo

                        closedir(dp);

                        return 1;
                    }

                }
                else {      // se for diretório, usar rmdir()

                    ret = rmdir(caminho);

                    if (!ret) {       // erro ao tentar remover arquivo

                        closedir(dp);

                        return 2;
                    }
                }

            }
            else {

                nomeIrregular = 1;
            }

		}

        closedir(dp);

        if (nomeIrregular)
            return 3;

        // arquivos e subdiretórios apagados

        return 0;
    }
    else {
        // não foi possível abrir o diretório

        return 4;
    }

}








/*
 * https://stackoverflow.com/questions/39429803/how-to-list-first-level-directories-only-in-c
 *
 * https://stackoverflow.com/questions/30877110/how-to-determine-directory-or-file-in-linux-in-c
 *
 * https://stackoverflow.com/questions/5467725/how-to-delete-a-directory-and-its-contents-in-posix-c
 *
 *
 */




#endif
