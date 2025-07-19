#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
} Node;

int altura (Node *no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

int maxAvl (int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento (Node *no) {
    if (no == NULL)
        return 0;
    return altura(no->direita) - altura(no->esquerda);
}

Node *rotacaoDireita (Node *y) {

    if (y == NULL || y->esquerda == NULL) {
        return y;
    }

    Node *x = y->esquerda;
    Node *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + maxAvl(altura(y->esquerda), altura(y->direita));
    x->altura = 1 + maxAvl(altura(x->esquerda), altura(x->direita));

    return x;

}

Node *rotacaoEsquerda (Node *x) {

    if (x == NULL || x->direita == NULL) {
        return x;
    }

    Node *y = x->direita;
    Node *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + maxAvl(altura(x->esquerda), altura(x->direita));
    y->altura = 1 + maxAvl(altura(y->esquerda), altura(y->direita));

    return y;

}

Node *adicionar (Node *raiz, int valor) {
    if (raiz == NULL) {
        Node *novo = (Node *)calloc(1, sizeof(Node));
        novo->valor = valor;
        novo->altura = 1;
        return novo;
    }

    if (valor < raiz->valor)
        raiz->esquerda = adicionar(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = adicionar(raiz->direita, valor);
    else
        return raiz; // valores duplicados não são permitidos

    raiz->altura = 1 + maxAvl(altura(raiz->esquerda), altura(raiz->direita));
    int fb = fatorBalanceamento(raiz);

    // Casos de rotação
    if (fb > 1 && valor < raiz->esquerda->valor)
        return rotacaoDireita(raiz);

    if (fb < -1 && valor > raiz->direita->valor)
        return rotacaoEsquerda(raiz);

    if (fb > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;

}

Node* encontrarMenor (Node* no) {
    Node* atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;

}

Node* remover (Node* raiz, int valor) {

    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);

    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    
    } else {

        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            Node* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            free(raiz);
            return temp;

        } else {
            Node* temp = encontrarMenor(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }

    raiz->altura = 1 + maxAvl(altura(raiz->esquerda), altura(raiz->direita));

    int fb = fatorBalanceamento(raiz);

    if (fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0) {
        return rotacaoDireita(raiz);
    }

    if (fb > 1 && fatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    if (fb < -1 && fatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;

}

void preOrder (Node *root) {
    if (root != NULL) {
        printf("%d ", root->valor);
        preOrder(root->esquerda);
        preOrder(root->direita);
    }
}

int main() {

    Node *root = NULL;

    root = adicionar(root, 13); 
    root = adicionar(root, 16); 
    root = adicionar(root, 6); 
    root = adicionar(root, 1); 
    root = adicionar(root, 9); 
    root = adicionar(root, 1); 
    root = adicionar(root, 8); 
    root = adicionar(root, 7); 
    
    root = remover(root, 9); 

    return 0;
}
