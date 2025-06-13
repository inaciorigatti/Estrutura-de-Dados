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

int hash_q4(const int k) { 
    return k % TAM; 
}

TabelaHash *criarTabelaHash() {
    TabelaHash *tabela = (TabelaHash *)calloc(1, sizeof(TabelaHash));

    for (int i = 0; i < TAM; i++) {
        tabela->dados[i] = NULL;
    }

    return tabela;
}

void inserirQ4 (TabelaHash *tabela, const int chave) {
    No *no = (No *) calloc(1, sizeof(No));

    no->chave = chave; 
    no->proximo = NULL; 

    int indice = hash_q4(no->chave);
    int inicio = indice;

    while (tabela->dados[indice] != NULL) {
        indice = (indice + 1) % TAM;

            if (indice == inicio) {
            printf("Tabela cheia.\n");
            return;
        }
    }

    tabela->dados[indice] = no;
}

void remover (TabelaHash *tabela, const int chave) {

    for (int i = 0; i < TAM; i++){
        if (tabela->dados[i] != NULL && tabela->dados[i]->chave == chave) {
            free(tabela->dados[i]);
            tabela->dados[i] = NULL;
            return; 
        }
    }

}


void imprimir(const TabelaHash *tabela) {

    for (int i = 0; i < TAM; i++)
    {
        if(tabela->dados[i] == NULL) {
        printf("[%d]: NULL\n", i);
    } else {
        printf("[%d]: [%d]\n", i, tabela->dados[i]->chave);
        }
    }
}

int main() {

    TabelaHash *tabela4 = criarTabelaHash();
    inserirQ4(tabela4, 8);
    inserirQ4(tabela4, 21);
    inserirQ4(tabela4, 19);
    inserirQ4(tabela4, 33);
    inserirQ4(tabela4, 27);
    inserirQ4(tabela4, 5);
    inserirQ4(tabela4, 0);
    inserirQ4(tabela4, 12);
    inserirQ4(tabela4, 31);

    imprimir(tabela4); 
    printf("\n");

    remover(tabela4, 27);
    remover(tabela4, 5);

    imprimir(tabela4);
    printf("\n");
    
    inserirQ4(tabela4, 17);
    inserirQ4(tabela4, 2);


    imprimir(tabela4);
    
    return 0;
}


