#ifndef INIMIGO_HPP_INCLUDED
#define INIMIGO_HPP_INCLUDED

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
    bool ativo;

};

void InitInimigo (Inimigo inimigos[], int tamanho);
void GeraInimigos (Inimigo inimigos[], int tamanho);
void AtualizaInimigos (Inimigo inimigos[], int tamanho);
void DesenhaInimigos (Inimigo inimigos[], int tamanho);
void InimigoColidido (Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, ALLEGRO_SAMPLE *hit);

#endif // INIMIGO_HPP_INCLUDED
