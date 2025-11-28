#ifndef CADPERFILLISTAS_H
#define CADPERFILLISTAS_H



/* <nome-respondedor>, <email-respondedor>, <login-respondedor>, <senha-respondedor>, <matricula-perfil>, <codigo-curso-perfil>, <sigla-instituição-perfil>*/

typedef struct LinhaPerfilLote {
	char* nome;
	char* email;
	char* login;
	char* senha;
	char* matricula;
	char* codigoCurso;
	char* siglaInst;
} LinhaPerfilLote;

LinhaPerfilLote* lplCriarLinhaPL();

LinhaPerfilLote* lplConstruirLinhaPL(char* nome, char* email, char* login, char* senha, char* matricula, char* codigoCurso, char* siglaInst);

void imprimirLPL(LinhaPerfilLote* lp);


typedef struct NoLinhaPerfilLote NoLinhaPerfilLote;
struct NoLinhaPerfilLote {
    LinhaPerfilLote* linhapl;

    NoLinhaPerfilLote* ante;
    NoLinhaPerfilLote* prox;

};

typedef struct ListaPerfilLote {
    NoLinhaPerfilLote* prim;
    NoLinhaPerfilLote* ult;

    int numlpls;
} ListaPerfilLote;


ListaPerfilLote* lplCriarListaPL();
NoLinhaPerfilLote* lplCriarNoLinhaPerfilLote(LinhaPerfilLote* linhapl);
int lplInserirLinhaPerfilLote(LinhaPerfilLote* linhapl, ListaPerfilLote* listapl);




typedef struct LinhaRelatorioCadastroLote {
	int numerr;
	char* msg;
	LinhaPerfilLote* lpl;
	Usuario* usuExistente;
} LinhaRelatorioCadastroLote;

LinhaRelatorioCadastroLote* rclCriarLRCL();
LinhaRelatorioCadastroLote* rclConstruirLRCL(int numerr, char* msg, LinhaPerfilLote* lpl, Usuario* usuExistente);

void imprimirLRCL(LinhaRelatorioCadastroLote* linharcl);


typedef struct NoLinhaRelatorioCadastroLote NoLinhaRelatorioCadastroLote;
struct NoLinhaRelatorioCadastroLote {
    LinhaRelatorioCadastroLote* linharcl;

    NoLinhaRelatorioCadastroLote* ante;
    NoLinhaRelatorioCadastroLote* prox;
};

typedef struct RelatorioCadastroLote {
    NoLinhaRelatorioCadastroLote* prim;
    NoLinhaRelatorioCadastroLote* ult;

    int numlrcls;
} RelatorioCadastroLote;


RelatorioCadastroLote* rclCriarRCL();
NoLinhaRelatorioCadastroLote* rclCriarNoLinhaRelatorioCadastroLote(LinhaRelatorioCadastroLote* lrcl);
int rclInserirLinhaRelatorioCadastroLote(LinhaRelatorioCadastroLote* lrcl, RelatorioCadastroLote* rcl);






/*      Implementações      */



LinhaPerfilLote* lplCriarLinhaPL() {

    LinhaPerfilLote* linhapl = (LinhaPerfilLote *) malloc(sizeof(LinhaPerfilLote));

    linhapl->nome = NULL;
    linhapl->email = NULL;
    linhapl->login = NULL;
    linhapl->senha = NULL;
    linhapl->matricula = NULL;
    linhapl->codigoCurso = NULL;
    linhapl->siglaInst = NULL;

    return linhapl;
}



LinhaPerfilLote* lplConstruirLinhaPL(char* nome, char* email, char* login, char* senha, char* matricula, char* codigoCurso, char* siglaInst) {

    LinhaPerfilLote* linhapl = lplCriarLinhaPL();

    linhapl->nome = nome;
    linhapl->email = email;
    linhapl->login = login;
    linhapl->senha = senha;
    linhapl->matricula = matricula;
    linhapl->codigoCurso = codigoCurso;
    linhapl->siglaInst = siglaInst;

    return linhapl;
}



void imprimirLPL(LinhaPerfilLote* lp) {

	printf("nome: %s", lp->nome);
	printf("email: %s", lp->email);
	printf("login: %s", lp->login);
	printf("senha: %s", lp->senha);
	printf("matricula: %s", lp->matricula);
	printf("codigo curso: %s", lp->codigoCurso);
	printf("sigla inst: %s", lp->siglaInst);
}


ListaPerfilLote* lplCriarListaPL() {

    ListaPerfilLote* listapl = (ListaPerfilLote *) malloc(sizeof(ListaPerfilLote));

    listapl->prim = NULL;
    listapl->ult = NULL;
    listapl->numlpls = 0;

    return listapl;
}


NoLinhaPerfilLote* lplCriarNoLinhaPerfilLote(LinhaPerfilLote* linhapl) {

    NoLinhaPerfilLote* nlpl = (NoLinhaPerfilLote *) malloc(sizeof(NoLinhaPerfilLote));

    nlpl->linhapl = linhapl;
    nlpl->ante = NULL;
    nlpl->prox = NULL;

    return nlpl;
}


int lplInserirLinhaPerfilLote(LinhaPerfilLote* linhapl, ListaPerfilLote* listapl) {

    if (linhapl && listapl) {

        NoLinhaPerfilLote* nlpl = lplCriarNoLinhaPerfilLote(linhapl);

        if (listapl->ult) {
            listapl->ult->prox = nlpl;
            nlpl->ante = listapl->ult;

            listapl->numlpls++;
            listapl->ult = nlpl;
        }
        else {
            listapl->prim = nlpl;
            listapl->ult = nlpl;

            listapl->numlpls++;
        }

        return 0;

    }


    return 1;
}


LinhaRelatorioCadastroLote* rclCriarLRCL() {

    LinhaRelatorioCadastroLote* lrcl = (LinhaRelatorioCadastroLote *) malloc(sizeof(LinhaRelatorioCadastroLote));

    lrcl->numerr = 0;
    lrcl->msg = NULL;
    lrcl->lpl = NULL;
    lrcl->usuExistente = NULL;

    return lrcl;
}


LinhaRelatorioCadastroLote* rclConstruirLRCL(int numerr, char* msg, LinhaPerfilLote* lpl, Usuario* usuExistente) {

    LinhaRelatorioCadastroLote* lrcl = (LinhaRelatorioCadastroLote *) malloc(sizeof(LinhaRelatorioCadastroLote));

    lrcl->numerr = numerr;
    lrcl->msg = msg;
    lrcl->lpl = lpl;
    lrcl->usuExistente = usuExistente;

    return lrcl;
}


void imprimirLRCL(LinhaRelatorioCadastroLote* linharcl) {
    if (linharcl) {

        printf("numerr: %d, msg: %s, usuExistente: %p", linharcl->numerr, linharcl->msg, linharcl->usuExistente);
    }
}


RelatorioCadastroLote* rclCriarRCL() {

    RelatorioCadastroLote* rcl = (RelatorioCadastroLote *) malloc(sizeof(RelatorioCadastroLote));

    rcl->prim = NULL;
    rcl->ult = NULL;
    rcl->numlrcls = 0;

    return rcl;
}


NoLinhaRelatorioCadastroLote* rclCriarNoLinhaRelatorioCadastroLote(LinhaRelatorioCadastroLote* lrcl) {

    NoLinhaRelatorioCadastroLote* nolinharcl = (NoLinhaRelatorioCadastroLote *) malloc(sizeof(NoLinhaRelatorioCadastroLote));

    nolinharcl->linharcl = lrcl;
    nolinharcl->ante = NULL;
    nolinharcl->prox = NULL;

    return nolinharcl;
}



int rclInserirLinhaRelatorioCadastroLote(LinhaRelatorioCadastroLote* lrcl, RelatorioCadastroLote* rcl) {

    if (lrcl && rcl) {

        NoLinhaRelatorioCadastroLote* nlrcl = rclCriarNoLinhaRelatorioCadastroLote(lrcl);

        if (rcl->ult) {

            rcl->ult->prox = nlrcl;
            nlrcl->ante = rcl->ult;

            rcl->numlrcls++;
            rcl->ult = nlrcl;
        }
        else {

            rcl->prim = nlrcl;
            rcl->ult = nlrcl;

            rcl->numlrcls++;
        }

        return 0;

    }

    return 1;
}




#endif
