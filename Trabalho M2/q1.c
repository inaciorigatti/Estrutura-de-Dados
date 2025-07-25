#include <stdio.h>
#include <stdlib.h>

#define TAM 7

typedef struct _no
{
    int chave;
    struct _no *proximo;
} No;

typedef struct _tabelaHash 
{
    No *dados[TAM];
} TabelaHash;

int hash_q1(const int k) {
    return k % TAM;
}


TabelaHash *criarTabelaHash() {
    TabelaHash *tabela = (TabelaHash *)calloc(1, sizeof(TabelaHash));

    for (int i = 0; i < TAM; i++) {
        tabela->dados[i] = NULL;
    }

    return tabela;
}

void inserirQ1 (TabelaHash *tabela, const int chave) {
    No *no = (No *) calloc(1, sizeof(No));
    no->chave = chave;
    no->proximo = NULL;

    int indice = hash_q1(no->chave);

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

    //q1 - > 17, 8, 26, 31, 29, 3, 14, 10 e 21
    // 15, 11, 27, 8, 12, 14, 20

    TabelaHash *tabela = criarTabelaHash();
    inserirQ1(tabela, 15);
    imprimir(tabela); printf("\n");
    inserirQ1(tabela, 11);
    imprimir(tabela); printf("\n");
    inserirQ1(tabela, 27);
    imprimir(tabela); printf("\n");
    inserirQ1(tabela, 8);
    imprimir(tabela); printf("\n");
    inserirQ1(tabela, 12);
    imprimir(tabela); printf("\n");
    inserirQ1(tabela, 14);
    imprimir(tabela); printf("\n");
    inserirQ1(tabela, 20);
    imprimir(tabela); printf("\n");

    return 0;
}


