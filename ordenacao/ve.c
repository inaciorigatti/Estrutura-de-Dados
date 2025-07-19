#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>  
#include <locale.h>
                                             //declaração variaveis e constantes,além dos chars
char j[3][3];
char jogador1[20], jogador2[20];
char simb ='O';
int nj=0, j1=0, j2=0, emp=0, op=0, lin=0, col=0;
_Bool enc=false;
                                             //inicialização dos acrescimos de linha e coluna com for
void inicializar(){  
  for(int lin=0; lin<3; lin++){
    for(int col=0; col<3; col++){
      j[lin][col] = ' ';
    }
  }
  nj=0;
  enc=false;
}
                                              //troca de símbolos     
char simbolo(){
  if (simb == 'O'){
    simb = 'X';
  }else{
    simb ='O';
  }
  nj++;
  return simb;
}
                                              //Campo de nomeação dos jogadores
void nomear(){
  printf("Digite o nome do jogador 1: ");
  scanf("%s", jogador1);
  printf("Digite o nome do jogador 2: ");
  scanf("%s", jogador2);
}
                                              // desenho do menu do jogo da velha e da matriz do jogo
void menu(){
  system("clear");
  printf("***************************\n");
  printf("*       GAME VELHA        *\n");
  printf("***************************\n");
  printf("*                         *\n");
  printf("*   1 - INICIAR           *\n");
  printf("*   2 - ESTATÍSTICA       *\n");
  printf("*   3 - SAIR              *\n");
  printf("*                         *\n");
  printf("***************************\n\n");
  printf("ESCOLHA A OPÇÃO DESEJADA: ");
}

void game(){
  system("clear");
  printf("    0   1   2   \n");
  printf("  -------------\n");
  for (int i = 0; i < 3; i++) {
    printf("%d | %c | %c | %c |\n", i, j[i][0], j[i][1], j[i][2]);
    printf("  -------------\n");
  }
}
                                               //configuração de desenho do menu de estatisticas
void estatistica(){
  printf("***************************\n");
  printf("*       ESTATÍSTICA       *\n");
  printf("**************************\n");
  printf("                           \n");
  printf("    %s = %d    \n", jogador1, j1);
  printf("    %s = %d    \n", jogador2, j2);
  printf("    Empate = %i        \n", emp);
  printf("                           \n");
  printf("***************************\n");
  sleep(5);
}

_Bool verificarjogada(int l, int c){
  return j[l][c] == ' ';
}                                                        
                                                 //Verificação de vitoria linha por linha e coluna por coluna usando variaveis para poupar espaço,com mensagens de vitória e empate e alimentação das estatísticas

void verificarvitoria(){  
  for (int i = 0; i < 3; i++) {
    if ((j[i][0] == j[i][1] && j[i][1] == j[i][2] && j[i][0] != ' ') ||
       (j[0][i] == j[1][i] && j[1][i] == j[2][i] && j[0][i] != ' ')){
      enc = true;
    }    
  }
  if ((j[0][0] == j[1][1] && j[1][1] == j[2][2] && j[0][0] != ' ') ||
      (j[0][2] == j[1][1] && j[1][1] == j[2][0] && j[0][2] != ' ')) {
    enc = true;
  }
  if (enc) {
    game();
    if (simb == 'X') {
      j1++;
      printf("Parabéns, %s, você ganhou!!\n", jogador1);
    } else {
      j2++;
      printf("Parabéns, %s, você ganhou!!\n", jogador2);
    }
    estatistica();
  } else if (nj == 9) {
    emp++;
    printf("Deu velha!!!\n");
    sleep(2);
    estatistica();
  }
}
                                        // Estrutura switch case com do while para fazer o looping da jogada no caso 1 e verificar o caminho da vitória a partir de 9 jogadas. Também regula o break das estatisticas caso o usuario escolha uma opção inválida                                                                                                                                                            // Estrutura switch case para fazer o looping da jogada
int main(){
  setlocale(LC_ALL, "Portuguese");
  nomear();
  do{
    menu();
    scanf("%d", &op);  
    switch(op){
      case 1:{
        inicializar();
        do{          
          game();
          do{
            printf("Digite a linha entre 0-2: ");
            scanf("%i", &lin);
          }while(lin<0 || lin>2);

          do{
            printf("Digite a coluna entre 0-2: ");
            scanf("%i", &col);
          }while(col<0 || col>2);

          if (verificarjogada(lin, col)){
            j[lin][col] = simbolo();
            game();
            if(nj>4) verificarvitoria();
          }else{
            printf("Jogada não permitida!\n");
          }
        }while(enc == false && nj < 9);        
        break;
      }
      case 2:{
        estatistica();
        break;
      }
      default:{
        if(op > 3 || op < 1){
          printf("Opção inválida!\n");             
        }
        break;
      }
    }

                                                          //finalização do sistema 
  }while(op > 0 && op < 3); 
  printf("Sistema finalizado com sucesso!\n");
}
