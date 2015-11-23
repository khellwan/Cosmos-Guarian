#ifndef INIMIGO_HPP_INCLUDED
#define INIMIGO_HPP_INCLUDED
#include "includes.h"

class Inimigo
{
public:
    ALLEGRO_BITMAP *bmp;
    int ID;
    int x;
    int y;
    int velocidade;
    int borda_x;
    int borda_y;
    int tipo;
    bool ativo;

    void InitInimigo()
    {
        ID = INIMIGOS;
        velocidade = 7;
        borda_x = 77;
        borda_y = 71;
        ativo = false;
        bmp = NULL;
    }
    void GeraInimigos ()
    {
        if(!ativo)
        {
            if(rand() % 500 == 0) //Geração aleatória de inimigos = 1 em 500.
            {
                x = LARGURA_T;
                y = 30 + rand() % (ALTURA_T - 91); //Expressão que fornence um número dentro da tela do jogo.
                ativo = true;
            }
        }
    }
    void AtualizaInimigos ()
    {
        if (ativo)
            x -= velocidade;
    }
    void DesenhaInimigos ()
    {
        if (ativo)
            al_draw_bitmap(bmp, x, y, 0);
    }
    void InimigoColidido (Personagem &personagem_principal, ALLEGRO_SAMPLE *hit)
    {
        if (ativo)
        {
            if ((x - borda_x) < (personagem_principal.x + personagem_principal.borda_x) &&
                (x + borda_x) > (personagem_principal.x - personagem_principal.borda_x) &&
                (y - borda_y) < (personagem_principal.y + personagem_principal.borda_y) &&
                (y + borda_y) > (personagem_principal.y - personagem_principal.borda_y))
            {

              ativo = false;
              al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
              personagem_principal.vidas--;

            }

            else if (x < 0)
            {
                ativo = false;
                personagem_principal.vidas--;
            }
        }
    }

};


#endif // INIMIGO_HPP_INCLUDED
