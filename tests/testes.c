/*
 * tarefas.c
 *
 * Script cgi principal do sistema Tarefas.
 *
 */



#include <stdlib.h>
#include <stdio.h>


#include "bib/str/bibstring2.h"
#include "bib/str/multilinhas.h"


// Incluir bibliotecas cgi

#include "../bibcgi/formhtmlcgi.h"


// Incluir bibliotecas de sistema

#include "bib/bd/tarefasbd.h"


int main() {

	printf("Tarefas\n");

	criarSessao(1,1,600, 60000);

}
