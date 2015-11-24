#ifndef PROJETIL_HPP_INCLUDED
#define PROJETIL_HPP_INCLUDED
#include "inimigo.hpp"

//Classe responsável pelas balas da nave
class Projetil
{
public:
    ALLEGRO_BITMAP *bmp;
    int ID;
    int x;
    int y;
    int velocidade;
    bool ativo;

    //Inicializa as balas com valores padrões
    void InitBalas ()
    {
        ID = PROJETIL;
        velocidade = 10;
        ativo = false;
        bmp = NULL;
    }

    //Movimenta as balas
    void AtualizaBalas (int tipo)
    {
        if (ativo)
        {
            if (tipo == 1)
                x -= velocidade;
            else
                x += velocidade;
            if (x > LARGURA_T || (x<50 && tipo == 1))
                ativo = false;
        }
    }

    //Desenha as balas
    void DesenhaBalas ()
    {
        if (ativo)
             al_draw_bitmap(bmp, x, y, 0);
    }

};

//Declaração de funções relacionadas as balas mas que não estão dentro da classe
void AtiraBalas (Projetil balas[], int tamanho, Personagem personagem_principal, int y);
void AtiraBalasBoss (Projetil balas[], int tamanho, Inimigo boss);
void BalaColididaBoss (Projetil balas[], int b_tamanho, Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, ALLEGRO_SAMPLE *morte_inimigo);
void BalaColidida (Projetil balas[], int b_tamanho, Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, int &dificuldade, ALLEGRO_SAMPLE *morte_inimigo);
#endif // PROJETIL_HPP_INCLUDED
