#include <stdio.h>
#include <stdlib.h>

// Casos
void melhorCaso (int vetor[], int tam);
void piorCaso (int vetor[], int tam);
void aleatorioCaso (int vetor[], int tam);

// Ordenar
void merge(int vetor[], int inicio, int meio, int fim);
void mergeSort(int vetor[], int inicio, int fim);
void selectionSort(int vetor[], int tam);
void bubbleSort(int vetor[], int tam);
void insertionSort(int vetor[], int tam);
void swap(int *a, int *b);
int particionar(int vetor[], int inicio, int fim);
void quickSort(int vetor[], int inicio, int fim);
void shellSort(int vetor[], int tamanho);
void cocktailSort(int vetor[], int tamanho);

// Pesquisa
void pesquisaLinear (int vetor[], int tam, int valor);
void pesquisaBinaria(int vetor[], int tam, int valor);