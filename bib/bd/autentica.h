/*
 * autentica.h
 *
 * implementa métodos relativos à autenticação de usuários
 *
 * OBS: Utiliza como caminho do banco a variável
 *
 * 			caminho_banco
 *
 * definida na biblioteca tarefasbd.h
 *
 */





// Retorna dados do usuario caso login e senha sejam válidos
int bdAutenticaUsuario(char* login, char* senha, Usuario** usu);

// Retorna os perfis de respondedor
int bdPerfisRespondedor(long long int idUsuario, PerfilRespondedor** prs, int* numPerfis);

// Retorna usuario a partir do idUsuario
int bdUsuarioIdUsuario(long long int idUsuario, Usuario** usu);

// Retorna dados de usuario a partir de sessão
int bdUsuarioSessao(long long int idSessao, Usuario** usu);








/*
 * Implementações
 *
 *
 * //int execSelecao(char* caminhoBanco, char* consulta, void*** resultado, char*** nomesCols, int** tiposCols, int* numcols, int* numlins)
 */




int bdAutenticaUsuario(char* login, char* senha, Usuario** usu) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idUsuario, nome, email, adm, professor, habilitado "
			"FROM Usuario "
			"WHERE login='%s' AND senha='%s'",
		 	login, senha);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usu = NULL;

	if (ret) return ret;

	if (numlins) {

		// coletar dados do usuário

		*usu = (Usuario *) malloc( sizeof(Usuario) );

		(*usu)->idUsuario = *((long long int **) (resultado[0]));
		(*usu)->nome = *((char **) (resultado[1]));
		(*usu)->email = *((char **) (resultado[2]));
		(*usu)->adm = *((long long int **) (resultado[3]));
		(*usu)->professor = *((long long int **) (resultado[4]));
		(*usu)->habilitado = *((long long int **) (resultado[5]));

		(*usu)->login = login;

		// obter perfis

		//ret = bdPerfisRespondedor(*((*usu)->idUsuario), &((*usu)->perfis),&((*usu)->numPerfis));

		PerfilRespondedor* prs = NULL;
		int numPerfis = 0;

		ret = bdPerfisRespondedor(*((*usu)->idUsuario), &prs, &numPerfis);

		(*usu)->perfis = prs;
		(*usu)->numPerfis = numPerfis;

		return 0;

	}

	return 1;
}


/*
int bdPerfisRespondedor(long long int idUsuario, PerfilRespondedor** prs, int* numPerfis) {

	//
	//O parâmetro pr é passado por referência.
	//É a lista de perfis retornada.
	//

	char consulta[4097];
	sprintf(consulta,
			"SELECT PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCurso, PR.idInstituicao as idInstituicao, PR.habilitado as habilitado, PR.obs as obs, "
			"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, C.obs as obsCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM PerfilRespondedor as PR "
			"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"LEFT JOIN Curso as C ON PR.idCurso = C.idCurso "
			"LEFT JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.idUsuario = %lld", idUsuario);

	printf("%s", consulta);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret) {		// erro na execução da consulta
		return ret;
	}
	else {
		if (numlins > 0) {

			*numPerfis = numlins;

			PerfilRespondedor* perfis = (PerfilRespondedor *) malloc( numlins * sizeof(PerfilRespondedor));
			for (int i = 0; i < numlins; i++) {
				perfis[i].inst = (Instituicao *) malloc( sizeof(Instituicao));
				perfis[i].curso = (Curso *) malloc( sizeof(Curso));
				perfis[i].curso->inst = (Instituicao *) malloc( sizeof(Instituicao));

				perfis[i].idPerfilRespondedor = ( ( (long long int **) (resultado[0]) )[i]);

				perfis[i].idUsuario = (long long int *) malloc(sizeof(long long int));
				*(perfis[i].idUsuario) = idUsuario;

				perfis[i].matricula = ((char **) (resultado[1]))[i];
				perfis[i].curso->idCurso = ( ( (long long int **) (resultado[2]) )[i]);
				perfis[i].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[i]);
				perfis[i].habilitado = ( ( (long long int **) (resultado[4]) )[i]);
				perfis[i].obs = ((char **) (resultado[5]))[i];

				perfis[i].inst->sigla = ((char **) (resultado[6]))[i];
				perfis[i].inst->nome = ((char **) (resultado[7]))[i];
				perfis[i].inst->obs = ((char **) (resultado[8]))[i];

				perfis[i].curso->codigo = ((char **) (resultado[9]))[i];
				perfis[i].curso->nome = ((char **) (resultado[10]))[i];
				perfis[i].curso->inst->idInstituicao = ( ( (long long int **) (resultado[11]) )[i]);
				perfis[i].curso->obs = ((char **) (resultado[12]))[i];

				perfis[i].curso->inst->sigla = ((char **) (resultado[13]))[i];
				perfis[i].curso->inst->nome = ((char **) (resultado[14]))[i];
				perfis[i].curso->inst->obs = ((char **) (resultado[15]))[i];
			}

			*prs = perfis;
		}
		else {
			//*numPerfis = 0;
			*prs = NULL;
		}
	}

	return ret;
}
*/

int bdPerfisRespondedor(long long int idUsuario, PerfilRespondedor** prs, int* numPerfis) {

	//
	//O parâmetro pr é passado por referência.
	//É a lista de perfis retornada.
	//

	char consulta[4097];
	sprintf(consulta,
			//"SELECT PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCurso, PR.idInstituicao as idInstituicao, PR.habilitado as habilitado, PR.obs as obs, "
			"SELECT PR.idPerfilRespondedor as idPerfilRespondedor, PR.matricula as matricula, PR.idCurso as idCurso, PR.habilitado as habilitado, PR.obs as obs, "
			//"		I.sigla as siglaInstituicao, I.nome as nomeInstituicao, I.obs as obsInstituicao, "
			"		C.codigo as codigoCurso, C.nome as nomeCurso, C.idInstituicao as idInstituicaoCurso, C.obs as obsCurso, "
			"		IC.sigla as siglaInstituicaoCurso, IC.nome as nomeInstituicaoCurso, IC.obs as obsInstituicaoCurso "
			"FROM PerfilRespondedor as PR "
			//"LEFT JOIN Instituicao as I ON PR.idInstituicao = I.idInstituicao "
			"LEFT JOIN Curso as C ON PR.idCurso = C.idCurso "
			"LEFT JOIN Instituicao as IC ON C.idInstituicao = IC.idInstituicao "
			"WHERE PR.idUsuario = %lld", idUsuario);

	//printf("%s", consulta);

	//return 0;

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret) {		// erro na execução da consulta
		return ret;
	}
	else {
		if (numlins > 0) {

			*numPerfis = numlins;

			PerfilRespondedor* perfis = (PerfilRespondedor *) malloc( numlins * sizeof(PerfilRespondedor));
			for (int i = 0; i < numlins; i++) {
				//perfis[i].inst = (Instituicao *) malloc( sizeof(Instituicao));
				perfis[i].curso = (Curso *) malloc( sizeof(Curso));
				perfis[i].curso->inst = (Instituicao *) malloc( sizeof(Instituicao));

				perfis[i].idPerfilRespondedor = ( ( (long long int **) (resultado[0]) )[i]);

				perfis[i].idUsuario = (long long int *) malloc(sizeof(long long int));
				*(perfis[i].idUsuario) = idUsuario;

				perfis[i].matricula = ((char **) (resultado[1]))[i];
				perfis[i].curso->idCurso = ( ( (long long int **) (resultado[2]) )[i]);
				//perfis[i].inst->idInstituicao = ( ( (long long int **) (resultado[3]) )[i]);
				perfis[i].habilitado = ( ( (long long int **) (resultado[3]) )[i]);
				perfis[i].obs = ((char **) (resultado[4]))[i];

				//perfis[i].inst->sigla = ((char **) (resultado[6]))[i];
				//perfis[i].inst->nome = ((char **) (resultado[7]))[i];
				//perfis[i].inst->obs = ((char **) (resultado[8]))[i];

				perfis[i].curso->codigo = ((char **) (resultado[5]))[i];
				perfis[i].curso->nome = ((char **) (resultado[6]))[i];
				perfis[i].curso->inst->idInstituicao = ( ( (long long int **) (resultado[7]) )[i]);
				perfis[i].curso->obs = ((char **) (resultado[8]))[i];

				perfis[i].curso->inst->sigla = ((char **) (resultado[9]))[i];
				perfis[i].curso->inst->nome = ((char **) (resultado[10]))[i];
				perfis[i].curso->inst->obs = ((char **) (resultado[11]))[i];
			}

			*prs = perfis;
		}
		else {
			*numPerfis = 0;
			*prs = NULL;
		}
	}

	return ret;
}


int bdUsuarioIdUsuario(long long int idUsuario, Usuario** usu) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT nome, login, email, adm, professor, habilitado "
			"FROM Usuario "
			"WHERE idUsuario=%lld",
		 	idUsuario);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usu = NULL;

	int ret = 0;

	if (numlins) {

		// coletar dados do usuário

		(*usu) = (Usuario *) malloc( sizeof(Usuario) );
		(*usu)->idUsuario = (long long int *) malloc(sizeof(long long int));

		*((*usu)->idUsuario) = idUsuario;
		(*usu)->nome = *((char **) (resultado[0]));
		(*usu)->login = *((char **) (resultado[1]));
		(*usu)->email = *((char **) (resultado[2]));
		(*usu)->adm = *((long long int **) (resultado[3]));
		(*usu)->professor = *((long long int **) (resultado[4]));
		(*usu)->habilitado = *((long long int **) (resultado[5]));

		// obter perfis

		//ret = bdPerfisRespondedor(*((*usu)->idUsuario), &((*usu)->perfis),&((*usu)->numPerfis));

		PerfilRespondedor* prs = NULL;
		int numPerfis = 0;

		ret = bdPerfisRespondedor(*((*usu)->idUsuario), &prs, &numPerfis);

		(*usu)->perfis = prs;
		(*usu)->numPerfis = numPerfis;

	}

	return ret;
}


int bdUsuarioSessao(long long int idSessao, Usuario** usu) {

	char consulta[4097];
	sprintf(consulta,
			"SELECT idUsuario, nome, login, email, adm, professor, habilitado "
			"FROM Usuario "
			"JOIN Sessao ON Usuario.idUsuario = Sessao.idUsuario "
			"WHERE idSessao=%lld",
		 	idSessao);

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	*usu = NULL;

	int ret = 0;

	if (numlins) {

		// coletar dados do usuário

		(*usu) = (Usuario *) malloc( sizeof(Usuario) );

		(*usu)->idUsuario = *((long long int **) (resultado[0]));
		(*usu)->nome = *((char **) (resultado[1]));
		(*usu)->login = *((char **) (resultado[2]));
		(*usu)->email = *((char **) (resultado[3]));
		(*usu)->adm = *((long long int **) (resultado[4]));
		(*usu)->professor = *((long long int **) (resultado[5]));
		(*usu)->habilitado = *((long long int **) (resultado[6]));

		// obter perfis

		//ret = bdPerfisRespondedor(*((*usu)->idUsuario), &((*usu)->perfis),&((*usu)->numPerfis));

	}

	return ret;

}



/*
 * TODO
 *
 * - checar se a função usuarioSessao() ficaria mais eficiente se for feita
 *   apenas uma consulta.
 *
 */
