#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define LARGURA 1280
#define ALTURA 720

#define MAX_MOEDAS 10
#define MAX_INIMIGOS 5

#define TOTAL_FRAMES_PLAYER 10
#define TOTAL_FRAMES_MOEDA 10

#define VELOCIDADE 5

// ========================= STRUCTS =========================

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
} Moeda;

typedef struct
{
    Posicao pos;
    int velocidade;
} Inimigo;

typedef struct
{
    char nome[50];
    int pontos;
} Score;

// ========================= FUNÇÃO SALVAR SCORE =========================

void salvar_score(char nome[], int pontos)
{
    FILE *arquivo = fopen("Scores.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir Scores.txt\n");
        return;
    }

    fprintf(arquivo, "%s %d\n", nome, pontos);

    fclose(arquivo);
}

// ========================= BUBBLE SORT =========================

void bubble_sort(Score v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (v[j].pontos < v[j + 1].pontos)
            {
                Score temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// ========================= CARREGAR SCORES =========================

int carregar_scores(Score scores[])
{
    FILE *arquivo = fopen("Scores.txt", "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    int i = 0;

    while (fscanf(arquivo, "%s %d",
                  scores[i].nome,
                  &scores[i].pontos) != EOF)
    {
        i++;
    }

    fclose(arquivo);

    bubble_sort(scores, i);

    return i;
}

// ========================= MOVER JOGADOR =========================

void mover_jogador(Jogador *j, int dx, int dy)
{
    j->pos.x += dx;
    j->pos.y += dy;

    // limites da tela

    if (j->pos.x < 0)
        j->pos.x = 0;

    if (j->pos.x > LARGURA - 64)
        j->pos.x = LARGURA - 64;

    if (j->pos.y < 0)
        j->pos.y = 0;

    if (j->pos.y > ALTURA - 64)
        j->pos.y = ALTURA - 64;
}

// ========================= COLISÃO =========================

int colisao(Jogador *j, Moeda *m)
{
    if (!m->ativa)
        return 0;

    int jogador_esquerda = j->pos.x;
    int jogador_direita = j->pos.x + 64;
    int jogador_cima = j->pos.y;
    int jogador_baixo = j->pos.y + 64;

    int moeda_esquerda = m->pos.x;
    int moeda_direita = m->pos.x + 32;
    int moeda_cima = m->pos.y;
    int moeda_baixo = m->pos.y + 32;

    if (jogador_direita > moeda_esquerda &&
        jogador_esquerda < moeda_direita &&
        jogador_baixo > moeda_cima &&
        jogador_cima < moeda_baixo)
    {
        return 1;
    }

    return 0;
}

// ========================= MAIN =========================

int main()
{
    srand(time(NULL));

    // ========================= INICIALIZA ALLEGRO =========================

    al_init();

    al_install_keyboard();

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // ========================= DISPLAY =========================

    ALLEGRO_DISPLAY *display =
        al_create_display(LARGURA, ALTURA);

    if (!display)
    {
        printf("Erro ao criar display\n");
        return 1;
    }

    // ========================= EVENTOS =========================

    ALLEGRO_EVENT_QUEUE *fila =
        al_create_event_queue();

    ALLEGRO_TIMER *timer =
        al_create_timer(1.0 / 60.0);

    al_register_event_source(
        fila,
        al_get_keyboard_event_source());

    al_register_event_source(
        fila,
        al_get_display_event_source(display));

    al_register_event_source(
        fila,
        al_get_timer_event_source(timer));

    // ========================= FONTE =========================

    ALLEGRO_FONT *fonte =
        al_load_ttf_font("arial.ttf", 24, 0);

    if (!fonte)
    {
        printf("Erro ao carregar arial.ttf\n");
        return 1;
    }

    // ========================= BACKGROUND =========================

    ALLEGRO_BITMAP *background =
        al_load_bitmap("background.png");

    if (!background)
    {
        printf("Erro background.png\n");
    }

    // ========================= PLAYER =========================

    ALLEGRO_BITMAP *player[TOTAL_FRAMES_PLAYER];

    char nome_arquivo[100];

    for (int i = 0; i < TOTAL_FRAMES_PLAYER; i++)
    {
        sprintf(nome_arquivo,
                "Knight_01_WALK_00%d.png",
                i);

        player[i] = al_load_bitmap(nome_arquivo);

        if (player[i] == NULL)
        {
            printf("Erro ao carregar %s\n",
                   nome_arquivo);
        }
    }

    // ========================= MOEDA =========================

    ALLEGRO_BITMAP *coin[TOTAL_FRAMES_MOEDA];

    for (int i = 21; i <= 30; i++)
    {
        sprintf(nome_arquivo,
                "Gold_%d.png",
                i);

        coin[i - 21] =
            al_load_bitmap(nome_arquivo);

        if (coin[i - 21] == NULL)
        {
            printf("Erro ao carregar %s\n",
                   nome_arquivo);
        }
    }

    // ========================= ENEMY =========================

    ALLEGRO_BITMAP *enemy =
        al_load_bitmap("enemy.png");

    if (!enemy)
    {
        printf("Erro enemy.png\n");
    }

    // ========================= JOGADOR =========================

    Jogador jogador;

    strcpy(jogador.nome, "Player");

    jogador.pontuacao = 0;

    jogador.pos.x = LARGURA / 2;
    jogador.pos.y = ALTURA - 120;

    // ========================= MOEDAS =========================

    Moeda moedas[MAX_MOEDAS];

    for (int i = 0; i < MAX_MOEDAS; i++)
    {
        moedas[i].pos.x =
            rand() % (LARGURA - 100);

        moedas[i].pos.y =
            rand() % (ALTURA - 100);

        moedas[i].ativa = 1;
    }

    // ========================= INIMIGOS =========================

    Inimigo inimigos[MAX_INIMIGOS];

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigos[i].pos.x =
            rand() % LARGURA;

        inimigos[i].pos.y =
            rand() % 200;

        inimigos[i].velocidade =
            2 + rand() % 3;
    }

    // ========================= SCORES =========================

    Score scores[100];

    int total_scores =
        carregar_scores(scores);

    // ========================= CONTROLES =========================

    int teclas[4] = {0};

    int rodando = 1;

    // animação

    int frame_player = 0;
    int frame_coin = 0;

    int contador_animacao = 0;

    // ========================= TIMER =========================

    al_start_timer(timer);

    // ========================= LOOP PRINCIPAL =========================

    while (rodando)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila, &ev);

        // ========================= TIMER =========================

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            int dx = 0;
            int dy = 0;

            // movimentação

            if (teclas[0])
                dx -= VELOCIDADE;

            if (teclas[1])
                dx += VELOCIDADE;

            if (teclas[2])
                dy -= VELOCIDADE;

            if (teclas[3])
                dy += VELOCIDADE;

            mover_jogador(&jogador, dx, dy);

            // ========================= COLISÃO COM MOEDAS =========================

            for (int i = 0; i < MAX_MOEDAS; i++)
            {
                if (colisao(&jogador, &moedas[i]))
                {
                    moedas[i].ativa = 0;

                    jogador.pontuacao += 10;
                }
            }

            // ========================= MOVIMENTO INIMIGOS =========================

            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                inimigos[i].pos.y +=
                    inimigos[i].velocidade;

                if (inimigos[i].pos.y > ALTURA)
                {
                    inimigos[i].pos.y = -50;

                    inimigos[i].pos.x =
                        rand() % LARGURA;
                }
            }

            // ========================= ANIMAÇÃO =========================

            contador_animacao++;

            if (contador_animacao >= 8)
            {
                contador_animacao = 0;

                frame_player++;
                frame_coin++;

                if (frame_player >= TOTAL_FRAMES_PLAYER)
                    frame_player = 0;

                if (frame_coin >= TOTAL_FRAMES_MOEDA)
                    frame_coin = 0;
            }

            // ========================= DESENHAR =========================

            al_clear_to_color(
                al_map_rgb(0, 0, 0));

            // background

            if (background)
            {
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
            }

            // moedas

            for (int i = 0; i < MAX_MOEDAS; i++)
            {
                if (moedas[i].ativa)
                {
                    al_draw_bitmap(
                        coin[frame_coin],
                        moedas[i].pos.x,
                        moedas[i].pos.y,
                        0);
                }
            }

            // inimigos

            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                if (enemy)
                {
                    al_draw_bitmap(
                        enemy,
                        inimigos[i].pos.x,
                        inimigos[i].pos.y,
                        0);
                }
            }

            // player

            if (player[frame_player])
            {
                al_draw_bitmap(
                    player[frame_player],
                    jogador.pos.x,
                    jogador.pos.y,
                    0);
            }

            // ========================= HUD =========================

            al_draw_textf(
                fonte,
                al_map_rgb(255, 255, 255),
                20,
                20,
                0,
                "Pontuacao: %d",
                jogador.pontuacao);

            al_draw_text(
                fonte,
                al_map_rgb(255, 255, 0),
                20,
                60,
                0,
                "WASD para mover");

            al_draw_text(
                fonte,
                al_map_rgb(255, 0, 0),
                20,
                100,
                0,
                "ESC para sair");

            // ========================= LEADERBOARD =========================

            al_draw_filled_rectangle(
                LARGURA - 320,
                20,
                LARGURA - 20,
                320,
                al_map_rgba(0, 0, 0, 180));

            al_draw_text(
                fonte,
                al_map_rgb(255, 215, 0),
                LARGURA - 250,
                30,
                0,
                "LEADERBOARD");

            // score atual

            al_draw_textf(
                fonte,
                al_map_rgb(255, 255, 255),
                LARGURA - 280,
                80,
                0,
                "Atual: %d",
                jogador.pontuacao);

            // top scores

            for (int i = 0; i < total_scores && i < 5; i++)
            {
                al_draw_textf(
                    fonte,
                    al_map_rgb(255, 255, 255),
                    LARGURA - 280,
                    130 + (i * 30),
                    0,
                    "%d. %s - %d",
                    i + 1,
                    scores[i].nome,
                    scores[i].pontos);
            }

            // atualiza tela

            al_flip_display();
        }

        // ========================= TECLA APERTADA =========================

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                rodando = 0;
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_A)
                teclas[0] = 1;

            if (ev.keyboard.keycode == ALLEGRO_KEY_D)
                teclas[1] = 1;

            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
                teclas[2] = 1;

            if (ev.keyboard.keycode == ALLEGRO_KEY_S)
                teclas[3] = 1;
        }

        // ========================= TECLA SOLTA =========================

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

        // ========================= FECHAR JANELA =========================

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            rodando = 0;
        }
    }

    // ========================= SALVAR SCORE =========================

    salvar_score(
        jogador.nome,
        jogador.pontuacao);

    // ========================= LIBERAR MEMÓRIA =========================

    for (int i = 0; i < TOTAL_FRAMES_PLAYER; i++)
    {
        if (player[i])
            al_destroy_bitmap(player[i]);
    }

    for (int i = 0; i < TOTAL_FRAMES_MOEDA; i++)
    {
        if (coin[i])
            al_destroy_bitmap(coin[i]);
    }

    if (enemy)
        al_destroy_bitmap(enemy);

    if (background)
        al_destroy_bitmap(background);

    al_destroy_font(fonte);

    al_destroy_timer(timer);

    al_destroy_event_queue(fila);

    al_destroy_display(display);

    return 0;
}