#include <stdio.h> 
#include <stdlib.h>

void selection (int lista[], int tam) { // guarda o indice 
    //int minidx, temp; 

    for (int  i = 0; i < tam -1; i++) {
        int minidx = i;

        for (int j = i +1; j < tam; j++) {
            if (lista[j] < lista[minidx]) {
                minidx = j; 
            }
        }
        int temp = lista[i];
        lista[i] = lista[minidx];
        lista[minidx] = temp;  
    }
}

int binary (int lista[], int inicio, int fim, int chave) {

    while (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2; 

        if (lista[meio] == chave) {
            return meio;  
        }

        if (lista[meio] < chave) {
            inicio = meio +1; 
        } else {
            fim = meio -1; 
        }
    }
    
    return -1; 
}

void inserction (int lista[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int index = i+1;
        
        while (lista[i] > lista[index])
        {
            if (i < 0) {
                break; 
            }
            
            int temp = lista[i];
            lista[i] = lista[index]; 
            lista[index] = temp;

            i--;
            index--; 
        }
        
    }
}

void imprimir (int lista[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", lista[i]); 
    }
}

int main () {
    
    int lista [] = { 34, 87, 12, 56, 9, 78, 23, 45, 67, 89, 1, 33, 55, 77, 99, 22, 44, 66, 88, 10 };
    int tam = sizeof(lista) / sizeof(lista[0]); 


    selection(lista, tam); 
    printf("%d", binary(lista, 0, tam-1, 10203)); 
    return 0;
}