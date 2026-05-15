#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FPS 60

// ================= STRUCT =================
typedef struct
{
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// ================= FUNÇÕES =================

// Salvar em arquivo
void salvar(Jogador *v, int n)
{
    FILE *f = fopen("leaderboard.txt", "w");

    if (f == NULL)
    {
        printf("Erro ao salvar arquivo\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d %s %d\n", v[i].id, v[i].nome, v[i].pontuacao);
    }

    fclose(f);
}

// Busca linear
int buscaLinear(Jogador *v, int n, int id)
{
    for (int i = 0; i < n; i++)
    {
        if (v[i].id == id)
            return i;
    }
    return -1;
}

// Bubble Sort (decrescente)
void ordenar(Jogador *v, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j].pontuacao < v[j + 1].pontuacao)
            {
                Jogador temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// ================= MAIN =================
int main()
{

    // ================= DADOS =================
    int n;
    printf("Quantidade de jogadores: ");
    scanf("%d", &n);

    Jogador *jogadores = malloc(n * sizeof(Jogador));

    if (jogadores == NULL)
    {
        printf("Erro de memoria!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nJogador %d\n", i + 1);

        printf("ID: ");
        scanf("%d", &jogadores[i].id);

        printf("Nome: ");
        scanf("%49s", jogadores[i].nome); // seguro

        printf("Pontuacao: ");
        scanf("%d", &jogadores[i].pontuacao);
    }

    // Ordenar
    ordenar(jogadores, n);

    // Mostrar ranking
    printf("\n=== LEADERBOARD ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d - %s (%d)\n",
               jogadores[i].id,
               jogadores[i].nome,
               jogadores[i].pontuacao);
    }

    // Salvar
    salvar(jogadores, n);

    // Busca
    int id_busca;
    printf("\nDigite ID para buscar: ");
    scanf("%d", &id_busca);

    int pos = buscaLinear(jogadores, n, id_busca);

    if (pos != -1)
    {
        printf("Encontrado: %s - %d pontos\n",
               jogadores[pos].nome,
               jogadores[pos].pontuacao);
    }
    else
    {
        printf("Nao encontrado!\n");
    }

    // ================= ALLEGRO =================

    if (!al_init())
    {
        printf("Erro ao iniciar Allegro!\n");
        return 1;
    }

    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    if (!display)
    {
        printf("Erro ao criar display!\n");
        return 1;
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();

    ALLEGRO_FONT *fonte = al_load_ttf_font("arial.ttf", 20, 0);
    if (!fonte)
    {
        printf("Erro ao carregar fonte!\n");
        return 1;
    }

    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));

    al_start_timer(timer);

    int rodando = 1;
    int redraw = 0;

    while (rodando)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            rodando = 0;
        }

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = 1;
        }

        if (redraw && al_is_event_queue_empty(fila))
        {
            redraw = 0;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_text(fonte, al_map_rgb(255, 255, 255),
                         400, 50, ALLEGRO_ALIGN_CENTER,
                         "Leaderboard do Jogo");

            for (int i = 0; i < n && i < 5; i++)
            {
                char texto[100];
                sprintf(texto, "%s - %d",
                        jogadores[i].nome,
                        jogadores[i].pontuacao);

                al_draw_text(fonte, al_map_rgb(255, 255, 255),
                             400, 150 + i * 40,
                             ALLEGRO_ALIGN_CENTER, texto);
            }

            al_flip_display();
        }
    }

    // ================= FINAL =================
    free(jogadores);

    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
    al_destroy_display(display);

    return 0;
}