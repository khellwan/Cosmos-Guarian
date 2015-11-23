#include "includes.h"

void InitBalas (Projetil balas[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        balas[i].ID = PROJETIL;
        balas[i].velocidade = 10;
        balas[i].ativo = false;
        balas[i].bmp = NULL;
    }
}
void AtiraBalas (Projetil balas[], int tamanho, Personagem personagem_principal, int y)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (!balas[i].ativo)
        {
            balas[i].x = personagem_principal.x + 53;
            balas[i].y = y;
            balas[i].ativo = true;
            break;
        }
    }
}
void AtualizaBalas (Projetil balas[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (balas[i].ativo)
        {
            balas[i].x += balas[i].velocidade;

            if (balas[i].x > LARGURA_T)
                balas[i].ativo = false;
        }
    }
}
void DesenhaBalas (Projetil balas[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (balas[i].ativo)
             al_draw_bitmap(balas[i].bmp, balas[i].x, balas[i].y, 0); //mem leak
    }
}
void BalaColidida (Projetil balas[], int b_tamanho, Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, int &dificuldade, ALLEGRO_SAMPLE *morte_inimigo)
{
    int i, j;
    for (i = 0; i < b_tamanho; i++)
    {
        if (balas[i].ativo)
        {
            for (j = 0; j < i_tamanho; j++)
            {

                if (inimigos[j].ativo)
                {
                    if (balas[i].x > inimigos[j].x &&
                        balas[i].x < (inimigos[j].x + inimigos[j].borda_x) &&
                        balas[i].y > (inimigos[j].y-10) &&
                        balas[i].y < (inimigos[j].y + inimigos[j].borda_y))
                    {
                        balas[i].ativo = false;

                        inimigos[j].ativo = false;
                        al_play_sample(morte_inimigo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                        personagem_principal.pontos++;
                        dificuldade++;
                    }
                }
            }
        }
    }
}
