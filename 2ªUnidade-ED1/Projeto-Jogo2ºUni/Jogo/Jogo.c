#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define LARGURA 800
#define ALTURA 600

#define MAX_MOEDAS 5
#define MAX_INIMIGOS 3
#define MAX_SCORE 100

#define TAM_JOGADOR 64
#define TAM_MOEDA 32

// ================= ENUM =================

typedef enum
{
    MENU,
    JOGANDO,
    LEADERBOARD,
    SAIR
} EstadoJogo;

// ================= STRUCTS =================

typedef struct
{
    int x;
    int y;
} Posicao;

typedef struct
{
    char nome[50];
    int pontuacao;
    Posicao pos;
} Jogador;

typedef struct
{
    Posicao pos;
    int ativa;
    int valor;
} Moeda;

typedef struct
{
    int x;
    int y;
    int velocidade;
} Inimigo;

typedef struct
{
    char nome[50];
    int pontuacao;
} Score;

// ================= FUNÇÕES =================

void mover_jogador(Jogador *j, int dx, int dy)
{
    j->pos.x += dx;
    j->pos.y += dy;

    if (j->pos.x < 0)
        j->pos.x = 0;

    if (j->pos.x > LARGURA - TAM_JOGADOR)
        j->pos.x = LARGURA - TAM_JOGADOR;

    if (j->pos.y < 0)
        j->pos.y = 0;

    if (j->pos.y > ALTURA - TAM_JOGADOR)
        j->pos.y = ALTURA - TAM_JOGADOR;
}

int colisao(Jogador *j, Moeda *m)
{
    if (!m->ativa)
        return 0;

    if (j->pos.x < m->pos.x + TAM_MOEDA &&
        j->pos.x + TAM_JOGADOR > m->pos.x &&
        j->pos.y < m->pos.y + TAM_MOEDA &&
        j->pos.y + TAM_JOGADOR > m->pos.y)
    {
        return 1;
    }

    return 0;
}

void salvar_score(Jogador jogador)
{
    FILE *arquivo = fopen("scores.txt", "a");

    if (arquivo != NULL)
    {
        fprintf(arquivo,
                "%s %d\n",
                jogador.nome,
                jogador.pontuacao);

        fclose(arquivo);
    }
}

void trocar(Score *a, Score *b)
{
    Score temp = *a;
    *a = *b;
    *b = temp;
}

int particao(Score v[], int inicio, int fim)
{
    int pivo = v[fim].pontuacao;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (v[j].pontuacao > pivo)
        {
            i++;
            trocar(&v[i], &v[j]);
        }
    }

    trocar(&v[i + 1], &v[fim]);

    return i + 1;
}

void quickSort(Score v[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int p = particao(v, inicio, fim);

        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int carregar_scores(Score ranking[])
{
    FILE *arquivo = fopen("scores.txt", "r");

    int total = 0;

    if (arquivo == NULL)
        return 0;

    while (fscanf(arquivo,
                  "%s %d",
                  ranking[total].nome,
                  &ranking[total].pontuacao) != EOF)
    {
        total++;
    }

    fclose(arquivo);

    quickSort(ranking, 0, total - 1);

    return total;
}

// ================= MAIN =================

int main()
{
    // ================= ALLEGRO =================

    al_init();
    al_install_keyboard();

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *display =
        al_create_display(LARGURA, ALTURA);

    ALLEGRO_TIMER *timer =
        al_create_timer(1.0 / 60);

    ALLEGRO_EVENT_QUEUE *fila =
        al_create_event_queue();

    ALLEGRO_FONT *font =
        al_load_ttf_font("arial.ttf", 24, 0);

    // ================= IMAGENS =================

    ALLEGRO_BITMAP *background =
        al_load_bitmap("../BackGround/BackGround.png");

    ALLEGRO_BITMAP *player =
        al_load_bitmap("../Hero/player.png");

    ALLEGRO_BITMAP *enemy =
        al_load_bitmap("../Enemy/Golem_01.png");

    ALLEGRO_BITMAP *coin =
        al_load_bitmap("../Coin/Gold_21.png");

    // ================= EVENTOS =================

    al_register_event_source(
        fila,
        al_get_keyboard_event_source());

    al_register_event_source(
        fila,
        al_get_display_event_source(display));

    al_register_event_source(
        fila,
        al_get_timer_event_source(timer));

    // ================= JOGADOR =================

    Jogador jogador;

    strcpy(jogador.nome, "Heroi");

    jogador.pontuacao = 0;

    jogador.pos.x = 100;
    jogador.pos.y = 100;

    // ================= MOEDAS =================

    Moeda moedas[MAX_MOEDAS];

    for (int i = 0; i < MAX_MOEDAS; i++)
    {
        moedas[i].pos.x = 150 + i * 100;
        moedas[i].pos.y = 250;

        moedas[i].ativa = 1;
        moedas[i].valor = 10;
    }

    // ================= INIMIGOS =================

    Inimigo inimigos[MAX_INIMIGOS];

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigos[i].x = 700;
        inimigos[i].y = 100 + i * 120;
        inimigos[i].velocidade = 2 + i;
    }

    // ================= LEADERBOARD =================

    Score ranking[MAX_SCORE];
    int total_scores = 0;

    // ================= CONTROLE =================

    EstadoJogo estado = MENU;

    int teclas[4] = {0};

    int rodando = 1;

    al_start_timer(timer);

    // ================= LOOP =================

    while (rodando)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila, &ev);

        // ================= TIMER =================

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (estado == JOGANDO)
            {
                int dx = 0;
                int dy = 0;

                if (teclas[0])
                    dx -= 5;
                if (teclas[1])
                    dx += 5;
                if (teclas[2])
                    dy -= 5;
                if (teclas[3])
                    dy += 5;

                mover_jogador(&jogador, dx, dy);

                // ================= COLISÃO =================

                for (int i = 0; i < MAX_MOEDAS; i++)
                {
                    if (colisao(&jogador, &moedas[i]))
                    {
                        jogador.pontuacao += moedas[i].valor;
                        moedas[i].ativa = 0;
                    }
                }

                // ================= MOVIMENTO INIMIGOS =================

                for (int i = 0; i < MAX_INIMIGOS; i++)
                {
                    inimigos[i].x -= inimigos[i].velocidade;

                    if (inimigos[i].x < -64)
                    {
                        inimigos[i].x = 800;
                    }
                }
            }

            // ================= DESENHO =================

            al_clear_to_color(al_map_rgb(0, 0, 0));

            // ================= MENU =================

            if (estado == MENU)
            {
                al_draw_text(font,
                             al_map_rgb(255, 255, 255),
                             220,
                             250,
                             0,
                             "ENTER - JOGAR");

                al_draw_text(font,
                             al_map_rgb(255, 255, 255),
                             220,
                             300,
                             0,
                             "L - LEADERBOARD");

                al_draw_text(font,
                             al_map_rgb(255, 255, 255),
                             220,
                             350,
                             0,
                             "ESC - SAIR");
            }

            // ================= JOGO =================

            if (estado == JOGANDO)
            {
                al_draw_bitmap(background, 0, 0, 0);

                // player
                al_draw_bitmap(player,
                               jogador.pos.x,
                               jogador.pos.y,
                               0);

                // moedas
                for (int i = 0; i < MAX_MOEDAS; i++)
                {
                    if (moedas[i].ativa)
                    {
                        al_draw_bitmap(coin,
                                       moedas[i].pos.x,
                                       moedas[i].pos.y,
                                       0);
                    }
                }

                // inimigos
                for (int i = 0; i < MAX_INIMIGOS; i++)
                {
                    al_draw_bitmap(enemy,
                                   inimigos[i].x,
                                   inimigos[i].y,
                                   0);
                }

                // score
                al_draw_textf(font,
                              al_map_rgb(255, 255, 255),
                              10,
                              10,
                              0,
                              "Score: %d",
                              jogador.pontuacao);
            }

            // ================= LEADERBOARD =================

            if (estado == LEADERBOARD)
            {
                al_draw_text(font,
                             al_map_rgb(255, 255, 0),
                             260,
                             40,
                             0,
                             "LEADERBOARD");

                for (int i = 0; i < total_scores; i++)
                {
                    al_draw_textf(font,
                                  al_map_rgb(255, 255, 255),
                                  220,
                                  120 + i * 40,
                                  0,
                                  "%d. %s - %d",
                                  i + 1,
                                  ranking[i].nome,
                                  ranking[i].pontuacao);
                }
            }

            al_flip_display();
        }

        // ================= TECLADO =================

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            // MENU
            if (estado == MENU)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    estado = JOGANDO;
                }

                if (ev.keyboard.keycode == ALLEGRO_KEY_L)
                {
                    total_scores = carregar_scores(ranking);

                    estado = LEADERBOARD;
                }
            }

            // JOGO
            if (estado == JOGANDO)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_A)
                    teclas[0] = 1;

                if (ev.keyboard.keycode == ALLEGRO_KEY_D)
                    teclas[1] = 1;

                if (ev.keyboard.keycode == ALLEGRO_KEY_W)
                    teclas[2] = 1;

                if (ev.keyboard.keycode == ALLEGRO_KEY_S)
                    teclas[3] = 1;

                // salva score e abre leaderboard
                if (ev.keyboard.keycode == ALLEGRO_KEY_P)
                {
                    salvar_score(jogador);

                    total_scores = carregar_scores(ranking);

                    estado = LEADERBOARD;
                }
            }

            // LEADERBOARD
            if (estado == LEADERBOARD)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    estado = MENU;
                }
            }

            // sair
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE &&
                estado == MENU)
            {
                rodando = 0;
            }
        }

        // ================= KEY UP =================

        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_A)
                teclas[0] = 0;

            if (ev.keyboard.keycode == ALLEGRO_KEY_D)
                teclas[1] = 0;

            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
                teclas[2] = 0;

            if (ev.keyboard.keycode == ALLEGRO_KEY_S)
                teclas[3] = 0;
        }

        // ================= FECHAR =================

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            rodando = 0;
        }
    }

    // ================= DESTROY =================

    al_destroy_bitmap(background);
    al_destroy_bitmap(player);
    al_destroy_bitmap(enemy);
    al_destroy_bitmap(coin);

    al_destroy_font(font);

    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
    al_destroy_display(display);

    return 0;
}