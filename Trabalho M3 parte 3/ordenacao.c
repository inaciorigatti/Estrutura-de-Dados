#include <stdio.h>
#include <stdlib.h>

#include "header.h"

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

void selectionSort (int vetor[], int tam) {
    int min; 
    for (int i = 0; i < tam - 1; i++) {
         min = i; 
        for (int j = i + 1; j < tam; j++) {
            if (vetor[min] > vetor[j]) {
                min = j; 
            }
            int aux = vetor[i];
            vetor[i] = vetor[min]; 
            vetor[min] = aux;
        }
    }
}

void bubbleSort (int vetor[], int tam) {
    
    if (tam < 1) {
        return;
    }

    for (int i = 0; i < tam; i++) {
        if (vetor[i] > vetor[i + 1]) {
            int temp = vetor[i]; 
            vetor[i] = vetor[i + 1];
            vetor[i + 1] = temp; 
        }
    }
    bubbleSort(vetor, tam - 1); 
}

void insertionSort(int vetor[], int tam) {
    int i, chave, j;
    for (i = 1; i < tam; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}
