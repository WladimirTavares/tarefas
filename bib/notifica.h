#ifndef NOTIFICA_H
#define NOTIFICA_H

#include <string.h>
#include "str/bibstring2.h"

typedef struct RegNoti {
    int numnoti;
    char* msg;
} RegNoti;

RegNoti* criarRegNoti(int numnoti, char* msg);

void imprimirRegnoti(RegNoti rn);

char* msgNotiHTML(RegNoti* rn);


/*      Implementações      */



RegNoti* criarRegNoti(int numnoti, char* msg) {

    RegNoti* rn = (RegNoti *) malloc (sizeof(RegNoti));
    rn->numnoti = numnoti;
    rn->msg = copiastr(msg);

    return rn;
}


void imprimirRegnoti(RegNoti rn) {

    printf("%d: %s", rn.numnoti, rn.msg);
}

char* msgNotiHTML(RegNoti* rn) {

    if (rn) {
        size_t tammsg = rn->msg ? strlen(rn->msg) : 0;

        if (rn->msg) {
            char* html = (char *) malloc((29 + tammsg + 1));

            if (rn->numnoti)      // notificação de erro
                sprintf(html, "<font color=\"#ff0000\">%s</font>", rn->msg);
            else
                sprintf(html, "<font color=\"#0000ff\">%s</font>", rn->msg);

            //printf("%s", html);
            return html;
        }
        else
            return strdup("");
    }

    return strdup("");
}


#endif
