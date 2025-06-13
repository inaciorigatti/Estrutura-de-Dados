#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

typedef struct _no {
    int valor;
    struct _no *proximo;
} No;

typedef struct _lista_encadeada
{
    No *inicio;
} ListaEncadeada;

No *_criarNo(int valor) {
    No *no = (No *) calloc(1, (sizeof(No)));
    no->valor = valor;
    no->proximo = NULL;

    return no;
}

ListaEncadeada *criarListaEncadeada(){
    ListaEncadeada *lista = (ListaEncadeada *) calloc(1, (sizeof(ListaEncadeada)));
    lista->inicio = NULL;

    return lista;
}

void adicionarNoInicio(ListaEncadeada *lista, int valor) {
    No *no = _criarNo(valor);
    no->proximo = lista->inicio;
    lista->inicio = no;
}

void imprimir(const ListaEncadeada *lista) {
    No *no = lista->inicio;
    while (no != NULL)
    {
        printf("%d -> ", no->valor);
        no = no->proximo;
    }

    printf("NULL \n");
}

void adicionarNoFinal(ListaEncadeada *lista, int valor) {
    No *novoNo = _criarNo(valor);

    if (lista->inicio == NULL)
    {
        lista->inicio = novoNo;
    } 
    else 
    {
        No *noAxu = lista->inicio;
        while (noAxu->proximo != NULL)
        {
            noAxu = noAxu->proximo;
        }

        noAxu->proximo = novoNo;
    }
}

void removerPrimeiro(ListaEncadeada *lista) {
    if (lista->inicio == NULL) {
        return;
    }

    No *temp = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    temp->proximo = NULL; 
}

void removerUltimo(ListaEncadeada *lista) {
    if (lista->inicio == NULL) {
        return;
    }

    if (lista->inicio->proximo == NULL) {
        lista->inicio->proximo = NULL;
        return;
    }

    No *atual = lista->inicio;
    while (atual->proximo->proximo != NULL) {
        atual = atual->proximo;
    }

    atual->proximo->proximo = NULL; 
    atual->proximo = NULL;
}

void removerEspecifico(ListaEncadeada *lista, int valor) {
    if (lista->inicio == NULL) {
        return;
    }

    if (lista->inicio->valor == valor) {
        removerPrimeiro(lista);
        return;
    }

    No *atual = lista->inicio;
    while (atual->proximo != NULL && atual->proximo->valor != valor) {
        atual = atual->proximo;
    }

    if (atual->proximo != NULL) {
        No *temp = atual->proximo;
        atual->proximo = atual->proximo->proximo;
        temp->proximo = NULL; 
    }
}
