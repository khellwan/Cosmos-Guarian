#include "includes.h"

int main(int argc, char *argv[])
{

// -------- VARIÁVEIS DO JOGO --------
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *font20 = NULL;
ALLEGRO_SAMPLE *ataque = NULL;
ALLEGRO_SAMPLE *morte_inimigo = NULL;
ALLEGRO_SAMPLE *morte_personagem = NULL;
ALLEGRO_SAMPLE *hit = NULL;
ALLEGRO_SAMPLE *item = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL;
/** Mudança aqui*/
ALLEGRO_BITMAP *start = NULL;
/** Fim Mudança*/


bool fim = false;
/** Mudança aqui*/
bool menu = true;
int flag = 0;
/** Fim Mudança*/
bool desenha = true;
bool game_over = false;
bool Tem_boss;
bool teclas[] = {false, false, false, false, false, false};
int i;
int dificuldade;


// ___________________________________


// -------- INICIALIZAÇÃO DE OBJETOS --------
dificuldade = 0;
Personagem personagem_principal;
Selecionar select;
Projetil* balas = new Projetil [NUM_BALAS];
Projetil* balas_2 = new Projetil [NUM_BALAS];
Inimigo* inimigos = new Inimigo[NUM_INIMIGOS];
Inimigo* inimigos2 = new Inimigo [NUM_INIMIGOS];
Inimigo* boss = new Inimigo [1];
Coracao* coracoes = new Coracao[NUM_ITENS];
Speed* speed = new Speed[NUM_ITENS];
Energia* energia = new Energia[NUM_ITENS];
Estrelas estrelas_pf[NUM_PLANOS][NUM_ESTRELAS];


// __________________________________________

// -------- INICIALIZAÇÃO DA ALLEGRO E DO DISPLAY --------
    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init())
    {
        al_show_native_message_box(NULL, "AVISO!", "ERRO!", "ERRO AO INICIALIZAR A ALLEGRO!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    display = al_create_display(LARGURA_T, ALTURA_T);

    if (!display)
    {
        al_show_native_message_box(NULL, "AVISO!", "ERRO!", "ERRO AO CRIAR O DISPLAY!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_set_window_title(display, "Cosmos Guardian");


// ____________________________________________________

// -------- INICIALIZAÇÃO DE ADDONS E INSTALAÇÕES --------
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(100);

// _______________________________________________________

// -------- CRIAÇÃO DE FILAS E DEMAIS DISPOSITIVOS --------
    fila_eventos = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    font20 = al_load_font("BADABB__.ttf", 20, 0);


// ________________________________________________________

// -------- REGISTRO DE SOURCES --------
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

// _____________________________________

// -------- FUNÇÕES INICIAIS --------
    srand(time(NULL));
    personagem_principal.InitPersonagem();
    select.InitSelecionar();

    for (i = 0; i < NUM_BALAS; i++)
    {
        balas[i].InitBalas();
        balas_2[i].InitBalas();
    }


    for (i = 0; i < NUM_INIMIGOS; i++){
        inimigos[i].InitInimigo(7, 46, 47 ,1, 0);
        inimigos2[i].InitInimigo(3, 55, 94 , 3, 0);
    }

    boss[0].InitInimigo(1, 100, 100, 100, 1);

    for (i = 0; i < NUM_ITENS; i++)
    {
        coracoes[i].InitItem();
        speed[i].InitItem();
        energia[i].InitItem();
    }
    InitPlanoFundo(estrelas_pf, NUM_PLANOS, NUM_ESTRELAS);

    ataque = al_load_sample("laser.wav");
    morte_inimigo = al_load_sample("dead.wav");
    morte_personagem = al_load_sample("death.wav");
    hit = al_load_sample("hit.wav");
    item = al_load_sample("item.wav");
    musica = al_load_audio_stream("trilha_sonora.ogg", 4, 1024);

    /** Mudança aqui*/
    start = al_load_bitmap("start.jpg");
    select.bmp = al_load_bitmap("select.png");
    /** Fim Mudança*/

    personagem_principal.bmp = al_load_bitmap("ship.png");

    for (i = 0; i < NUM_BALAS; i++)
    {
        balas[i].bmp = al_load_bitmap("bala.png");
        balas_2[i].bmp = al_load_bitmap("bala.png");
    }
    for (i = 0; i < NUM_INIMIGOS; i++){
        inimigos[i].bmp = al_load_bitmap("enemyRed.png");
        inimigos2[i].bmp = al_load_bitmap("enemyWhite.png");
    }

    boss[0].bmp = al_load_bitmap("boss.png");

    for (i = 0; i < NUM_ITENS; i++)
        coracoes[i].imagem = al_load_bitmap("heart.png");
    for (i = 0; i < NUM_ITENS; i++)
        speed[i].imagem = al_load_bitmap("speed.png");
    for (i = 0; i < NUM_ITENS; i++)
        energia[i].imagem = al_load_bitmap("energia.png");


// __________________________________

// ----------------- LOOP PRINCIPAL -----------------
    al_start_timer(timer);

    while(!fim)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        // -------- EVENTOS E LÓGICA DO JOGO --------
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            fim = true;
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                fim = true;
                break;
            case ALLEGRO_KEY_UP:
                teclas[CIMA] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                teclas[BAIXO] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                teclas[ESQUERDA] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                teclas[DIREITA] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                teclas[ESPACO] = true;
                AtiraBalas(balas, NUM_BALAS, personagem_principal, personagem_principal.y + 12);
                AtiraBalas(balas_2, NUM_BALAS, personagem_principal, personagem_principal.y + 50);
                al_play_sample(ataque, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case ALLEGRO_KEY_ENTER:
                teclas[ENTER] = true;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                teclas[BACKSPACE] = true;
                break;
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                teclas[CIMA] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                teclas[BAIXO] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                teclas[ESQUERDA] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                teclas[DIREITA] = false;
                break;
            case ALLEGRO_KEY_ENTER:
                teclas[ENTER] = false;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                teclas[BACKSPACE] = false;
                break;

            }
        }

        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            desenha = true;

            if (teclas[CIMA])
                personagem_principal.MoveCima();
            if (teclas[BAIXO])
                personagem_principal.MoveBaixo(ALTURA_T);
            if (teclas[ESQUERDA])
                personagem_principal.MoveEsquerda();
            if (teclas[DIREITA])
                personagem_principal.MoveDireita(LARGURA_T);
            if (teclas[ESPACO])
            {
                for (i = 0; i < NUM_BALAS; i++)
                {
                    balas[i].AtualizaBalas();
                    balas_2[i].AtualizaBalas();
                }

            }

            /** Mudança aqui*/
            if(menu)
            {
                if (teclas[CIMA] && select.y!=235)
                    select.y -= 70;
                if (teclas[BAIXO] && select.y!=305)
                    select.y += 70;
                if (teclas[ENTER] && select.y==235)
                    menu = false;
            }

            if(!game_over && !menu)
            /** Fim da Mudança*/
            {
                al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
                al_set_audio_stream_playing(musica, true);

                AtualizaPlanoFundo(estrelas_pf, NUM_PLANOS, NUM_ESTRELAS);
                {
                    for (i = 0; i < NUM_INIMIGOS; i++)
                    {
                        if(!Tem_boss)
                        {
                            inimigos[i].GeraInimigos();
                            inimigos2[i].GeraInimigos();
                        }

                        inimigos[i].AtualizaInimigos();
                        inimigos[i].InimigoColidido(personagem_principal, hit);
                        inimigos2[i].AtualizaInimigos();
                        inimigos2[i].InimigoColidido(personagem_principal, hit);

                    }
                }

                if(personagem_principal.pontos > 50 && personagem_principal.pontos < 75)
                {
                    boss[0].GeraInimigos();
                    boss[0].AtualizaInimigos();
                    boss[0].InimigoColidido(personagem_principal, hit);
                    Tem_boss = true;
                }
                else
                    Tem_boss = false;

                BalaColidida(balas, NUM_BALAS, inimigos, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                BalaColidida(balas_2, NUM_BALAS, inimigos, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                BalaColidida(balas, NUM_BALAS, inimigos2, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                BalaColidida(balas_2, NUM_BALAS, inimigos2, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                BalaColidida(balas, NUM_BALAS, boss, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                BalaColidida(balas_2, NUM_BALAS, boss, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);

                for (i = 0; i < NUM_ITENS; i++)
                {
                    coracoes[i].GeraItens(inimigos[i]);
                    coracoes[i].AtualizaItens();
                    coracoes[i].ItemColidido(personagem_principal, item);
                    speed[i].GeraItens(inimigos[i]);
                    speed[i].AtualizaItens();
                    speed[i].ItemColidido(personagem_principal, item);
                    energia[i].GeraItens(inimigos[i]);
                    energia[i].AtualizaItens();
                    energia[i].ItemColidido(personagem_principal, item);
                }


                if ((dificuldade+1)%11 == 0) // Dificuldade aumenta a cada 10 pontos.
                {
                    for (i = 0; i < NUM_INIMIGOS; i++){
                        inimigos[i].velocidade++;
                        inimigos2[i].velocidade++;
                    }

                    dificuldade = 0;
                }

                if (personagem_principal.vidas <= 0)
                {
                    al_play_sample(morte_personagem, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    game_over = true;
                }
            }

            /** Mudança aqui*/
            else if (!menu)
            /** Fim da Mudança*/
            {
                al_set_audio_stream_playing(musica, false);
                if (teclas[ENTER])
                {
                    al_destroy_audio_stream(musica);

                    personagem_principal.InitPersonagem();

                    for (i = 0; i < NUM_BALAS; i++)
                    {
                        balas[i].InitBalas();
                        balas_2[i].InitBalas();
                    }


                    for (i = 0; i < NUM_INIMIGOS; i++)
                    {
                        inimigos[i].InitInimigo(7, 46, 47, 1, 0);
                        inimigos2[i].InitInimigo(3, 60, 60, 3, 0);
                    }
                    boss[0].InitInimigo(1, 100, 100, 100, 1);

                    for (i = 0; i < NUM_ITENS; i++)
                    {
                        coracoes[i].InitItem();
                        speed[i].InitItem();
                        energia[i].InitItem();
                    }


                    personagem_principal.bmp = al_load_bitmap("ship.png");
                    musica = al_load_audio_stream("trilha_sonora.ogg", 4, 1024);

                    for (i = 0; i < NUM_BALAS; i++)
                    {
                        balas[i].bmp = al_load_bitmap("bala.png");
                        balas_2[i].bmp = al_load_bitmap("bala.png");
                    }
                    for (i = 0; i < NUM_INIMIGOS; i++)
                    {
                        inimigos[i].bmp = al_load_bitmap("enemyRed.png");
                        inimigos2[i].bmp = al_load_bitmap("enemyWhite.png");
                        coracoes[i].imagem = al_load_bitmap("heart.png");
                        speed[i].imagem = al_load_bitmap("heart.png");
                        energia[i].imagem = al_load_bitmap("heart.png");
                    }
                    boss[0].bmp = al_load_bitmap("boss.png");

                    game_over = false;
                }
            }

        }


        // _________________________________________

        // ---------------- DESENHO ----------------

        if(desenha && al_is_event_queue_empty(fila_eventos))
        {
            desenha = false;

            /** Mudança aqui*/
            if(menu)
            {
                al_draw_bitmap(start, 0, 0, 0);
                if (select.ativo)
                    al_draw_bitmap(select.bmp, select.x, select.y, 0);

                if (teclas[ENTER] && flag == 0)
                {
                    flag = 1;
                    teclas[BACKSPACE] = false;
                    select.ativo = false;
                    start = al_load_bitmap("como_jogar.jpg");
                    al_draw_bitmap(start, 0, 0, 0);
                }
                else if (teclas[BACKSPACE] && flag == 1)
                {
                    flag = 0;
                    select.ativo = true;
                    start = al_load_bitmap("start.jpg");
                    al_draw_bitmap(start, 0, 0, 0);
                }
            }
            /** Fim da Mudança*/
            if(!game_over && !menu)
            {
                DesenhaPlanoFundo(estrelas_pf, NUM_PLANOS, NUM_ESTRELAS);
                personagem_principal.DesenhaPersonagem();
                for (i = 0; i < NUM_BALAS; i++)
                {
                    balas[i].DesenhaBalas();
                    balas_2[i].DesenhaBalas();
                }

                for (i = 0; i < NUM_INIMIGOS; i++){
                    inimigos[i].DesenhaInimigos();
                    inimigos2[i].DesenhaInimigos();
                }
                boss[0].DesenhaInimigos();
                for (i = 0; i < NUM_ITENS; i++)
                {
                    coracoes[i].DesenhaItens();
                    speed[i].DesenhaItens();
                    energia[i].DesenhaItens();
                }


                al_draw_textf(font20, al_map_rgb(255, 255, 255), 0, 0, 0, "VIDAS: %d / PONTOS: %d", personagem_principal.vidas, personagem_principal.pontos);
            }

            else if (!menu)
            {
                al_draw_textf(font20, al_map_rgb(255, 255, 255), LARGURA_T / 2, ALTURA_T / 2, ALLEGRO_ALIGN_CENTRE, "FIM DE JOGO. SEUS PONTOS FORAM: %d. TECLE ENTER PARA JOGAR NOVAMENTE OU ESC PARA SAIR DO JOGO.", personagem_principal.pontos);
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }


        // _________________________________________
    }

// _________________________________________________

// -------- FINALIZAÇÕES DO PROGRAMA --------
    delete[] inimigos;
    delete[] inimigos2;
    delete[] boss;
    delete[] balas;
    delete[] balas_2;
    delete[] coracoes;
    delete[] speed;
    delete[] energia;



    al_destroy_sample(ataque);
    al_destroy_sample(morte_inimigo);
    al_destroy_sample(morte_personagem);
    al_destroy_sample(hit);
    al_destroy_sample(item);
    al_destroy_audio_stream(musica);

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_font(font20);
    al_destroy_event_queue(fila_eventos);

//___________________________________________
    return 0;
}
