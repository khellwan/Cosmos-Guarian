#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED
#include "includes.h"

// Classe responsável pelos itens em geral
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

    //Método puramente virtual para termos certeza de não chamá-lo nunca
    virtual void ItemColidido(Personagem &personagem_principal, ALLEGRO_SAMPLE *item) = 0;

    //Inicializa os itens com valores padrão
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

    // É colocada uma porcentagem para a qual o item em questão é gerado.
    void GeraItens(Inimigo inimigo)
    {
        if(!inimigo.ativo)
        {
            if(rand() % 5800 == 0) //Geração aleatória de itens = 1 em 5800.
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

    //Função responsável por desenhar os itens no display
    void DesenhaItens()
    {
        if (ativo)
            al_draw_bitmap(imagem, x, y, 0);
    }
};

// Classe responsável pelo item que dá vida (coração)
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

// Classe responsável pelo item que dá velocidade (speed)
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
            if(rand() % 7500 == 0) //Geração aleatória de itens = 1 em 7500.
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

// Classe responsável pelo item que dá pontos extras (ItemPontos)
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
            if(rand() % 3000 == 0) //Geração aleatória de itens = 1 em 3000.
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
