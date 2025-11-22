#include <stdio.h>

#define TAM 10          // Tamanho do tabuleiro
#define TAM_NAVIO 3     // Tamanho dos navios
#define HAB 7           // Tamanho das matrizes de habilidades

// -----------------------------------------------------------
// Função para validar se é possível colocar um navio sem sair
// dos limites ou sobrepor outro navio
// -----------------------------------------------------------
int validarPosicao(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {

    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (orientacao == 0) c += i;             // Horizontal
        else if (orientacao == 1) l += i;        // Vertical
        else if (orientacao == 2) { l += i; c += i; }  // Diagonal ↘
        else if (orientacao == 3) { l -= i; c += i; }  // Diagonal ↗

        if (l < 0 || l >= TAM || c < 0 || c >= TAM)
            return 0;

        if (tabuleiro[l][c] == 3)
            return 0;
    }

    return 1;
}

// -----------------------------------------------------------
// Função para colocar um navio no tabuleiro
// -----------------------------------------------------------
void colocarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {

    for (int i = 0; i < TAM_NAVIO; i++) {

        int l = linha;
        int c = coluna;

        if (orientacao == 0) c += i;
        else if (orientacao == 1) l += i;
        else if (orientacao == 2) { l += i; c += i; }
        else if (orientacao == 3) { l -= i; c += i; }

        tabuleiro[l][c] = 3;
    }
}

// -----------------------------------------------------------
// Criar matriz de habilidade: CONE (ponta para cima ou baixo)
// -----------------------------------------------------------
void criarCone(int H[HAB][HAB]) {

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {

            // a linha aumenta e a coluna abre como um cone
            if (j >= HAB/2 - i && j <= HAB/2 + i)
                H[i][j] = 1;
            else
                H[i][j] = 0;
        }
    }
}

// -----------------------------------------------------------
// Criar matriz de habilidade: CRUZ
// -----------------------------------------------------------
void criarCruz(int H[HAB][HAB]) {

    int centro = HAB / 2;

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {

            if (i == centro || j == centro)
                H[i][j] = 1;
            else
                H[i][j] = 0;
        }
    }
}

// -----------------------------------------------------------
// Criar matriz de habilidade: OCTAEDRO (losango)
// -----------------------------------------------------------
void criarOctaedro(int H[HAB][HAB]) {

    int centro = HAB / 2;

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {

            if (abs(i - centro) + abs(j - centro) <= centro)
                H[i][j] = 1;
            else
                H[i][j] = 0;
        }
    }
}

// -----------------------------------------------------------
// Sobrepor habilidade no tabuleiro, respeitando limites
// -----------------------------------------------------------
void aplicarHabilidade(int tabuleiro[TAM][TAM], int H[HAB][HAB], int origemL, int origemC) {

    int offset = HAB / 2;

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {

            if (H[i][j] == 1) {

                int l = origemL + (i - offset);
                int c = origemC + (j - offset);

                // Verifica se está dentro do tabuleiro
                if (l >= 0 && l < TAM && c >= 0 && c < TAM) {

                    // Não sobrescreve navio (valor 3)
                    if (tabuleiro[l][c] != 3)
                        tabuleiro[l][c] = 5;
                }
            }
        }
    }
}

int main() {

    int tabuleiro[TAM][TAM];

    // ----------------------------------------
    // 1. Inicializar tabuleiro com água (0)
    // ----------------------------------------
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    // ----------------------------------------
    // 2. Definir navios (coordenadas + orientação)
    // ----------------------------------------
    int n1_l = 2, n1_c = 1, ori1 = 0;   // horizontal
    int n2_l = 6, n2_c = 3, ori2 = 1;   // vertical
    int n3_l = 1, n3_c = 1, ori3 = 2;   // diagonal ↘
    int n4_l = 8, n4_c = 1, ori4 = 3;   // diagonal ↗

    if (!validarPosicao(tabuleiro, n1_l, n1_c, ori1)) return 1;
    colocarNavio(tabuleiro, n1_l, n1_c, ori1);

    if (!validarPosicao(tabuleiro, n2_l, n2_c, ori2)) return 1;
    colocarNavio(tabuleiro, n2_l, n2_c, ori2);

    if (!validarPosicao(tabuleiro, n3_l, n3_c, ori3)) return 1;
    colocarNavio(tabuleiro, n3_l, n3_c, ori3);

    if (!validarPosicao(tabuleiro, n4_l, n4_c, ori4)) return 1;
    colocarNavio(tabuleiro, n4_l, n4_c, ori4);

    // ----------------------------------------
    // 3. Criar matrizes das habilidades
    // ----------------------------------------
    int cone[HAB][HAB], cruz[HAB][HAB], oct[HAB][HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(oct);

    // ----------------------------------------
    // 4. Aplicar habilidades no tabuleiro
    // ----------------------------------------
    aplicarHabilidade(tabuleiro, cone, 2, 5);  // cone no tabuleiro
    aplicarHabilidade(tabuleiro, cruz, 7, 7);  // cruz no tabuleiro
    aplicarHabilidade(tabuleiro, oct, 5, 2);   // octaedro no tabuleiro

    // ----------------------------------------
    // 5. Exibir tabuleiro final
    // ----------------------------------------
    printf("\n===== TABULEIRO FINAL COM HABILIDADES =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tabuleiro[i][j] == 0) printf("0 ");
            else if (tabuleiro[i][j] == 3) printf("3 ");
            else if (tabuleiro[i][j] == 5) printf("5 ");
        }
        printf("\n");
    }

    return 0;
}
