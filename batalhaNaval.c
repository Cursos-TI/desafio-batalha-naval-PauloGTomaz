#include <stdio.h>

#define TAM 10        // Tamanho fixo do tabuleiro (10x10)
#define TAM_NAVIO 3   // Tamanho fixo dos navios

int main() {

    // --------------------------
    // 1. REPRESENTAÇÃO DO TABULEIRO
    // --------------------------
    int tabuleiro[TAM][TAM];

    // Inicializa todas as posições com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // --------------------------
    // 2. POSICIONAMENTO DOS NAVIOS
    // --------------------------

    // Coordenadas iniciais dos navios (definidas no código)
    int navio1_linha = 2, navio1_coluna = 4;  // Navio horizontal
    int navio2_linha = 5, navio2_coluna = 1;  // Navio vertical

    // Validação simples de limites
    // Navio 1 horizontal
    if (navio1_coluna + TAM_NAVIO > TAM) {
        printf("Erro: Navio 1 ultrapassa os limites do tabuleiro!\n");
        return 1;
    }

    // Navio 2 vertical
    if (navio2_linha + TAM_NAVIO > TAM) {
        printf("Erro: Navio 2 ultrapassa os limites do tabuleiro!\n");
        return 1;
    }

    // Validação de sobreposição
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[navio1_linha][navio1_coluna + i] == 3) {
            printf("Erro: Sobreposição detectada no Navio 1!\n");
            return 1;
        }
        if (tabuleiro[navio2_linha + i][navio2_coluna] == 3) {
            printf("Erro: Sobreposição detectada no Navio 2!\n");
            return 1;
        }
    }

    // Coloca o navio 1 (horizontal) no tabuleiro
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[navio1_linha][navio1_coluna + i] = 3;
    }

    // Coloca o navio 2 (vertical) no tabuleiro
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[navio2_linha + i][navio2_coluna] = 3;
    }

    // --------------------------
    // 3. EXIBIÇÃO DO TABULEIRO
    // --------------------------
    printf("\n===== TABULEIRO BATALHA NAVAL =====\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
