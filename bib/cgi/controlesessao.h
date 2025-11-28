/*
 * controlesessao.h
 *
 * implementa métodos relativos ao controle de sessão
 *
 * OBS: Utiliza como caminho do banco a variável
 *
 * 			caminho_banco
 *
 * definida na biblioteca tarefasbd.h
 *
 */


#include <time.h>



Sessao* criarSessao(long long int idUsuario, long long int idPerfilRespondedor, long long int segTempoValidade, long long int segTempoValidadeMax);


int sessaoValida(Sessao* sessao);


int atualizarHoraSessao(Sessao* sessao);


int encerrarSessao(Sessao* sessao);






/* Implementações */



Sessao* criarSessao(long long int idUsuario, long long int idPerfilRespondedor, long long int segTempoValidade, long long int segTempoValidadeMax) {

	Sessao* sessao = (Sessao *) malloc( sizeof(Sessao));

	bdProxContadorIdSessao(&(sessao->idSessao));
	sessao->idUsuario = idUsuario;
	sessao->idPerfilRespondedor = idPerfilRespondedor;

	// gravar horário de criação

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);

	sessao->segHoraCriacao = ts.tv_sec;
	sessao->nsegHoraCriacao = ts.tv_nsec;

	sessao->segHoraAtualizacao = ts.tv_sec;
	sessao->nsegHoraAtualizacao = ts.tv_nsec;

	sessao->segTempoValidade = segTempoValidade;
	sessao->segTempoValidadeMax = segTempoValidadeMax;

	bdInserirSessao(sessao->idSessao, sessao->idUsuario, sessao->idPerfilRespondedor, sessao->segHoraCriacao, sessao->nsegHoraCriacao, sessao->segHoraAtualizacao, sessao->nsegHoraAtualizacao, sessao->segTempoValidade, sessao->segTempoValidadeMax);

	return sessao;
}


int sessaoValida(Sessao* sessao) {

	if (sessao) {
		// obter hora atual

		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);

		if (ts.tv_sec - sessao->segHoraCriacao > sessao->segTempoValidadeMax) {

			// validade maxima da sessão execedida
			return 2;
		}
		else if (ts.tv_sec - sessao->segHoraAtualizacao > sessao->segTempoValidade) {

			// sessão expirada
			return 3;
		}

		return 0;
	}

	return 1;

}


int atualizarHoraSessao(Sessao* sessao) {

	if (sessao) {
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);

		int ret = bdAtualizarSessaoId(sessao->idSessao, ts.tv_sec, ts.tv_nsec);

		if (ret == 0) {
			sessao->segHoraAtualizacao = ts.tv_sec;
			sessao->nsegHoraAtualizacao = ts.tv_nsec;
		}

		return ret;
	}

	return 1;

}


int encerrarSessao(Sessao* sessao) {

	if (sessao) {
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);

		// inserir sessao encerrada
		int ret = bdInserirSessaoEncerrada(sessao->idSessao, sessao->idUsuario, sessao->idPerfilRespondedor, sessao->segHoraCriacao, sessao->nsegHoraCriacao, sessao->segHoraAtualizacao, sessao->nsegHoraAtualizacao, sessao->segTempoValidade, sessao->segTempoValidadeMax, 1, ts.tv_sec);

		if (ret) return ret;

		// remover sessao da tabela de sessões ativas
		ret = bdRemoverSessao(sessao->idSessao);

		return ret;
	}

	return 1;

}
