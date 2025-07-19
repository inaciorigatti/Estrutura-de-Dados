// Inácio Radin Rigatti

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
} Node;


Node *inserir (Node *root, int valor) {
    Node *new = (Node *)calloc(1, sizeof(Node));
    new->valor = valor;
    new->esquerda = NULL;
    new->direita = NULL;

    if (root == NULL) {
        return new; 

    } else {
        Node *atual = root; 
        Node *pai = NULL; 
        
        while (1)
        {
            pai = atual;
            if (valor < pai->valor) {
                atual = atual->esquerda;
                
                if (atual == NULL){
                    pai->esquerda = new; 
                    return root; 
                }
            } else { 
                atual = atual->direita;
                if (atual == NULL) {
                    pai->direita = new; 
                    return root; 
                }
            }
        }
        
    }

}

//Questao 6
Node* buscar (Node *root, int valor) {

    while (root != NULL) {

        if (valor == root->valor) {
            return root; 

        } else if (valor < root->valor) {
            root = root->esquerda; //continua na subarvore esquerda

        } else {
            root = root->direita; //continua na subarvore direita
        }
    }

    return 0;
}


void preOrder (Node *root) {
    if (root != NULL) {
        printf("%d ", root->valor);
        preOrder(root->esquerda);
        preOrder(root->direita);
    }
}


//Questão 1
int contarFolhas (Node *root) {

    if (root == NULL) {
        return 0; 
    }

    if (root->esquerda == NULL && root->direita == NULL) {
        return 1;
    }

    return contarFolhas(root->esquerda) + contarFolhas(root->direita);

}

//Questao 5 
int saoIguais (Node *a, Node *b) {
    
    if (a == NULL && b == NULL) {
        return 1;
    }

    if (a == NULL || b == NULL) {
        return 0;
    }

    if (a->valor == b->valor) {
        return saoIguais(a->esquerda, b->esquerda) && saoIguais(a->direita, b->direita);

    } else {
        return 0;
    }

}

//Questao 4 
int alturaArvore (Node *root) {
    
    if (root == NULL) {
        return -1; 
    }

    int alturaEsquerda = alturaArvore(root->esquerda);
    int alturaDireita = alturaArvore(root->direita);

    
    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;

    } else {
        return alturaDireita + 1;
    }

}

//Questao 3
void listarIntervalo (Node *root, int a, int b) {

    if (root == NULL) {
        return;
    }

    if (root->valor > a) {
        listarIntervalo(root->esquerda, a, b);
    }

    if (root->valor >= a && root->valor <= b) {
        printf("%d ", root->valor);
    }

    if (root->valor < b) {
        listarIntervalo(root->direita, a, b);
    }

}

//Questao 2
int verificarArvoreBinaria (Node *root, int min, int max) {

    if (root == NULL) {
        return 1;
    }

    if (root->valor <= min || root->valor >= max) {
        return 0; 
    }

    return verificarArvoreBinaria(root->esquerda, min, root->valor) && verificarArvoreBinaria(root->direita, root->valor, max);

}

int arvoreBinara (Node *root) {
    return verificarArvoreBinaria(root, INT_MIN, INT_MAX);
}


int main() {

    int array[] = {10, 5, 20, 3, 7, 15, 30};
    int n = sizeof(array) / sizeof(array[0]);

    Node *root1 = NULL;
    Node *root2 = NULL;

    for (int i = 0; i < n; i++) {
        root1 = inserir(root1, array[i]);
        root2 = inserir(root2, array[i]);
        printf("Inserido: %d\n", array[i]);
    }

    printf("Pre-Order Traversal: ");
    preOrder(root1);
    printf("\n");

    printf("%d\n", contarFolhas(root1));
    
    Node *busca = buscar(root1, 12);
    if (busca != NULL) {
        printf("Valor %d encontrado na arvore\n", busca->valor);

    } else {
        printf("Valor nao encontrado na arvore\n");
    }

    if (saoIguais(root1, root2)) {
        printf("Sao iguais\n");

    } else {
        printf("Sao diferentes\n");
    }

    printf("\nAltura da arvore: %d", alturaArvore(root1));

    listarIntervalo(root1, 6, 25);   

    if (arvoreBinara(root1)) {
        printf("Binaria.\n");
        
    } else {
        printf("Nao binaria.\n");
    }

    return 0;
}


