#ifndef ESTRELAS_HPP_INCLUDED
#define ESTRELAS_HPP_INCLUDED
#include "variaveis_globais.hpp"

//Classe responsável pelo plano de fundo
class Estrelas
{
public:
    int ID;
    int x;
    int y;
    int velocidade;
};

//Declaração de funções relacionadas ao plano de fundo mas que não estão dentro da classe
void InitPlanoFundo(Estrelas estrelas_pf[][NUM_ESTRELAS], int pf_tamanho, int e_tamanho);
void AtualizaPlanoFundo(Estrelas estrelas_pf[][NUM_ESTRELAS], int pf_tamanho, int e_tamanho);
void DesenhaPlanoFundo(Estrelas estrelas_pf[][NUM_ESTRELAS], int pf_tamanho, int e_tamanho);

#endif // ESTRELAS_HPP_INCLUDED
