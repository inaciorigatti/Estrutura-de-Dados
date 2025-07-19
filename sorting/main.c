#include <stdio.h>
#include <stdlib.h>

void bubblesort (int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam - i; j++) {
            if (vetor[j] > vetor[j+1]) {
                int temp = vetor[j+1]; 
                vetor[j+1] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}

void imprimir(int vetor[], int tam) {
    for (int i =0; i <tam; i++) {
        printf("%d ", vetor[i]); 
    }
}

int main () { 
    
    int vetor[] = {3, 5, 1, 6, 9};
    int tam = sizeof(vetor) / sizeof(vetor[0]); 

    bubblesort(vetor, tam -1);

    imprimir(vetor, tam);
    return 0;
}