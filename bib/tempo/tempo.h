/*
 * tempo.h:	Implementa métodos de manipuação de data e hora
 *
 *
 * Versão: 0.1
 *
 */


#ifndef TEMPO_H
#define TEMPO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>






void imprimirTM(struct tm* dh);

// a string com a data/hora tem o formato "yyyy-mm-dd HH:MM"
struct tm* extrairDataHora(char* str);

time_t calcTempo(struct tm* dh);

char* horaAtual();
char* dataAtual();

char* dataStr(time_t datahora);
char* horaStr(time_t datahora);


//struct timespec ts;
//clock_gettime(CLOCK_REALTIME, &ts);



/*      Implementações      */


void imprimirTM(struct tm* dh) {

    if (dh) {

        printf("sec: %d, min: %d, hora: %d, dia: %d, mes: %d, ano: %d, diasemana: %d, diaano: %d, horarioverao: %d", dh->tm_sec, dh->tm_min, dh->tm_hour, dh->tm_mday, dh->tm_mon, dh->tm_year, dh->tm_wday, dh->tm_yday, dh->tm_isdst);

        printf(", timestamp: %ld", calcTempo(dh));
    }
    else
        printf("NULL");
}

struct tm* extrairDataHora(char* str) {

    if (str) {

        int ano, mes, diam, hora, min;

        //int ret = sscanf(str, "%4d-%2d-%2d %2d:%2d", &(dh->tm_year), &(dh->tm_mon), &(dh->tm_mday), &(dh->tm_hour), &(dh->tm_min));
        int ret = sscanf(str, "%4d-%2d-%2d %2d:%2d", &ano, &mes, &diam, &hora, &min);

        if (ret != 5) {

            return NULL;
        }
        else {

            struct tm* dh = (struct tm *) malloc(sizeof(struct tm));


            dh->tm_year = ano - 1900;
            dh->tm_mon = mes - 1;
            dh->tm_mday = diam;
            dh->tm_hour = hora;
            dh->tm_min = min;

            // inicializar demais campos

            dh->tm_sec = 0;
            dh->tm_wday = 0;
            dh->tm_yday = 0;
            dh->tm_isdst = 0;

            return dh;
        }
    }

    return NULL;

}


time_t calcTempo(struct tm* dh) {

    if (dh) {
        return mktime(dh);
    }
    return 0;
}


char* horaAtual() {

    char* hora = malloc(40*sizeof(char));

    struct timespec tsc;
	clock_gettime(CLOCK_REALTIME, &tsc);
    struct tm* dh = localtime(&tsc.tv_sec);

    sprintf(hora, "%02d:%02d", dh->tm_hour, dh->tm_min);

    return hora;
}


char* dataAtual() {

    char* data = malloc(40*sizeof(char));

    struct timespec tsc;
	clock_gettime(CLOCK_REALTIME, &tsc);
    struct tm* dh = localtime(&tsc.tv_sec);

    sprintf(data, "%4d-%02d-%02d", dh->tm_year + 1900, dh->tm_mon + 1, dh->tm_mday);

    return data;
}



char* dataStr(time_t datahora) {

    char* data = malloc(40*sizeof(char));

    struct tm* dh = localtime(&datahora);

    sprintf(data, "%4d-%02d-%02d", dh->tm_year + 1900, dh->tm_mon + 1, dh->tm_mday);

    return data;
}

char* horaStr(time_t datahora) {

    char* hora = malloc(40*sizeof(char));

    struct tm* dh = localtime(&datahora);

    sprintf(hora, "%02d:%02d", dh->tm_hour, dh->tm_min);

    return hora;
}



#endif
