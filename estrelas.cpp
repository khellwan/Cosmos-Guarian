#include "includes.h"

void InitPlanoFundo(Estrelas estrelas_pf[][NUM_ESTRELAS], int pf_tamanho, int e_tamanho)
{
    int i, j;
    for (i = 0; i < pf_tamanho; i++)
    {
        for (j = 0; j < e_tamanho; j++)
        {
            if (i == 0)
            {
                estrelas_pf[i][j].ID = ESTRELA;
                estrelas_pf[i][j].x = 5 + rand() % (LARGURA_T - 10);
                estrelas_pf[i][j].y = 5 + rand() % (ALTURA_T - 10);
                estrelas_pf[i][j].velocidade = 8;
            }
            else if (i == 1)
            {
                estrelas_pf[i][j].ID = ESTRELA;
                estrelas_pf[i][j].x = 5 + rand() % (LARGURA_T - 10);
                estrelas_pf[i][j].y = 5 + rand() % (ALTURA_T - 10);
                estrelas_pf[i][j].velocidade = 3;
            }
            else if(i == 2)
            {
                estrelas_pf[i][j].ID = ESTRELA;
                estrelas_pf[i][j].x = 5 + rand() % (LARGURA_T - 10);
                estrelas_pf[i][j].y = 5 + rand() % (ALTURA_T - 10);
                estrelas_pf[i][j].velocidade = 1;
            }
        }
    }
}
void AtualizaPlanoFundo(Estrelas estrelas_pf[][NUM_ESTRELAS], int pf_tamanho, int e_tamanho)
{
    int i, j;
    for (i = 0; i < pf_tamanho; i++)
    {
        for (j = 0; j < e_tamanho; j++)
        {
            if (i == 0)
            {
                estrelas_pf[i][j].x -= estrelas_pf[i][j].velocidade;

                if (estrelas_pf[i][j].x < 0)
                    estrelas_pf[i][j].x = LARGURA_T;
            }
            else if (i == 1)
            {
                 estrelas_pf[i][j].x -= estrelas_pf[i][j].velocidade;

                if (estrelas_pf[i][j].x < 0)
                    estrelas_pf[i][j].x = LARGURA_T;
            }
            else if(i == 2)
            {
                 estrelas_pf[i][j].x -= estrelas_pf[i][j].velocidade;

                if (estrelas_pf[i][j].x < 0)
                    estrelas_pf[i][j].x = LARGURA_T;
            }
        }
    }
}
void DesenhaPlanoFundo(Estrelas estrelas_pf[][NUM_ESTRELAS], int pf_tamanho, int e_tamanho)
{
    int i, j;
    for (i = 0; i < pf_tamanho; i++)
    {
        for (j = 0; j < e_tamanho; j++)
        {
            if (i == 0)
            {
                al_draw_pixel(estrelas_pf[i][j].x, estrelas_pf[i][j].y, al_map_rgb(255, 255, 255));
            }
            else if (i == 1)
            {
                 al_draw_pixel(estrelas_pf[i][j].x, estrelas_pf[i][j].y, al_map_rgb(255, 255, 255));
            }
            else if(i == 2)
            {
                 al_draw_pixel(estrelas_pf[i][j].x, estrelas_pf[i][j].y, al_map_rgb(255, 255, 255));
            }
        }
    }
}
