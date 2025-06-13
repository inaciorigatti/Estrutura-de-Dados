#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define TAMANHO 6

// Chave única para a inserção do nó na tabela
typedef struct _no
{
    int chave;
    char nome[100];
    struct _no *proximo;
} No;

// Define a quantidade de Nós que cabem dentro da tabela, sendo ela um tipo de dado não linear
typedef struct _tabelaHash
{
    No *dados[TAMANHO];
} TabelaHash;

// Cálculo para receber o indíce do elemento na tabela
int _hash(const int chave)
{
    return chave % TAMANHO;
}

TabelaHash *criarTabelaHash()
{
    TabelaHash *tabela = (TabelaHash *)calloc(1, sizeof(TabelaHash));
    for (int i = 0; i < TAMANHO; i++)
        tabela->dados[i] = NULL;
    
    return tabela;
}

// Calcula em qual indíce o nó será inserido na tabela
void inserirDado(TabelaHash *tabela, const int chave, const char *nome)
{
    No *novo = (No *)calloc(1, sizeof(No));
    novo->chave = chave;
    novo->proximo = NULL;
    
    

    int indice = _hash(novo->chave);
    if (tabela->dados[indice] == NULL)
    {
        tabela->dados[indice] = novo;
        return;
    }

    No *atual = tabela->dados[indice];
    while (atual != NULL)
    {
        if (atual->chave == chave)
        {
            strcpy(atual->nome, nome);
            free(novo);
            return;
        }

        if (atual->proximo == NULL)
        {
            atual->proximo = novo;
            return;
        }

        atual = atual->proximo;
    }
}

void imprimir(const TabelaHash *tabela)
{
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("[%d]: ", i);
        No *atual = tabela->dados[i];
        if (atual != NULL)
        {
            No *proximo = atual->proximo;
            if (proximo == NULL)
                printf("(%d, %s) \n", atual->chave, atual->nome);
            else
                printf("(%d, %s) -> ", atual->chave, atual->nome);

            while (proximo != NULL)
            {
                printf("(%d, %s) -> ", proximo->chave, proximo->nome);
                proximo = proximo->proximo;
                if (proximo == NULL)
                    printf("NULL\n");
            }
        }
        else
            printf("NULL\n");
    }
}