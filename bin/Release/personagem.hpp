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
    int energia;

    //Inicia o personagem com valores padrões
    void InitPersonagem()
    {
        x = 20;
        y = ALTURA_T / 2;
        ID = JOGADOR;
        vidas = 3;
        velocidade = 5;
        borda_x = 40;
        borda_y = 50;
        bmp = NULL;
        pontos = 0;
        energia = 0;
    }

    //Desenha o Personagem
    void DesenhaPersonagem()
    {
        al_draw_bitmap(bmp, x, y, 0);
    }

    //Move o personagem para cima
    void MoveCima()
    {
        y -= velocidade;

        if (y < 9) // Ajuste para não sair do mapa por cima.
            y = 9;

    }
    //Move o personagem para baixo
    void MoveBaixo(int ALTURA_T)
    {
        y += velocidade;

        if (y > ALTURA_T-90) // Ajuste para não sair do mapa por baixo.
            y = ALTURA_T-90;

    }
    //Move o personagem para esquerda
    void MoveEsquerda()
    {
        x -= velocidade;

        if (x < 0) // Ajuste para não sair do mapa pela esquerda.
            x = 0;

    }
    //Move o personagem para direita
    void MoveDireita(int LARGURA_T)
    {
        x += velocidade;

        if (x > LARGURA_T-90) // Ajuste para não sair do mapa pela direita.
            x = LARGURA_T-90;
    }
};
#endif // PERSONAGEM_HPP_INCLUDED
