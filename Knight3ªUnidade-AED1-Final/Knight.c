#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "Fila.h"

#define LARGURA 1280
#define ALTURA 720

#define MAX_MOEDAS 10
#define MAX_INIMIGOS 5

#define TOTAL_FRAMES_PLAYER 10
#define TOTAL_FRAMES_MOEDA 10
#define TOTAL_FRAMES_INIMIGO 8

#define VELOCIDADE 5
#define TAM_JOGADOR 128
#define TAM_INIMIGO 64
#define TAM_MOEDA 32

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

// ========================= FUNÇÕES DE SCORE =========================

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

// ========================= MOVIMENTAÇÃO E COLISÃO =========================

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

int colisao_moeda(Jogador *j, Moeda *m)
{
    if (!m->ativa)
        return 0;

    int je = j->pos.x, jd = j->pos.x + TAM_JOGADOR;
    int jc = j->pos.y, jb = j->pos.y + TAM_JOGADOR;
    int me = m->pos.x, md = m->pos.x + TAM_MOEDA;
    int mc = m->pos.y, mb = m->pos.y + TAM_MOEDA;

    return (jd > me && je < md && jb > mc && jc < mb);
}

int colisao_inimigo(Jogador *j, Inimigo *inim)
{
    int je = j->pos.x, jd = j->pos.x + TAM_JOGADOR;
    int jc = j->pos.y, jb = j->pos.y + TAM_JOGADOR;
    int ie = inim->pos.x, id = inim->pos.x + TAM_INIMIGO;
    int ic = inim->pos.y, ib = inim->pos.y + TAM_INIMIGO;

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

    // Fonte (com fallback para evitar erro)
    ALLEGRO_FONT *fonte = al_load_ttf_font("arial.ttf", 24, 0);
    if (!fonte)
        fonte = al_create_builtin_font();

    // ======================== CARREGAR IMAGENS ========================
    ALLEGRO_BITMAP *background = al_load_bitmap("Imagens/background.png");
    if (!background)
        printf("Aviso: Imagens/background.png não encontrado. Usando fundo preto.\n");
    else
    {
        int larg_original = al_get_bitmap_width(background);
        int alt_original = al_get_bitmap_height(background);
        int larg_corte = larg_original - 80;
        int alt_corte = alt_original - 50;

        if (larg_corte > 0 && alt_corte > 0)
        {
            ALLEGRO_BITMAP *background_cortado = al_create_bitmap(larg_corte, alt_corte);
            al_set_target_bitmap(background_cortado);
            al_draw_bitmap_region(background, 0, 0, larg_corte, alt_corte, 0, 0, 0);
            al_set_target_backbuffer(display);
            al_destroy_bitmap(background);
            background = background_cortado;
        }
        else
            printf("Aviso: Dimensões da imagem muito pequenas para cortar.\n");
    }

    // Player (frames com dois underscores, i começando em 0)
    ALLEGRO_BITMAP *player[TOTAL_FRAMES_PLAYER];
    char nome_arquivo[100];
    for (int i = 0; i < TOTAL_FRAMES_PLAYER; i++)
    {
        sprintf(nome_arquivo, "Imagens/Knight_01__WALK_%03d.png", i);
        ALLEGRO_BITMAP *orig = al_load_bitmap(nome_arquivo);
        if (!orig)
        {
            printf("Erro ao carregar %s\n", nome_arquivo);
            player[i] = NULL;
            continue;
        }
        player[i] = al_create_bitmap(TAM_JOGADOR, TAM_JOGADOR);
        al_set_target_bitmap(player[i]);
        al_draw_scaled_bitmap(orig, 0, 0, al_get_bitmap_width(orig), al_get_bitmap_height(orig),
                              0, 0, TAM_JOGADOR, TAM_JOGADOR, 0);
        al_set_target_backbuffer(display);
        al_destroy_bitmap(orig);
    }

    // Moeda
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
        coin[i] = al_create_bitmap(TAM_MOEDA, TAM_MOEDA);
        al_set_target_bitmap(coin[i]);
        al_draw_scaled_bitmap(orig, 0, 0, al_get_bitmap_width(orig), al_get_bitmap_height(orig),
                              0, 0, TAM_MOEDA, TAM_MOEDA, 0);
        al_set_target_backbuffer(display);
        al_destroy_bitmap(orig);
    }

    // Inimigo
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
        inimigo_frames[i] = al_create_bitmap(TAM_INIMIGO, TAM_INIMIGO);
        al_set_target_bitmap(inimigo_frames[i]);
        al_draw_scaled_bitmap(orig, 0, 0, al_get_bitmap_width(orig), al_get_bitmap_height(orig),
                              0, 0, TAM_INIMIGO, TAM_INIMIGO, 0);
        al_set_target_backbuffer(display);
        al_destroy_bitmap(orig);
    }

    // Power-up (imagem) - se não existir, usa um retângulo magenta
    ALLEGRO_BITMAP *powerup_img = al_load_bitmap("Imagens/powerup.png");
    if (!powerup_img)
    {
        powerup_img = al_create_bitmap(32, 32);
        al_set_target_bitmap(powerup_img);
        al_clear_to_color(al_map_rgb(255, 0, 255)); // magenta
        al_set_target_backbuffer(display);
        printf("Aviso: Imagens/powerup.png não encontrada. Usando retângulo magenta.\n");
    }

    // ======================== INICIALIZA ENTIDADES ========================
    Jogador jogador;
    strcpy(jogador.nome, "Player");
    jogador.pontuacao = 0;
    jogador.pos.x = LARGURA / 2 - TAM_JOGADOR / 2;
    jogador.pos.y = ALTURA - 120;

    Moeda moedas[MAX_MOEDAS];
    for (int i = 0; i < MAX_MOEDAS; i++)
    {
        moedas[i].pos.x = rand() % (LARGURA - TAM_MOEDA);
        moedas[i].pos.y = rand() % (ALTURA - TAM_MOEDA);
        moedas[i].ativa = 1;
    }

    Inimigo inimigos[MAX_INIMIGOS];
    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigos[i].pos.x = rand() % (LARGURA - TAM_INIMIGO);
        inimigos[i].pos.y = rand() % (ALTURA - TAM_INIMIGO);
        inimigos[i].velocidade = 1 + rand() % 2;
        inimigos[i].frame_atual = 0;
        inimigos[i].contador_anim = 0;
    }

    Score scores[100];
    int total_scores = carregar_scores(scores);

    // ======================== FILA DE POWER-UPS ========================
    Fila fila_powerups;
    inicializarFila(&fila_powerups);
    carregarFila(&fila_powerups, "powerups.bin");

    // Power-up flutuante na tela
    Posicao pos_powerup;
    pos_powerup.x = rand() % (LARGURA - 64);
    pos_powerup.y = rand() % (ALTURA - 64);
    int powerup_ativo = 1;
    int contador_coletas = 0; // para gerar power-up a cada 3 moedas

    // Controles
    int teclas[4] = {0};
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
            int dx = 0, dy = 0;
            if (teclas[0])
                dx -= VELOCIDADE;
            if (teclas[1])
                dx += VELOCIDADE;
            if (teclas[2])
                dy -= VELOCIDADE;
            if (teclas[3])
                dy += VELOCIDADE;
            mover_jogador(&jogador, dx, dy);

            // Colisão com moedas + geração de power-up na fila
            for (int i = 0; i < MAX_MOEDAS; i++)
            {
                if (colisao_moeda(&jogador, &moedas[i]))
                {
                    moedas[i].ativa = 0;
                    jogador.pontuacao += 10;
                    contador_coletas++;

                    if (contador_coletas >= 3)
                    {
                        contador_coletas = 0;
                        PowerUp novo;
                        novo.id = 1;
                        strcpy(novo.nome, "Moeda Extra");
                        novo.valor = 50;
                        inserirPowerUp(&fila_powerups, novo);
                        printf("Power-up adicionado à fila!\n");
                    }

                    moedas[i].pos.x = rand() % (LARGURA - TAM_MOEDA);
                    moedas[i].pos.y = rand() % (ALTURA - TAM_MOEDA);
                    moedas[i].ativa = 1;
                }
            }

            // Colisão com power-up flutuante na tela
            if (powerup_ativo)
            {
                int je = jogador.pos.x, jd = jogador.pos.x + TAM_JOGADOR;
                int jc = jogador.pos.y, jb = jogador.pos.y + TAM_JOGADOR;
                int pe = pos_powerup.x, pd = pos_powerup.x + 32;
                int pc = pos_powerup.y, pb = pos_powerup.y + 32;

                if (jd > pe && je < pd && jb > pc && jc < pb)
                {
                    powerup_ativo = 0;
                    PowerUp novo;
                    novo.id = 2;
                    strcpy(novo.nome, "Power-Up Coletado");
                    novo.valor = 20;
                    inserirPowerUp(&fila_powerups, novo);
                    printf("Power-up coletado! +1 item na fila\n");
                }
            }

            // Movimento dos inimigos (perseguição)
            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                int dx_inim = 0, dy_inim = 0;
                if (inimigos[i].pos.x < jogador.pos.x)
                    dx_inim = 1;
                else if (inimigos[i].pos.x > jogador.pos.x)
                    dx_inim = -1;

                if (inimigos[i].pos.y < jogador.pos.y)
                    dy_inim = 1;
                else if (inimigos[i].pos.y > jogador.pos.y)
                    dy_inim = -1;

                if (rand() % 5 == 0)
                {
                    dx_inim += (rand() % 3) - 1;
                    dy_inim += (rand() % 3) - 1;
                }

                inimigos[i].pos.x += dx_inim * inimigos[i].velocidade;
                inimigos[i].pos.y += dy_inim * inimigos[i].velocidade;

                if (inimigos[i].pos.x < 0)
                    inimigos[i].pos.x = 0;
                if (inimigos[i].pos.x > LARGURA - TAM_INIMIGO)
                    inimigos[i].pos.x = LARGURA - TAM_INIMIGO;
                if (inimigos[i].pos.y < 0)
                    inimigos[i].pos.y = 0;
                if (inimigos[i].pos.y > ALTURA - TAM_INIMIGO)
                    inimigos[i].pos.y = ALTURA - TAM_INIMIGO;

                inimigos[i].contador_anim++;
                if (inimigos[i].contador_anim >= 10)
                {
                    inimigos[i].contador_anim = 0;
                    inimigos[i].frame_atual = (inimigos[i].frame_atual + 1) % TOTAL_FRAMES_INIMIGO;
                }

                if (colisao_inimigo(&jogador, &inimigos[i]))
                {
                    jogador.pontuacao -= 5;
                    if (jogador.pontuacao < 0)
                        jogador.pontuacao = 0;
                    inimigos[i].pos.x = rand() % (LARGURA - TAM_INIMIGO);
                    inimigos[i].pos.y = rand() % (ALTURA - TAM_INIMIGO);
                }
            }

            // Animação geral
            contador_animacao++;
            if (contador_animacao >= 8)
            {
                contador_animacao = 0;
                frame_player = (frame_player + 1) % TOTAL_FRAMES_PLAYER;
                frame_coin = (frame_coin + 1) % TOTAL_FRAMES_MOEDA;
            }

            // ======================== DESENHO ========================
            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (background)
                al_draw_scaled_bitmap(background, 0, 0,
                                      al_get_bitmap_width(background),
                                      al_get_bitmap_height(background),
                                      0, 0, LARGURA, ALTURA, 0);

            // Moedas
            for (int i = 0; i < MAX_MOEDAS; i++)
                if (moedas[i].ativa && coin[frame_coin])
                    al_draw_bitmap(coin[frame_coin], moedas[i].pos.x, moedas[i].pos.y, 0);

            // Power-up flutuante
            if (powerup_ativo && powerup_img)
                al_draw_bitmap(powerup_img, pos_powerup.x, pos_powerup.y, 0);

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
            al_draw_textf(fonte, al_map_rgb(0, 255, 0), 20, 60, 0, "Power-ups na fila: %d", tamanhoFila(&fila_powerups));
            al_draw_text(fonte, al_map_rgb(255, 255, 0), 20, 100, 0, "WASD mover | E usar power-up");
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 20, 140, 0, "ESC sair");

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
            if (ev.keyboard.keycode == ALLEGRO_KEY_E && !estaVazia(&fila_powerups))
            {
                PowerUp p = removerPowerUp(&fila_powerups);
                jogador.pontuacao += p.valor;
                printf("Power-up usado: %s! +%d pontos!\n", p.nome, p.valor);
            }
        }
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
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            rodando = 0;
    }

    // Salvar pontuação e fila
    salvar_score(jogador.nome, jogador.pontuacao);
    salvarFila(&fila_powerups, "powerups.bin");

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
    if (powerup_img)
        al_destroy_bitmap(powerup_img);
    if (fonte && fonte != al_create_builtin_font())
        al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
    al_destroy_display(display);

    liberarFila(&fila_powerups);
    return 0;
}