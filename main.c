#include <stdio.h> 

char tabuleiro[3][3];     
char nomejogador1[2];     
char nomejogador2[2];     
int emPartida = 1;        // Indicador para ver se o jogo esta em andamento (1 = sim, 0 = fim)

void limparTabuleiro() {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      tabuleiro[i][j] = ' ';
}

void imprimirTabuleiro() {
  printf("\n");
  for (int i = 0; i < 3; i++) {
    printf(" %c | %c | %c ", tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
    if (i < 2)
      printf("\n---|---|---\n"); 
  }
  printf("\n\n");
}

void jogada(char simbolo, int linha, int coluna) {
  if (tabuleiro[linha][coluna] == ' ') {           
    tabuleiro[linha][coluna] = simbolo;            
  } else {
    printf("Essa posição já está ocupada!\n");     
  }
}

void verificarVencedor(char simbolo) {
  for (int i = 0; i < 3; i++) {
    if (tabuleiro[i][0] == simbolo && tabuleiro[i][1] == simbolo && tabuleiro[i][2] == simbolo) {
      printf("O jogador %c venceu!\n", simbolo);
      emPartida = 0;   // Encerra a partida
      return;
    }
    if (tabuleiro[0][i] == simbolo && tabuleiro[1][i] == simbolo && tabuleiro[2][i] == simbolo) {
      printf("O jogador %c venceu!\n", simbolo);
      emPartida = 0;
      return;
    }
  }

  if ((tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) ||
      (tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo)) {
    printf("O jogador %c venceu!\n", simbolo);
    emPartida = 0;
  }
}

int verificarEmpate() {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (tabuleiro[i][j] == ' ')   // Se ainda há espaço vazio, não é empate
        return 0;
  return 1; // Se todas estão preenchidas e ninguém venceu, é empate
}

int main(void) {
  printf("Qual caractere o jogador 1 irá usar?: ");
  scanf("%1s", nomejogador1); // %1s garante que só um caractere será lido

  printf("Qual caractere o jogador 2 irá usar?: ");
  scanf("%1s", nomejogador2);

  char jogarNovamente = 's';

  while (jogarNovamente == 's' || jogarNovamente == 'S') {
    limparTabuleiro();
    emPartida = 1;

    char nomejogadorAtual = nomejogador1[0];

    // Loop principal da partida
    while (emPartida == 1) {
      imprimirTabuleiro();
      printf("Jogador %c, escolha sua jogada.\n", nomejogadorAtual);

      int linha, coluna;
      printf("Linha (0 a 2): ");
      scanf("%d", &linha);
      printf("Coluna (0 a 2): ");
      scanf("%d", &coluna);

      // Validação de entrada
      if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
        printf("Posição inválida. Tente novamente.\n");
        continue;
      }

      if (tabuleiro[linha][coluna] != ' ') {
        printf("Posição já ocupada. Tente novamente.\n");
        continue;
      }

      // Executa a jogada
      jogada(nomejogadorAtual, linha, coluna);

      verificarVencedor(nomejogadorAtual);

      if (emPartida && verificarEmpate()) {
        imprimirTabuleiro();  // Mostra o tabuleiro final
        printf("Deu velha!\n");
        emPartida = 0;
      }

      // Alterna para o outro jogador
      nomejogadorAtual = (nomejogadorAtual == nomejogador1[0]) ? nomejogador2[0] : nomejogador1[0];
    }

    imprimirTabuleiro();
    printf("Fim de jogo.\n");

    printf("Deseja jogar novamente? (s/n): ");
    scanf(" %c", &jogarNovamente); 
  }

  printf("Obrigado por jogar!\n");

  return 0;
}