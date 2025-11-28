/*
 * Tabela Sessao
 * - - - -
 *
 * CREATE TABLE SessaoEncerrada (
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

int bdInserirSessaoEncerrada(long long int idSessao, long long int idUsuario, long long int idPerfilRespondedor, long long int segHoraCriacao, long long int nsegHoraCriacao, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao, long long int segTempoValidade, long long int segTempoValidadeMax, long long int encerrada, long long int segHoraEncerramento);

int bdSelSessaoEncerradaId(long long int id, long long int*** idSessao, long long int*** idUsuario, long long int*** idPerfilRespondedor, long long int*** segHoraCriacao, long long int*** nsegHoraCriacao, long long int*** segHoraAtualizacao, long long int*** nsegHoraAtualizacao, long long int*** segTempoValidade, long long int*** segTempoValidadeMax, long long int*** encerrada, long long int*** segHoraEncerramento, int* numlins);



/* Implementação
 * - - - - - - -
 */

int bdInserirSessaoEncerrada(long long int idSessao, long long int idUsuario, long long int idPerfilRespondedor, long long int segHoraCriacao, long long int nsegHoraCriacao, long long int segHoraAtualizacao, long long int nsegHoraAtualizacao, long long int segTempoValidade, long long int segTempoValidadeMax, long long int encerrada, long long int segHoraEncerramento){

	// Escrever consulta
	char consulta[4097];
	sprintf(consulta, "insert into SessaoEncerrada values (%lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld)", idSessao, idUsuario, idPerfilRespondedor, segHoraCriacao, nsegHoraCriacao, segHoraAtualizacao, nsegHoraAtualizacao, segTempoValidade, segTempoValidadeMax, encerrada, segHoraEncerramento);

	return bdExecConsIAR(caminho_banco, consulta);
}


int bdSelSessaoEncerradaId(long long int id, long long int*** idSessao, long long int*** idUsuario, long long int*** idPerfilRespondedor, long long int*** segHoraCriacao, long long int*** nsegHoraCriacao, long long int*** segHoraAtualizacao, long long int*** nsegHoraAtualizacao, long long int*** segTempoValidade, long long int*** segTempoValidadeMax, long long int*** encerrada, long long int*** segHoraEncerramento, int* numlins) {

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
	sprintf(consulta, "select * from SessaoEncerrada where idSessao = %lld", id);

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
	*encerrada = (long long int **) resultado[9];
	*segHoraEncerramento = (long long int **) resultado[10];

	return 0;
}
