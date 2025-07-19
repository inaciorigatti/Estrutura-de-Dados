#include <stdio.h>
#include <stdlib.h>

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

void imprimir (int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
}

int main () {

    int vetor[] = { 9, 1, 13, 55, 16, 27, 7, 22, 10 };
    int tam = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor desorenado: ");
    imprimir(vetor, tam);

    bubbleSort(vetor, tam);

    printf("\nVetor ordenado: ");
    imprimir(vetor, tam);
    
    return 0;
}