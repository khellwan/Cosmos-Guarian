#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED
#include "includes.h"


class Item
{
public:
    ALLEGRO_BITMAP *imagem;
    int x;
    int y;
    int borda_x;
    int borda_y;
    int velocidade;
    bool ativo;

    virtual void ItemColidido(Personagem &personagem_principal, ALLEGRO_SAMPLE *item) = 0;

    virtual void InitItem()
    {
        borda_x = 50;
        borda_y = 50;
        ativo = false;
        imagem = NULL;
        velocidade = 5;
    }

    void AtualizaItens()
    {
        if (ativo)
            x -= velocidade;
    }

    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 2000 == 0) //Geração aleatória de itens = 1 em 2000.
            {
                x = inimigo.x;
                y = inimigo.y;
                ativo = true;
            }
        }

    }
    void DesenhaItens()
    {
        if (ativo)
            al_draw_bitmap(imagem, x, y, 0);

    }
};

class Coracao : public Item
{
public:
    void ItemColidido (Personagem &personagem_principal, ALLEGRO_SAMPLE *item)
    {
        if (ativo)
        {
            if ((x - borda_x) < (personagem_principal.x + personagem_principal.borda_x) &&
                (x + borda_x) > (personagem_principal.x - personagem_principal.borda_x) &&
                (y - borda_y) < (personagem_principal.y + personagem_principal.borda_y) &&
                (y + borda_y) > (personagem_principal.y - personagem_principal.borda_y))
            {

              ativo = false;
              al_play_sample(item, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
              personagem_principal.vidas++;
              x = 1300;
              y = 900;

            }
        }
    }


    void InitItem ()
    {
        borda_x = 48;
        borda_y = 47;
        ativo = false;
        imagem = NULL;
        velocidade = 4;
    }
};



#endif // ITEMS_H_INCLUDED
