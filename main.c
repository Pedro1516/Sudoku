#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void escrever_matriz(int num, int l, int c, int tabuleiro[][9]);
void exibir_matriz(int tabuleiro[][9], int err, int l, int c);
void zerar_matriz(int tabuleiro[][9]);
int teste_linha(int num, int l, int c, int tabuleiro[][9]);
int teste_coluna(int num, int l, int c, int tabuleiro[][9]);
int teste_area(int num, int l, int c, int tabuleiro[][9]);
int teste_geral(int num, int l, int c, int tabuleiro[][9]);
void escrever_matriz(int num, int l, int c, int tabuleiro[][9]);
void gerar_dicas(int tabuleiro[][9]);

int main()
{
    srand(time(NULL));

    int num, lin, col;
    int tabuleiro[9][9];

    zerar_matriz(tabuleiro);
    gerar_dicas(tabuleiro);
    exibir_matriz(tabuleiro, 0, 0, 0);

    while (1)
    {
        scanf("%d %d %d", &num, &lin, &col);
        escrever_matriz(num, lin, col, tabuleiro);
        system("clear");

        int err = teste_geral(num, lin, col, tabuleiro);

        exibir_matriz(tabuleiro, err, lin, col);

      
    }

    return 0;
}

void exibir_matriz(int tabuleiro[][9], int err, int l, int c)
{
    printf("-------------------------------------\n");
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            printf("\033[%dm|\033[0m", (j == 3 || j == 6) ? 34 : 0);

            if (tabuleiro[i][j] == 0)
            {
                printf(" %d ", tabuleiro[i][j]);
            }
            else
            {
                printf("\033[%d;01m %d \033[0m", (!teste_geral(tabuleiro[i][j], i, j, tabuleiro)) ? 33 : 31, tabuleiro[i][j]);
            }
        }
        printf("|\n\033[%dm-------------------------------------\033[0m\n", (i == 2 || i == 5) ? 34 : 0);
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
        aux_l = 7;
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
        aux_c = 7;
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
    tabuleiro[l][c] = num;
}

void gerar_dicas(int tabuleiro[][9])
{
    int parada = 0, quant_dicas = 20;

    while (1)
    {
        int rand_col = rand() % 9;
        int rand_lin = rand() % 9;
        int rand_num = rand() % 9 + 1;

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