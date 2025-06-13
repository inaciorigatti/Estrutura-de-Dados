#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 1000
#define FILENAME "massa_1000.txt"
volatile double sink;

void selectionSort(int lista[], int n) {
    for (int i = 0; i < n - 1; i++) {
        
        // assume que a primera posição possui o menor numero
        int min_idx = i;
    
        for (int j = i + 1; j < n; j++) {       // procura o minimo em todos os numeros maiores q i 
            if (lista[j] < lista[min_idx]) {    // se o minimo estiver em j ele indica o novo minimo 
              
                // muda o menor indice para o encontrado
                min_idx = j;
            }
        }
        
        int temp = lista[i];        // guarda o antigo minimo
        lista[i] = lista[min_idx];  // coloca o minimo novo onde estava para a posicao verificada (swap)
        lista[min_idx] = temp;      // coloca o antigo minimo na posição correta 
       }
}

int main () {

    clock_t start = clock();

    int lista[MAX_SIZE];
    int tamanho = 0;

    FILE *file;
    char line[256];
    char *token;

    // Abre o arquivo para leitura
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê os números do arquivo
    while (fgets(line, sizeof(line), file) != NULL) {
        // Divide a linha em tokens usando a vírgula como delimitador
        token = strtok(line, ",");
        while (token != NULL && tamanho < MAX_SIZE) {
            lista[tamanho++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    // Fecha o arquivo
    fclose(file);

    //int teste[] = {34, 25, 12, 43, 9};
    //int n = sizeof(teste) / sizeof(teste[0]);

    selectionSort(lista, tamanho);

    // Imprime 
    printf("lista ordenada:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 
    printf("\n%f segundos para executar.", cpu_time_used);

    return 0;
}