#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define LARGURA 800
#define ALTURA 600

#define MAX_MOEDAS 5
#define MAX_INIMIGOS 3

#define TAM_JOGADOR 64
#define TAM_MOEDA 32
#define TAM_INIMIGO 64

// ================= STRUCTS =================

typedef enum
{
    PARADO,
    ANDANDO
} Estado;

typedef struct
{
    int x;
    int y;
} Posicao;

typedef struct
{
    char nome[50];
    int pontuacao;
    Estado estado;
    Posicao pos;
} Jogador;

typedef struct
{
    Posicao pos;
    int valor;
    int ativa;
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
    int score;
} Leaderboard;

// ================= FUNÇÕES =================

void mover_jogador(Jogador *j, int dx, int dy)
{
    j->pos.x += dx;
    j->pos.y += dy;

    if (dx != 0 || dy != 0)
        j->estado = ANDANDO;
    else
        j->estado = PARADO;

    // Limites da tela
    if (j->pos.x < 0)
        j->pos.x = 0;

    if (j->pos.x > LARGURA - TAM_JOGADOR)
        j->pos.x = LARGURA - TAM_JOGADOR;

    if (j->pos.y < 0)
        j->pos.y = 0;

    if (j->pos.y > ALTURA - TAM_JOGADOR)
        j->pos.y = ALTURA - TAM_JOGADOR;
}

int verificar_colisao(Jogador *j, Moeda *m)
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

void coletar_moeda(Jogador *j, Moeda *m)
{
    j->pontuacao += m->valor;
    m->ativa = 0;
}

void salvar_score(char nome[], int score)
{
    FILE *arquivo = fopen("Scores.txt", "a");

    if (arquivo != NULL)
    {
        fprintf(arquivo, "%s %d\n", nome, score);
        fclose(arquivo);
    }
}

void ordenar_scores(Leaderboard v[], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (v[j].score < v[j + 1].score)
            {
                Leaderboard temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int carregar_scores(Leaderboard v[])
{
    FILE *arquivo = fopen("Scores.txt", "r");

    if (arquivo == NULL)
        return 0;

    int i = 0;

    while (fscanf(arquivo, "%s %d",
                  v[i].nome,
                  &v[i].score) != EOF)
    {
        i++;
    }

    fclose(arquivo);

    ordenar_scores(v, i);

    return i;
}

// ================= MAIN =================

int main()
{
    srand(time(NULL));

    // ================= ALLEGRO =================

    al_init();
    al_install_keyboard();

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *display =
        al_create_display(LARGURA, ALTURA);

    ALLEGRO_EVENT_QUEUE *fila =
        al_create_event_queue();

    ALLEGRO_TIMER *timer =
        al_create_timer(1.0 / 60);

    // ================= FONT =================

    ALLEGRO_FONT *font =
        al_load_ttf_font("../assets/arial.ttf", 24, 0);

    // ================= IMAGENS =================

    ALLEGRO_BITMAP *background =
        al_load_bitmap("../BackGround/BackGround.png");

    // PLAYER

    ALLEGRO_BITMAP *player[4];

    player[0] = al_load_bitmap("../Hero/player_1.png");
    player[1] = al_load_bitmap("../Hero/player_2.png");
    player[2] = al_load_bitmap("../Hero/player_3.png");
    player[3] = al_load_bitmap("../Hero/player_4.png");

    // ENEMY

    ALLEGRO_BITMAP *enemy[4];

    enemy[0] = al_load_bitmap("../Enemy/Golem_01.png");
    enemy[1] = al_load_bitmap("../Enemy/Golem_02.png");
    enemy[2] = al_load_bitmap("../Enemy/Golem_03.png");
    enemy[3] = al_load_bitmap("../Enemy/Golem_04.png");

    // COIN

    ALLEGRO_BITMAP *coin[10];

    coin[0] = al_load_bitmap("../Coin/Gold_21.png");
    coin[1] = al_load_bitmap("../Coin/Gold_22.png");
    coin[2] = al_load_bitmap("../Coin/Gold_23.png");
    coin[3] = al_load_bitmap("../Coin/Gold_24.png");
    coin[4] = al_load_bitmap("../Coin/Gold_25.png");
    coin[5] = al_load_bitmap("../Coin/Gold_26.png");
    coin[6] = al_load_bitmap("../Coin/Gold_27.png");
    coin[7] = al_load_bitmap("../Coin/Gold_28.png");
    coin[8] = al_load_bitmap("../Coin/Gold_29.png");
    coin[9] = al_load_bitmap("../Coin/Gold_30.png");

    // ================= EVENTOS =================

    al_register_event_source(
        fila,
        al_get_keyboard_event_source());

    al_register_event_source(
        fila,
        al_get_timer_event_source(timer));

    al_register_event_source(
        fila,
        al_get_display_event_source(display));

    // ================= JOGADOR =================

    Jogador jogador;

    strcpy(jogador.nome, "Heroi");

    jogador.pontuacao = 0;
    jogador.pos.x = 100;
    jogador.pos.y = 100;
    jogador.estado = PARADO;

    // ================= MOEDAS =================

    Moeda moedas[MAX_MOEDAS];

    for (int i = 0; i < MAX_MOEDAS; i++)
    {
        moedas[i].pos.x = rand() % 700 + 50;
        moedas[i].pos.y = rand() % 500 + 50;

        moedas[i].valor = 10;
        moedas[i].ativa = 1;
    }

    // ================= INIMIGOS =================

    Inimigo inimigos[MAX_INIMIGOS];

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigos[i].x = rand() % 700;
        inimigos[i].y = rand() % 500;
        inimigos[i].velocidade = 2;
    }

    // ================= LEADERBOARD =================

    Leaderboard ranking[100];

    int total_scores = carregar_scores(ranking);

    // ================= CONTROLE =================

    int teclas[4] = {0};

    int rodando = 1;

    // ANIMAÇÃO

    int framePlayer = 0;
    int frameEnemy = 0;
    int frameCoin = 0;

    int contadorAnimacao = 0;

    // ================= LOOP =================

    al_start_timer(timer);

    while (rodando)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila, &ev);

        // ================= TIMER =================

        if (ev.type == ALLEGRO_EVENT_TIMER)
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
                if (verificar_colisao(
                        &jogador,
                        &moedas[i]))
                {
                    coletar_moeda(
                        &jogador,
                        &moedas[i]);
                }
            }

            // ================= ANIMAÇÃO =================

            contadorAnimacao++;

            if (contadorAnimacao >= 10)
            {
                contadorAnimacao = 0;

                framePlayer++;
                frameEnemy++;
                frameCoin++;

                if (framePlayer > 3)
                    framePlayer = 0;

                if (frameEnemy > 3)
                    frameEnemy = 0;

                if (frameCoin > 9)
                    frameCoin = 0;
            }

            // ================= DESENHO =================

            al_clear_to_color(
                al_map_rgb(0, 0, 0));

            // BACKGROUND

            al_draw_scaled_bitmap(
                background,
                0,
                0,
                al_get_bitmap_width(background),
                al_get_bitmap_height(background),
                0,
                0,
                LARGURA,
                ALTURA,
                0);

            // PLAYER

            al_draw_bitmap(
                player[framePlayer],
                jogador.pos.x,
                jogador.pos.y,
                0);

            // MOEDAS

            for (int i = 0; i < MAX_MOEDAS; i++)
            {
                if (moedas[i].ativa)
                {
                    al_draw_bitmap(
                        coin[frameCoin],
                        moedas[i].pos.x,
                        moedas[i].pos.y,
                        0);
                }
            }

            // INIMIGOS

            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                al_draw_bitmap(
                    enemy[frameEnemy],
                    inimigos[i].x,
                    inimigos[i].y,
                    0);
            }

            // SCORE

            char texto[100];

            sprintf(
                texto,
                "Score: %d",
                jogador.pontuacao);

            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                10,
                10,
                0,
                texto);

            // LEADERBOARD

            al_draw_text(
                font,
                al_map_rgb(255, 255, 0),
                600,
                20,
                0,
                "LEADERBOARD");

            for (int i = 0;
                 i < total_scores && i < 5;
                 i++)
            {
                char linha[100];

                sprintf(
                    linha,
                    "%d. %s - %d",
                    i + 1,
                    ranking[i].nome,
                    ranking[i].score);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    550,
                    60 + i * 30,
                    0,
                    linha);
            }

            al_flip_display();
        }

        // ================= TECLADO =================

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_ESCAPE)
            {
                rodando = 0;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_A)
            {
                teclas[0] = 1;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_D)
            {
                teclas[1] = 1;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_W)
            {
                teclas[2] = 1;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_S)
            {
                teclas[3] = 1;
            }
        }

        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_A)
            {
                teclas[0] = 0;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_D)
            {
                teclas[1] = 0;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_W)
            {
                teclas[2] = 0;
            }

            if (ev.keyboard.keycode ==
                ALLEGRO_KEY_S)
            {
                teclas[3] = 0;
            }
        }

        if (ev.type ==
            ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            rodando = 0;
        }
    }

    // ================= SALVAR SCORE =================

    salvar_score(
        jogador.nome,
        jogador.pontuacao);

    // ================= DESTROY =================

    al_destroy_bitmap(background);

    for (int i = 0; i < 4; i++)
    {
        al_destroy_bitmap(player[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        al_destroy_bitmap(enemy[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        al_destroy_bitmap(coin[i]);
    }

    al_destroy_font(font);

    al_destroy_display(display);
    al_destroy_event_queue(fila);
    al_destroy_timer(timer);

    return 0;
}
