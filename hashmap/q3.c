#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

#define TAM 16

typedef struct _no
{
    char chave;
    struct _no *proximo;
} No;

typedef struct _tabelaHash
{
    No *dados[TAM];
} TabelaHash;


int validarLetra(const char letra) {
    char letraMin = tolower(letra);

    if (letraMin >= 'a' && letraMin <= 'z') {
        return letraMin - 'a' + 1;
    }
    
    return -1;
}

int hash_q3(const char letra) { 
    return (11 * validarLetra(letra)) % TAM; 
}

TabelaHash *criarTabelaHash() {
    TabelaHash *tabela = (TabelaHash *)calloc(1, sizeof(TabelaHash));

    for (int i = 0; i < TAM; i++) {
        tabela->dados[i] = NULL;
    }

    return tabela;
}

void inserirQ3 (TabelaHash *tabela, const char chave) {
    No *no = (No *) calloc(1, sizeof(No));

    no->chave = chave; 
    no->proximo = NULL; 

    int indice = hash_q3(no->chave);
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


void imprimir(const TabelaHash *tabela) {

    for (int i = 0; i < TAM; i++)
    {
        if(tabela->dados[i] == NULL) {
        printf("[%d]: NULL\n", i);
    } else {
        printf("[%d]: [%c]\n", i, tabela->dados[i]->chave);
        }
    }
}

int main() {

    TabelaHash *tabela3 = criarTabelaHash();
    inserirQ3(tabela3, 'a');
    inserirQ3(tabela3, 'l');
    inserirQ3(tabela3, 'g');
    inserirQ3(tabela3, 'o');
    inserirQ3(tabela3, 'r');
    inserirQ3(tabela3, 'i');
    inserirQ3(tabela3, 't');
    inserirQ3(tabela3, 'i');
    inserirQ3(tabela3, 'm');
    inserirQ3(tabela3, 'o');
    inserirQ3(tabela3, 's');

    inserirQ3(tabela3, 'i');
    inserirQ3(tabela3, 'n');
    inserirQ3(tabela3, 'a');
    inserirQ3(tabela3, 'c');
    inserirQ3(tabela3, 'i');
    inserirQ3(tabela3, 'o');

    imprimir(tabela3);  
    return 0;
}


