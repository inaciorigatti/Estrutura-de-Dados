#include <stdio.h>
#include <stdlib.h>

// Funções de ordenação
void merge(int vetor[], int inicio, int meio, int fim);
void mergeSort(int vetor[], int inicio, int fim);
void selectionSort(int vetor[], int tam);
void bubbleSort(int vetor[], int tam);
void insertionSort(int vetor[], int tam);

// Funções de pesquisa
void pesquisaLinear(int vetor[], int tam, int valor);
void executarPesquisa(int vetor[], int tamanho, int opcao, int valor);  // Adicione o quarto parâmetro aqui

// Funções de inicialização de dados
void melhorCaso(int vetor[], int tam);
void piorCaso(int vetor[], int tam);
void aleatorioCaso(int vetor[], int tam);
