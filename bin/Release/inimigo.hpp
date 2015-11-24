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
    int vidas;
    int vidas_max;
    int tipo;
    bool ativo;

    // Inicia os inimigos com valores passados por parâmetros
    void InitInimigo(int v, int x, int y, int vida, int tipos)
    {
        tipo = tipos;
        vidas = vida;
        vidas_max = vida;
        ID = INIMIGOS;
        velocidade = v;
        borda_x = x;
        borda_y = y;
        ativo = false;
        bmp = NULL;
    }

    // Essa função é responsável por gerar inimigos em posições aletórias e em momentos aleatórios
    void GeraInimigos ()
    {
        if(!ativo)
        {
            if (tipo == 1){
                vidas = vidas_max;
                x = LARGURA_T;
                y = ALTURA_T/2 - 225;
                ativo = true;
            }
            if(rand() % (vidas_max*vidas_max*800) == 0) //Geração aleatória de inimigos
            {
                vidas = vidas_max;
                x = LARGURA_T;
                y = 30 + rand() % (ALTURA_T - 91); //Expressão que fornence um número dentro da tela do jogo.
                ativo = true;
            }
        }
    }

    // Faz os inimigos se moverem
    void AtualizaInimigos ()
    {
        ID++;
        if (ID == 10)
            ID = 0;
        if (tipo==1 && x<LARGURA_T);
        else if (ativo)
            x -= velocidade;
    }

    void DesenhaInimigos ()
    {
        if (ativo)
            al_draw_bitmap(bmp, x, y, 0);
    }

    // Checa colisões dos inimigos com o personagem
    void InimigoColidido (Personagem &personagem_principal, ALLEGRO_SAMPLE *hit)
    {
        if (ativo)
        {
            if  (x < (personagem_principal.x + personagem_principal.borda_x) &&
                (x + borda_x) > (personagem_principal.x) &&
                y < (personagem_principal.y + personagem_principal.borda_y) &&
                (y + borda_y) > (personagem_principal.y))
            {

              ativo = false;
              al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                personagem_principal.vidas--;

            }

            else if (x < 0)
            {
                personagem_principal.vidas--;
                ativo = false;
            }
        }
    }

};


#endif // INIMIGO_HPP_INCLUDED
