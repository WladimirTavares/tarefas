/*
 * Tabela Sessao
 * - - - -
 *
 * CREATE TABLE Sessao (
	idSessao integer PRIMARY KEY,
	idUsuario integer REFERENCES Usuario (idUsuario),
	idPerfilRespondedor integer REFERENCES PerfilRespondedor (idPerfilRespondedor),
	segHoraCriacao integer,
	nsegHoraCriacao integer,
	segHoraAtualizacao integer,
	nsegHoraAtualizacao integer,
	segTempoValidade integer,
	segTempoValidadeMax integer
) STRICT;
 *
 */

int bdInserirSessao(long long int idSessao, long long int idUsuario, long long int idPerfilRespondedor, long long int segHoraCriacao, long long int nsegHoraCriacao, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao, long long int segTempoValidade, long long int segTempoValidadeMax);

int bdSelSessaoId(long long int id, long long int*** idSessao, long long int*** idUsuario, long long int*** idPerfilRespondedor, long long int*** segHoraCriacao, long long int*** nsegHoraCriacao, long long int*** segHoraAtualizacao, long long int*** nsegHoraAtualizacao, long long int*** segTempoValidade, long long int*** segTempoValidadeMax, int* numlins);

int bdAtualizarSessaoId(long long int id, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao);

int bdAtualizarSessaoPerfilRespondedor(long long int id, long long int idPerfilRespondedor, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao);

int bdRemoverSessao(long long int id);



/* Implementação
 * - - - - - - -
 */

int bdInserirSessao(long long int idSessao, long long int idUsuario, long long int idPerfilRespondedor, long long int segHoraCriacao, long long int nsegHoraCriacao, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao, long long int segTempoValidade, long long int segTempoValidadeMax){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into Sessao values (%lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld)", idSessao, idUsuario, idPerfilRespondedor, segHoraCriacao, nsegHoraCriacao, segHoraAtualizacao, nsegHoraAtualizacao, segTempoValidade, segTempoValidadeMax);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelSessaoId(long long int id, long long int*** idSessao, long long int*** idUsuario, long long int*** idPerfilRespondedor, long long int*** segHoraCriacao, long long int*** nsegHoraCriacao, long long int*** segHoraAtualizacao, long long int*** nsegHoraAtualizacao, long long int*** segTempoValidade, long long int*** segTempoValidadeMax, int* numlins) {

	/* As variáveis:
	 *
	 *		idUsuario,
	 * 		nome,
	 * 		login,
	 * 		senha,
	 * 		email e
	 * 		habilitado
	 *
	 * são referências. Devem, portanto, ser desreferenciadas
	 * para acessar as posições de memória originais.
	 */


	// Ecrever consulta

	char consulta[4097];
	sprintf(consulta, "select * from Sessao where idSessao = %lld", id);

	// Executar consulta

	void** resultado = NULL;
	char** nomesCols = NULL;
	int* tiposCols = NULL;
	int numcols = 0;

	int ret = bdExecSelecao(caminho_banco, consulta, &resultado, &nomesCols, &tiposCols, &numcols, numlins);

	if (ret)
		return ret;

	// Converter colunas

	*idSessao = (long long int **) resultado[0];
	*idUsuario = (long long int **) resultado[1];
	*idPerfilRespondedor = (long long int **) resultado[2];
	*segHoraCriacao = (long long int **) resultado[3];
	*nsegHoraCriacao = (long long int **) resultado[4];
	*segHoraAtualizacao = (long long int **) resultado[5];
	*nsegHoraAtualizacao = (long long int **) resultado[6];
	*segTempoValidade = (long long int **) resultado[7];
	*segTempoValidadeMax = (long long int **) resultado[8];

	return 0;
}


int bdAtualizarSessaoId(long long int id, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Sessao set segHoraAtualizacao = %lld, nsegHoraAtualizacao = %lld where idSessao = %lld", segHoraAtualizacao, nsegHoraAtualizacao, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdAtualizarSessaoPerfilRespondedor(long long int id, long long int idPerfilRespondedor, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "update Sessao set idPerfilRespondedor = %lld, segHoraAtualizacao = %lld, nsegHoraAtualizacao = %lld where idSessao = %lld", idPerfilRespondedor, segHoraAtualizacao, nsegHoraAtualizacao, id);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdRemoverSessao(long long int id) {

	// Escrever consulta

	char consulta[4097];
	sprintf(consulta, "delete from Sessao where idSessao = %lld", id);

	return bdExecConsIAR(caminho_banco, consulta);

}
