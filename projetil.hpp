#ifndef PROJETIL_HPP_INCLUDED
#define PROJETIL_HPP_INCLUDED


class Inimigo;
class Personagem;

class Projetil
{
public:
    ALLEGRO_BITMAP *bmp;
    int ID;
    int x;
    int y;
    int velocidade;
    bool ativo;

};

void InitBalas (Projetil balas[], int tamanho);
void AtiraBalas (Projetil balas[], int tamanho, Personagem personagem_principal, int y);
void AtualizaBalas (Projetil balas[], int tamanho);
void DesenhaBalas (Projetil balas[], int tamanho);
void BalaColidida (Projetil balas[], int b_tamanho, Inimigo inimigos[], int i_tamanho, Personagem &personagem_principal, int &dificuldade, ALLEGRO_SAMPLE *morte_personagem);


#endif // PROJETIL_HPP_INCLUDED
