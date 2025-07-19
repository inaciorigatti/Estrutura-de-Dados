#include <stdio.h> 
#include <stdlib.h>

void merge (int lista[], int esquerda, int meio, int direita) { 
    int n1 = meio - esquerda + 1; 
    int n2 = direita - meio; 

    int listaEsq[n1] = {};
    for (int i = 0; i < n1; i++) {
        listaEsq
    }
}

void mergeSort (int lista[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(lista, esquerda, meio); 
        mergeSort(lista, meio + 1, direita); 

        merge(lista, esquerda, meio, direita); 
    }
}

void imprimir (int lista[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", lista[i]); 
    }
}

int main () {
    
    int lista [] = { 12, 1, 6, 88, 9, 14, 3, 15 };
    int tam = sizeof(lista) / sizeof(lista[0]); 


    imprimir(lista, tam); 
    return 0;
}