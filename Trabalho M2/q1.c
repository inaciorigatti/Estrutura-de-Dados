#include <stdio.h>
#include <stdlib.h>

#define TAM 13

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

    TabelaHash *tabela = criarTabelaHash();
    inserirQ1(tabela, 17);
    inserirQ1(tabela, 8);
    inserirQ1(tabela, 26);
    inserirQ1(tabela, 31);
    inserirQ1(tabela, 29);
    inserirQ1(tabela, 3);
    inserirQ1(tabela, 14);
    inserirQ1(tabela, 10);
    inserirQ1(tabela, 21);
    imprimir(tabela); 

    return 0;
}


