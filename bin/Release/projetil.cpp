#include "includes.h"
// Função que gera os disparos do personagem
void AtiraBalas (Projetil balas[], int tamanho, Personagem personagem_principal, int y)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (!balas[i].ativo)
        {
            balas[i].x = personagem_principal.x + 15;
            balas[i].y = y;
            balas[i].ativo = true;
            break;
        }
    }
}

// Função que checa colisões relacionadas aos projeteis do personagem
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
                        balas[i].y > (inimigos[j].y-10) &&
                        balas[i].y < (inimigos[j].y + inimigos[j].borda_y))
                        {
                        balas[i].ativo = false;
                        inimigos[j].vidas --;
                        if (inimigos[j].vidas <= 0)
                        {
                            if(inimigos[j].tipo == 1)
                                personagem_principal.pontos += 24;
                            personagem_principal.pontos++;
                            dificuldade++;
                            inimigos[j].ativo = false;
                        }

                        al_play_sample(morte_inimigo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    }
                }
            }
        }
    }
};


