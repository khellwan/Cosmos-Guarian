#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED
#include "includes.h"

// Classe respons�vel pelos itens em geral
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

    //M�todo puramente virtual para termos certeza de n�o cham�-lo nunca
    virtual void ItemColidido(Personagem &personagem_principal, ALLEGRO_SAMPLE *item) = 0;

    //Inicializa os itens com valores padr�o
    virtual void InitItem()
    {
        ID = ITENS;
        borda_x = 20;
        borda_y = 20;
        ativo = false;
        imagem = NULL;
        velocidade = 5;
    }

    //Faz com que os os itens se movam
    void AtualizaItens()
    {
        if (ativo)
            x -= velocidade;
    }

    // � colocada uma porcentagem para a qual o item em quest�o � gerado.
    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 5800 == 0) //Gera��o aleat�ria de itens = 1 em 5800.
            {
                if (inimigo.x > LARGURA_T/2)
                    x = inimigo.x;
                else
                    x = LARGURA_T/2;
                if (inimigo.y > 80)
                    y = inimigo.y;
                else
                    y = (rand() % 400) + 100;
                ativo = true;
            }
        }

    }

    //Fun��o respons�vel por desenhar os itens no display
    void DesenhaItens()
    {
        if (ativo)
            al_draw_bitmap(imagem, x, y, 0);
    }
};

// Classe respons�vel pelo item que d� vida (cora��o)
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
        borda_x = 10;
        borda_y = 10;
        ativo = false;
        imagem = NULL;
        velocidade = 4;
    }
};

// Classe respons�vel pelo item que d� velocidade (speed)
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
        borda_x = 10;
        borda_y = 10;
        ativo = false;
        imagem = NULL;
        velocidade = 4;
    }
    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 7500 == 0) //Gera��o aleat�ria de itens = 1 em 7500.
            {
                if (inimigo.x > LARGURA_T/2)
                    x = inimigo.x;
                else
                    x = LARGURA_T/2;
                if (inimigo.y > 80)
                    y = inimigo.y;
                else
                    y = (rand() % 400) + 100;
                ativo = true;
            }
        }
    }
};

// Classe respons�vel pelo item que d� pontos extras (ItemPontos)
class ItemPontos : public Item
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
              personagem_principal.pontos += 5;
            }
        }
    }
    void InitItem ()
    {
        borda_x = 10;
        borda_y = 10;
        ativo = false;
        imagem = NULL;
        velocidade = 4;
    }

    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 3000 == 0) //Gera��o aleat�ria de itens = 1 em 3000.
            {
                if (inimigo.x > LARGURA_T/2)
                    x = inimigo.x;
                else
                    x = LARGURA_T/2;
                if (inimigo.y > 80)
                    y = inimigo.y;
                else
                    y = (rand() % 400) + 100;
                ativo = true;
            }
        }
    }
};

#endif // ITEMS_H_INCLUDED
