#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

// Estrutura do nó da árvore de Huffman
typedef struct HuffmanNode {
    char caractere;
    int frequencia;
    struct HuffmanNode *esquerda, *direita;
} HuffmanNode;

// Estrutura para armazenar o código de Huffman
typedef struct {
    char caractere;
    char codigo[100];
} CodigoHuffman;

HuffmanNode* criarNo(char caractere, int frequencia) {
    HuffmanNode* no = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    no->caractere = caractere;
    no->frequencia = frequencia;
    no->esquerda = no->direita = NULL;
    return no;
}

// Fila de prioridade mínima para construir a árvore
void inserirFila(HuffmanNode** fila, int* tamanho, HuffmanNode* novoNo) {
    fila[(*tamanho)++] = novoNo;
    for (int i = *tamanho - 1; i > 0 && fila[i]->frequencia < fila[i-1]->frequencia; i--) {
        HuffmanNode* temp = fila[i];
        fila[i] = fila[i-1];
        fila[i-1] = temp;
    }
}

HuffmanNode* removerMin(HuffmanNode** fila, int* tamanho) {
    return fila[--(*tamanho)];
}

void construirCodigos(HuffmanNode* raiz, char* codigo, int profundidade, CodigoHuffman* tabela, int* indice) {
    if (raiz == NULL) return;

    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        codigo[profundidade] = '\0';
        tabela[*indice].caractere = raiz->caractere;
        strcpy(tabela[*indice].codigo, codigo);
        (*indice)++;
        return;
    }

    codigo[profundidade] = '0';
    construirCodigos(raiz->esquerda, codigo, profundidade + 1, tabela, indice);

    codigo[profundidade] = '1';
    construirCodigos(raiz->direita, codigo, profundidade + 1, tabela, indice);
}

void mostrarArvore(HuffmanNode* raiz, int nivel) {
    if (raiz == NULL) return;

    for (int i = 0; i < nivel; i++) printf("  ");
    if (raiz->caractere >= 32 && raiz->caractere < 127)
        printf("%c (%d)\n", raiz->caractere, raiz->frequencia);
    else
        printf("• (%d)\n", raiz->frequencia);

    mostrarArvore(raiz->esquerda, nivel + 1);
    mostrarArvore(raiz->direita, nivel + 1);
}

void codificarTexto(const char* texto, CodigoHuffman* tabela, int tamanhoTabela, char* resultado) {
    resultado[0] = '\0';
    for (int i = 0; texto[i] != '\0'; i++) {
        for (int j = 0; j < tamanhoTabela; j++) {
            if (tabela[j].caractere == texto[i]) {
                strcat(resultado, tabela[j].codigo);
                break;
            }
        }
    }
}

float calcularTaxaCompressao(const char* original, const char* codificado) {
    int tamanhoOriginal = strlen(original) * 8; // cada caractere é 8 bits
    int tamanhoCodificado = strlen(codificado);
    return 100.0 * (1.0 - ((float)tamanhoCodificado / tamanhoOriginal));
}

int main() {
    char texto[1000];
    HuffmanNode* fila[256];
    int frequencias[MAX_CHARS] = {0};
    CodigoHuffman tabela[MAX_CHARS];
    int tamanhoFila = 0;
    int tamanhoTabela = 0;
    char codigo[100];
    char codificado[10000];
    HuffmanNode* raiz = NULL;

    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir novo texto\n");
        printf("2. Exibir árvore de Huffman\n");
        printf("3. Exibir tabela de códigos\n");
        printf("4. Mostrar texto codificado\n");
        printf("5. Mostrar taxa de compressão\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                printf("Digite o texto: ");
                fgets(texto, sizeof(texto), stdin);
                texto[strcspn(texto, "\n")] = '\0'; // remover \n

                // Reset    
                memset(frequencias, 0, sizeof(frequencias));
                tamanhoFila = 0;
                tamanhoTabela = 0;

                for (int i = 0; texto[i] != '\0'; i++)
                    frequencias[(unsigned char)texto[i]]++;

                for (int i = 0; i < MAX_CHARS; i++)
                    if (frequencias[i] > 0)
                        inserirFila(fila, &tamanhoFila, criarNo(i, frequencias[i]));

                while (tamanhoFila > 1) {
                    HuffmanNode* esq = removerMin(fila, &tamanhoFila);
                    HuffmanNode* dir = removerMin(fila, &tamanhoFila);
                    HuffmanNode* novo = criarNo(0, esq->frequencia + dir->frequencia);
                    novo->esquerda = esq;
                    novo->direita = dir;
                    inserirFila(fila, &tamanhoFila, novo);
                }

                raiz = fila[0];
                construirCodigos(raiz, codigo, 0, tabela, &tamanhoTabela);
                codificarTexto(texto, tabela, tamanhoTabela, codificado);
                printf("Texto processado com sucesso.\n");
                break;

            case 2:
                if (raiz) mostrarArvore(raiz, 0);
                else printf("Insira um texto primeiro.\n");
                break;

            case 3:
                printf("Tabela de Códigos:\n");
                for (int i = 0; i < tamanhoTabela; i++) {
                    if (tabela[i].caractere >= 32 && tabela[i].caractere < 127)
                        printf("'%c' : %s\n", tabela[i].caractere, tabela[i].codigo);
                    else
                        printf("0x%02x : %s\n", (unsigned char)tabela[i].caractere, tabela[i].codigo);
                }
                break;

            case 4:
                printf("Texto codificado:\n%s\n", codificado);
                break;

            case 5:
                printf("Taxa de compressão: %.2f%%\n", calcularTaxaCompressao(texto, codificado));
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
