#ifndef PROJETIL_HPP_INCLUDED
#define PROJETIL_HPP_INCLUDED
#include "inimigo.hpp"

class Projetil
{
public:
    ALLEGRO_BITMAP *bmp;
    int ID;
    int x;
    int y;
    int velocidade;
    bool ativo;

    void InitBalas ()
    {
        ID = PROJETIL;
        velocidade = 10;
        ativo = false;
        bmp = NULL;
    }

    void AtualizaBalas ()
    {
        if (ativo)
        {
            x += velocidade;

            if (x > LARGURA_T)
                ativo = false;
        }
    }
    void DesenhaBalas ()
    {
        if (ativo)
             al_draw_bitmap(bmp, x, y, 0);
    }

};

void AtiraBalas (Projetil balas[], int tamanho, Personagem personagem_principal, int y);
void BalaColidida (Projetil balas[], int b_tamanho, Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, int &dificuldade, ALLEGRO_SAMPLE *morte_inimigo);

#endif // PROJETIL_HPP_INCLUDED
