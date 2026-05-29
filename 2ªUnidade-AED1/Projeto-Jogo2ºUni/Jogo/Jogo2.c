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
#define TOTAL_FRAMES_INIMIGO 8 // <-- ajustar o frames do golem

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
    int frame_atual;
    int contador_anim;
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
        for (int j = 0; j < n - 1 - i; j++)
            if (v[j].pontos < v[j + 1].pontos)
            {
                Score temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
}

// ========================= CARREGAR SCORES =========================

int carregar_scores(Score scores[])
{
    FILE *arquivo = fopen("Scores.txt", "r");
    if (arquivo == NULL)
        return 0;

    int i = 0;
    while (fscanf(arquivo, "%s %d", scores[i].nome, &scores[i].pontos) != EOF)
        i++;
    fclose(arquivo);

    bubble_sort(scores, i);
    return i;
}

// ========================= MOVER JOGADOR =========================

void mover_jogador(Jogador *j, int dx, int dy)
{
    j->pos.x += dx;
    j->pos.y += dy;

    if (j->pos.x < 0)
        j->pos.x = 0;
    if (j->pos.x > LARGURA - 64)
        j->pos.x = LARGURA - 64;
    if (j->pos.y < 0)
        j->pos.y = 0;
    if (j->pos.y > ALTURA - 64)
        j->pos.y = ALTURA - 64;
}

// ========================= COLISÃO COM MOEDA =========================

int colisao_moeda(Jogador *j, Moeda *m)
{
    if (!m->ativa)
        return 0;

    int je = j->pos.x, jd = j->pos.x + 64;
    int jc = j->pos.y, jb = j->pos.y + 64;
    int me = m->pos.x, md = m->pos.x + 32;
    int mc = m->pos.y, mb = m->pos.y + 32;

    return (jd > me && je < md && jb > mc && jc < mb);
}

// ========================= COLISÃO COM INIMIGO =========================

int colisao_inimigo(Jogador *j, Inimigo *inim)
{
    int je = j->pos.x, jd = j->pos.x + 64;
    int jc = j->pos.y, jb = j->pos.y + 64;
    int ie = inim->pos.x, id = inim->pos.x + 64;
    int ic = inim->pos.y, ib = inim->pos.y + 64;

    return (jd > ie && je < id && jb > ic && jc < ib);
}

// ========================= MAIN =========================

int main()
{
    srand(time(NULL));

    // Inicializa Allegro
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // Display
    ALLEGRO_DISPLAY *display = al_create_display(LARGURA, ALTURA);
    if (!display)
    {
        printf("Erro ao criar display\n");
        return 1;
    }

    // Eventos e timer
    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));

    // Fonte
    ALLEGRO_FONT *fonte = al_load_ttf_font("arial.ttf", 24, 0);
    if (!fonte)
    {
        printf("Erro ao carregar arial.ttf\n");
        return 1;
    }

    // ======================== CARREGAR IMAGENS ========================
    // Background (certifique-se de que a imagem está em Imagens/background.png)
    ALLEGRO_BITMAP *background = al_load_bitmap("Imagens/background.png");
    if (!background)
    {
        printf("Aviso: Imagens/background.png não encontrado. Usando fundo preto.\n");
    }
    else
    {
        int larg_original = al_get_bitmap_width(background);
        int alt_original = al_get_bitmap_height(background);
        int larg_corte = larg_original - 80;
        int alt_corte = alt_original - 50;

        if (larg_corte > 0 && alt_corte > 0)
        {
            // Cria um bitmap novo com o tamanho cortado
            ALLEGRO_BITMAP *background_cortado = al_create_bitmap(larg_corte, alt_corte);
            al_set_target_bitmap(background_cortado);
            // Copia a região do original para o novo bitmap
            al_draw_bitmap_region(background, 0, 0, larg_corte, alt_corte, 0, 0, 0);
            al_set_target_backbuffer(display);
            al_destroy_bitmap(background);
            background = background_cortado;
        }
        else
        {
            printf("Aviso: Dimensões da imagem muito pequenas para cortar.\n");
        }
    }

    // Player (10 frames: Knight_01_WALK_001.png a 010.png)
    ALLEGRO_BITMAP *player[TOTAL_FRAMES_PLAYER];
    char nome_arquivo[100];

    for (int i = 0; i < TOTAL_FRAMES_PLAYER; i++)
    {
        sprintf(nome_arquivo, "Imagens/Knight__01_WALK_%03d.png", i + 1);
        ALLEGRO_BITMAP *orig = al_load_bitmap(nome_arquivo);

        if (!orig)
        {
            printf("Erro ao carregar %s\n", nome_arquivo);
            player[i] = NULL;
            continue;
        }

        // Cria um bitmap redimensionado para 64x64
        player[i] = al_create_bitmap(64, 64);
        al_set_target_bitmap(player[i]);
        al_draw_scaled_bitmap(orig, 0, 0,
                              al_get_bitmap_width(orig), al_get_bitmap_height(orig),
                              0, 0, 64, 64, 0);
        al_set_target_backbuffer(display); // volta a desenhar na tela
        al_destroy_bitmap(orig);           // libera o original
    }

    // Moeda (10 frames: Gold_21.png a 30.png)
    ALLEGRO_BITMAP *coin[TOTAL_FRAMES_MOEDA];
    for (int i = 0; i < TOTAL_FRAMES_MOEDA; i++)
    {
        sprintf(nome_arquivo, "Imagens/Gold_%d.png", 21 + i);
        ALLEGRO_BITMAP *orig = al_load_bitmap(nome_arquivo);
        if (!orig)
        {
            printf("Erro ao carregar %s\n", nome_arquivo);
            coin[i] = NULL;
            continue;
        }
        // Redimensiona para 32x32
        coin[i] = al_create_bitmap(32, 32);
        al_set_target_bitmap(coin[i]);
        al_draw_scaled_bitmap(orig, 0, 0, al_get_bitmap_width(orig), al_get_bitmap_height(orig),
                              0, 0, 32, 32, 0);
        al_set_target_backbuffer(display);
        al_destroy_bitmap(orig);
    }

    // Inimigo (8 frames: Golem_01_Walking_001.png a 008.png)
    ALLEGRO_BITMAP *inimigo_frames[TOTAL_FRAMES_INIMIGO];
    for (int i = 0; i < TOTAL_FRAMES_INIMIGO; i++)
    {
        sprintf(nome_arquivo, "Imagens/Golem_01_Walking_%03d.png", i + 1);
        ALLEGRO_BITMAP *orig = al_load_bitmap(nome_arquivo);
        if (!orig)
        {
            printf("Erro ao carregar %s\n", nome_arquivo);
            inimigo_frames[i] = NULL;
            continue;
        }
        // Redimensiona para 64x64
        inimigo_frames[i] = al_create_bitmap(64, 64);
        al_set_target_bitmap(inimigo_frames[i]);
        al_draw_scaled_bitmap(orig, 0, 0, al_get_bitmap_width(orig), al_get_bitmap_height(orig),
                              0, 0, 64, 64, 0);
        al_set_target_backbuffer(display);
        al_destroy_bitmap(orig);
    }

    // ======================== INICIALIZA ENTIDADES ========================
    Jogador jogador;
    strcpy(jogador.nome, "Player");
    jogador.pontuacao = 0;
    jogador.pos.x = LARGURA / 2;
    jogador.pos.y = ALTURA - 120;

    Moeda moedas[MAX_MOEDAS];
    for (int i = 0; i < MAX_MOEDAS; i++)
    {
        moedas[i].pos.x = rand() % (LARGURA - 100);
        moedas[i].pos.y = rand() % (ALTURA - 100);
        moedas[i].ativa = 1;
    }

    Inimigo inimigos[MAX_INIMIGOS];
    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigos[i].pos.x = rand() % LARGURA;
        inimigos[i].pos.y = rand() % 200;
        inimigos[i].velocidade = 2 + rand() % 3;
        inimigos[i].frame_atual = 0;
        inimigos[i].contador_anim = 0;
    }

    Score scores[100];
    int total_scores = carregar_scores(scores);

    // Controles
    int teclas[4] = {0}; // A, D, W, S
    int rodando = 1;
    int frame_player = 0, frame_coin = 0, contador_animacao = 0;

    al_start_timer(timer);

    // ======================== LOOP PRINCIPAL ========================
    while (rodando)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            // Movimento do jogador
            int dx = 0, dy = 0;
            if (teclas[0])
                dx -= VELOCIDADE; // A
            if (teclas[1])
                dx += VELOCIDADE; // D
            if (teclas[2])
                dy -= VELOCIDADE; // W
            if (teclas[3])
                dy += VELOCIDADE; // S
            mover_jogador(&jogador, dx, dy);

            // Colisão com moedas
            for (int i = 0; i < MAX_MOEDAS; i++)
            {
                if (colisao_moeda(&jogador, &moedas[i]))
                {
                    moedas[i].ativa = 0;
                    jogador.pontuacao += 10;
                    // Reposiciona a moeda em outro lugar
                    moedas[i].pos.x = rand() % (LARGURA - 100);
                    moedas[i].pos.y = rand() % (ALTURA - 100);
                    moedas[i].ativa = 1;
                }
            }

            // Movimento e colisão dos inimigos
            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                inimigos[i].pos.y += inimigos[i].velocidade;
                if (inimigos[i].pos.y > ALTURA)
                {
                    inimigos[i].pos.y = -50;
                    inimigos[i].pos.x = rand() % LARGURA;
                }

                // Animação do inimigo (troca de frame a cada 10 ticks)
                inimigos[i].contador_anim++;
                if (inimigos[i].contador_anim >= 10)
                {
                    inimigos[i].contador_anim = 0;
                    inimigos[i].frame_atual = (inimigos[i].frame_atual + 1) % TOTAL_FRAMES_INIMIGO;
                }

                // Colisão com jogador
                if (colisao_inimigo(&jogador, &inimigos[i]))
                {
                    jogador.pontuacao -= 5;
                    if (jogador.pontuacao < 0)
                        jogador.pontuacao = 0;
                    // Respawn do inimigo
                    inimigos[i].pos.y = -50;
                    inimigos[i].pos.x = rand() % LARGURA;
                }
            }

            // Animação geral (player e moeda)
            contador_animacao++;
            if (contador_animacao >= 8)
            {
                contador_animacao = 0;
                frame_player = (frame_player + 1) % TOTAL_FRAMES_PLAYER;
                frame_coin = (frame_coin + 1) % TOTAL_FRAMES_MOEDA;
            }

            // ======================== DESENHO ========================
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Background
            if (background)
                al_draw_scaled_bitmap(background, 0, 0,
                                      al_get_bitmap_width(background),
                                      al_get_bitmap_height(background),
                                      0, 0, LARGURA, ALTURA, 0);

            // Moedas
            for (int i = 0; i < MAX_MOEDAS; i++)
                if (moedas[i].ativa && coin[frame_coin])
                    al_draw_bitmap(coin[frame_coin], moedas[i].pos.x, moedas[i].pos.y, 0);

            // Inimigos
            for (int i = 0; i < MAX_INIMIGOS; i++)
                if (inimigo_frames[inimigos[i].frame_atual])
                    al_draw_bitmap(inimigo_frames[inimigos[i].frame_atual],
                                   inimigos[i].pos.x, inimigos[i].pos.y, 0);

            // Jogador
            if (player[frame_player])
                al_draw_bitmap(player[frame_player], jogador.pos.x, jogador.pos.y, 0);

            // HUD
            al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20, 20, 0, "Pontuacao: %d", jogador.pontuacao);
            al_draw_text(fonte, al_map_rgb(255, 255, 0), 20, 60, 0, "WASD para mover");
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 20, 100, 0, "ESC para sair");

            // Leaderboard
            al_draw_filled_rectangle(LARGURA - 320, 20, LARGURA - 20, 320, al_map_rgba(0, 0, 0, 180));
            al_draw_text(fonte, al_map_rgb(255, 215, 0), LARGURA - 250, 30, 0, "LEADERBOARD");
            al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA - 280, 80, 0, "Atual: %d", jogador.pontuacao);
            for (int i = 0; i < total_scores && i < 5; i++)
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA - 280, 130 + i * 30, 0,
                              "%d. %s - %d", i + 1, scores[i].nome, scores[i].pontos);

            al_flip_display();
        }

        // Teclas pressionadas
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                rodando = 0;
            if (ev.keyboard.keycode == ALLEGRO_KEY_A)
                teclas[0] = 1;
            if (ev.keyboard.keycode == ALLEGRO_KEY_D)
                teclas[1] = 1;
            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
                teclas[2] = 1;
            if (ev.keyboard.keycode == ALLEGRO_KEY_S)
                teclas[3] = 1;
        }
        // Teclas soltas
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
        // Fechar janela
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            rodando = 0;
    }

    // Salvar pontuação
    salvar_score(jogador.nome, jogador.pontuacao);

    // Liberar memória
    for (int i = 0; i < TOTAL_FRAMES_PLAYER; i++)
        if (player[i])
            al_destroy_bitmap(player[i]);
    for (int i = 0; i < TOTAL_FRAMES_MOEDA; i++)
        if (coin[i])
            al_destroy_bitmap(coin[i]);
    for (int i = 0; i < TOTAL_FRAMES_INIMIGO; i++)
        if (inimigo_frames[i])
            al_destroy_bitmap(inimigo_frames[i]);
    if (background)
        al_destroy_bitmap(background);
    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
    al_destroy_display(display);

    return 0;
}