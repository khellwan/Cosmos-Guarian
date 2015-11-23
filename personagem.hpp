#ifndef PERSONAGEM_HPP_INCLUDED
#define PERSONAGEM_HPP_INCLUDED


class Personagem
{
public:
    ALLEGRO_BITMAP *bmp;
    int ID;
    int x;
    int y;
    int velocidade;
    int vidas;
    int borda_x;
    int borda_y;
    int pontos;

    void MoveCima()
    {
        y -= velocidade;

        if (y < 9) // Ajuste para n�o sair do mapa por cima.
            y = 9;

    }
    void MoveBaixo(int ALTURA_T)
    {
        y += velocidade;

        if (y > ALTURA_T-15) // Ajuste para n�o sair do mapa por baixo.
            y = ALTURA_T-15;

    }
    void MoveEsquerda()
    {
        x -= velocidade;

        if (x < 0) // Ajuste para n�o sair do mapa pela esquerda.
            x = 0;

    }
    void MoveDireita(int LARGURA_T)
    {
        x += velocidade;

        if (x > LARGURA_T-15) // Ajuste para n�o sair do mapa pela direita.
            x = LARGURA_T-15;

    }


};

void InitPersonagem(Personagem &personagem_principal);
void DesenhaPersonagem(Personagem personagem_principal);

#endif // PERSONAGEM_HPP_INCLUDED
