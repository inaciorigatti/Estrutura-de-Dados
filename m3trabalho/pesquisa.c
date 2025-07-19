#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

volatile double sink;

void pesquisaLinear (int vetor[], int tam, int valor) {
    
    clock_t start = clock();

    for (int i = 0; i < tam; i++) {
        if (vetor[i] == valor) {
            printf("Valor %d encontrado na posicao %d", vetor[i], i);

            clock_t end = clock();
            double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
            printf("\nTempo total de execucao: %.2f segundos\n", cpu_time_used);
            
            return;
        }
    }
    printf("%d nao encontrado", valor);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
    printf("\nTempo total de execucao: %.2f segundos\n", cpu_time_used); 
}

void pesquisaBinaria(int vetor[], int tam, int valor) {
    clock_t start = clock();

    int inicio = 0;
    int fim = tam - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (vetor[meio] == valor) {
            printf("Valor %d encontrado na posicao %d", vetor[meio], meio);

            clock_t end = clock();
            double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("\nTempo total de execucao: %.2f segundos\n", cpu_time_used);

            return;
        } else if (vetor[meio] < valor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("%d nao encontrado", valor);

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo total de execucao: %.2f segundos\n", cpu_time_used);
}
