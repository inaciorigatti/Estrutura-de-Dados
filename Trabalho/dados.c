#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que gera e salva números aleatórios em um arquivo
void gerarMassaDados(const char *nomeArquivo, int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        int numeroAleatorio = rand(); // Gera número inteiro entre 0 e RAND_MAX
        fprintf(arquivo, "%d\n", numeroAleatorio);
    }

    fclose(arquivo);
    printf("Arquivo '%s' gerado com %d números.\n", nomeArquivo, quantidade);
}

int main() {
    // Inicializa o gerador de números aleatórios com base no tempo
    srand(time(NULL));

    // Gerar os três arquivos
    gerarMassaDados("massa_1000.txt", 1000);
    gerarMassaDados("massa_100000.txt", 100000);
    gerarMassaDados("massa_500000.txt", 500000);

    return 0;
}
