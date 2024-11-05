#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Pessoa {
    unsigned long long cpf;
    wchar_t nome[100];  // Usar wchar_t para suportar caracteres Unicode
    wchar_t dataNasc[11];
    wchar_t end[200];
    wchar_t tel[15];
} Pessoa;

typedef struct NoAvl {
    Pessoa pessoa;
    struct NoAvl *esq;
    struct NoAvl *dir;
    int altura;
} NoAvl;

int altura(NoAvl *no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

void atualizaAltura(NoAvl *no) {
    no->altura = 1 + (altura(no->esq) > altura(no->dir) ? altura(no->esq) : altura(no->dir));
}

int fatorBalanceamento(NoAvl *no) {
    return altura(no->esq) - altura(no->dir);
}

NoAvl *rotacaoEsquerda(NoAvl *no) {
    NoAvl *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    atualizaAltura(no);
    atualizaAltura(aux);
    return aux;
}

NoAvl *rotacaoDireita(NoAvl *no) {
    NoAvl *aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    atualizaAltura(no);
    atualizaAltura(aux);
    return aux;
}

NoAvl *rotacaoDuplaEsquerda(NoAvl *no) {
    no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
}

NoAvl *rotacaoDuplaDireita(NoAvl *no) {
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
}

NoAvl* inserir(NoAvl* raiz, Pessoa p) {
    if (raiz == NULL) {
        NoAvl *novoNo = (NoAvl*)malloc(sizeof(NoAvl));
        novoNo->pessoa = p;
        novoNo->esq = novoNo->dir = NULL;
        novoNo->altura = 1;
        return novoNo;
    }

    if (p.cpf < raiz->pessoa.cpf) {
        raiz->esq = inserir(raiz->esq, p);
    } else if (p.cpf > raiz->pessoa.cpf) {
        raiz->dir = inserir(raiz->dir, p);
    } else {
        return raiz;
    }

    atualizaAltura(raiz);

    int fator = fatorBalanceamento(raiz);

    if (fator > 1 && p.cpf < raiz->esq->pessoa.cpf) {
        return rotacaoDireita(raiz);
    }

    if (fator < -1 && p.cpf > raiz->dir->pessoa.cpf) {
        return rotacaoEsquerda(raiz);
    }

    if (fator > 1 && p.cpf > raiz->esq->pessoa.cpf) {
        return rotacaoDuplaDireita(raiz);
    }

    if (fator < -1 && p.cpf < raiz->dir->pessoa.cpf) {
        return rotacaoDuplaEsquerda(raiz);
    }

    return raiz;
}

void imprimirEmOrdem(NoAvl *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        wprintf(L"CPF: %llu, Nome: %ls\n", raiz->pessoa.cpf, raiz->pessoa.nome);
        imprimirEmOrdem(raiz->dir);
    }
}

int main() {
    // Definindo a localidade para UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");

    NoAvl *raiz = NULL;
    
    Pessoa p1 = {12345678901, L"João", L"01/01/1990", L"Rua A", L"1111-1111"};
    Pessoa p2 = {98765432100, L"Maria", L"02/02/1985", L"Rua B", L"2222-2222"};
    Pessoa p3 = {11122334455, L"José", L"03/03/1980", L"Rua C", L"3333-3333"};
    Pessoa p4 = {55544332211, L"Ana", L"04/04/1995", L"Rua D", L"4444-4444"};

    raiz = inserir(raiz, p1);
    raiz = inserir(raiz, p2);
    raiz = inserir(raiz, p3);
    raiz = inserir(raiz, p4);

    wprintf(L"Árvore AVL em ordem:\n");
    imprimirEmOrdem(raiz);

    return 0;
}
