#include <stdio.h> 

void quickSort (int vetor[], int inicio, int fim) {
    int pivo = vetor[inicio]; 
    int esquerdo = inicio;
    int direita = fim; 

    while (esquerdo <= direita) {

        while (vetor[esquerdo] < pivo) esquerdo++;
        while (vetor[direita] > pivo) direita--;

        if (esquerdo <= direita) {
            int valorAtualDireito = vetor[direita]; 
            int valorAtualEsquerda = vetor[esquerdo]; 

            int temp = vetor[esquerdo];
            vetor[esquerdo] = vetor[direita];
            vetor[esquerdo] = temp;
            
            esquerdo++;
            direita--; 
        }
        
    }

    if (inicio < direita) {
        quickSort(vetor, inicio, direita);
    }

    if (esquerdo < fim) {
        quickSort(vetor, inicio, fim); 
    }

}

void imprimir (int vetor[], int tam) {
    
    for(int i = 0; i <= tam; i++) {
        printf("%d ", vetor[i]); 
    }

}

int main () {

    int vetor[] = {4, 2, 8, 7, 1, 5, 3, 6}; 
    int tam = sizeof(vetor) / sizeof(vetor[0]); 

    printf("Vetor original: "); 
    imprimir(vetor, tam); 

    quickSort(vetor, 0, tam - 1); 

    printf("\nVetor ordenado: "); 
    imprimir(vetor, tam);

    return 0;
}   