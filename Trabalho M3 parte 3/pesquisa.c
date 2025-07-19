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
