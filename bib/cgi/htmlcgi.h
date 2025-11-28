/*
 * Implementa métodos para construção de códigos html diversos a serem usados pelos scripts cgi.
 *
 */


#ifndef HTMLCGI_H
#define HTMLCGI_H


#include "../str/bibstring2.h"
#include "../str/multilinhas.h"

#include "../lugar.h"


// Cria lista de elementos <option> de instituições
// O valor é o id da instituição
// É passado o id da opção que deve aparecer selecionada
char* htmlOpcoesInstituicoes(long long int idInst);

// Cria lista de elementos <option> de instituições
// O valor é o id da instituição
// É passado o id da opção que deve aparecer selecionada
// Adiciona uma opção sem instituição (-)
char* htmlOpcoesInstituicoes2(long long int idInst);

// Cria lista de elementos <option> de cursos de uma instituição dada
// O valor de cada opção é o id do curso
// É passado o id da opção que deve aparecer selecionada
char* htmlOpcoesCursos(char* idInst, long long int idCurso);

// Cria lista de elementos <option> de cursos de uma instituição dada
// O valor de cada opção é o id do curso
// É passado o id da opção que deve aparecer selecionada
char* htmlOpcoesDisciplinas(char* idInst, long long int idDisciplina);



/*      Implementações      */




char* htmlOpcoesInstituicoes(long long int idInst) {

	Instituicao* insts = NULL;
	int numInsts = 0;

	bdTodasInstituicoes(&insts, &numInsts);

	Multilinhas* ml = mlCriar();

	char elHtml[500];

	mlAnexarLinha("<option value=\"\">-</option>", ml);
	for (int i = 0; i < numInsts; i++) {
		//if (*(curso->inst->idInstituicao) == *(insts[i].idInstituicao))		//seleciona o id da instituição do curso
		if (idInst == *(insts[i].idInstituicao))		//seleciona o id da instituição do curso
			sprintf(elHtml, "<option value=%lld selected>%s</option>", *(insts[i].idInstituicao), insts[i].sigla);
		else
			sprintf(elHtml, "<option value=%lld>%s</option>", *(insts[i].idInstituicao), insts[i].sigla);

		mlAnexarLinha(elHtml, ml);
	}

    return mlExtrairTexto(ml);

}


char* htmlOpcoesInstituicoes2(long long int idInst) {

	Instituicao* insts = NULL;
	int numInsts = 0;

	bdTodasInstituicoes(&insts, &numInsts);

	Multilinhas* ml = mlCriar();

	char elHtml[500];

	sprintf(elHtml, "<option value=0>-</option>");
	mlAnexarLinha(elHtml, ml);

	for (int i = 0; i < numInsts; i++) {
		//if (*(curso->inst->idInstituicao) == *(insts[i].idInstituicao))		//seleciona o id da instituição do curso
		if (idInst == *(insts[i].idInstituicao))		//seleciona o id da instituição do curso
			sprintf(elHtml, "<option value=%lld selected>%s</option>", *(insts[i].idInstituicao), insts[i].sigla);
		else
			sprintf(elHtml, "<option value=%lld>%s</option>", *(insts[i].idInstituicao), insts[i].sigla);

		mlAnexarLinha(elHtml, ml);
	}

    return mlExtrairTexto(ml);

}


char* htmlOpcoesCursos(char* idInst, long long int idCurso) {

		Curso* cursos = NULL;
		int numCursos = 0;

		bdBuscarCursoIdInstituicao(idInst, &cursos, &numCursos);

		Multilinhas* ml = mlCriar();

		char elHtml[500];

		sprintf(elHtml, "<option value=\"\">-</option>");
		//mlSubstituirTodosEmLinha("@OpcoesCurso", elHtml, nl);
		mlAnexarLinha(elHtml, ml);

		for (int i = 0; i < numCursos; i++) {
			if (idCurso == *(cursos[i].idCurso))		// repete o selecionado da tela anterior
				sprintf(elHtml, "<option value=%lld selected>%s - %s</option>", *(cursos[i].idCurso), cursos[i].codigo, cursos[i].nome);
			else
				sprintf(elHtml, "<option value=%lld>%s - %s</option>", *(cursos[i].idCurso), cursos[i].codigo, cursos[i].nome);

			//mlSubstituirTodosEmLinha("@OpcoesCurso", elHtml, nl);
			mlAnexarLinha(elHtml, ml);
		}

		return mlExtrairTexto(ml);
}



char* htmlOpcoesDisciplinas(char* idInst, long long int idDisciplina) {

		Disciplina* disciplinas = NULL;
		int numDisciplinas = 0;

		//printf("%s", idInst);
		//printf("%lld", idDisciplina);

		bdBuscarDisciplinaIdInstituicao(idInst, &disciplinas, &numDisciplinas);

		//printf("%d", numDisciplinas);

		Multilinhas* ml = mlCriar();

		char elHtml[500];

		sprintf(elHtml, "<option value=\"\">-</option>");
		//mlSubstituirTodosEmLinha("@OpcoesCurso", elHtml, nl);
		mlAnexarLinha(elHtml, ml);

		for (int i = 0; i < numDisciplinas; i++) {
			if (idDisciplina == *(disciplinas[i].idDisciplina))		// repete o selecionado da tela anterior
				sprintf(elHtml, "<option value=%lld selected>%s - %s</option>", *(disciplinas[i].idDisciplina), disciplinas[i].codigo, disciplinas[i].nome);
			else
				sprintf(elHtml, "<option value=%lld>%s - %s</option>", *(disciplinas[i].idDisciplina), disciplinas[i].codigo, disciplinas[i].nome);

			//mlSubstituirTodosEmLinha("@OpcoesCurso", elHtml, nl);
			mlAnexarLinha(elHtml, ml);
		}

		return mlExtrairTexto(ml);
}





#endif
