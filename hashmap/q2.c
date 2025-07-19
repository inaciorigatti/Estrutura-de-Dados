#include <stdio.h>
#include <stdlib.h>

#define TAM 11

typedef struct _no
{
    int chave;
    struct _no *proximo;
} No;

typedef struct _tabelaHash
{
    No *dados[TAM];
} TabelaHash;


int hash_q2(const int k) {
    return (2*k + 5) % 11;
}

TabelaHash *criarTabelaHash() {
    TabelaHash *tabela = (TabelaHash *)calloc(1, sizeof(TabelaHash));

    for (int i = 0; i < TAM; i++) {
        tabela->dados[i] = NULL;
    }

    return tabela;
}

void inserirQ2 (TabelaHash *tabela, const int chave) {
    No *no = (No *) calloc(1, sizeof(No));

    no->chave = chave;
    no->proximo = NULL;

    int indice = hash_q2(no->chave);

    if (tabela->dados[indice] == NULL) {
        tabela->dados[indice] = no;
        return;
    }

    No *aux = tabela->dados[indice];

    while (aux != NULL) {

        if (aux->chave == chave) {
            free(aux);
            return;
        }

        if (aux->proximo == NULL) {
            aux->proximo = no;
            return;
        }

        aux = aux->proximo;

    }

}

void imprimir(const TabelaHash *tabela) {
    for (int i = 0; i < TAM; i++)
    {
        printf("[%d]: ", i);
        No *atual = tabela->dados[i];

        if (atual != NULL) {
            No *proximo = atual->proximo;

            if (proximo == NULL) {
                printf("[%d] \n", atual->chave);
            } else {
                printf("[%d] -> ", atual->chave);
            }
            while (proximo != NULL) {
                printf("[%d] -> ", proximo->chave);
                proximo = proximo->proximo;
                if (proximo == NULL)
                    printf("NULL\n");
            }
        }
        else
            printf("NULL\n");
    }
}

int main() {

    TabelaHash *tabela2 = criarTabelaHash();
    inserirQ2(tabela2, 7);
    inserirQ2(tabela2, 18);
    inserirQ2(tabela2, 30);
    inserirQ2(tabela2, 25);
    inserirQ2(tabela2, 50);
    inserirQ2(tabela2, 41);
    inserirQ2(tabela2, 62);
    inserirQ2(tabela2, 14);
    inserirQ2(tabela2, 9);
    inserirQ2(tabela2, 37);
    inserirQ2(tabela2, 3);
    imprimir(tabela2);

    return 0;
}


