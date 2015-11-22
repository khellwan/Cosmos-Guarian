#include "includes.h"

void InitPersonagem (Personagem &personagem_principal)
{
    personagem_principal.x = 20;
    personagem_principal.y = ALTURA_T / 2;
    personagem_principal.ID = JOGADOR;
    personagem_principal.vidas = 3;
    personagem_principal.velocidade = 7;
    personagem_principal.borda_x = 4;
    personagem_principal.borda_y = 7;
    personagem_principal.bmp = NULL;
    personagem_principal.pontos = 0;
}

void DesenhaPersonagem (Personagem personagem_principal)
{
    al_draw_bitmap(personagem_principal.bmp, personagem_principal.x, personagem_principal.y, 0);
}

void MovePersonagemCima (Personagem &personagem_principal)
{
    personagem_principal.y -= personagem_principal.velocidade;

    if (personagem_principal.y < 9)
        personagem_principal.y = 9;

}
void MovePersonagemBaixo (Personagem &personagem_principal)
{
    personagem_principal.y += personagem_principal.velocidade;

    if (personagem_principal.y > ALTURA_T-15)
        personagem_principal.y = ALTURA_T-15;

}
void MovePersonagemEsquerda (Personagem &personagem_principal)
{
    personagem_principal.x -= personagem_principal.velocidade;

    if (personagem_principal.x < 0)
        personagem_principal.x = 0;

}
void MovePersonagemDireita (Personagem &personagem_principal)
{
    personagem_principal.x += personagem_principal.velocidade;

    if (personagem_principal.x > LARGURA_T-15)
        personagem_principal.x = LARGURA_T-15;

}

