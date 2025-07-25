#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 20
#define TAM_MAX_NOME 50

typedef struct No {
    char chave[TAM_MAX_NOME];
    struct No *proximo;
} No;

typedef struct {
    No *dados[TAM];
} TabelaHash;

int hash(const char texto[]) {
    int soma = 0;
    for (int i = 0; texto[i] != '\0'; i++) {
        soma += texto[i];
    }
    return soma % TAM;
}

TabelaHash* criarTabela() {
    TabelaHash *tabela = (TabelaHash *) calloc(1, sizeof(TabelaHash));
    for (int i = 0; i < TAM; i++) {
        tabela->dados[i] = NULL;
    }
    return tabela;
}

void inserir(TabelaHash *tabela, const char *chave) {
    int indice = hash(chave);
    No *aux = tabela->dados[indice];

    
    while (aux != NULL) {
        if (strcmp(aux->chave, chave) == 0) {
            printf("'%s' já está na tabela.\n", chave);
            return;
        }
        aux = aux->proximo;
    }

    No *novo = (No *) malloc(sizeof(No));
    strcpy(novo->chave, chave);
    novo->proximo = tabela->dados[indice];
    tabela->dados[indice] = novo;

    printf("'%s' inserida na tabela com sucesso.\n", chave);
}

void remover(TabelaHash *tabela, const char *chave) {
    int indice = hash(chave);
    No *atual = tabela->dados[indice];
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            if (anterior == NULL) {
                tabela->dados[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("'%s' removida da tabela.\n", chave);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("'%s' não encontrada na tabela.\n", chave);
}

void imprimir(TabelaHash *tabela) {
    for (int i = 0; i < TAM; i++) {
        printf("[%2d]: ", i);
        No *atual = tabela->dados[i];
        while (atual != NULL) {
            printf("[%s] -> ", atual->chave);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

void liberarTabela(TabelaHash *tabela) {
    for (int i = 0; i < TAM; i++) {
        No *atual = tabela->dados[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(tabela);
}


int main() {
    TabelaHash *tabela = criarTabela();

    const char *linguagens[] = {
        "Python", "Java", "C", "Go", "Kotlin",
        "Swift", "Rust", "Ruby", "PHP", "TypeScript"
    };

    int total = sizeof(linguagens) / sizeof(linguagens[0]);
    for (int i = 0; i < total; i++) {
        inserir(tabela, linguagens[i]);
    }

    int opcao;
    char nome[TAM_MAX_NOME];

    do {
        printf("\n=== MENU ===\n");
        printf("1. Inserir nova linguagem\n");
        printf("2. Remover linguagem\n");
        printf("3. Imprimir tabela\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf(" %d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                printf("Digite o nome da linguagem: ");
                fgets(nome, TAM_MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0'; 
                inserir(tabela, nome);
                break;
            case 2:
                printf("Digite a linguagem para remover: ");
                fgets(nome, TAM_MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                remover(tabela, nome);
                break;
            case 3:
                imprimir(tabela);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarTabela(tabela);
    return 0;
}

// Corrigido
int particiona (int v[], int inicio, int fim) {
    int pivo = v[fim];
    int i = inicio - 1;
    int j, temp;

    for (j = inicio; j < fim; j++) {
        if (v[j] < pivo) {
            i++;
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    temp = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = temp;

    return i + 1;
}

void quickSort (int v[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particiona(v, inicio, fim);

        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int buscaBinaria(int v[], int n, int chave) {
    int inicio = 0;
    int fim = n - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if (v[meio] == chave) {
            return meio; 
        } else if (v[meio] < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1; 
}
