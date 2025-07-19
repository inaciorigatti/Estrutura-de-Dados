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

ArvoreBNo *criarNo(bool ehFolha) {
    ArvoreBNo *no = (ArvoreBNo *) calloc(1, sizeof(ArvoreBNo)); 

    no->ehFolha = ehFolha;
    no->numeroDeChaves = 0;

    for (int i = 0; i < 2 * D; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

ArvoreBNo *adicionarNo(ArvoreBNo *raiz, int chave) {

    if (raiz == NULL) { 
        raiz = criarNo(true);
        raiz->chaves[0] = chave;
        raiz->numeroDeChaves = 1;

        return raiz;
    }

    if (raiz->numeroDeChaves == 2 * D - 1) {
        ArvoreBNo *novaRaiz = criarNo(false); // não é mais um nó folha
        novaRaiz->filhos[0] = raiz;
        divisao(novaRaiz, 0, raiz);
        adicionarAoNoNaoCheio(novaRaiz, chave);
        return novaRaiz;
    } else {
        adicionarAoNoNaoCheio(raiz, chave);
        return raiz;
    }
}

void divisao(ArvoreBNo *pai, int i, ArvoreBNo *filhoCheio) {
    ArvoreBNo *novoFilho = criarNo(filhoCheio->ehFolha); // vai ter o mesmo status do irmao
    novoFilho->numeroDeChaves = D - 1;

    // Copia as chaves da metade superior de filhoCheio para novoFilho
    for (int j = 0; j < D - 1; j++) {
        novoFilho->chaves[j] = filhoCheio->chaves[j + D];
    }

    // Copia os filhos da metade superior de filhoCheio para novoFilho
    if (!filhoCheio->ehFolha) {
        for (int j = 0; j < D; j++) {
            novoFilho->filhos[j] = filhoCheio->filhos[j + D];
            filhoCheio->filhos[j + D] = NULL; // Importante: Limpa o ponteiro no filhoCheio
        }
    }

    filhoCheio->numeroDeChaves = D - 1;

    // Desloca os filhos do pai para abrir espaço para o novoFilho
    for (int j = pai->numeroDeChaves; j >= i + 1; j--) {  // Corrigido o loop
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = novoFilho;

    // Desloca as chaves do pai para abrir espaço para a chave promovida
    for (int j = pai->numeroDeChaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[i] = filhoCheio->chaves[D - 1];

    pai->numeroDeChaves++;

    filhoCheio->numeroDeChaves = D - 1; // Atualiza o número de chaves do filhoCheio
}


void adicionarAoNoNaoCheio(ArvoreBNo *no, int chave) {
    int i = no->numeroDeChaves - 1;

    if (no->ehFolha) {
        // Encontra a posição correta para inserir a nova chave
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }

        // Insere a nova chave
        no->chaves[i + 1] = chave;
        no->numeroDeChaves++;
    } else {
        // Encontra o filho apropriado para inserir a chave
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++; // Incrementa i para obter o índice do filho correto

        // Se o filho estiver cheio, divide-o
        if (no->filhos[i]->numeroDeChaves == 2 * D - 1) {
            divisao(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) {
                i++;
            }
        }
         adicionarAoNoNaoCheio(no->filhos[i], chave);
    }
}

// Função para imprimir a árvore B (para fins de teste)
void imprimirArvoreB(ArvoreBNo *raiz, int nivel) {
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

// Função de Busca
ArvoreBNo *buscarChave(ArvoreBNo *raiz, int chave) {
    int i = 0;
    while (i < raiz->numeroDeChaves && chave > raiz->chaves[i]) {
        i++;
    }

    if (i < raiz->numeroDeChaves && chave == raiz->chaves[i]) {
        printf("%d", i); 
        return raiz; // Chave encontrada neste nó
    }

    if (raiz->ehFolha) {
        return NULL; // Chave não encontrada
    }

    return buscarChave(raiz->filhos[i], chave); // Busca no filho apropriado
}

// Função para encontrar o predecessor (maior chave na subárvore esquerda)
int encontrarAnterior(ArvoreBNo *no) {
    while (!no->ehFolha) {
        no = no->filhos[no->numeroDeChaves];
    }
    return no->chaves[no->numeroDeChaves - 1];
}

// Função para encontrar o sucessor (menor chave na subárvore direita)
int encontrarSucessor(ArvoreBNo *no) {
    while (!no->ehFolha) {
        no = no->filhos[0];
    }
    return no->chaves[0];
}

// Função para mesclar dois filhos quando um deles tem menos chaves que o mínimo
void mesclarFilhos(ArvoreBNo *no, int idx) {
    ArvoreBNo *filho = no->filhos[idx];
    ArvoreBNo *irmao = no->filhos[idx + 1];

    // Copia a chave do nó pai para o final do filho
    filho->chaves[D - 1] = no->chaves[idx];

    // Copia todas as chaves do irmão para o filho
    for (int i = 0; i < irmao->numeroDeChaves; i++) {
        filho->chaves[i + D] = irmao->chaves[i];
    }

    // Copia todos os filhos do irmão para o filho
    if (!filho->ehFolha) {
        for (int i = 0; i <= irmao->numeroDeChaves; i++) {
            filho->filhos[i + D] = irmao->filhos[i];
        }
    }

    filho->numeroDeChaves += irmao->numeroDeChaves + 1;

    // Desloca as chaves e filhos no nó pai para remover a chave e o ponteiro para o irmão
    for (int i = idx + 1; i < no->numeroDeChaves; i++) {
        no->chaves[i - 1] = no->chaves[i];
        no->filhos[i] = no->filhos[i + 1];
    }

    no->numeroDeChaves--;

    free(irmao);
}

// Função para preencher um filho que tem menos chaves que o mínimo
void preencherFilho(ArvoreBNo *no, int idx) {
    if (idx != 0 && no->filhos[idx - 1]->numeroDeChaves >= D) {
        // Pega uma chave do irmão anterior
        ArvoreBNo *filho = no->filhos[idx];
        ArvoreBNo *irmao = no->filhos[idx - 1];

        // Desloca todas as chaves no filho para abrir espaço para a nova chave
        for (int i = filho->numeroDeChaves - 1; i >= 0; i--) {
            filho->chaves[i + 1] = filho->chaves[i];
        }

        // Se o filho não for folha, desloca os filhos também
        if (!filho->ehFolha) {
            for (int i = filho->numeroDeChaves; i >= 0; i--) {
                filho->filhos[i + 1] = filho->filhos[i];
            }
        }

        filho->chaves[0] = no->chaves[idx - 1]; // Pega a chave do pai
        if (!filho->ehFolha) {
            filho->filhos[0] = irmao->filhos[irmao->numeroDeChaves];
        }

        no->chaves[idx - 1] = irmao->chaves[irmao->numeroDeChaves - 1];
        filho->numeroDeChaves++;
        irmao->numeroDeChaves--;

    } else if (idx != no->numeroDeChaves && no->filhos[idx + 1]->numeroDeChaves >= D) {
        // Pega uma chave do irmão posterior
        ArvoreBNo *filho = no->filhos[idx];
        ArvoreBNo *irmao = no->filhos[idx + 1];

        filho->chaves[filho->numeroDeChaves] = no->chaves[idx]; // Pega a chave do pai
        if (!filho->ehFolha) {
            filho->filhos[filho->numeroDeChaves + 1] = irmao->filhos[0];
        }

        no->chaves[idx] = irmao->chaves[0];

        // Desloca as chaves e filhos no irmão para remover a chave que foi movida
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
        // Mescla com um dos irmãos
        if (idx != no->numeroDeChaves) {
            mesclarFilhos(no, idx);
        } else {
            mesclarFilhos(no, idx - 1);
        }
    }
}

// Função de Remoção
ArvoreBNo *removerChave(ArvoreBNo *raiz, int chave) {
    int idx = 0;
    while (idx < raiz->numeroDeChaves && chave > raiz->chaves[idx]) {
        idx++;
    }

    if (idx < raiz->numeroDeChaves && chave == raiz->chaves[idx]) {
        // Chave encontrada no nó
        if (raiz->ehFolha) {
            // Caso 1: Nó folha
            for (int i = idx + 1; i < raiz->numeroDeChaves; i++) {
                raiz->chaves[i - 1] = raiz->chaves[i];
            }
            raiz->numeroDeChaves--;
            return raiz;
        } else {
            // Caso 2: Nó interno
            // a) O filho anterior tem pelo menos D chaves
            if (raiz->filhos[idx]->numeroDeChaves >= D) {
                int predecessor = encontrarAnterior(raiz->filhos[idx]);
                raiz->chaves[idx] = predecessor;
                raiz->filhos[idx] = removerChave(raiz->filhos[idx], predecessor);
            }
            // b) O filho posterior tem pelo menos D chaves
            else if (raiz->filhos[idx + 1]->numeroDeChaves >= D) {
                int sucessor = encontrarSucessor(raiz->filhos[idx + 1]);
                raiz->chaves[idx] = sucessor;
                raiz->filhos[idx + 1] = removerChave(raiz->filhos[idx + 1], sucessor);
            }
            // c) Ambos os filhos têm D-1 chaves
            else {
                mesclarFilhos(raiz, idx);
                raiz->filhos[idx] = removerChave(raiz->filhos[idx], chave);
            }
        }
    } else {
        // Chave não encontrada neste nó
        if (raiz->ehFolha) {
            printf("Chave %d não encontrada na árvore.\n", chave);
            return raiz;
        }

        // Desce para o filho apropriado
        bool flag = (idx == raiz->numeroDeChaves);
        if (raiz->filhos[idx]->numeroDeChaves < D) {
            preencherFilho(raiz, idx);
        }
        if (flag && idx > raiz->numeroDeChaves) {
            raiz->filhos[idx - 1] = removerChave(raiz->filhos[idx - 1], chave);
        } else {
            raiz->filhos[idx] = removerChave(raiz->filhos[idx], chave);
        }
    }
    if (raiz->numeroDeChaves == 0) {
        // Se a raiz ficou vazia, retorna o primeiro filho como a nova raiz
        ArvoreBNo *tmp = raiz->filhos[0];
        free(raiz);
        return tmp;
    }
    return raiz;
}

int main() {
    ArvoreBNo *raiz = NULL;

    int valores[] = {30, 20, 10, 25, 28, 27, 5, 50, 40, 60, 45};
    int tam = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < tam; i++) {
        raiz = adicionarNo(raiz, valores[i]);
    }

    printf("Árvore B antes da remoção:\n");
    imprimirArvoreB(raiz, 0);

    //busca
    int chaveBusca = 25;
    ArvoreBNo *noEncontrado = buscarChave(raiz, chaveBusca);
    if (noEncontrado != NULL) {
        printf("Chave %d encontrada na árvore.\n", chaveBusca);
    } else {
        printf("Chave %d não encontrada na árvore.\n", chaveBusca);
    }

    return 0;
}