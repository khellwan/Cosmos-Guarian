#include "includes.h"

void InitInimigo (Inimigo inimigos[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        inimigos[i].ID = INIMIGOS;
        inimigos[i].velocidade = 5;
        inimigos[i].borda_x = 77;
        inimigos[i].borda_y = 71;
        inimigos[i].ativo = false;
        inimigos[i].bmp = NULL;
    }
}
void GeraInimigos (Inimigo inimigos[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if(!inimigos[i].ativo)
        {
            if(rand() % 500 == 0) //Geração aleatória de inimigos = 1 em 500.
            {
                inimigos[i].x = LARGURA_T;
                inimigos[i].y = 30 + rand() % (ALTURA_T - 91); //Expressão que fornence um número dentro da tela do jogo.
                inimigos[i].ativo = true;
                break;
            }
        }
    }
}
void AtualizaInimigos (Inimigo inimigos[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (inimigos[i].ativo)
        {
            inimigos[i].x -= inimigos[i].velocidade;

        }
    }
}
void DesenhaInimigos (Inimigo inimigos[], int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (inimigos[i].ativo)
        {
            al_draw_bitmap(inimigos[i].bmp, inimigos[i].x, inimigos[i].y, 0);
        }

    }
}
void InimigoColidido (Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, ALLEGRO_SAMPLE *hit)
{
    int i;
    for (i = 0; i < i_tamanho; i++)
    {
        if (inimigos[i].ativo)
        {
            if ((inimigos[i].x - inimigos[i].borda_x) < (personagem_principal.x + personagem_principal.borda_x) &&
                (inimigos[i].x + inimigos[i].borda_x) > (personagem_principal.x - personagem_principal.borda_x) &&
                (inimigos[i].y - inimigos[i].borda_y) < (personagem_principal.y + personagem_principal.borda_y) &&
                (inimigos[i].y + inimigos[i].borda_y) > (personagem_principal.y - personagem_principal.borda_y))
            {

              inimigos[i].ativo = false;
              al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
              personagem_principal.vidas--;

            }

            else if (inimigos[i].x < 0)
            {
                inimigos[i].ativo = false;
                personagem_principal.vidas--;
            }
        }
    }
}
