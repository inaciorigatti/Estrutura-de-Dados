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
        }
        int aux = vetor[i];
        vetor[i] = vetor[min]; 
        vetor[min] = aux;
    }
}

void bubbleSort(int vetor[], int tam) {
    for (int j = 0; j < tam - 1; j++) {
        for (int i = 0; i < tam - 1 - j; i++) {  
            if (vetor[i] > vetor[i + 1]) {
                int temp = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = temp;
            }
        } 
    }
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

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar (int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];         // pivô escolhido como o último elemento
    int i = inicio - 1;            // índice do menor elemento

    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            swap(&vetor[i], &vetor[j]); // coloca os menores na esquerda do pivô
        }
    }

    swap(&vetor[i + 1], &vetor[fim]); // arruma o pivo
    
    return i + 1;                     // retorna o índice do pivô
}

void quickSort (int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int indicePivo = particionar(vetor, inicio, fim); // partição

        quickSort(vetor, inicio, indicePivo - 1);          // esquerda
        quickSort(vetor, indicePivo + 1, fim);             // direita
    }
}


void shellSort (int vetor[], int tamanho) {
    // gap grande e vai diminuindo pela metade
    for (int gap = tamanho / 2; gap > 0; gap /= 2) {

        // insertion sort para os elementos com  gap
        for (int i = gap; i < tamanho; i++) {
            int temp = vetor[i];
            int j;

            for (j = i; j >= gap && vetor[j - gap] > temp; j -= gap) {
                vetor[j] = vetor[j - gap];
            }

            vetor[j] = temp; 
        }
    }
}

void cocktailSort (int vetor[], int tamanho) {

    int trocado = 1;
    int inicio = 0;
    int fim = tamanho - 1;

    while (trocado) {
        trocado = 0;

        // esquerda para a direita 
        for (int i = inicio; i < fim; i++) {
            if (vetor[i] > vetor[i + 1]) {
                int temp = vetor[i];

                vetor[i] = vetor[i + 1];
                vetor[i + 1] = temp;

                trocado = 1;
            }
        }

        // se nada foi trocado o vetor está ordenado
        if (!trocado) {
            break;
        }

        fim--;
        trocado = 0;

        // direita para esquerdda
        for (int i = fim; i > inicio; i--) {

            if (vetor[i] < vetor[i - 1]) {
                int temp = vetor[i];

                vetor[i] = vetor[i - 1];
                vetor[i - 1] = temp;

                trocado = 1;
            }
        }

        inicio++;
    }
}


