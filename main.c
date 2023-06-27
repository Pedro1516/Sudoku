#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void exibir_matriz(int tabuleiro[][9]);
void zerar_matriz(int tabuleiro[][9]);
int teste_linha(int num, int l, int c, int tabuleiro[][9]);
int teste_coluna(int num, int l, int c, int tabuleiro[][9]);
int teste_area(int num, int l, int c, int tabuleiro[][9]);
int teste_geral(int num, int l, int c, int tabuleiro[][9]);
void escrever_matriz(int num, int l, int c, int tabuleiro[][9]);
void gerar_dicas(int tabuleiro[][9]);
void update(int num, int l, int c, int tabuleiro[][9]);
int verifica_vitoria(int tabuleiro[][9], int err);

int main()
{
    srand(time(NULL));

    char num[2], lin[2], col[2];
    int tabuleiro[9][9];

    zerar_matriz(tabuleiro);
    gerar_dicas(tabuleiro);
    system("clear");
    exibir_matriz(tabuleiro);

    while (1)
    {
        while (1)
        {
            printf("\nDigite um numero de 1 a 9: ");

            fgets(num, 2, stdin);
            if (num[strlen(num) - 1] == '\n')
            {
                num[strlen(num) - 1] = '\0';
            }
            getchar();
            if (atoi(num) >= 1 && atoi(num) <= 9)
            {
                break;
            }
            printf("\n\033[31mPor favor, digite um numero de 1 a 9\033[00m\n");
        }

        while (1)
        {
            printf("\nDigite a linha de 1 a 9: ");

            fgets(lin, 2, stdin);
            if (lin[strlen(lin) - 1] == '\n')
                lin[strlen(lin) - 1] = '\0';

            getchar();
            if (atoi(lin) >= 1 && atoi(lin) <= 9)
            {
                break;
            }
            printf("\n\033[31mPor favor, digite uma linha de 1 a 9\033[00m\n");
        }

        while (1)
        {
            printf("\nDigite a coluna de 1 a 9: ");

            fgets(col, 2, stdin);
            if (col[strlen(col) - 1] == '\n')
            {
                col[strlen(col) - 1] = '\0';
            }
            getchar();
            if (atoi(col) >= 1 && atoi(col) <= 9)
            {
                break;
            }

            printf("\n\033[31mPor favor, digite uma coluna de 1 a 9\033[00m\n");
        }

        update(atoi(num), atoi(lin) - 1, atoi(col) - 1, tabuleiro);

        if (verifica_vitoria(tabuleiro, teste_geral(atoi(num), atoi(lin), atoi(col), tabuleiro)))
        {
            printf("Voce Ganhou!\n");
        }
    }

    return 0;
}

void exibir_matriz(int tabuleiro[][9])
{
    printf("\033[32m-------------------------------------\n");
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            printf("\033[%dm|\033[0m", (j == 3 || j == 6) ? 34 : 0);

            if (tabuleiro[i][j] == 0)
            {
                printf(" %d ", tabuleiro[i][j] > 10);
            }
            else
            {
                printf("\033[%d;01m %d \033[0m", (!teste_geral(tabuleiro[i][j], i, j, tabuleiro)) ? 33 : 31, (tabuleiro[i][j] > 10) ? tabuleiro[i][j] - 10 : tabuleiro[i][j]);
            }
        }
        printf("|%s", (i == 2 || i == 5) ? "\n\033[34m-------------------------------------\033[0m\n" : "\n─────────────────────────────────────\n");
    }
}

void zerar_matriz(int tabuleiro[][9])
{
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            tabuleiro[i][j] = 0;
        }
    }
}

int teste_linha(int num, int l, int c, int tabuleiro[][9])
{
    for (size_t i = 0; i < 9; i++)
    {
        if (tabuleiro[l][i] == num && i != c)
        {
            return 1;
        }
    }
    return 0;
}

int teste_coluna(int num, int l, int c, int tabuleiro[][9])
{
    for (size_t i = 0; i < 9; i++)
    {
        if (tabuleiro[i][c] == num && i != l)
        {
            return 1;
        }
    }
    return 0;
}

int teste_area(int num, int l, int c, int tabuleiro[][9])
{
    int aux_l, aux_c;

    if (l >= 0 && l <= 2)
    {
        aux_l = 0;
    }

    else if (l >= 3 && l <= 5)
    {
        aux_l = 3;
    }

    else if (l >= 6 && l <= 8)
    {
        aux_l = 6;
    }

    if (c >= 0 && c <= 2)
    {
        aux_c = 0;
    }

    else if (c >= 3 && c <= 5)
    {
        aux_c = 3;
    }

    else if (c >= 6 && c <= 8)
    {
        aux_c = 6;
    }

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (tabuleiro[i + aux_l][j + aux_c] == num && (i + aux_l != l || j + aux_c != c))
            {
                return 1;
            }
        }
    }

    return 0;
}

int teste_geral(int num, int l, int c, int tabuleiro[][9])
{
    if (teste_linha(num, l, c, tabuleiro))
    {
        return 1;
    }
    if (teste_coluna(num, l, c, tabuleiro))
    {
        return 1;
    }
    if (teste_area(num, l, c, tabuleiro))
    {
        return 1;
    }

    return 0;
}

void escrever_matriz(int num, int l, int c, int tabuleiro[][9])
{
    if (tabuleiro[l][c] < 10)
    {
        tabuleiro[l][c] = num;
    }
}

void gerar_dicas(int tabuleiro[][9])
{
    int parada = 0, quant_dicas = 20;

    while (1)
    {
        int rand_col = rand() % 9;
        int rand_lin = rand() % 9;
        int rand_num = rand() % 9 + 11;

        if (tabuleiro[rand_lin][rand_col] == 0 && !teste_geral(rand_num, rand_lin, rand_col, tabuleiro))
        {
            tabuleiro[rand_lin][rand_col] = rand_num;
            parada++;
        }

        if (parada >= quant_dicas)
        {
            break;
        }
    }
}

void update(int num, int l, int c, int tabuleiro[][9])
{
    escrever_matriz(num, l, c, tabuleiro);
    system("clear");
    exibir_matriz(tabuleiro);
}

int verifica_vitoria(int tabuleiro[][9], int err)
{
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            if (tabuleiro[i][j] == 0)
            {
                return 0;
            }
        }
    }

    if (!err)
    {
        return 1;
    }

    return 0;
}