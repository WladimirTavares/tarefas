/*
 * autentica.h
 *
 * implementa consultas de busca no banco
 *
 * OBS: Utiliza como caminho do banco a variável
 *
 * 			caminho_banco
 *
 * definida na biblioteca tarefasbd.h
 *
 */


int bdBuscarInstituicao(char* sigla, char* nome, char* obs, Instituicao** insts, int* num);

int bdBuscarInstituicaoId(char* idInstituicao, Instituicao** inst, int* num);

int bdBuscarInstituicaoSigla(char* sigla, Instituicao** inst, int* num);

int bdTodasInstituicoes(Instituicao** insts, int* num);

int bdBuscarCurso(char* codigo, char* nome, char* idInst, char* obs, Curso** cursos, int* num);

int bdBuscarCursoId(char* idCurso, Curso** cursos, int* num);

int bdBuscarCursoCodigoSiglaInst(char* codigo, char* siglaInst, Curso** cursos, int* num);

int bdBuscarCursoIdInstituicao(char* idInst, Curso** cursos, int* num);

int bdBuscarDisciplina(char* codigo, char* nome, char* idInst, char* obs, Disciplina** disciplinas, int* num);

int bdBuscarDisciplinaId(char* idCurso, Disciplina** disciplinas, int* num);

int bdBuscarDisciplinaIdInstituicao(char* idInstituicao, Disciplina** disciplinas, int* num);

int bdBuscarUsuario(char* nome, char* login, char* email, char* adm, char* professor, char* habilitado, Usuario** usuarios, int* num);

int bdBuscarUsuarioId(char* idUsuario, Usuario** usuarios, int* num);

int bdBuscarUsuarioLogin(char* login, Usuario** usuarios);

int bdBuscarUsuarioPerfil(char* nome, char* login, char* email, char* matricula, char* idCurso, char* idInstituicao, Usuario** usuarios, int* num);

int bdBuscarUsuarioPerfilId(char* idUsuario, char* idPerfil, Usuario** usuario, int* num);

int bdBuscarUsuarioPerfilId2(char* idPerfil, Usuario** usuario);

int bdBuscarUsuarioPerfilMatriculaCodCursoSiglaInst(char* matricula, char* codCurso, char* siglaInst, Usuario** usuario, int* num);

int bdBuscarUsuarioPerfilMatriculaIdCurso(char* matricula, char* idCurso, Usuario** usuario);

int bdBuscarUsuarioPerfilIdPerfilRespondedor(char* idPerfilRespondedor, Usuario** usuario);

int bdBuscarTurma(char* idInstituicao, char* idDisciplina, char* codigo, char* professor, char* descricao, char* ano, char* semestre, char* encerrada, char* obs, Turma** turmas, int* num);

int bdBuscarTurma2(char* idInstituicao, char* idDisciplina, char* codigo, char* idProfCriador, char* professor, char* descricao, char* ano, char* semestre, char* encerrada, char* obs, Turma** turmas, int* num);

int bdBuscarTurmaId(char* idTurma, Turma** turmas, int* num);

int bdBuscarProfPartIdTurma(char* idTurma, Usuario** usus, int* num);

int bdMinhasTurmas(char* idProf, Turma** turmas, int* num);

int bdBuscarTurmaId2(char* idTurma, Turma** turma);

int bdBuscarProfsTurmaId(char* idTurma, char* idProfCriador, Usuario** usuarios, int* num);

int bdBuscarRespondedoresTurmaId(char* idTurma, Usuario** usuarios, int* num);

int bdBuscarTrabalhosTurmaId(char* idTurma, Trabalho** trabalhos, int* num);

int bdBuscarTrabalhoId(char* idTrabalho, Trabalho** trabalho, int* num);

int bdBuscarTrabalhoIdUsuario(char* idTrabalho, char* idUsuario, Trabalho** trabalho, long long int* idPerfilRespondedor, int* num);

int bdBuscarItensTarefaIdTrabalho(char* idTrabalho, ItemTarefa** tarefa, int* num);

int bdNumeroItensTarefaIdTrabalho(char* idTrabalho, int* numItensTarefa);

int bdBuscarItensTarefaId(char* idItemTarefa, ItemTarefa** tarefa, int* num);

int bdContarItensDaTarefaId(char* idTarefa, int* numItens);

int bdContarItensDaTarefaDoItemId(char* idItemTarefa, int* numItens);

int bdBuscarTarefaId(char* idTarefa, Tarefa** tarefa, int* num);

int bdBuscarTarefaIdItemTarefa(char* idItemTarefa, Tarefa** tarefa, int* num);

int bdBuscarUsuarioPerfilIdUsu(char* idUsuario, Usuario** usu, int* num);

int bdTurmasPerfil(char* idPerfilRespondedor, Turma** turmas, int* num);

int bdBuscarSessao(char* idSessao, Sessao** sessao);

int bdDadosSessao(long long int idSessao, DadoSessao** dados, int* num);

int bdDadosSessaoGrupo(long long int idSessao, char* grupo, DadoSessao** dados, int* num);

// retorna os perfis do usuário que estão associados a alguma turma onde há algum trabalho onde há algum item relativo àquela tarefa
int bdPerfisTarefa(char* idUsuario, char* idTarefa, Usuario** usuperfil);

// retorna tumas com o trabalho com a tarefa desejada
int bdTurmasPerfilTarefa(char* idPerfilRespondedor, char* idTarefa, Turma** turmas, int* num);

// retorna os trabalhos da turma com a tarefa desejada
int bdBuscarTrabalhosTurmaTarefa(char* idTurma, char* idTarefa, Trabalho** trabalhos, int* num);

// retorna item de tarefa do trabalho e da tarefa
int bdBuscarItensTarefaIdTrabalhoTarefa(char* idTrabalho, char* idTarefa, ItemTarefa** itenstarefa, int* num);






/*		Implementações		*/



int bdBuscarInstituicao(char* sigla, char* nome, char* obs, Instituicao** insts, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idInstituicao, sigla, nome, obs "
			"FROM Instituicao "
			"WHERE "
			);

	char props[150];

	if (strcmp(sigla, "")){ sprintf(props, "sigla like \'%%%s%%\' AND ", sigla); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(nome, "")){ sprintf(props, "nome like \'%%%s%%\' AND ", nome); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(obs, "")){ sprintf(props, "obs like \'%%%s%%\'", obs); strcat(consulta, props); }
	else strcat(consulta, "TRUE");

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*insts = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Instituicao* instituicoes = NULL;

		*num = numlins;

		if (numlins > 0) {

			instituicoes = (Instituicao *) malloc( numlins * sizeof(Instituicao) );

			for (int i = 0; i < numlins; i++) {

				instituicoes[i].idInstituicao = ( ( (long long int **) (resultado[0]) )[i]);
				instituicoes[i].sigla =  ( (char **) (resultado[1]) )[i];
				instituicoes[i].nome =  ( (char **) (resultado[2]) )[i];
				instituicoes[i].obs =  ( (char **) (resultado[3]) )[i];
			}

		}

		*insts = instituicoes;

		return 0;

	}
}


int bdBuscarInstituicaoId(char* idInstituicao, Instituicao** inst, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idInstituicao, sigla, nome, obs "
			"FROM Instituicao "
			"WHERE idInstituicao = \'%s\'",
			idInstituicao);

	char props[100];

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*inst = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Instituicao* instituicoes = NULL;

		*num = numlins;

		if (numlins > 0) {

			instituicoes = (Instituicao *) malloc( sizeof(Instituicao) );

			instituicoes[0].idInstituicao = ( ( (long long int **) (resultado[0]) )[0]);
			instituicoes[0].sigla =  ( (char **) (resultado[1]) )[0];
			instituicoes[0].nome =  ( (char **) (resultado[2]) )[0];
			instituicoes[0].obs =  ( (char **) (resultado[3]) )[0];
		}

		*inst = instituicoes;

		ret = 0;

		return ret;

	}
}


int bdBuscarInstituicaoSigla(char* sigla, Instituicao** inst, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idInstituicao, sigla, nome, obs "
			"FROM Instituicao "
			"WHERE sigla = \'%s\'",
			sigla);

	char props[100];

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*inst = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Instituicao* instituicoes = NULL;

		*num = numlins;

		if (numlins > 0) {

			instituicoes = (Instituicao *) malloc( sizeof(Instituicao) );

			instituicoes[0].idInstituicao = ( ( (long long int **) (resultado[0]) )[0]);
			instituicoes[0].sigla =  ( (char **) (resultado[1]) )[0];
			instituicoes[0].nome =  ( (char **) (resultado[2]) )[0];
			instituicoes[0].obs =  ( (char **) (resultado[3]) )[0];
		}

		*inst = instituicoes;

		ret = 0;

		return ret;

	}
}


int bdTodasInstituicoes(Instituicao** insts, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idInstituicao, sigla, nome, obs "
			"FROM Instituicao");

	char props[150];

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*insts = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Instituicao* instituicoes = NULL;

		*num = numlins;

		if (numlins > 0) {

			instituicoes = (Instituicao *) malloc( numlins * sizeof(Instituicao) );

			for (int i = 0; i < numlins; i++) {

				instituicoes[i].idInstituicao = ( ( (long long int **) (resultado[0]) )[i]);
				instituicoes[i].sigla =  ( (char **) (resultado[1]) )[i];
				instituicoes[i].nome =  ( (char **) (resultado[2]) )[i];
				instituicoes[i].obs =  ( (char **) (resultado[3]) )[i];
			}

		}

		*insts = instituicoes;

		ret = 0;

		return ret;

	}
}


int bdBuscarCurso(char* codigo, char* nome, char* idInst, char* obs, Curso** cursos, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT C.idCurso, C.codigo, C.nome, C.idInstituicao, C.obs, I.sigla, I.nome, I.obs "
			"FROM Curso as C "
			"LEFT JOIN Instituicao as I ON C.idInstituicao = I.idInstituicao "
			"WHERE "
			);

	char props[150];

	if (strcmp(codigo, "")){ sprintf(props, "C.codigo like \'%%%s%%\' AND ", codigo); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(nome, "")){ sprintf(props, "C.nome like \'%%%s%%\' AND ", nome); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(idInst, "")){ sprintf(props, "C.idInstituicao = %s AND ", idInst); strcat(consulta, props); }
	else strcat(consulta, "FALSE AND ");

	if (strcmp(obs, "")){ sprintf(props, "C.obs like \'%%%s%%\'", obs); strcat(consulta, props); }
	else strcat(consulta, "TRUE");

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*cursos = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Curso* auxCursos = NULL;

		*num = numlins;

		if (numlins > 0) {

			auxCursos = (Curso *) malloc( numlins * sizeof(Curso) );

			for (int i = 0; i < numlins; i++) {
				auxCursos[i].inst = (Instituicao *) malloc( sizeof(Instituicao));

				auxCursos[i].idCurso = ( ( (long long int **) (resultado[0]) )[i]);
				auxCursos[i].codigo =  ( (char **) (resultado[1]) )[i];
				auxCursos[i].nome =  ( (char **) (resultado[2]) )[i];
				auxCursos[i].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[i]);
				auxCursos[i].obs =  ( (char **) (resultado[4]) )[i];

				auxCursos[i].inst->sigla = ( (char **) (resultado[5]) )[i];
				auxCursos[i].inst->nome = ( (char **) (resultado[6]) )[i];
				auxCursos[i].inst->obs = ( (char **) (resultado[7]) )[i];
			}

		}

		*cursos = auxCursos;

		ret = 0;

		return ret;

	}
}


int bdBuscarCursoId(char* idCurso, Curso** cursos, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT C.idCurso, C.codigo, C.nome, C.idInstituicao, C.obs, I.sigla, I.nome, I.obs "
			"FROM Curso as C "
			"LEFT JOIN Instituicao as I ON C.idInstituicao = I.idInstituicao "
			"WHERE C.idCurso = %s",
			idCurso);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*cursos = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Curso* auxCursos = NULL;

		*num = numlins;

		if (numlins > 0) {

			auxCursos = (Curso *) malloc( sizeof(Curso) );

			auxCursos[0].inst = (Instituicao *) malloc( sizeof(Instituicao));

			auxCursos[0].idCurso = ( ( (long long int **) (resultado[0]) )[0]);
			auxCursos[0].codigo =  ( (char **) (resultado[1]) )[0];
			auxCursos[0].nome =  ( (char **) (resultado[2]) )[0];
			auxCursos[0].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[0]);
			auxCursos[0].obs =  ( (char **) (resultado[4]) )[0];

			auxCursos[0].inst->sigla = ( (char **) (resultado[5]) )[0];
			auxCursos[0].inst->nome = ( (char **) (resultado[6]) )[0];
			auxCursos[0].inst->obs = ( (char **) (resultado[7]) )[0];

		}

		*cursos = auxCursos;

		ret = 0;

		return ret;

	}

}


int bdBuscarCursoCodigoSiglaInst(char* codigo, char* siglaInst, Curso** cursos, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT C.idCurso, C.codigo, C.nome, C.idInstituicao, C.obs, I.sigla, I.nome, I.obs "
			"FROM Curso as C "
			"LEFT JOIN Instituicao as I ON C.idInstituicao = I.idInstituicao "
			"WHERE C.codigo = \'%s\' and I.sigla = \'%s\' ",
			codigo, siglaInst);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*cursos = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Curso* auxCursos = NULL;

		*num = numlins;

		if (numlins > 0) {

			auxCursos = (Curso *) malloc( sizeof(Curso) );

			auxCursos[0].inst = (Instituicao *) malloc( sizeof(Instituicao));

			auxCursos[0].idCurso = ( ( (long long int **) (resultado[0]) )[0]);
			auxCursos[0].codigo =  ( (char **) (resultado[1]) )[0];
			auxCursos[0].nome =  ( (char **) (resultado[2]) )[0];
			auxCursos[0].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[0]);
			auxCursos[0].obs =  ( (char **) (resultado[4]) )[0];

			auxCursos[0].inst->sigla = ( (char **) (resultado[5]) )[0];
			auxCursos[0].inst->nome = ( (char **) (resultado[6]) )[0];
			auxCursos[0].inst->obs = ( (char **) (resultado[7]) )[0];

		}

		*cursos = auxCursos;

		ret = 0;

		return ret;

	}

}


int bdBuscarCursoIdInstituicao(char* idInst, Curso** cursos, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idCurso, codigo, nome, idInstituicao, obs "
			"FROM Curso "
			"WHERE idInstituicao = %s"
			, idInst);

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*cursos = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Curso* auxCursos = NULL;

		*num = numlins;

		if (numlins > 0) {

			auxCursos = (Curso *) malloc( numlins * sizeof(Curso) );

			for (int i = 0; i < numlins; i++) {
				//auxCursos[i].inst = (Instituicao *) malloc( sizeof(Instituicao));

				auxCursos[i].idCurso = ( ( (long long int **) (resultado[0]) )[i]);
				auxCursos[i].codigo =  ( (char **) (resultado[1]) )[i];
				auxCursos[i].nome =  ( (char **) (resultado[2]) )[i];
				//auxCursos[i].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[i]);
				auxCursos[i].obs =  ( (char **) (resultado[4]) )[i];
			}

		}

		*cursos = auxCursos;

		ret = 0;

		return ret;

	}

}


int bdBuscarDisciplina(char* codigo, char* nome, char* idInst, char* obs, Disciplina** disciplinas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT D.idDisciplina, D.codigo, D.nome, D.idInstituicao, D.obs, I.sigla, I.nome, I.obs "
			"FROM Disciplina as D "
			"LEFT JOIN Instituicao as I ON D.idInstituicao = I.idInstituicao "
			"WHERE "
			);

	char props[150];

	if (strcmp(codigo, "")){ sprintf(props, "D.codigo like \'%%%s%%\' AND ", codigo); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(nome, "")){ sprintf(props, "D.nome like \'%%%s%%\' AND ", nome); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(idInst, "")){ sprintf(props, "D.idInstituicao = %s AND ", idInst); strcat(consulta, props); }
	else strcat(consulta, "FALSE AND ");

	if (strcmp(obs, "")){ sprintf(props, "D.obs like \'%%%s%%\'", obs); strcat(consulta, props); }
	else strcat(consulta, "TRUE");

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*disciplinas = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Disciplina* discs = NULL;

		*num = numlins;

		if (numlins > 0) {

			discs = (Disciplina *) malloc( numlins * sizeof(Disciplina) );

			for (int i = 0; i < numlins; i++) {
				discs[i].inst = (Instituicao *) malloc( sizeof(Instituicao));

				discs[i].idDisciplina = ( ( (long long int **) (resultado[0]) )[i]);
				discs[i].codigo =  ( (char **) (resultado[1]) )[i];
				discs[i].nome =  ( (char **) (resultado[2]) )[i];
				discs[i].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[i]);
				discs[i].obs =  ( (char **) (resultado[4]) )[i];

				discs[i].inst->sigla = ( (char **) (resultado[5]) )[i];
				discs[i].inst->nome = ( (char **) (resultado[6]) )[i];
				discs[i].inst->obs = ( (char **) (resultado[7]) )[i];
			}

		}

		*disciplinas = discs;

		ret = 0;

		return ret;

	}
}


int bdBuscarDisciplinaId(char* idDisciplina, Disciplina** disciplinas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT D.idDisciplina, D.codigo, D.nome, D.idInstituicao, D.obs, I.sigla, I.nome, I.obs "
			"FROM Disciplina as D "
			"LEFT JOIN Instituicao as I ON D.idInstituicao = I.idInstituicao "
			"WHERE D.idDisciplina = %s",
			idDisciplina);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*disciplinas = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Disciplina* discs = NULL;

		*num = numlins;

		if (numlins > 0) {

			discs = (Disciplina *) malloc( sizeof(Disciplina) );

			discs[0].inst = (Instituicao *) malloc( sizeof(Instituicao));

			discs[0].idDisciplina = ( ( (long long int **) (resultado[0]) )[0]);
			discs[0].codigo =  ( (char **) (resultado[1]) )[0];
			discs[0].nome =  ( (char **) (resultado[2]) )[0];
			discs[0].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[0]);
			discs[0].obs =  ( (char **) (resultado[4]) )[0];

			discs[0].inst->sigla = ( (char **) (resultado[5]) )[0];
			discs[0].inst->nome = ( (char **) (resultado[6]) )[0];
			discs[0].inst->obs = ( (char **) (resultado[7]) )[0];

		}

		*disciplinas = discs;

		ret = 0;

		return ret;

	}

}


int bdBuscarDisciplinaIdInstituicao(char* idInstituicao, Disciplina** disciplinas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT D.idDisciplina, D.codigo, D.nome, D.idInstituicao, D.obs, I.sigla, I.nome, I.obs "
			"FROM Disciplina as D "
			"LEFT JOIN Instituicao as I ON D.idInstituicao = I.idInstituicao "
			"WHERE D.idInstituicao = %s",
			idInstituicao);

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*disciplinas = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Disciplina* discs = NULL;

		*num = numlins;

		if (numlins > 0) {

			discs = (Disciplina *) malloc( numlins * sizeof(Disciplina) );

			for (int i = 0; i < numlins; i++) {
				discs[i].inst = (Instituicao *) malloc( sizeof(Instituicao));

				discs[i].idDisciplina = ( ( (long long int **) (resultado[0]) )[i]);
				discs[i].codigo =  ( (char **) (resultado[1]) )[i];
				discs[i].nome =  ( (char **) (resultado[2]) )[i];
				discs[i].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[i]);
				discs[i].obs =  ( (char **) (resultado[4]) )[i];

				discs[i].inst->sigla = ( (char **) (resultado[5]) )[i];
				discs[i].inst->nome = ( (char **) (resultado[6]) )[i];
				discs[i].inst->obs = ( (char **) (resultado[7]) )[i];
			}

		}

		*disciplinas = discs;

		ret = 0;

		return ret;

	}

}


int bdBuscarUsuario(char* nome, char* login, char* email, char* adm, char* professor, char* habilitado, Usuario** usuarios, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idUsuario, nome, login, email, adm, professor, habilitado "
			"FROM Usuario "
			"WHERE "
			);

	char props[150];

	if (strcmp(nome, "")){ sprintf(props, "nome like \'%%%s%%\' AND ", nome); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(login, "")){ sprintf(props, "login like \'%%%s%%\' AND ", login); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(email, "")){ sprintf(props, "email like \'%%%s%%\' AND ", email); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(adm, "")){ sprintf(props, "adm = %s AND ", adm); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(professor, "")){ sprintf(props, "professor = %s AND ", professor); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(habilitado, "")){ sprintf(props, "habilitado = %s", habilitado); strcat(consulta, props); }
	else strcat(consulta, "TRUE");

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usuarios = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Usuario* usus = NULL;

		*num = numlins;

		if (numlins > 0) {

			usus = (Usuario *) malloc( numlins * sizeof(Usuario) );

			for (int i = 0; i < numlins; i++) {

				usus[i].idUsuario = ( ( (long long int **) (resultado[0]) )[i]);
				usus[i].nome =  ( (char **) (resultado[1]) )[i];
				usus[i].login =  ( (char **) (resultado[2]) )[i];
				usus[i].email = ( (char **) (resultado[3]) )[i];
				usus[i].adm =  ( (long long int **) (resultado[4]) )[i];
				usus[i].professor =  ( (long long int **) (resultado[5]) )[i];
				usus[i].habilitado =  ( (long long int **) (resultado[6]) )[i];
			}

		}

		*usuarios = usus;

		ret = 0;

		return ret;

	}

}


int bdBuscarUsuarioId(char* idUsuario, Usuario** usuarios, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idUsuario, nome, email, login, adm, professor, habilitado "
			"FROM Usuario "
			"WHERE idUsuario = %s",
			idUsuario);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usuarios = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Usuario* usus = NULL;

		*num = numlins;

		if (numlins > 0) {

			usus = (Usuario *) malloc( sizeof(Usuario) );

			usus[0].idUsuario = ( ( (long long int **) (resultado[0]) )[0]);
			usus[0].nome =  ( (char **) (resultado[1]) )[0];
			usus[0].email =  ( (char **) (resultado[2]) )[0];
			usus[0].login = ( (char **) (resultado[3]) )[0];;
			usus[0].adm =  ( (long long int **) (resultado[4]) )[0];
			usus[0].professor =  ( (long long int **) (resultado[5]) )[0];
			usus[0].habilitado =  ( (long long int **) (resultado[6]) )[0];

		}

		*usuarios = usus;

		ret = 0;

		return ret;

	}

}


int bdBuscarUsuarioLogin(char* login, Usuario** usuarios) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idUsuario, nome, login, senha, email, adm, professor, habilitado "
			"FROM Usuario "
			"WHERE login=\'%s\'"
			, login);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usuarios = NULL;

	if (ret) {
		return ret;
	}
	else {

		Usuario* usus = NULL;

		if (numlins > 0) {

			usus = (Usuario *) malloc( sizeof(Usuario) );

			usus[0].idUsuario = ( ( (long long int **) (resultado[0]) )[0]);
			usus[0].nome =  ( (char **) (resultado[1]) )[0];
			usus[0].login =  ( (char **) (resultado[2]) )[0];
			usus[0].senha =  ( (char **) (resultado[3]) )[0];
			usus[0].email = ( (char **) (resultado[4]) )[0];
			usus[0].adm =  ( (long long int **) (resultado[5]) )[0];
			usus[0].professor =  ( (long long int **) (resultado[6]) )[0];
			usus[0].habilitado =  ( (long long int **) (resultado[7]) )[0];

		}

		*usuarios = usus;

		ret = 0;

		return ret;

	}
}


int bdBuscarProfessorLogin(char* login, Usuario** professores) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idUsuario, nome, login, email, adm, professor, habilitado "
			"FROM Usuario "
			"WHERE login=\'%s\' AND professor = 1"
			, login);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*professores = NULL;

	if (ret) {
		return ret;
	}
	else {

		Usuario* usus = NULL;

		if (numlins > 0) {

			usus = (Usuario *) malloc( sizeof(Usuario) );

			usus[0].idUsuario = ( ( (long long int **) (resultado[0]) )[0]);
			usus[0].nome =  ( (char **) (resultado[1]) )[0];
			usus[0].login =  ( (char **) (resultado[2]) )[0];
			usus[0].email = ( (char **) (resultado[3]) )[0];;
			usus[0].adm =  ( (long long int **) (resultado[4]) )[0];
			usus[0].professor =  ( (long long int **) (resultado[5]) )[0];
			usus[0].habilitado =  ( (long long int **) (resultado[6]) )[0];

		}

		*professores = usus;

		ret = 0;

		return ret;

	}
}


int bdBuscarUsuarioPerfil(char* nome, char* login, char* email, char* matricula, char* idCurso, char* idInstituicao, Usuario** usuarios, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE ");

	char props[250];

	if (strcmp(nome, "")){ sprintf(props, "nomeUsuario like \'%%%s%%\' AND ", nome); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(login, "")){ sprintf(props, "login like \'%%%s%%\' AND ", login); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(email, "")){ sprintf(props, "email like \'%%%s%%\' AND ", email); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(matricula, "")){ sprintf(props, "matricula like \'%%%s%%\' AND ", matricula); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(idCurso, "")){ sprintf(props, "idCursoPerfilRespondedor = %s AND ", idCurso); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(idInstituicao, "")){ sprintf(props, "idInstituicaoCurso = %s ", idInstituicao); strcat(consulta, props); }
	else strcat(consulta, "TRUE ");

	strcat(consulta, "ORDER BY idUsuario");


	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usus = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		Usuario* usuario = NULL;
		while (i < numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

				idUsuario = *( ( (long long int **) (resultado[0]) )[i]);

				numUsus++;

				usus = (Usuario *) realloc(usus, numUsus * (sizeof(Usuario)));

				usuario = &(usus[numUsus - 1]);

				// resgatar informações sobre usuario

				usuario->idUsuario = ( (long long int **) (resultado[0]) )[i];
				usuario->nome = ( (char **) (resultado[1]) )[i];
				usuario->login = ( (char **) (resultado[2]) )[i];
				usuario->email = ( (char **) (resultado[3]) )[i];
				usuario->numPerfis = 0;
				usuario->perfis = NULL;

			}


			// incrementar contador de perfil do usuario atual
			usuario->numPerfis++;

			// alocar espaço para o novo perfil
			usuario->perfis = (PerfilRespondedor *) realloc(usuario->perfis, usuario->numPerfis * sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = &(usuario->perfis[usuario->numPerfis - 1]);

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[i];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[i];
			pr->matricula = ( (char **) (resultado[5]) )[i];
			pr->usu = &(usus[numUsus - 1]);

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[i];
			curso->codigo = ( (char **) (resultado[9]) )[i];
			curso->nome = ( (char **) (resultado[10]) )[i];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[i];
			instCurso->sigla = ( (char **) (resultado[12]) )[i];
			instCurso->nome = ( (char **) (resultado[13]) )[i];
			// instCurso->obs (não precisa)

			i++;

		}

		*usuarios = usus;
		*num = numUsus;

		return ret;

	}

}


int bdBuscarUsuarioPerfilId(char* idUsuario, char* idPerfil, Usuario** usuarioPerfil, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE U.idUsuario = %s AND PR.idPerfilRespondedor = %s"
			, idUsuario, idPerfil);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usu = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		if (numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[0]);

			numUsus++;

			usu = (Usuario *) malloc((sizeof(Usuario)));

			//usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usu->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usu->nome = ( (char **) (resultado[1]) )[i];
			usu->login = ( (char **) (resultado[2]) )[i];
			usu->email = ( (char **) (resultado[3]) )[i];
			usu->numPerfis = 1;
			usu->perfis = NULL;

			//}

			// alocar espaço para o novo perfil
			usu->perfis = (PerfilRespondedor *) malloc(sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = usu->perfis;

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[0];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[0];
			pr->matricula = ( (char **) (resultado[5]) )[0];
			pr->habilitado = ( (long long int **) (resultado[7]) )[0];
			pr->obs = ( (char **) (resultado[8]) )[0];
			pr->usu = usu;

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[0];
			curso->codigo = ( (char **) (resultado[9]) )[0];
			curso->nome = ( (char **) (resultado[10]) )[0];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[0];
			instCurso->sigla = ( (char **) (resultado[12]) )[0];
			instCurso->nome = ( (char **) (resultado[13]) )[0];
			// instCurso->obs (não precisa)

		}

		*usuarioPerfil = usu;
		*num = numUsus;

		return ret;

	}

}



int bdBuscarUsuarioPerfilId2(char* idPerfil, Usuario** usuarioPerfil) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.idPerfilRespondedor = %s"
			, idPerfil);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usu = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		if (numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[0]);

			numUsus++;

			usu = (Usuario *) malloc((sizeof(Usuario)));

			//usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usu->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usu->nome = ( (char **) (resultado[1]) )[i];
			usu->login = ( (char **) (resultado[2]) )[i];
			usu->email = ( (char **) (resultado[3]) )[i];
			usu->numPerfis = 1;
			usu->perfis = NULL;

			//}

			// alocar espaço para o novo perfil
			usu->perfis = (PerfilRespondedor *) malloc(sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = usu->perfis;

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[0];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[0];
			pr->matricula = ( (char **) (resultado[5]) )[0];
			pr->habilitado = ( (long long int **) (resultado[7]) )[0];
			pr->obs = ( (char **) (resultado[8]) )[0];
			pr->usu = usu;

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[0];
			curso->codigo = ( (char **) (resultado[9]) )[0];
			curso->nome = ( (char **) (resultado[10]) )[0];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[0];
			instCurso->sigla = ( (char **) (resultado[12]) )[0];
			instCurso->nome = ( (char **) (resultado[13]) )[0];
			// instCurso->obs (não precisa)

		}

		*usuarioPerfil = usu;


		return ret;

	}

}



int bdBuscarUsuarioPerfilMatriculaCodCursoSiglaInst(char* matricula, char* codCurso, char* siglaInst, Usuario** usuario, int* num)  {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.senha as senha, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.matricula = \'%s\' AND C.codigo = \'%s\' AND IC.sigla = \'%s\' "
			, matricula, codCurso, siglaInst);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usu = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		if (numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[0]);

			numUsus++;

			usu = (Usuario *) malloc((sizeof(Usuario)));

			//usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usu->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usu->nome = ( (char **) (resultado[1]) )[i];
			usu->login = ( (char **) (resultado[2]) )[i];
			usu->senha = ( (char **) (resultado[3]) )[i];
			usu->email = ( (char **) (resultado[4]) )[i];
			usu->numPerfis = 1;
			usu->perfis = NULL;

			//}

			// alocar espaço para o novo perfil
			usu->perfis = (PerfilRespondedor *) malloc(sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = usu->perfis;

			pr->idPerfilRespondedor = ( (long long int **) (resultado[5]) )[0];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[0];
			pr->matricula = ( (char **) (resultado[6]) )[0];
			pr->habilitado = ( (long long int **) (resultado[8]) )[0];
			pr->obs = ( (char **) (resultado[9]) )[0];
			pr->usu = usu;

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[7]) )[0];
			curso->codigo = ( (char **) (resultado[10]) )[0];
			curso->nome = ( (char **) (resultado[11]) )[0];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[12]) )[0];
			instCurso->sigla = ( (char **) (resultado[13]) )[0];
			instCurso->nome = ( (char **) (resultado[14]) )[0];
			// instCurso->obs (não precisa)

		}

		*usuario = usu;
		*num = numUsus;

		return ret;

	}

}



int bdBuscarUsuarioPerfilMatriculaCodCursoSiglaInst2(char* matricula, char* codCurso, char* siglaInst, Usuario** usuario, int* num)  {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.senha as senha, U.email as email, U.adm as adm, U.professor as professor, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.matricula = \'%s\' AND C.codigo = \'%s\' AND IC.sigla = \'%s\' "
			, matricula, codCurso, siglaInst);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usu = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		if (numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[0]);

			numUsus++;

			usu = (Usuario *) malloc((sizeof(Usuario)));

			//usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usu->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usu->nome = ( (char **) (resultado[1]) )[i];
			usu->login = ( (char **) (resultado[2]) )[i];
			usu->senha = ( (char **) (resultado[3]) )[i];
			usu->email = ( (char **) (resultado[4]) )[i];
			usu->adm = ( (long long int **) (resultado[5]) )[i];
			usu->professor = ( (long long int **) (resultado[6]) )[i];

			usu->numPerfis = 1;
			usu->perfis = NULL;

			//}

			// alocar espaço para o novo perfil
			usu->perfis = (PerfilRespondedor *) malloc(sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = usu->perfis;

			pr->idPerfilRespondedor = ( (long long int **) (resultado[7]) )[0];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[0];
			pr->matricula = ( (char **) (resultado[8]) )[0];
			pr->habilitado = ( (long long int **) (resultado[10]) )[0];
			pr->obs = ( (char **) (resultado[11]) )[0];
			pr->usu = usu;

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[9]) )[0];
			curso->codigo = ( (char **) (resultado[12]) )[0];
			curso->nome = ( (char **) (resultado[13]) )[0];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[14]) )[0];
			instCurso->sigla = ( (char **) (resultado[15]) )[0];
			instCurso->nome = ( (char **) (resultado[16]) )[0];
			// instCurso->obs (não precisa)

		}

		*usuario = usu;
		*num = numUsus;

		return ret;

	}

}




int bdBuscarUsuarioPerfilMatriculaIdCurso(char* matricula, char* idCurso, Usuario** usuario)  {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.matricula = \'%s\' AND C.idCurso = %s "
			, matricula, idCurso);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usu = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		if (numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[0]);

			numUsus++;

			usu = (Usuario *) malloc((sizeof(Usuario)));

			//usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usu->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usu->nome = ( (char **) (resultado[1]) )[i];
			usu->login = ( (char **) (resultado[2]) )[i];
			usu->email = ( (char **) (resultado[3]) )[i];
			usu->numPerfis = 1;
			usu->perfis = NULL;

			//}

			// alocar espaço para o novo perfil
			usu->perfis = (PerfilRespondedor *) malloc(sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = usu->perfis;

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[0];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[0];
			pr->matricula = ( (char **) (resultado[5]) )[0];
			pr->habilitado = ( (long long int **) (resultado[7]) )[0];
			pr->obs = ( (char **) (resultado[8]) )[0];
			pr->usu = usu;

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[0];
			curso->codigo = ( (char **) (resultado[9]) )[0];
			curso->nome = ( (char **) (resultado[10]) )[0];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[0];
			instCurso->sigla = ( (char **) (resultado[12]) )[0];
			instCurso->nome = ( (char **) (resultado[13]) )[0];
			// instCurso->obs (não precisa)

		}

		*usuario = usu;

		return ret;

	}

}


int bdBuscarUsuarioPerfilIdPerfilRespondedor(char* idPerfilRespondedor, Usuario** usuario) {


	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.idPerfilRespondedor = \'%s\'"
			, idPerfilRespondedor);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usu = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		if (numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[0]);

			numUsus++;

			usu = (Usuario *) malloc((sizeof(Usuario)));

			//usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usu->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usu->nome = ( (char **) (resultado[1]) )[i];
			usu->login = ( (char **) (resultado[2]) )[i];
			usu->email = ( (char **) (resultado[3]) )[i];
			usu->numPerfis = 1;
			usu->perfis = NULL;

			//}

			// alocar espaço para o novo perfil
			usu->perfis = (PerfilRespondedor *) malloc(sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = usu->perfis;

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[0];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[0];
			pr->matricula = ( (char **) (resultado[5]) )[0];
			pr->habilitado = ( (long long int **) (resultado[7]) )[0];
			pr->obs = ( (char **) (resultado[8]) )[0];
			pr->usu = usu;

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[0];
			curso->codigo = ( (char **) (resultado[9]) )[0];
			curso->nome = ( (char **) (resultado[10]) )[0];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[0];
			instCurso->sigla = ( (char **) (resultado[12]) )[0];
			instCurso->nome = ( (char **) (resultado[13]) )[0];
			// instCurso->obs (não precisa)

		}

		*usuario = usu;

		return ret;

	}

}


int bdBuscarTurma(char* idInstituicao, char* idDisciplina, char* codigo, char* professor, char* descricao, char* ano, char* semestre, char* encerrada, char* obs, Turma** turmas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			"INNER JOIN Professor_Turma as PT on T.idTurma = PT.idTurma "
			"INNER JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "
			"WHERE "
	);

	char props[250];

	if (strcmp(idInstituicao, "")){ sprintf(props, "D.idInstituicao = %s AND ", idInstituicao); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(idDisciplina, "")){ sprintf(props, "T.idDisciplina = %s AND ", idDisciplina); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(codigo, "")){ sprintf(props, "T.codigo like \'%%%s%%\' AND ", codigo); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(professor, "")){ sprintf(props, "U.nome like \'%%%s%%\' AND ", professor); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(descricao, "")){ sprintf(props, "T.descricao like \'%%%s%%\' AND ", descricao); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(ano, "")){ sprintf(props, "T.ano = %s AND ", ano); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(semestre, "")){ sprintf(props, "T.semestre = %s AND ", semestre); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(encerrada, "0")){ sprintf(props, "T.encerrada = 1 AND "); strcat(consulta, props); }
	else strcat(consulta, "T.encerrada = 0 AND ");

	if (strcmp(obs, "")){ sprintf(props, "T.obs = \'%s\' ", obs); strcat(consulta, props); }
	else strcat(consulta, "TRUE ");


	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Turma* turs = NULL;
	int numTurmas = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		turs = (Turma *) malloc(numlins * sizeof(Turma));

		for (i = 0; i < numlins; i++) {

			turs[i].idTurma = ( (long long int **) (resultado[0]) )[i];
			turs[i].idDisciplina = ( (long long int **) (resultado[1]) )[i];
			turs[i].codigo = ( (char **) (resultado[2]) )[i];
			turs[i].idProfCriador = ( (long long int **) (resultado[3]) )[i];
			turs[i].descricao = ( (char **) (resultado[4]) )[i];
			turs[i].ano = ( (char **) (resultado[5]) )[i];
			turs[i].semestre = ( (char **) (resultado[6]) )[i];
			turs[i].encerrada = ( (int **) (resultado[7]) )[i];
			turs[i].obs = ( (char **) (resultado[8]) )[i];

			turs[i].disc = (Disciplina *) malloc(sizeof(Disciplina));

			turs[i].disc->codigo = ( (char **) (resultado[9]) )[i];
			turs[i].disc->nome = ( (char **) (resultado[10]) )[i];

			turs[i].disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			turs[i].disc->inst->sigla = ( (char **) (resultado[11]) )[i];
			turs[i].disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[i];
		}

		*turmas = turs;
		*num = numlins;

		return ret;
	}

}


int bdBuscarTurma2(char* idInstituicao, char* idDisciplina, char* codigo, char* idProfCriador, char* professor, char* descricao, char* ano, char* semestre, char* encerrada, char* obs, Turma** turmas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT DISTINCT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			"LEFT JOIN Professor_Turma as PT on T.idTurma = PT.idTurma "
			"LEFT JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "
			"WHERE T.idProfCriador = %s AND ",
			idProfCriador);

	char props[250];

	if (strcmp(idInstituicao, "")){ sprintf(props, "D.idInstituicao = %s AND ", idInstituicao); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(idDisciplina, "")){ sprintf(props, "T.idDisciplina = %s AND ", idDisciplina); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(codigo, "")){ sprintf(props, "T.codigo like \'%%%s%%\' AND ", codigo); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(professor, "")){ sprintf(props, "U.nome like \'%%%s%%\' AND ", professor); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(descricao, "")){ sprintf(props, "T.descricao like \'%%%s%%\' AND ", descricao); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(ano, "")){ sprintf(props, "T.ano = %s AND ", ano); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(semestre, "")){ sprintf(props, "T.semestre = %s AND ", semestre); strcat(consulta, props); }
	else strcat(consulta, "TRUE AND ");

	if (strcmp(encerrada, "0")){ sprintf(props, "T.encerrada = 1 AND "); strcat(consulta, props); }
	else strcat(consulta, "T.encerrada = 0 AND ");

	if (strcmp(obs, "")){ sprintf(props, "T.obs = \'%s\' ", obs); strcat(consulta, props); }
	else strcat(consulta, "TRUE ");


	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Turma* turs = NULL;
	int numTurmas = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		turs = (Turma *) malloc(numlins * sizeof(Turma));

		for (i = 0; i < numlins; i++) {

			turs[i].idTurma = ( (long long int **) (resultado[0]) )[i];
			turs[i].idDisciplina = ( (long long int **) (resultado[1]) )[i];
			turs[i].codigo = ( (char **) (resultado[2]) )[i];
			turs[i].idProfCriador = ( (long long int **) (resultado[3]) )[i];
			turs[i].descricao = ( (char **) (resultado[4]) )[i];
			turs[i].ano = ( (char **) (resultado[5]) )[i];
			turs[i].semestre = ( (char **) (resultado[6]) )[i];
			turs[i].encerrada = ( (int **) (resultado[7]) )[i];
			turs[i].obs = ( (char **) (resultado[8]) )[i];

			turs[i].disc = (Disciplina *) malloc(sizeof(Disciplina));

			turs[i].disc->codigo = ( (char **) (resultado[9]) )[i];
			turs[i].disc->nome = ( (char **) (resultado[10]) )[i];

			turs[i].disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			turs[i].disc->inst->sigla = ( (char **) (resultado[11]) )[i];
			turs[i].disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[i];
		}

		*turmas = turs;
		*num = numlins;

		return ret;
	}

}


int bdBuscarTurmaId(char* idTurma, Turma** turmas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			//"LEFT JOIN Professor_Turma as PT on T.idTurma = PT.idTurma "
			//"LEFT JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "
			"WHERE T.idTurma = %s",
	idTurma);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Turma* turs = NULL;
	int numTurmas = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		turs = (Turma *) malloc(numlins * sizeof(Turma));

		if (numlins) {
		//for (i = 0; i < numlins; i++) {

			turs[i].idTurma = ( (long long int **) (resultado[0]) )[i];
			turs[i].idDisciplina = ( (long long int **) (resultado[1]) )[i];
			turs[i].codigo = ( (char **) (resultado[2]) )[i];
			turs[i].idProfCriador = ( (long long int **) (resultado[3]) )[i];
			turs[i].descricao = ( (char **) (resultado[4]) )[i];
			turs[i].ano = ( (char **) (resultado[5]) )[i];
			turs[i].semestre = ( (char **) (resultado[6]) )[i];
			turs[i].encerrada = ( (int **) (resultado[7]) )[i];
			turs[i].obs = ( (char **) (resultado[8]) )[i];

			turs[i].disc = (Disciplina *) malloc(sizeof(Disciplina));

			turs[i].disc->codigo = ( (char **) (resultado[9]) )[i];
			turs[i].disc->nome = ( (char **) (resultado[10]) )[i];

			turs[i].disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			turs[i].disc->inst->sigla = ( (char **) (resultado[11]) )[i];
			turs[i].disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[i];
		}


		*turmas = turs;
		*num = numlins;

		return ret;
	}


}

int bdBuscarProfPartIdTurma(char* idTurma, Usuario** usuarios, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario, U.nome, U.login, U.email, U.adm, U.professor, U.habilitado "
			"FROM Usuario as U "
			"INNER JOIN Professor_Turma as PT ON U.idUsuario = PT.idUsuario "
			"WHERE PT.idTurma = \'%s\'"
			, idTurma);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usus = NULL;
	int numUsus = 0;

	if (ret) {
		return ret;
	}
	else {
		int i = 0;

		if (numlins > 0) {

			usus = (Usuario *) malloc(numlins * sizeof(Usuario));

			for (i = 0; i < numlins; i++) {

				usus[i].idUsuario = ( ( (long long int **) (resultado[0]) )[i]);
				usus[i].nome =  ( (char **) (resultado[1]) )[i];
				usus[i].login =  ( (char **) (resultado[2]) )[i];
				usus[i].email = ( (char **) (resultado[3]) )[i];
				usus[i].adm =  ( (long long int **) (resultado[4]) )[i];
				usus[i].professor =  ( (long long int **) (resultado[5]) )[i];
				usus[i].habilitado =  ( (long long int **) (resultado[6]) )[i];
			}
		}

		*usuarios = usus;
		*num = numlins;

		return ret;
	}
}


int bdMinhasTurmas(char* idProf, Turma** turmas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT DISTINCT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			"LEFT JOIN Professor_Turma as PT on T.idTurma = PT.idTurma "
			"LEFT JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "
			"WHERE T.idProfCriador = %s OR PT.idUsuario = %s ",
			idProf, idProf);

	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Turma* turs = NULL;
	int numTurmas = 0;


	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		turs = (Turma *) malloc(numlins * sizeof(Turma));

		for (i = 0; i < numlins; i++) {

			turs[i].idTurma = ( (long long int **) (resultado[0]) )[i];
			turs[i].idDisciplina = ( (long long int **) (resultado[1]) )[i];
			turs[i].codigo = ( (char **) (resultado[2]) )[i];
			turs[i].idProfCriador = ( (long long int **) (resultado[3]) )[i];
			turs[i].descricao = ( (char **) (resultado[4]) )[i];
			turs[i].ano = ( (char **) (resultado[5]) )[i];
			turs[i].semestre = ( (char **) (resultado[6]) )[i];
			turs[i].encerrada = ( (int **) (resultado[7]) )[i];
			turs[i].obs = ( (char **) (resultado[8]) )[i];

			turs[i].disc = (Disciplina *) malloc(sizeof(Disciplina));

			turs[i].disc->codigo = ( (char **) (resultado[9]) )[i];
			turs[i].disc->nome = ( (char **) (resultado[10]) )[i];

			turs[i].disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			turs[i].disc->inst->sigla = ( (char **) (resultado[11]) )[i];
			turs[i].disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[i];
		}

		*turmas = turs;
		*num = numlins;

		return ret;
	}

}


int bdBuscarTurmaId2(char* idTurma, Turma** turma) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT DISTINCT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			//"LEFT JOIN Professor_Turma as PT on T.idTurma = PT.idTurma "
			//"LEFT JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "
			"WHERE T.idTurma = %s",
			idTurma);

	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Turma* tur = NULL;
	//int numTurmas = 0;


	if (ret) {

		return ret;
	}
	else {

		if (numlins) {

			tur = (Turma *) malloc(sizeof(Turma));

			tur->idTurma = ( (long long int **) (resultado[0]) )[0];
			tur->idDisciplina = ( (long long int **) (resultado[1]) )[0];
			tur->codigo = ( (char **) (resultado[2]) )[0];
			tur->idProfCriador = ( (long long int **) (resultado[3]) )[0];
			tur->descricao = ( (char **) (resultado[4]) )[0];
			tur->ano = ( (char **) (resultado[5]) )[0];
			tur->semestre = ( (char **) (resultado[6]) )[0];
			tur->encerrada = ( (int **) (resultado[7]) )[0];
			tur->obs = ( (char **) (resultado[8]) )[0];

			tur->disc = (Disciplina *) malloc(sizeof(Disciplina));

			tur->disc->codigo = ( (char **) (resultado[9]) )[0];
			tur->disc->nome = ( (char **) (resultado[10]) )[0];

			tur->disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			tur->disc->inst->sigla = ( (char **) (resultado[11]) )[0];
			tur->disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[0];
		}

		*turma = tur;

		return ret;
	}
}


int bdBuscarProfsTurmaId(char* idTurma, char* idProfCriador, Usuario** usuarios, int* num) {


	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario, U.nome, U.login, U.email, U.adm, U.professor, U.habilitado "
			"FROM Usuario AS U "
			"WHERE U.idUsuario = %s OR idUsuario IN (SELECT PT.idUsuario "
													"FROM Professor_Turma AS PT "
													"WHERE PT.idTurma = %s)",
			idProfCriador, idTurma);

	//printf("%s",consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usuarios = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		Usuario* usus = NULL;

		*num = numlins;

		if (numlins > 0) {

			usus = (Usuario *) malloc( numlins * sizeof(Usuario) );

			for (int i = 0; i < numlins; i++) {

				usus[i].idUsuario = ( ( (long long int **) (resultado[0]) )[i]);
				usus[i].nome =  ( (char **) (resultado[1]) )[i];
				usus[i].login =  ( (char **) (resultado[2]) )[i];
				usus[i].email = ( (char **) (resultado[3]) )[i];
				usus[i].adm =  ( (long long int **) (resultado[4]) )[i];
				usus[i].professor =  ( (long long int **) (resultado[5]) )[i];
				usus[i].habilitado =  ( (long long int **) (resultado[6]) )[i];
			}

			*usuarios = usus;
			*num = numlins;
		}

		ret = 0;

		return ret;

	}

}

int bdBuscarRespondedoresTurmaId(char* idTurma, Usuario** usuarios, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
			"INNER JOIN PerfilRespondedor_Turma as PRT ON PRT.idPerfilRespondedor = PR.idPerfilRespondedor "
			"INNER JOIN Turma as T ON T.idTurma = PRT.idTurma "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE T.idTurma = %s",
			idTurma);


	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usus = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		Usuario* usuario = NULL;
		while (i < numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

				idUsuario = *( ( (long long int **) (resultado[0]) )[i]);

				numUsus++;

				usus = (Usuario *) realloc(usus, numUsus * (sizeof(Usuario)));

				usuario = &(usus[numUsus - 1]);

				// resgatar informações sobre usuario

				usuario->idUsuario = ( (long long int **) (resultado[0]) )[i];
				usuario->nome = ( (char **) (resultado[1]) )[i];
				usuario->login = ( (char **) (resultado[2]) )[i];
				usuario->email = ( (char **) (resultado[3]) )[i];
				usuario->numPerfis = 0;
				usuario->perfis = NULL;

			}


			// incrementar contador de perfil do usuario atual
			usuario->numPerfis++;

			// alocar espaço para o novo perfil
			usuario->perfis = (PerfilRespondedor *) realloc(usuario->perfis, usuario->numPerfis * sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = &(usuario->perfis[usuario->numPerfis - 1]);

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[i];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[i];
			pr->matricula = ( (char **) (resultado[5]) )[i];
			pr->usu = &(usus[numUsus - 1]);

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[i];
			curso->codigo = ( (char **) (resultado[9]) )[i];
			curso->nome = ( (char **) (resultado[10]) )[i];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[i];
			instCurso->sigla = ( (char **) (resultado[12]) )[i];
			instCurso->nome = ( (char **) (resultado[13]) )[i];
			// instCurso->obs (não precisa)

			i++;

		}

		*usuarios = usus;
		*num = numUsus;

		return ret;

	}


}



int bdBuscarTrabalhosTurmaId(char* idTurma, Trabalho** trabalhos, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTrabalho, T.idTurma, T.numTrabalho, T.titulo, T.descricao, T.segHoraCriacao, T.segHoraInicio, T.segHoraFim, T.oculto, T.obs "
			"FROM Trabalho as T "
			"WHERE T.idTurma = %s "
			"ORDER BY T.numTrabalho",
			idTurma);

	//printf("%s", consulta);



	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Trabalho* trabs = NULL;
	int numTrabs = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		if (numlins) {

			trabs = (Trabalho *) malloc(numlins * sizeof(Trabalho));

			for (int i = 0; i < numlins; i++) {

				trabs[i].idTrabalho = ( (long long int **) (resultado[0]) )[i];
				trabs[i].idTurma = ( (long long int **) (resultado[1]) )[i];
				trabs[i].numTrabalho = ( (int **) (resultado[2]) )[i];
				trabs[i].titulo = ( (char **) (resultado[3]) )[i];
				trabs[i].descricao = ( (char **) (resultado[4]) )[i];
				trabs[i].segHoraCriacao = ( (long long int **) (resultado[5]) )[i];
				trabs[i].segHoraInicio = ( (long long int **) (resultado[6]) )[i];
				trabs[i].segHoraFim = ( (long long int **) (resultado[7]) )[i];
				trabs[i].oculto = ( (int **) (resultado[8]) )[i];
				trabs[i].obs = ( (char **) (resultado[9]) )[i];
			}
		}

		*trabalhos = trabs;
		*num = numlins;

		return ret;
	}
}


int bdBuscarTrabalhoId(char* idTrabalho, Trabalho** trabalho, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTrabalho, T.idTurma, T.numTrabalho, T.titulo, T.descricao, T.segHoraCriacao, T.segHoraInicio, T.segHoraFim, T.oculto, T.obs "
			"FROM Trabalho as T "
			"WHERE T.idTrabalho = %s",
			idTrabalho);

	//printf("%s", consulta);



	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Trabalho* trab = NULL;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		if (numlins) {

			trab = (Trabalho *) malloc(numlins * sizeof(Trabalho));

				trab->idTrabalho = ( (long long int **) (resultado[0]) )[0];
				trab->idTurma = ( (long long int **) (resultado[1]) )[0];
				trab->numTrabalho = ( (int **) (resultado[2]) )[0];
				trab->titulo = ( (char **) (resultado[3]) )[0];
				trab->descricao = ( (char **) (resultado[4]) )[0];
				trab->segHoraCriacao = ( (long long int **) (resultado[5]) )[0];
				trab->segHoraInicio = ( (long long int **) (resultado[6]) )[0];
				trab->segHoraFim = ( (long long int **) (resultado[7]) )[0];
				trab->oculto = ( (int **) (resultado[8]) )[0];
				trab->obs = ( (char **) (resultado[9]) )[0];

		}

		*trabalho = trab;
		*num = numlins;

		return ret;
	}
}

int bdBuscarTrabalhoIdUsuario(char* idTrabalho, char* idUsuario, Trabalho** trabalho, long long int* idPerfilRespondedor, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTrabalho, T.idTurma, T.numTrabalho, T.titulo, T.descricao, T.segHoraCriacao, T.segHoraInicio, T.segHoraFim, T.oculto, T.obs, PR.idPerfilRespondedor "
			"FROM Trabalho as T "
			"INNER JOIN PerfilRespondedor_Turma as PRT "
			"INNER JOIN PerfilRespondedor as PR "
			"WHERE T.idTrabalho = %s "
			"	AND PRT.idTurma = T.idTurma "
			"	AND PRT.idPerfilRespondedor = PR.idPerfilRespondedor "
			"	AND PR.idUsuario = %s",
			idTrabalho,
			idUsuario);

	//printf("%s" consulta);



	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Trabalho* trab = NULL;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		if (numlins) {

			trab = (Trabalho *) malloc(numlins * sizeof(Trabalho));

				trab->idTrabalho = ( (long long int **) (resultado[0]) )[0];
				trab->idTurma = ( (long long int **) (resultado[1]) )[0];
				trab->numTrabalho = ( (int **) (resultado[2]) )[0];
				trab->titulo = ( (char **) (resultado[3]) )[0];
				trab->descricao = ( (char **) (resultado[4]) )[0];
				trab->segHoraCriacao = ( (long long int **) (resultado[5]) )[0];
				trab->segHoraInicio = ( (long long int **) (resultado[6]) )[0];
				trab->segHoraFim = ( (long long int **) (resultado[7]) )[0];
				trab->oculto = ( (int **) (resultado[8]) )[0];
				trab->obs = ( (char **) (resultado[9]) )[0];

			*idPerfilRespondedor = *(( (long long int **) (resultado[10]) )[0]);

		}

		*trabalho = trab;
		*num = numlins;

		return ret;
	}
}



int bdBuscarItensTarefaIdTrabalho(char* idTrabalho, ItemTarefa** itenstarefa, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT IT.idItemTarefa, IT.idTarefa, IT.idTrabalho, IT.numItemTarefa, T.tipo, T.titulo, T.descricao, T.obs "
			"FROM ItemTarefa as IT "
			"INNER JOIN Tarefa as T ON IT.idTarefa = T.idTarefa "
			"WHERE IT.idTrabalho = %s "
			"ORDER BY IT.numItemTarefa",
			idTrabalho);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	ItemTarefa* it = NULL;

	if (ret) {

		return ret;
	}
	else {

		if (numlins) {

			it = (ItemTarefa *) malloc(numlins * sizeof(ItemTarefa));

			for (int i = 0; i < numlins; i++) {

				it[i].idItemTarefa = ( (long long int **) (resultado[0]) )[i];
				it[i].idTarefa = ( (long long int **) (resultado[1]) )[i];
				it[i].idTrabalho = ( (long long int **) (resultado[2]) )[i];
				it[i].numItemTarefa = ( (int **) (resultado[3]) )[i];

				it[i].tarefa = (Tarefa *) malloc(sizeof(Tarefa));

				it[i].tarefa->idTarefa = ( (long long int **) (resultado[1]) )[i];
				it[i].tarefa->tipo = ( (int **) (resultado[4]) )[i];
				it[i].tarefa->titulo = ( (char **) (resultado[5]) )[i];
				it[i].tarefa->descricao = ( (char **) (resultado[6]) )[i];
				it[i].tarefa->obs = ( (char **) (resultado[7]) )[i];

			}

		}

		*itenstarefa = it;
		*num = numlins;

		return ret;
	}
}


int bdNumeroItensTarefaIdTrabalho(char* idTrabalho, int* numItensTarefa) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT COUNT(IT.idItemTarefa) "
			"FROM ItemTarefa as IT "
			"INNER JOIN Tarefa as T ON IT.idTarefa = T.idTarefa "
			"WHERE IT.idTrabalho = %s",
			idTrabalho);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret) {

		return ret;
	}
	else {

		if (numlins) {
			*numItensTarefa = *(( (int **) (resultado[0]) )[0]);

			return ret;
		}
	}

}


int bdBuscarItensTarefaId(char* idItemTarefa, ItemTarefa** itemtarefa, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT IT.idItemTarefa, IT.idTarefa, IT.idTrabalho, IT.numItemTarefa, T.tipo, T.titulo, T.descricao, T.obs "
			"FROM ItemTarefa as IT "
			"INNER JOIN Tarefa as T ON IT.idTarefa = T.idTarefa "
			"WHERE IT.idItemTarefa = %s",
			idItemTarefa);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	ItemTarefa* it = NULL;

	if (ret) {

		return ret;
	}
	else {

		if (numlins) {

			it = (ItemTarefa *) malloc(numlins * sizeof(ItemTarefa));

			//for (int i = 0; i < numlins; i++) {

				it->idItemTarefa = ( (long long int **) (resultado[0]) )[0];
				it->idTarefa = ( (long long int **) (resultado[1]) )[0];
				it->idTrabalho = ( (long long int **) (resultado[2]) )[0];
				it->numItemTarefa = ( (int **) (resultado[3]) )[0];

				it->tarefa = (Tarefa *) malloc(sizeof(Tarefa));

				it->tarefa->idTarefa = ( (long long int **) (resultado[1]) )[0];
				it->tarefa->tipo = ( (int **) (resultado[4]) )[0];
				it->tarefa->titulo = ( (char **) (resultado[5]) )[0];
				it->tarefa->descricao = ( (char **) (resultado[6]) )[0];
				it->tarefa->obs = ( (char **) (resultado[7]) )[0];

			//}

		}

		*itemtarefa = it;
		*num = numlins;

		return ret;
	}
}


int bdContarItensDaTarefaId(char* idTarefa, int* numItens) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT COUNT(*) "
			"FROM ItemTarefa "
			"WHERE idTarefa = %s",
			idTarefa);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret) {

		return ret;
	}
	else {

		*numItens = 0;

		if (numlins) {

			//for (int i = 0; i < numlins; i++) {

				*(numItens) = *(( (long long int **) (resultado[0]) )[0]);

		}

		return ret;
	}

}


int bdContarItensDaTarefaDoItemId(char* idItemTarefa, int* numItens) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT COUNT(*) "
			"FROM ItemTarefa "
			"WHERE idTarefa IN (SELECT idTarefa FROM ItemTarefa WHERE idItemTarefa = %s)",
			idItemTarefa);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret) {

		return ret;
	}
	else {

		*numItens = 0;

		if (numlins) {

			//for (int i = 0; i < numlins; i++) {

				*(numItens) = *(( (long long int **) (resultado[0]) )[0]);

		}

		return ret;
	}

}




int bdBuscarTarefaId(char* idTarefa, Tarefa** tarefa, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idTarefa, tipo, titulo, descricao, obs "
			"FROM Tarefa "
			"WHERE idTarefa = %s",
			idTarefa);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Tarefa* tar = NULL;

	if (ret) {

		return ret;
	}
	else {

		if (numlins) {

			tar = (Tarefa *) malloc(numlins * sizeof(Tarefa));

			//for (int i = 0; i < numlins; i++) {

				tar->idTarefa = ( (long long int **) (resultado[0]) )[0];
				tar->tipo = ( (int **) (resultado[1]) )[0];
				tar->titulo = ( (char **) (resultado[2]) )[0];
				tar->descricao = ( (char **) (resultado[3]) )[0];
				tar->obs = ( (char **) (resultado[4]) )[0];

			//}

		}

		*tarefa = tar;
		*num = numlins;

		return ret;
	}
}



int bdBuscarTarefaIdItemTarefa(char* idItemTarefa, Tarefa** tarefa, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTarefa, T.tipo, T.titulo, T.descricao, T.obs "
			"FROM Tarefa as T "
			"INNER JOIN ItemTarefa as IT on T.idTarefa = IT.idTarefa "
			"WHERE idItemTarefa = %s",
			idItemTarefa);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Tarefa* tar = NULL;

	if (ret) {

		return ret;
	}
	else {

		if (numlins) {

			tar = (Tarefa *) malloc(numlins * sizeof(Tarefa));

			//for (int i = 0; i < numlins; i++) {

				tar->idTarefa = ( (long long int **) (resultado[0]) )[0];
				tar->tipo = ( (int **) (resultado[1]) )[0];
				tar->titulo = ( (char **) (resultado[2]) )[0];
				tar->descricao = ( (char **) (resultado[3]) )[0];
				tar->obs = ( (char **) (resultado[4]) )[0];

			//}

		}

		*tarefa = tar;
		*num = numlins;

		return ret;
	}
}



int bdBuscarUsuarioPerfilIdUsu(char* idUsuario, Usuario** usu, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs, "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE U.idUsuario = %s",
			idUsuario);


	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usus = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		Usuario* usuario = NULL;
		while (i < numlins) {


			// checa se o próximo registro é do mesmo usuário que o registro anterior

			if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

				// apareceu novo usuario

				idUsuario = *( ( (long long int **) (resultado[0]) )[i]);

				numUsus++;

				usus = (Usuario *) realloc(usus, numUsus * (sizeof(Usuario)));

				usuario = &(usus[numUsus - 1]);

				// resgatar informações sobre usuario

				usuario->idUsuario = ( (long long int **) (resultado[0]) )[i];
				usuario->nome = ( (char **) (resultado[1]) )[i];
				usuario->login = ( (char **) (resultado[2]) )[i];
				usuario->email = ( (char **) (resultado[3]) )[i];
				usuario->numPerfis = 0;
				usuario->perfis = NULL;

			}


			// incrementar contador de perfil do usuario atual
			usuario->numPerfis++;

			// alocar espaço para o novo perfil
			usuario->perfis = (PerfilRespondedor *) realloc(usuario->perfis, usuario->numPerfis * sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = &(usuario->perfis[usuario->numPerfis - 1]);

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[i];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[i];
			pr->matricula = ( (char **) (resultado[5]) )[i];
			pr->usu = &(usus[numUsus - 1]);

			// alocar espaço para o curso correspondente ao perfil
			pr->curso = (Curso *) malloc(sizeof(Curso));

			// acessar curso do perfil
			Curso* curso = pr->curso;

			curso->idCurso = ( (long long int **) (resultado[6]) )[i];
			curso->codigo = ( (char **) (resultado[9]) )[i];
			curso->nome = ( (char **) (resultado[10]) )[i];
			// curso->obs (não precisa)

			// alocar espaço para a institução do curso
			curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// acessar instituição do curso do usuário
			Instituicao* instCurso = curso->inst;

			instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[i];
			instCurso->sigla = ( (char **) (resultado[12]) )[i];
			instCurso->nome = ( (char **) (resultado[13]) )[i];
			// instCurso->obs (não precisa)

			i++;

		}

		*usu = usus;
		*num = numUsus;

		return ret;

	}

}



int bdTurmasPerfil(char* idPerfilRespondedor, Turma** turmas, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT DISTINCT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			"LEFT JOIN PerfilRespondedor_Turma as PRT on T.idTurma = PRT.idTurma "
			//"LEFT JOIN PerfilRespondedor as PR on PR.idPerfilRespondedor = PRT.idPerfilRespondedor "
			//"LEFT JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "
			"WHERE PRT.idPerfilRespondedor = %s ",
			idPerfilRespondedor);

	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Turma* turs = NULL;
	int numTurmas = 0;


	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		turs = (Turma *) malloc(numlins * sizeof(Turma));

		for (i = 0; i < numlins; i++) {

			turs[i].idTurma = ( (long long int **) (resultado[0]) )[i];
			turs[i].idDisciplina = ( (long long int **) (resultado[1]) )[i];
			turs[i].codigo = ( (char **) (resultado[2]) )[i];
			turs[i].idProfCriador = ( (long long int **) (resultado[3]) )[i];
			turs[i].descricao = ( (char **) (resultado[4]) )[i];
			turs[i].ano = ( (char **) (resultado[5]) )[i];
			turs[i].semestre = ( (char **) (resultado[6]) )[i];
			turs[i].encerrada = ( (int **) (resultado[7]) )[i];
			turs[i].obs = ( (char **) (resultado[8]) )[i];

			turs[i].disc = (Disciplina *) malloc(sizeof(Disciplina));

			turs[i].disc->codigo = ( (char **) (resultado[9]) )[i];
			turs[i].disc->nome = ( (char **) (resultado[10]) )[i];

			turs[i].disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			turs[i].disc->inst->sigla = ( (char **) (resultado[11]) )[i];
			turs[i].disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[i];
		}

		*turmas = turs;
		*num = numlins;

		return ret;
	}

}


int bdBuscarSessao(char* idSessao, Sessao** sessao) {

	if (idSessao && sessao) {
		char consulta[4097];
		sprintf(consulta,
				"SELECT idSessao, idUsuario, idPerfilRespondedor, segHoraCriacao, nsegHoraCriacao, segHoraAtualizacao, nsegHoraAtualizacao, segTempoValidade, segTempoValidadeMax "
				"FROM Sessao "
				"WHERE idSessao='%s'",
				idSessao);

		//printf("%s", consulta);

		void** resultado = NULL;
		char** nomesCols = NULL;
		int* tiposCols = NULL;
		int numcols = 0;
		int numlins = 0;

		*sessao = NULL;

		int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

		if (ret == 0 && numlins) {

			// coletar dados do usuário

			*sessao = (Sessao *) malloc( sizeof(Sessao) );

			(*sessao)->idSessao = **((long long int **) (resultado[0]));
			(*sessao)->idUsuario = **((long long int **) (resultado[1]));
			(*sessao)->idPerfilRespondedor = **((long long int **) (resultado[2]));
			(*sessao)->segHoraCriacao = **((long long int **) (resultado[3]));
			(*sessao)->nsegHoraCriacao = **((long long int **) (resultado[4]));
			(*sessao)->segHoraAtualizacao = **((long long int **) (resultado[5]));
			(*sessao)->nsegHoraAtualizacao = **((long long int **) (resultado[6]));
			(*sessao)->segTempoValidade = **((long long int **) (resultado[7]));
			(*sessao)->segTempoValidadeMax = **((long long int **) (resultado[8]));

		}
		else if (numlins == 0) {
			// Sessão não encontrada

			return 2;
		}

		return ret;
	}

}


int bdDadosSessao(long long int idSessao, DadoSessao** dados, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT grupo, chave, valor "
			"FROM DadoSessao "
			"WHERE idSessao = \'%lld\'",
			idSessao);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*dados = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		DadoSessao* dadossessao = NULL;

		*num = numlins;

		if (numlins > 0) {

			dadossessao = (DadoSessao *) malloc( numlins * sizeof(DadoSessao) );

			for (int i = 0; i < numlins; i++) {

				dadossessao[i].idSessao = idSessao;
				dadossessao[i].grupo =  ( (char **) (resultado[0]) )[i];
				dadossessao[i].chave =  ( (char **) (resultado[1]) )[i];
				dadossessao[i].valor =  ( (char **) (resultado[2]) )[i];
			}

		}

		*dados = dadossessao;

		ret = 0;

		return ret;

	}
}


int bdDadosSessaoGrupo(long long int idSessao, char* grupo, DadoSessao** dados, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT chave, valor "
			"FROM DadoSessao "
			"WHERE idSessao = \'%lld\' AND grupo=\'%s\'",
			idSessao, grupo);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*dados = NULL;
	*num = 0;

	if (ret) {
		return ret;
	}
	else {

		DadoSessao* dadossessao = NULL;

		*num = numlins;

		if (numlins > 0) {

			dadossessao = (DadoSessao *) malloc( numlins * sizeof(DadoSessao) );

			for (int i = 0; i < numlins; i++) {

				dadossessao[i].idSessao = idSessao;
				dadossessao[i].grupo =  grupo;
				dadossessao[i].chave =  ( (char **) (resultado[0]) )[i];
				dadossessao[i].valor =  ( (char **) (resultado[1]) )[i];
			}

		}

		*dados = dadossessao;

		ret = 0;

		return ret;

	}
}








int bdPerfisTarefa(char* idUsuario, char* idTarefa, Usuario** usuperfil) {


	char consulta[4097];
	sprintf(consulta,
			"SELECT U.idUsuario as idUsuario, U.nome as nomeUsuario, U.login as login, U.email as email, "
			"		PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCursoPerfilRespondedor, PR.habilitado as habilitado, PR.obs as obs "
//			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
//			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, "
//			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM Usuario as U "
			"INNER JOIN PerfilRespondedor as PR ON U.idUsuario = PR.idUsuario "
			"INNER JOIN PerfilRespondedor_Turma as PRT ON PRT.idPerfilRespondedor = PR.idPerfilRespondedor "
			"INNER JOIN Trabalho as TRAB ON TRAB.idTurma = PRT.idTurma "
			"INNER JOIN ItemTarefa as IT ON IT.idTrabalho = TRAB.idTrabalho "
			"INNER JOIN Tarefa as TAR ON TAR.idTarefa = IT.idTarefa "
//			"INNER JOIN Turma as T ON T.idTurma = PRT.idTurma "
//			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
//			"INNER JOIN Curso as C ON PR.idCurso = C.idCurso "
//			"INNER JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE TAR.idTarefa = %s AND U.idUsuario = %s",
			idTarefa,
			idUsuario);


	//printf("%s", consulta);


	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Usuario* usus = NULL;
	int numUsus = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;
		int idUsuario = 0;

		Usuario* usuario = NULL;


		//if (idUsuario !=  *( ( (long long int **) (resultado[0]) )[i])  ) {

			// apareceu novo usuario

			idUsuario = *( ( (long long int **) (resultado[0]) )[i]);

			numUsus++;

			usus = (Usuario *) realloc(usus, numUsus * (sizeof(Usuario)));

			usuario = &(usus[numUsus - 1]);

			// resgatar informações sobre usuario

			usuario->idUsuario = ( (long long int **) (resultado[0]) )[i];
			usuario->nome = ( (char **) (resultado[1]) )[i];
			usuario->login = ( (char **) (resultado[2]) )[i];
			usuario->email = ( (char **) (resultado[3]) )[i];
			usuario->numPerfis = 0;
			usuario->perfis = NULL;

		//}


		while (i < numlins) {

			// incrementar contador de perfil do usuario atual
			usuario->numPerfis++;

			// alocar espaço para o novo perfil
			usuario->perfis = (PerfilRespondedor *) realloc(usuario->perfis, usuario->numPerfis * sizeof(PerfilRespondedor));

			// acessar último perfil
			PerfilRespondedor* pr = &(usuario->perfis[usuario->numPerfis - 1]);

			pr->idPerfilRespondedor = ( (long long int **) (resultado[4]) )[i];
			pr->idUsuario = ( (long long int **) (resultado[0]) )[i];
			pr->matricula = ( (char **) (resultado[5]) )[i];
			pr->usu = &(usus[numUsus - 1]);

			// // alocar espaço para o curso correspondente ao perfil
			// pr->curso = (Curso *) malloc(sizeof(Curso));

			// // acessar curso do perfil
			// Curso* curso = pr->curso;

			// curso->idCurso = ( (long long int **) (resultado[6]) )[i];
			// curso->codigo = ( (char **) (resultado[9]) )[i];
			// curso->nome = ( (char **) (resultado[10]) )[i];
			// // curso->obs (não precisa)

			// // alocar espaço para a institução do curso
			// curso->inst = (Instituicao *) malloc (sizeof(Instituicao));

			// // acessar instituição do curso do usuário
			// Instituicao* instCurso = curso->inst;

			// instCurso->idInstituicao = ( (long long int **) (resultado[11]) )[i];
			// instCurso->sigla = ( (char **) (resultado[12]) )[i];
			// instCurso->nome = ( (char **) (resultado[13]) )[i];
			// // instCurso->obs (não precisa)

			i++;

		}

		*usuperfil = usus;
		//*num = numUsus;

		return ret;

	}


}




int bdTurmasPerfilTarefa(char* idPerfilRespondedor, char* idTarefa, Turma** turmas, int* num) {


	char consulta[4097];
	sprintf(consulta,
			"SELECT DISTINCT T.idTurma as idTurma, T.idDisciplina as idDisciplina, T.codigo as codigo, T.idProfCriador as idProfCriador, T.descricao as descricao, T.ano as ano, T.semestre as semestre, T.encerrada as encerrada, T.obs as obs, "
			"		D.codigo as codigoDisciplina, D.nome as nomeDisciplina, "
			"		I.sigla as siglaInstituicao, I.idInstituicao as idInstituicao "
			"FROM Turma as T "
			"LEFT JOIN PerfilRespondedor_Turma as PRT on T.idTurma = PRT.idTurma "
			//"LEFT JOIN PerfilRespondedor as PR on PR.idPerfilRespondedor = PRT.idPerfilRespondedor "
			//"LEFT JOIN Usuario as U on PT.idUsuario = U.idUsuario "
			"INNER JOIN Disciplina as D on D.idDisciplina = T.idDisciplina "
			"INNER JOIN Instituicao as I on I.idInstituicao = D.idInstituicao "

			"INNER JOIN Trabalho as TRAB ON TRAB.idTurma = PRT.idTurma "
			"INNER JOIN ItemTarefa as IT ON IT.idTrabalho = TRAB.idTrabalho "
			"INNER JOIN Tarefa as TAR ON TAR.idTarefa = IT.idTarefa "

			"WHERE PRT.idPerfilRespondedor = %s AND TAR.idTarefa = %s",
			idPerfilRespondedor, idTarefa);

	// printf("%s", consulta); return 0;

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	Turma* turs = NULL;
	int numTurmas = 0;


	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		turs = (Turma *) malloc(numlins * sizeof(Turma));

		for (i = 0; i < numlins; i++) {

			turs[i].idTurma = ( (long long int **) (resultado[0]) )[i];
			turs[i].idDisciplina = ( (long long int **) (resultado[1]) )[i];
			turs[i].codigo = ( (char **) (resultado[2]) )[i];
			turs[i].idProfCriador = ( (long long int **) (resultado[3]) )[i];
			turs[i].descricao = ( (char **) (resultado[4]) )[i];
			turs[i].ano = ( (char **) (resultado[5]) )[i];
			turs[i].semestre = ( (char **) (resultado[6]) )[i];
			turs[i].encerrada = ( (int **) (resultado[7]) )[i];
			turs[i].obs = ( (char **) (resultado[8]) )[i];

			turs[i].disc = (Disciplina *) malloc(sizeof(Disciplina));

			turs[i].disc->codigo = ( (char **) (resultado[9]) )[i];
			turs[i].disc->nome = ( (char **) (resultado[10]) )[i];

			turs[i].disc->inst = (Instituicao *) malloc(sizeof(Instituicao));

			turs[i].disc->inst->sigla = ( (char **) (resultado[11]) )[i];
			turs[i].disc->inst->idInstituicao = ( (long long int **) (resultado[12]) )[i];
		}

		*turmas = turs;
		*num = numlins;

		return ret;
	}
}



int bdBuscarTrabalhosTurmaTarefa(char* idTurma, char* idTarefa, Trabalho** trabalhos, int* num) {


	char consulta[4097];
	sprintf(consulta,
			"SELECT T.idTrabalho, T.idTurma, T.numTrabalho, T.titulo, T.descricao, T.segHoraCriacao, T.segHoraInicio, T.segHoraFim, T.oculto, T.obs "
			"FROM Trabalho as T "
			"INNER JOIN ItemTarefa as IT ON IT.idTrabalho = T.idTrabalho "
			"WHERE T.idTurma = %s AND IT.idTarefa = %s "
			"ORDER BY T.numTrabalho",
			idTurma, idTarefa);

	//printf("%s", consulta);



	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	Trabalho* trabs = NULL;
	int numTrabs = 0;

	if (ret) {

		return ret;
	}
	else {

		int i = 0;

		if (numlins) {

			trabs = (Trabalho *) malloc(numlins * sizeof(Trabalho));

			for (int i = 0; i < numlins; i++) {

				trabs[i].idTrabalho = ( (long long int **) (resultado[0]) )[i];
				trabs[i].idTurma = ( (long long int **) (resultado[1]) )[i];
				trabs[i].numTrabalho = ( (int **) (resultado[2]) )[i];
				trabs[i].titulo = ( (char **) (resultado[3]) )[i];
				trabs[i].descricao = ( (char **) (resultado[4]) )[i];
				trabs[i].segHoraCriacao = ( (long long int **) (resultado[5]) )[i];
				trabs[i].segHoraInicio = ( (long long int **) (resultado[6]) )[i];
				trabs[i].segHoraFim = ( (long long int **) (resultado[7]) )[i];
				trabs[i].oculto = ( (int **) (resultado[8]) )[i];
				trabs[i].obs = ( (char **) (resultado[9]) )[i];
			}
		}

		*trabalhos = trabs;
		*num = numlins;

		return ret;
	}
}


int bdBuscarItensTarefaIdTrabalhoTarefa(char* idTrabalho, char* idTarefa, ItemTarefa** itenstarefa, int* num) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT IT.idItemTarefa, IT.idTarefa, IT.idTrabalho, IT.numItemTarefa, T.tipo, T.titulo, T.descricao, T.obs "
			"FROM ItemTarefa as IT "
			"INNER JOIN Tarefa as T ON IT.idTarefa = T.idTarefa "
			"WHERE IT.idTrabalho = %s AND T.idTarefa = %s "
			"ORDER BY IT.numItemTarefa",
			idTrabalho, idTarefa);

	//printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);


	ItemTarefa* it = NULL;

	if (ret) {

		return ret;
	}
	else {

		if (numlins) {

			it = (ItemTarefa *) malloc(numlins * sizeof(ItemTarefa));

			for (int i = 0; i < numlins; i++) {

				it[i].idItemTarefa = ( (long long int **) (resultado[0]) )[i];
				it[i].idTarefa = ( (long long int **) (resultado[1]) )[i];
				it[i].idTrabalho = ( (long long int **) (resultado[2]) )[i];
				it[i].numItemTarefa = ( (int **) (resultado[3]) )[i];

				it[i].tarefa = (Tarefa *) malloc(sizeof(Tarefa));

				it[i].tarefa->idTarefa = ( (long long int **) (resultado[1]) )[i];
				it[i].tarefa->tipo = ( (int **) (resultado[4]) )[i];
				it[i].tarefa->titulo = ( (char **) (resultado[5]) )[i];
				it[i].tarefa->descricao = ( (char **) (resultado[6]) )[i];
				it[i].tarefa->obs = ( (char **) (resultado[7]) )[i];

			}

		}

		*itenstarefa = it;
		*num = numlins;

		return ret;
	}
}




