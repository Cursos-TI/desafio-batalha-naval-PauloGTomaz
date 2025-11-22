#include <stdio.h>

#define TAM 10          // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3     // Todos os navios têm tamanho 3

// -----------------------------------------------------------
// Função para verificar se um navio pode ser colocado
// sem sair dos limites e sem sobrepor outro navio.
// Retorna 1 (válido) ou 0 (inválido).
// -----------------------------------------------------------
int validarPosicao(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    /*
    Orientações:
    0 = horizontal
    1 = vertical
    2 = diagonal ↘ (linha++, coluna++)
    3 = diagonal ↗ (linha--, coluna++)
    */

    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (orientacao == 0) c += i;          // horizontal
        else if (orientacao == 1) l += i;     // vertical
        else if (orientacao == 2) { l += i; c += i; }  // diagonal ↘
        else if (orientacao == 3) { l -= i; c += i; }  // diagonal ↗

        // Verifica limites
        if (l < 0 || l >= TAM || c < 0 || c >= TAM)
            return 0; // inválido

        // Verifica sobreposição
        if (tabuleiro[l][c] == 3)
            return 0; // inválido
    }

    return 1; // posição válida
}

// -----------------------------------------------------------
// Função para posicionar um navio no tabuleiro
// -----------------------------------------------------------
void colocarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (orientacao == 0) c += i;          // horizontal
        else if (orientacao == 1) l += i;     // vertical
        else if (orientacao == 2) { l += i; c += i; }  // diagonal ↘
        else if (orientacao == 3) { l -= i; c += i; }  // diagonal ↗

        tabuleiro[l][c] = 3;
    }
}

int main() {

    // ------------------------------
    // 1. Criar e inicializar tabuleiro
    // ------------------------------
    int tabuleiro[TAM][TAM];

    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    // ------------------------------
    // 2. Coordenadas e orientações dos 4 navios
    // ------------------------------

    // Navios retos (horizontal/vertical)
    int n1_l = 2, n1_c = 1, ori1 = 0;   // horizontal
    int n2_l = 6, n2_c = 3, ori2 = 1;   // vertical

    // Navios diagonais
    int n3_l = 1, n3_c = 1, ori3 = 2;   // diagonal ↘
    int n4_l = 8, n4_c = 1, ori4 = 3;   // diagonal ↗

    // ------------------------------
    // 3. Validar e posicionar navios
    // ------------------------------
    if (!validarPosicao(tabuleiro, n1_l, n1_c, ori1)) { printf("Erro Navio 1\n"); return 1; }
    colocarNavio(tabuleiro, n1_l, n1_c, ori1);

    if (!validarPosicao(tabuleiro, n2_l, n2_c, ori2)) { printf("Erro Navio 2\n"); return 1; }
    colocarNavio(tabuleiro, n2_l, n2_c, ori2);

    if (!validarPosicao(tabuleiro, n3_l, n3_c, ori3)) { printf("Erro Navio 3\n"); return 1; }
    colocarNavio(tabuleiro, n3_l, n3_c, ori3);

    if (!validarPosicao(tabuleiro, n4_l, n4_c, ori4)) { printf("Erro Navio 4\n"); return 1; }
    colocarNavio(tabuleiro, n4_l, n4_c, ori4);

    // ------------------------------
    // 4. Exibir Tabuleiro
    // ------------------------------
    printf("\n===== TABULEIRO FINAL =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
