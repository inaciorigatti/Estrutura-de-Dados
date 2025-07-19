#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "header.h"

void melhorCaso (int vetor[], int tam) {
    for (int i = 0; i < tam; i++) { 
        vetor[i] = i + 1; 
    }
}

void piorCaso (int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        vetor[i] = tam - 1 - i; 
    }
}

void aleatorioCaso(int vetor[], int tam) {
    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        vetor[i] = rand() % 100005;
    }
}