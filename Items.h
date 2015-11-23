#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED
#include "includes.h"


class Item
{
public:
    ALLEGRO_BITMAP *imagem;
    int ID;
    int x;
    int y;
    int borda_x;
    int borda_y;
    int velocidade;
    bool ativo;

    virtual void ItemColidido(Personagem &personagem_principal, ALLEGRO_SAMPLE *item) = 0;

    virtual void InitItem()
    {
        ID = ITENS;
        borda_x = 20;
        borda_y = 20;
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
            if(rand() % 2500 == 0) //Geração aleatória de itens = 1 em 2000.
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

            }
        }
    }


    void InitItem ()
    {
        ID = ITENS;
        borda_x = 48;
        borda_y = 47;
        ativo = false;
        imagem = NULL;
        velocidade = 4;
    }
};

class Speed : public Item
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
              personagem_principal.velocidade ++;

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


    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 7500 == 0) //Geração aleatória de itens = 1 em 2000.
            {
                x = inimigo.x;
                y = inimigo.y;
                ativo = true;
            }
        }

    }
};

class Energia : public Item
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
              personagem_principal.energia ++;

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


    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 7500 == 0) //Geração aleatória de itens = 1 em 2000.
            {
                x = inimigo.x;
                y = inimigo.y;
                ativo = true;
            }
        }

    }
};

#endif // ITEMS_H_INCLUDED
