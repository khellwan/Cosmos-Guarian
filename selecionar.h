#ifndef SELECIONAR_H_INCLUDED
#define SELECIONAR_H_INCLUDED

class Selecionar
{
public:
    ALLEGRO_BITMAP *bmp;
    int x;
    int y;
    int ativo;

    void InitSelecionar()
    {
        x = 550;
        y = 235;
        ativo = true;
        bmp = NULL;
    }
};


#endif // SELECIONAR_H_INCLUDED
