#include <stdio.h>
#include <stdlib.h>

#include "header.h"

void limpar () {
    printf("\e[H\e[2J"); // LIMPA O CONSOLE
}

int main () {

    int tamanho = 0;
    int *vetor = NULL;

    printf("\nDigite o tamanho do vetor (1 - 100000): ");
    scanf("%d", &tamanho);
            
    while (tamanho < 1 || tamanho > 100000) { // cem mil 
        limpar();
        printf("Tamanho invalido! Digite um valor entre 1 e 10000.\n");
        scanf("%d", &tamanho); 
    }
    
    // aloca o vetor
    vetor = (int *)malloc(tamanho * sizeof(int));          
    limpar(); 

    printf("Situacao inicial dos dados:\n");
    printf("1. Melhor caso\n");
    printf("2. Pior caso\n");
    printf("3. Aleatorio\n");
    int escolhaCaso = -1; 
    while (escolhaCaso < 1 || escolhaCaso > 3) {
        scanf("%d", &escolhaCaso);
    }
    limpar();

    // SITUACAO INICIAL DADOS 
    switch (escolhaCaso) {
        case 1: 
            // melhor caso  
            break;
        case 2:
            // pior
            break;
        case 3:
            // aleatorio
            break;
    }
    limpar();
    
    // MENU
    int escolhaMenu = -1; 
    while (escolhaMenu != 0) {
        printf("-== MENU ==-\n");
        printf("1. Ordenar\n");
        printf("2. Pesquisar\n");
        printf("3. Imprimir\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolhaMenu); 

        switch (escolhaMenu) {
            // ordenar
            case 1:
                printf("1. Merge sort\n");
                printf("2. Quick sort\n");
                printf("3. Insertion sort\n");
                printf("4. Shell sort\n");
                printf("5. Cocktail sort\n");
                printf("6. Bubble sort\n"); 

                int escolhaOrdenar = -1;
                while (escolhaOrdenar < 1 || escolhaOrdenar > 6) {
                    scanf("%d", &escolhaOrdenar);
                }
                
                switch (escolhaOrdenar) {
                    case 1: 
                        //merge
                        break;
                    case 2: 
                        //quick
                        break;
                    case 3: 
                        //insertion
                        break;
                    case 4: 
                        //shell
                        break;
                    case 5: 
                        //cocktail
                        break;
                    case 6: 
                        //bubble
                        break;
                }
            break; 
            
            // pesquisar
            case 2:
            
                printf("Informe o valor a ser buscado: ");
                int valor; 
                scanf("%d", &valor); 

                printf("1. Pesquisa Linear\n");
                printf("2. Pesquisa Binaria\n");

                int escolhaPesquisa = -1;
                while (escolhaPesquisa < 1 || escolhaPesquisa > 2) {
                    scanf("%d", &escolhaPesquisa);
                }

                switch (escolhaPesquisa) {
                    case 1:
                        pesquisaLinear(vetor, tamanho, valor); 
                        break;
                    
                    case 2:
                        //binara
                        break; 
                }
            break;
            
            // imprimir
            case 3: 
                for (int i = 0; i < tamanho; i++) {
                    printf("%d ", vetor[i]);
                }
                printf("\n");
                break;
            
            // sair
            case 0:
                break;
        
            default:
                printf("Escolha Invalida!\n"); 
                break;
        }
    }
    free(vetor); 
    printf("Saindo..."); 

    return 0; 
}