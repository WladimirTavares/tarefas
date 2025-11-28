/*
 * Tabela Contadores
 *
 * CREATE TABLE Contadores (
	idUsuario integer,
	idPerfilRespondedor integer,
	idCurso integer,
	idDisciplina integer,
	idTurma integer,
	idTrabalho integer,
	idSessao integer
) STRICT;
 *
 */



int bdProxContadorIdUsuario(long long int* proxIdUsuario);

//int bdProxContadorIdAdm(long long int* proxIdAdm);

//int bdProxContadorIdElaborador(long long int* proxIdElaborador);

int bdProxContadorIdPerfilRespondedor(long long int* proxIdRespondedor);

int bdProxContadorIdInstituicao(long long int* proxContadorIdInstituicao);

int bdProxContadorIdCurso(long long int* proxIdCurso);

int bdProxContadorIdDisciplina(long long int* proxIdDisciplina);

int bdProxContadorIdTurma(long long int* proxIdTurma);

int bdProxContadorIdTrabalho(long long int* proxIdTrabalho);

int bdProxContadorIdSessao(long long int* proxIdSessao);

int bdProxContadorIdTarefa(long long int* proxIdTarefa);

int bdProxContadorIdItemTarefa(long long int* proxIdItemTarefa);



/* Implementação
 * - - - - - - -
 */



int bdProxContadorIdUsuario(long long int* proxIdUsuario) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idUsuario = idUsuario + 1 returning idUsuario");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdUsuario = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}



/*
int bdProxContadorIdAdm(long long int* proxIdAdm) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idAdm = idAdm + 1 returning idAdm");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdAdm = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}


int bdProxContadorIdElaborador(long long int* proxIdElaborador) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idElaborador = idElaborador + 1 returning idElaborador");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdElaborador = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}
*/


int bdProxContadorIdPerfilRespondedor(long long int* proxIdRespondedor) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idPerfilRespondedor = idPerfilRespondedor + 1 returning idPerfilRespondedor");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdRespondedor = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}


int bdProxContadorIdInstituicao(long long int* proxIdInstituicao) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idInstituicao = idInstituicao + 1 returning idInstituicao");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdInstituicao = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}

int bdProxContadorIdCurso(long long int* proxIdCurso) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idCurso = idCurso + 1 returning idCurso");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdCurso = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}


int bdProxContadorIdDisciplina(long long int* proxIdDisciplina) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idDisciplina = idDisciplina + 1 returning idDisciplina");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdDisciplina = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}


int bdProxContadorIdTurma(long long int* proxIdTurma) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idTurma = idTurma + 1 returning idTurma");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdTurma = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}


int bdProxContadorIdTrabalho(long long int* proxIdTrabalho) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idTrabalho = idTrabalho + 1 returning idTrabalho");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdTrabalho = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}


int bdProxContadorIdSessao(long long int* proxIdSessao) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idSessao = idSessao + 1 returning idSessao");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdSessao = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}

int bdProxContadorIdTarefa(long long int* proxIdTarefa) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idTarefa = idTarefa + 1 returning idTarefa");

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdTarefa = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}

int bdProxContadorIdItemTarefa(long long int* proxIdItemTarefa) {

	char consulta[4097];
	sprintf(consulta, "update Contadores set idItemTarefa = idItemTarefa + 1 returning idItemTarefa");

	//printf("%s", consulta);

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;
	int numlins = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, &numlins);

	if (ret)
		return ret;

	// Converter colunas

	*proxIdItemTarefa = (*((long long int **) resultado[0]))[0];		// Supõe que a tabela de contadores não está corrompida

	return 0;
}
