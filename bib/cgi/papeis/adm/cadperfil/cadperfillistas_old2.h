#ifndef CADPERFILLISTAS_H
#define CADPERFILLISTAS_H



/* <nome-respondedor>, <email-respondedor>, <senha-respondedor>, <matricula-perfil>, <codigo-curso-perfil>, <sigla-instituição-perfil>*/

typedef struct LinhaPerfilLote {
	char* nome;
	char* email;
	char* login;
    char* senha;
	char* matricula;
	char* codigoCurso;
	char* siglaInst;

    int perfilExiste;

    Usuario* usuExistente;
} LinhaPerfilLote;

LinhaPerfilLote* lplCriarLinha();

LinhaPerfilLote* lplConstruirLinha(char* nome, char* email, char* login, char* senha, char* matricula, char* codigoCurso, char* siglaInst);

void lplImprimir(LinhaPerfilLote* linha);


typedef struct NoLinhaPerfilLote NoLinhaPerfilLote;
struct NoLinhaPerfilLote {
    LinhaPerfilLote* linha;

    NoLinhaPerfilLote* ante;
    NoLinhaPerfilLote* prox;

};

typedef struct ListaPerfilLote {
    NoLinhaPerfilLote* prim;
    NoLinhaPerfilLote* ult;

    int numlins;
} ListaPerfilLote;


ListaPerfilLote* lplCriarLista();
NoLinhaPerfilLote* lplCriarNo(LinhaPerfilLote* linha);
int lplInserirLinha(LinhaPerfilLote* linha, ListaPerfilLote* lista);




typedef struct LinhaRelCadPerfil {
	int numerr;        // Número de erro:       1 - linha nula
                       //                       2 - quantidade de campos errada
                       //                       3 - linha nula durante extração de campos
                       //                       11 a 23 - erro de validação de campos



	char* msg;
	LinhaPerfilLote* lpl;
    //Usuario* usuExistente;
} LinhaRelCadPerfil;

LinhaRelCadPerfil* rcpCriarLinha();
LinhaRelCadPerfil* rcpConstruirLinha(int numerr, char* msg, LinhaPerfilLote* lpl);

void rcpImprimir(LinhaRelCadPerfil* linha);


typedef struct NoLinhaRelCadPerfil NoLinhaRelCadPerfil;
struct NoLinhaRelCadPerfil {
    LinhaRelCadPerfil* linha;

    NoLinhaRelCadPerfil* ante;
    NoLinhaRelCadPerfil* prox;
};

typedef struct RelatorioCadPerfil {
    NoLinhaRelCadPerfil* prim;
    NoLinhaRelCadPerfil* ult;

    int status;                 // Número de erro:      1 - Linha nula, problema na leitura do arquivo
                                //                      2 - Linhas com número de campos errado
                                //                      3 - Erro na separação dos campos
                                //                      4 - Caractere ou valor inválido
                                //                      5 - Erro ao buscar login no banco
                                //                      6 - Já existe usuário com esse login
                                //                      7 - Curso não existe
                                //                      8 - Login repetido entre novos logins

    int numlins;
} RelatorioCadPerfil;


RelatorioCadPerfil* rcpCriar();
NoLinhaRelCadPerfil* rcpCriarNo(LinhaRelCadPerfil* linha);
int rcpInserirLinha(LinhaRelCadPerfil* linha, RelatorioCadPerfil* rel);




////////////////////////////////


int lplNumCamposListaPerfis(Multilinhas* ml, RelatorioCadPerfil* rel);






/*      Implementações      */



LinhaPerfilLote* lplCriarLinha() {

    LinhaPerfilLote* linhapl = (LinhaPerfilLote *) malloc(sizeof(LinhaPerfilLote));

    linhapl->nome = NULL;
    linhapl->email = NULL;
    linhapl->login = NULL;
    linhapl->senha = NULL;
    linhapl->matricula = NULL;
    linhapl->codigoCurso = NULL;
    linhapl->siglaInst = NULL;

    linhapl->perfilExiste = 0;

    linhapl->usuExistente = NULL;

    return linhapl;
}



LinhaPerfilLote* lplConstruirLinha(char* nome, char* email, char* login, char* senha, char* matricula, char* codigoCurso, char* siglaInst) {

    LinhaPerfilLote* linhapl = lplCriarLinha();

    linhapl->nome = nome;
    linhapl->email = email;
    linhapl->login = login;
    linhapl->senha = senha;
    linhapl->matricula = matricula;
    linhapl->codigoCurso = codigoCurso;
    linhapl->siglaInst = siglaInst;

    linhapl->perfilExiste = 0;

    linhapl->usuExistente = NULL;

    return linhapl;
}



void lplImprimir(LinhaPerfilLote* lp) {

	printf("nome: %s", lp->nome);
	printf("email: %s", lp->email);
	printf("login: %s", lp->login);
	printf("senha: %s", lp->senha);
	printf("matricula: %s", lp->matricula);
	printf("codigo curso: %s", lp->codigoCurso);
	printf("sigla inst: %s", lp->siglaInst);
}


ListaPerfilLote* lplCriarLista() {

    ListaPerfilLote* listapl = (ListaPerfilLote *) malloc(sizeof(ListaPerfilLote));

    listapl->prim = NULL;
    listapl->ult = NULL;
    listapl->numlins = 0;

    return listapl;
}

NoLinhaPerfilLote* lplCriarNo(LinhaPerfilLote* linha) {

    NoLinhaPerfilLote* nolp = (NoLinhaPerfilLote *) malloc(sizeof(NoLinhaPerfilLote));

    nolp->linha = linha;
    nolp->ante = NULL;
    nolp->prox = NULL;

    return nolp;
}


int lplInserirLinha(LinhaPerfilLote* linha, ListaPerfilLote* lista) {

    if (linha && lista) {

        NoLinhaPerfilLote* nolp = lplCriarNo(linha);

        if (lista->ult) {
            lista->ult->prox = nolp;
            nolp->ante = lista->ult;

            lista->numlins++;
            lista->ult = nolp;
        }
        else {
            lista->prim = nolp;
            lista->ult = nolp;

            lista->numlins  ++;
        }

        return 0;

    }


    return 1;
}


LinhaRelCadPerfil* rcpCriarLinha() {

    LinhaRelCadPerfil* linha = (LinhaRelCadPerfil *) malloc(sizeof(LinhaRelCadPerfil));

    linha->numerr = 0;
    linha->msg = NULL;
    linha->lpl = NULL;
    //linha->usuExistente = NULL;

    return linha;
}


LinhaRelCadPerfil* rcpConstruirLinha(int numerr, char* msg, LinhaPerfilLote* lpl) {

    LinhaRelCadPerfil* linha = (LinhaRelCadPerfil *) malloc(sizeof(LinhaRelCadPerfil));

    linha->numerr = numerr;

    linha->msg = msg ? copiastr(msg) : "";
    linha->lpl = lpl;
    //linha->usuExistente = usuExistente;

    return linha;
}


void rcpImprimir(LinhaRelCadPerfil* linha) {
    if (linha){

        printf("numerr: %d, msg: %s, usuExistente: %p", linha->numerr, linha->msg, linha->lpl->usuExistente);
    }
}


RelatorioCadPerfil* rcpCriar() {

    RelatorioCadPerfil* rel = (RelatorioCadPerfil *) malloc(sizeof(RelatorioCadPerfil));

    rel->prim = NULL;
    rel->ult = NULL;
    rel->numlins = 0;
    rel->status = 0;

    return rel;
}


NoLinhaRelCadPerfil* rcpCriarNo(LinhaRelCadPerfil* linha) {

    NoLinhaRelCadPerfil* nolinha = (NoLinhaRelCadPerfil *) malloc(sizeof(NoLinhaRelCadPerfil));

    nolinha->linha = linha;
    nolinha->ante = NULL;
    nolinha->prox = NULL;

    return nolinha;
}



int rcpInserirLinha(LinhaRelCadPerfil* linha, RelatorioCadPerfil* rel) {

    if (linha && rel) {

        NoLinhaRelCadPerfil* nolinha = rcpCriarNo(linha);

        if (rel->ult) {

            rel->ult->prox = nolinha;
            nolinha->ante = rel->ult;

            rel->numlins++;
            rel->ult = nolinha;
        }
        else {

            rel->prim = nolinha;
            rel->ult = nolinha;

            rel->numlins++;
        }

        return 0;

    }

    return 1;
}






////////////////////////////////



int lplNumCamposListaPerfis(Multilinhas* ml, RelatorioCadPerfil* rel) {

    // criar relatório

    rel = rcpCriar();
    rel->status = 0;

    // checar número de campos em cada linha

    NoLinha* nl = ml->prim;
    int nlin = 0;
    int nc = 0;

    LinhaRelCadPerfil* linha = NULL;

    int ret = 0;
    while (nl) {

        if (nl->linha) {

            nc = contacar(nl->linha, ',');

            if (nc != 4) {		// número de campos errado

                rel->status = 2;

                char msg[500] = "";
                sprintf(msg, "A linha %d possui número errado de campos: %d campos.", nlin + 1, nc);

                linha = rcpConstruirLinha(2, msg, NULL);

                rcpInserirLinha(linha, rel);

                ret = 1;
            }
        }
        else {

            rel->status = 1;

            char msg[500] = "";
            sprintf(msg, "Linha %d nula. Houve um erro na leitura do arquivo de perfis. Verifique se o arquivo está corrompido.", nc);

            linha = rcpConstruirLinha(1, msg, NULL);

            rcpInserirLinha(linha, rel);

            ret = 1;
        }

        nl = nl->prox;
        nlin++;
    }

    return ret;

}







#endif
