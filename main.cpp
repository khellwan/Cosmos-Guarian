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
ALLEGRO_AUDIO_STREAM *musica = NULL;


bool fim = false;
bool desenha = true;
bool game_over = false;
bool teclas[] = {false, false, false, false, false, false};
int i;
int dificuldade;


// ___________________________________


// -------- INICIALIZAÇÃO DE OBJETOS --------
dificuldade = 0;
Personagem personagem_principal;
Projetil* balas = new Projetil [NUM_BALAS];
Projetil* balas_2 = new Projetil [NUM_BALAS];
Inimigo* inimigos = new Inimigo[NUM_INIMIGOS];
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
    InitPersonagem(personagem_principal);
    InitBalas(balas, NUM_BALAS);
    InitBalas(balas_2, NUM_BALAS);
    InitInimigo(inimigos, NUM_INIMIGOS);
    InitPlanoFundo(estrelas_pf, NUM_PLANOS, NUM_ESTRELAS);
    ataque = al_load_sample("laser.wav");
    morte_inimigo = al_load_sample("dead.wav");
    morte_personagem = al_load_sample("death.wav");
    hit = al_load_sample("hit.wav");
    musica = al_load_audio_stream("trilha_sonora.ogg", 4, 1024);


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
                AtiraBalas(balas_2, NUM_BALAS, personagem_principal, personagem_principal.y + 70);
                al_play_sample(ataque, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case ALLEGRO_KEY_ENTER:
                teclas[ENTER] = true;
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
                AtualizaBalas(balas, NUM_BALAS);
                AtualizaBalas(balas_2, NUM_BALAS);
            }


            if(!game_over)
            {
                al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
                al_set_audio_stream_playing(musica, true);

                AtualizaPlanoFundo(estrelas_pf, NUM_PLANOS, NUM_ESTRELAS);
                GeraInimigos(inimigos, NUM_INIMIGOS);
                AtualizaInimigos(inimigos, NUM_INIMIGOS);
                BalaColidida(balas, NUM_BALAS, inimigos, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                BalaColidida(balas_2, NUM_BALAS, inimigos, NUM_INIMIGOS, personagem_principal, dificuldade, morte_inimigo);
                InimigoColidido(inimigos, NUM_INIMIGOS, personagem_principal, hit);

                if ((dificuldade+1)%11 == 0) // Dificuldade aumenta a cada 10 pontos.
                {
                    for (i = 0; i < NUM_INIMIGOS; i++)
                        inimigos[i].velocidade++;

                    dificuldade = 0;
                }

                if (personagem_principal.vidas <= 0)
                {
                    al_play_sample(morte_personagem, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    game_over = true;
                }
            }

            else
            {
                al_set_audio_stream_playing(musica, false);
                if (teclas[ENTER])
                {
                    InitPersonagem(personagem_principal);
                    InitBalas(balas, NUM_BALAS);
                    InitBalas(balas_2, NUM_BALAS);
                    InitInimigo(inimigos, NUM_INIMIGOS);

                    game_over = false;
                }
            }

        }


        // _________________________________________

        // ---------------- DESENHO ----------------

        if(desenha && al_is_event_queue_empty(fila_eventos))
        {
            desenha = false;

            if(!game_over)
            {
                personagem_principal.bmp = al_load_bitmap("ship.png");
                for (i = 0; i < NUM_BALAS; i++)
                {
                    balas[i].bmp = al_load_bitmap("bala.png");
                    balas_2[i].bmp = al_load_bitmap("bala.png");
                }

                for (i = 0; i < NUM_INIMIGOS; i++)
                    inimigos[i].bmp = al_load_bitmap("enemyRed.png");

                DesenhaPlanoFundo(estrelas_pf, NUM_PLANOS, NUM_ESTRELAS);
                personagem_principal.DesenhaPersonagem();
                DesenhaBalas(balas, NUM_BALAS);
                DesenhaBalas(balas_2, NUM_BALAS);
                DesenhaInimigos(inimigos, NUM_INIMIGOS);

                al_draw_textf(font20, al_map_rgb(255, 255, 255), 0, 0, 0, "VIDAS: %d / PONTOS: %d", personagem_principal.vidas, personagem_principal.pontos);
            }

            else
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
    delete[] balas;
    delete[] balas_2;

    al_destroy_sample(ataque);
    al_destroy_sample(morte_inimigo);
    al_destroy_sample(morte_personagem);
    al_destroy_sample(hit);
    al_destroy_audio_stream(musica);

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_font(font20);
    al_destroy_event_queue(fila_eventos);






//___________________________________________
    return 0;
}
