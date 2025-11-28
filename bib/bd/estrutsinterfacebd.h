/*
 * estrutinterfacebd.h
 *
 * implementa estruturas de dados/registros correspondentes
 * às entidades do banco de dados, bem como métodos acessórios
 *
 */


typedef struct Instituicao {

	long long int* idInstituicao;
	char* sigla;
	char* nome;
	char* obs;
} Instituicao;


typedef struct Curso {

	long long int* idCurso;
	char* codigo;
	char* nome;
	//long long int idInstituicao;
	char* obs;

	Instituicao* inst;
} Curso;


typedef struct Disciplina {

	long long int* idDisciplina;
	char* codigo;
	char* nome;
	//long long int idInstituicao;
	char* obs;

	Instituicao* inst;
} Disciplina;


typedef struct Usuario Usuario;

typedef struct PerfilRespondedor PerfilRespondedor;

struct PerfilRespondedor {

	long long int* idPerfilRespondedor;
	long long int* idUsuario;
	char* matricula;
	//long long int idCurso;
	//long long int idInstituicao;
	long long int* habilitado;
	char* obs;

	Usuario* usu;

	Curso* curso;
	//Instituicao* inst;
};


struct Usuario {

	long long int* idUsuario;
	char* nome;
	char* login;
	char* email;
	char* senha;
	long long int* adm;				// boleano
	long long int* professor;			// boleano
	long long int* habilitado;			// boleano

	int numPerfis;
	PerfilRespondedor* perfis;
};


typedef struct Turma {

	long long int* idTurma;
	long long int* idDisciplina;
	char* codigo;
	long long int* idProfCriador;
	char* descricao;
	char* ano;
	char* semestre;
	int* encerrada;
	char* obs;

	Disciplina* disc;
} Turma;


typedef struct Trabalho {

	long long int* idTrabalho;
	long long int* idTurma;
	int* numTrabalho;
	char* titulo;
	long long int* segHoraCriacao;
	long long int* segHoraInicio;
	long long int* segHoraFim;
	char* descricao;
	int* oculto;
	char* obs;
} Trabalho;


typedef struct Tarefa {

	long long int* idTarefa;
	int* tipo;
	char* titulo;
	char* descricao;
	char* obs;
} Tarefa;

typedef struct ItemTarefa {

	long long int* idItemTarefa;
	long long int* idTarefa;
	long long int* idTrabalho;
	int* numItemTarefa;

	Tarefa* tarefa;
} ItemTarefa;


typedef struct Sessao {

	long long int idSessao;
	long long int idUsuario;
	long long int idPerfilRespondedor;
	long long int segHoraCriacao;
	long long int nsegHoraCriacao;
	long long int segHoraAtualizacao;
	long long int nsegHoraAtualizacao;
	long long int segTempoValidade;			// validade em segundos a partir da última atualização
	long long int segTempoValidadeMax;		// validade máxima em segundos a partir da criação

} Sessao;


typedef struct DadoSessao {
	long long int idSessao;
	char* grupo;
	char* chave;
	char* valor;
} DadoSessao;



/*		Cabeçalhos de métodos		*/



// Imprime Instituição
void imprimirInstituicao(Instituicao* inst);

// Imprime Instituição
void imprimirCurso(Curso* curso);

// Imprime PerfilRespondedor
void imprimirPerfilRespondedor(PerfilRespondedor* perfil);

// Imprime Usuario
void imprimirUsuario(Usuario* usu);


void imprimirSessao(Sessao* sessao);



/*		Implementações		*/




void imprimirInstituicao(Instituicao* inst) {
	printf("idInstituicao: %lld, ", *(inst->idInstituicao));
	printf("sigla: %s, ", inst->sigla);
	printf("nome: %s, ", inst->nome);
	printf("obs: %s", inst->obs);
}


void imprimirCurso(Curso* curso) {
	printf("idCurso: %lld, ", *(curso->idCurso));
	printf("codigo: %s, ", curso->codigo);
	printf("nome: %s, ", curso->nome);
	printf("obs: %s", curso->obs);

}


void imprimirDisciplina(Disciplina* disciplina) {
	printf("idCurso: %lld, ", *(disciplina->idDisciplina));
	printf("codigo: %s, ", disciplina->codigo);
	printf("nome: %s, ", disciplina->nome);
	printf("obs: %s", disciplina->obs);

}


void imprimirPerfilRespondedor(PerfilRespondedor* perfil) {
	printf("idPerfilRespondedor: %lld, ", *(perfil->idPerfilRespondedor));
	printf("idUsuario: %lld, ", *(perfil->idUsuario));
	printf("matricula: %s, ", perfil->matricula);
	//printf("idCurso: %lld, ", perfil->idCurso);
	//printf("idInstituicao: %lld, ", perfil->idInstituicao);
	printf("habilitado: %lld, ", *(perfil->habilitado));
	printf("obs: %s ", perfil->obs);

	printf("\n\t\t");
	imprimirCurso(perfil->curso);
	printf("\n\t\t");
	//imprimirInstituicao(perfil->inst);
}


void imprimirUsuario(Usuario* usu) {
	printf("idUsuario: %lld\n", *(usu->idUsuario));
	printf("login: %s\n", usu->login);
	printf("nome: %s\n", usu->nome);
	printf("email: %s\n", usu->email);
	printf("adm: %lld\n", *(usu->adm));
	printf("professor: %lld\n", *(usu->professor));
	printf("habilitado: %lld\n", *(usu->habilitado));
	printf("numPerfis: %d\n", usu->numPerfis);

	for (int i = 0; i < usu->numPerfis; i++) {
		printf("\t");
		imprimirPerfilRespondedor(&(usu->perfis[i]));
		printf("\n");
	}
}


void imprimirSessao(Sessao* sessao) {
	printf("idSessao: %lld\n", sessao->idSessao);
	printf("idUsuario: %lld\n", sessao->idUsuario);
	printf("idPerfilRespondedor: %lld\n", sessao->idPerfilRespondedor);
	printf("segHoraCriacao: %lld\n", sessao->segHoraCriacao);
	printf("nsegHoraCriacao: %lld\n", sessao->nsegHoraCriacao);
	printf("segHoraAtualizacao: %lld\n", sessao->segHoraAtualizacao);
	printf("nsegHoraAtualizacao: %lld\n", sessao->nsegHoraAtualizacao);
	printf("segTempoValidade: %lld\n", sessao->segTempoValidade);
	printf("segTempoValidadeMax: %lld\n", sessao->segTempoValidadeMax);
}
