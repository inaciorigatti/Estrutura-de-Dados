#include <stdio.h>
#include <stdlib.h>
#include <time.h>

volatile double sink;

#define MAX 1000 
#define FILENAME "massa_1000.txt"

//#define MAX 100000
//#define FILENAME "massa_100000.txt"

//#define MAX 500000
//#define FILENAME "massa_500000.txt"

void merge (int vetor[], int inicio, int meio, int fim) {
    
    int indiceEsq, indiceDir, indice;
    int tamanhoEsq = meio - inicio + 1;
    int tamanhoDir = fim - meio;

    int* vetorEsquerdo = (int*) malloc(tamanhoEsq * sizeof(int));
    int* vetorDireito = (int*) malloc(tamanhoDir * sizeof(int));

    for (indiceEsq = 0; indiceEsq < tamanhoEsq; indiceEsq++) {
        vetorEsquerdo[indiceEsq] = vetor[inicio + indiceEsq];
    }

    for (indiceDir = 0; indiceDir < tamanhoDir; indiceDir++) {
        vetorDireito[indiceDir] = vetor[meio + 1 + indiceDir];
    }   

    indiceEsq = 0;
    indiceDir = 0;
    indice = inicio;

    while (indiceEsq < tamanhoEsq && indiceDir < tamanhoDir) {
        if (vetorEsquerdo[indiceEsq] <= vetorDireito[indiceDir]) {
            vetor[indice] = vetorEsquerdo[indiceEsq];
            indiceEsq++;
        } else {
            vetor[indice] = vetorDireito[indiceDir];
            indiceDir++;
        }
        indice++;
    }

    while (indiceEsq < tamanhoEsq) {
        vetor[indice] = vetorEsquerdo[indiceEsq];
        indiceEsq++;
        indice++;
    }

    while (indiceDir < tamanhoDir) {
        vetor[indice] = vetorDireito[indiceDir];
        indiceDir++;
        indice++;
    }

    free(vetorEsquerdo);
    free(vetorDireito);

}

void mergeSort (int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        merge(vetor, inicio, meio, fim);
    }
}

void imprimir (int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d\n", vetor[i]);
    }
}

int main() {

    clock_t start = clock();

    FILE *arquivo;
    int vetor[MAX];
    int tam = 0;

    // Abre o arquivo para leitura
    arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Lê os dados do arquivo
    while (tam < MAX && fscanf(arquivo, "%d", &vetor[tam]) == 1) {
        tam++;
    }
    fclose(arquivo);

    mergeSort(vetor, 0, tam - 1);

    printf("\nVetor ordenado:\n", tam);
    imprimir(vetor, tam); 

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 
    printf("\n%f segundos para executar.", cpu_time_used);
    return 0;
}