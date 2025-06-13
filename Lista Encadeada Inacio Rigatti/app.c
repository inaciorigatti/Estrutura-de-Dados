#include <stdio.h>
#include "lista_encadeada.h"

int main() {

    ListaEncadeada * lista = criarListaEncadeada();
    ListaEncadeada * lista2 = criarListaEncadeada();
    
    imprimir(lista);
    adicionarNoInicio(lista, 29);
    imprimir(lista);
    adicionarNoInicio(lista, 36);
    imprimir(lista);
    adicionarNoInicio(lista, 12);
    imprimir(lista);
    adicionarNoInicio(lista, 99);
    imprimir(lista);

    printf("\n");

    imprimir(lista2);
    adicionarNoFinal(lista2, 77);
    imprimir(lista2);
    adicionarNoFinal(lista2, 45);
    imprimir(lista2);
    adicionarNoFinal(lista2, 11);
    imprimir(lista2);
    adicionarNoFinal(lista2, 9);
    imprimir(lista2);

    printf("\n");

    printf("\nRemovendo o primeiro elemento:\n");
    removerPrimeiro(lista);
    imprimir(lista);

    printf("\nRemovendo o último elemento:\n");
    removerUltimo(lista);
    imprimir(lista);

    printf("\nRemovendo o elemento 77:\n");
    removerEspecifico(lista2, 77);
    imprimir(lista2);


    return 0;
}