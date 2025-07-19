#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define D 2 // grau minimo da árvore

typedef struct ArvoreBNo {
    int chaves[2 * D - 1];
    struct ArvoreBNo *filhos[2 * D];
    int numeroDeChaves;
    bool ehFolha;
} ArvoreBNo;

ArvoreBNo *criarNo (bool ehFolha) {
    ArvoreBNo *no = (ArvoreBNo *) calloc(1, sizeof(ArvoreBNo));
    
    no->ehFolha = ehFolha;
    no->numeroDeChaves = 0;

    for (int i = 0; i < 2 * D; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

void divisao(ArvoreBNo *pai, int i, ArvoreBNo *filhoCheio);
void adicionarAoNoNaoCheio(ArvoreBNo *no, int chave);
ArvoreBNo *adicionarNo(ArvoreBNo *raiz, int chave);
bool buscarChaveAux(ArvoreBNo *raiz, int chave, int nivel, int *nivelEncontrado);
bool buscarChave(ArvoreBNo *raiz, int chave, int *nivelEncontrado);
int encontrarAnterior(ArvoreBNo *no);
int encontrarSucessor(ArvoreBNo *no);
void mesclarFilhos(ArvoreBNo *no, int idx);
void preencherFilho(ArvoreBNo *no, int idx);
ArvoreBNo *removerChave(ArvoreBNo *raiz, int chave);
void imprimirArvoreB(ArvoreBNo *raiz, int nivel);

bool buscarChaveAux (ArvoreBNo *raiz, int chave, int nivel, int *nivelEncontrado) {
    int i = 0;
    while (i < raiz->numeroDeChaves && chave > raiz->chaves[i]) {
        i++;
    }

    if (i < raiz->numeroDeChaves && chave == raiz->chaves[i]) {
        *nivelEncontrado = nivel; 
        return true; 
    }

    if (raiz->ehFolha) {
        return false; 
    }

    return buscarChaveAux(raiz->filhos[i], chave, nivel + 1, nivelEncontrado); 
}

bool buscarChave (ArvoreBNo *raiz, int chave, int *nivelEncontrado) {
    if (raiz == NULL) {
        return false; 
    }

    return buscarChaveAux(raiz, chave, 0, nivelEncontrado); 
}

int encontrarAnterior (ArvoreBNo *no) {

    while (!no->ehFolha) {
        no = no->filhos[no->numeroDeChaves];
    }

    return no->chaves[no->numeroDeChaves - 1];
}

int encontrarSucessor (ArvoreBNo *no) {

    while (!no->ehFolha) {
        no = no->filhos[0];
    }

    return no->chaves[0];
}

void mesclarFilhos (ArvoreBNo *no, int i) {
    ArvoreBNo *filho = no->filhos[i];
    ArvoreBNo *irmao = no->filhos[i + 1];

    filho->chaves[D - 1] = no->chaves[i];

    for (int i = 0; i < irmao->numeroDeChaves; i++) {
        filho->chaves[i + D] = irmao->chaves[i];
    }

    if (!filho->ehFolha) {
        for (int i = 0; i <= irmao->numeroDeChaves; i++) {
            filho->filhos[i + D] = irmao->filhos[i];
        }
    }

    filho->numeroDeChaves += irmao->numeroDeChaves + 1;

    for (int j = i + 1; j < no->numeroDeChaves; j++) {
        no->chaves[j - 1] = no->chaves[j];
        no->filhos[j] = no->filhos[j + 1];
    }

    no->numeroDeChaves--;
    free(irmao);
}

void preencherFilho (ArvoreBNo *no, int idx) {
    if (idx != 0 && no->filhos[idx - 1]->numeroDeChaves >= D) {
        ArvoreBNo *filho = no->filhos[idx];
        ArvoreBNo *irmao = no->filhos[idx - 1];

        for (int i = filho->numeroDeChaves - 1; i >= 0; i--) {
            filho->chaves[i + 1] = filho->chaves[i];
        }

        if (!filho->ehFolha) {
            for (int i = filho->numeroDeChaves; i >= 0; i--) {
                filho->filhos[i + 1] = filho->filhos[i];
            }
        }

        filho->chaves[0] = no->chaves[idx - 1]; 
        if (!filho->ehFolha) {
            filho->filhos[0] = irmao->filhos[irmao->numeroDeChaves];
        }

        no->chaves[idx - 1] = irmao->chaves[irmao->numeroDeChaves - 1];
        filho->numeroDeChaves++;
        irmao->numeroDeChaves--;

    } else if (idx != no->numeroDeChaves && no->filhos[idx + 1]->numeroDeChaves >= D) {
       
        ArvoreBNo *filho = no->filhos[idx];
        ArvoreBNo *irmao = no->filhos[idx + 1];

        filho->chaves[filho->numeroDeChaves] = no->chaves[idx];
        if (!filho->ehFolha) {
            filho->filhos[filho->numeroDeChaves + 1] = irmao->filhos[0];
        }

        no->chaves[idx] = irmao->chaves[0];

        for (int i = 1; i < irmao->numeroDeChaves; i++) {
            irmao->chaves[i - 1] = irmao->chaves[i];
        }

        if (!irmao->ehFolha) {
            for (int i = 1; i <= irmao->numeroDeChaves; i++) {
                irmao->filhos[i - 1] = irmao->filhos[i];
            }
        }

        filho->numeroDeChaves++;
        irmao->numeroDeChaves--;

    } else {
        if (idx != no->numeroDeChaves) {
            mesclarFilhos(no, idx);
        } else {
            mesclarFilhos(no, idx - 1);
        }
    }
}

ArvoreBNo *adicionarNo (ArvoreBNo *raiz, int chave) {
    if (raiz == NULL) {
        raiz = criarNo(true);
        raiz->chaves[0] = chave;
        raiz->numeroDeChaves = 1;
        return raiz;
    }

    if (raiz->numeroDeChaves == 2 * D - 1) {
        ArvoreBNo *novaRaiz = criarNo(false);
        novaRaiz->filhos[0] = raiz;
        divisao(novaRaiz, 0, raiz);
        adicionarAoNoNaoCheio(novaRaiz, chave);

        return novaRaiz;
    } else {
        adicionarAoNoNaoCheio(raiz, chave);
        return raiz;
    }
}

void divisao (ArvoreBNo *pai, int i, ArvoreBNo *filhoCheio) {
    ArvoreBNo *novoFilho = criarNo(filhoCheio->ehFolha);
    novoFilho->numeroDeChaves = D - 1;

    for (int j = 0; j < D - 1; j++) {
        novoFilho->chaves[j] = filhoCheio->chaves[j + D];
    }

    if (!filhoCheio->ehFolha) {
        for (int j = 0; j < D; j++) {
            novoFilho->filhos[j] = filhoCheio->filhos[j + D];
            filhoCheio->filhos[j + D] = NULL;
        }
    }

    filhoCheio->numeroDeChaves = D - 1;

    for (int j = pai->numeroDeChaves; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = novoFilho;

    for (int j = pai->numeroDeChaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[i] = filhoCheio->chaves[D - 1];

    pai->numeroDeChaves++;
    filhoCheio->numeroDeChaves = D - 1; 
}

void adicionarAoNoNaoCheio (ArvoreBNo *no, int chave) {
    int i = no->numeroDeChaves - 1;

    if (no->ehFolha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numeroDeChaves++;
    } else {
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;

        if (no->filhos[i]->numeroDeChaves == 2 * D - 1) {
            divisao(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        adicionarAoNoNaoCheio(no->filhos[i], chave);
    }
}

void imprimirArvoreB (ArvoreBNo *raiz, int nivel) {
    if (raiz != NULL) {
        printf("Nível %d: ", nivel);
        for (int i = 0; i < raiz->numeroDeChaves; i++) {
            printf("%d ", raiz->chaves[i]);
        }
        printf("\n");

        if (!raiz->ehFolha) {
            for (int i = 0; i <= raiz->numeroDeChaves; i++) {
                imprimirArvoreB(raiz->filhos[i], nivel + 1);
            }
        }
    }
}

int main () {
    
    ArvoreBNo *raiz = NULL;

    int valores[] = {30, 20, 10, 25, 28, 27, 5, 50, 40, 60, 45};
    int tam = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < tam; i++) {
        raiz = adicionarNo(raiz, valores[i]);
    }

    imprimirArvoreB(raiz, 0);

    int chaveBusca = 60;
    int nivel;
    if (buscarChave(raiz, chaveBusca, &nivel)) {
        printf("Chave encontrada no nível %d.", nivel);
    } else {
        printf("Chave %d não encontrada.", chaveBusca);
    }


    return 0;
}