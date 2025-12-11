#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "visibilidade.h"
#include "anteparo.h"
#include "arvore.h" 
#include "poligono.h"
#include "lista.h" 

#define PI 3.14159265359
#define INFINITO 999999.0
#define EPSILON 1e-9

#define MIN_MUNDO -5000.0
#define MAX_MUNDO 5000.0

static double g_x_bomba;
static double g_y_bomba;
static double g_angulo_atual; 

typedef struct {
    double angulo;
    int tipo;
    Anteparo seg;   
} Evento;

double normaliza_rad(double a) {
    while (a < 0) a += 2 * PI;
    while (a >= 2 * PI) a -= 2 * PI;
    return a;
}

double get_distancia_raio(Anteparo ant, double angulo) {
    if (ant == NULL) return INFINITO;

    double x1 = get_ant_x1(ant); double y1 = get_ant_y1(ant);
    double x2 = get_ant_x2(ant); double y2 = get_ant_y2(ant);

    double dx_seg = x2 - x1;
    double dy_seg = y2 - y1;
    double dx_raio = cos(angulo);
    double dy_raio = sin(angulo);

    double det = dx_raio * dy_seg - dy_raio * dx_seg;

    if (fabs(det) < EPSILON) return INFINITO; 

    double t = ((x1 - g_x_bomba) * dy_seg - (y1 - g_y_bomba) * dx_seg) / det;
    double u = ((x1 - g_x_bomba) * dy_raio - (y1 - g_y_bomba) * dx_raio) / det;

    if (t > -EPSILON && u > -EPSILON && u < 1.0 + EPSILON) {
        return t; 
    }
    return INFINITO;
}

void adiciona_ponto_interseccao(Poligono pol, Anteparo ant, double angulo) {
    if (ant == NULL) return;
    
    double dist = get_distancia_raio(ant, angulo);
    if (dist < INFINITO - 1.0) {
        float rx = (float)(g_x_bomba + dist * cos(angulo));
        float ry = (float)(g_y_bomba + dist * sin(angulo));
        insere_vertice(pol, rx, ry);
    }
}

int cmp_eventos(const void* a, const void* b) {
    Evento* e1 = (Evento*)a;
    Evento* e2 = (Evento*)b;
    
    if (e1->angulo < e2->angulo - EPSILON) return -1;
    if (e1->angulo > e2->angulo + EPSILON) return 1;
    
    return (e1->tipo - e2->tipo);
}

int cmp_segmentos_ativos(void* a, void* b) {
    Anteparo s1 = (Anteparo)a;
    Anteparo s2 = (Anteparo)b;
    if (s1 == s2) return 0;

    double d1 = get_distancia_raio(s1, g_angulo_atual);
    double d2 = get_distancia_raio(s2, g_angulo_atual);

    if (fabs(d1 - d2) < EPSILON) {
        return (s1 < s2) ? -1 : 1;
    }
    return (d1 < d2) ? -1 : 1;
}

Poligono calcular_visibilidade(float x_bomba, float y_bomba, LISTA lista_anteparos) {
    g_x_bomba = (double)x_bomba; 
    g_y_bomba = (double)y_bomba;
    
    Poligono pol = cria_poligono();
    int n = tamanho_lista(lista_anteparos);
    
    int cap_max = (n + 4) * 4;
    Evento* eventos = malloc(sizeof(Evento) * cap_max);
    int qtd_ev = 0;

    Anteparo box[4];
    box[0] = cria_anteparo(-1, MIN_MUNDO, MIN_MUNDO, MAX_MUNDO, MIN_MUNDO);
    box[1] = cria_anteparo(-2, MAX_MUNDO, MIN_MUNDO, MAX_MUNDO, MAX_MUNDO);
    box[2] = cria_anteparo(-3, MAX_MUNDO, MAX_MUNDO, MIN_MUNDO, MAX_MUNDO);
    box[3] = cria_anteparo(-4, MIN_MUNDO, MAX_MUNDO, MIN_MUNDO, MIN_MUNDO);

    LISTA todos_anteparos = criar_lista(); 
    for(int i=0; i<4; i++) inserir_na_lista(todos_anteparos, box[i]);
    
    if (n > 0) {
        POSIC p = get_primeiro_no(lista_anteparos);
        while(p) {
            inserir_na_lista(todos_anteparos, get_info_do_no(lista_anteparos, p));
            p = get_proximo_no(lista_anteparos, p);
        }
    }

    POSIC no = get_primeiro_no(todos_anteparos);
    while (no != NULL) {
        Anteparo ant = get_info_do_no(todos_anteparos, no);
        double x1 = get_ant_x1(ant); double y1 = get_ant_y1(ant);
        double x2 = get_ant_x2(ant); double y2 = get_ant_y2(ant);

        double ang1 = normaliza_rad(atan2(y1 - g_y_bomba, x1 - g_x_bomba));
        double ang2 = normaliza_rad(atan2(y2 - g_y_bomba, x2 - g_x_bomba));

        if (fabs(ang1 - ang2) > PI) { 
            double menor = (ang1 < ang2) ? ang1 : ang2;
            double maior = (ang1 > ang2) ? ang1 : ang2;

            eventos[qtd_ev].angulo = maior; eventos[qtd_ev].tipo = 0; eventos[qtd_ev].seg = ant; qtd_ev++;
            eventos[qtd_ev].angulo = 2 * PI; eventos[qtd_ev].tipo = 1; eventos[qtd_ev].seg = ant; qtd_ev++;
            
            eventos[qtd_ev].angulo = 0; eventos[qtd_ev].tipo = 0; eventos[qtd_ev].seg = ant; qtd_ev++;
            eventos[qtd_ev].angulo = menor; eventos[qtd_ev].tipo = 1; eventos[qtd_ev].seg = ant; qtd_ev++;
        } 
        else {
            double menor = (ang1 < ang2) ? ang1 : ang2;
            double maior = (ang1 > ang2) ? ang1 : ang2;
            eventos[qtd_ev].angulo = menor; eventos[qtd_ev].tipo = 0; eventos[qtd_ev].seg = ant; qtd_ev++;
            eventos[qtd_ev].angulo = maior; eventos[qtd_ev].tipo = 1; eventos[qtd_ev].seg = ant; qtd_ev++;
        }
        no = get_proximo_no(todos_anteparos, no);
    }

    qsort(eventos, qtd_ev, sizeof(Evento), cmp_eventos);

    Arvore ativos = cria_arvore(cmp_segmentos_ativos);
    Anteparo ant_anterior = NULL;
    int primeira_passada = 1;

    int i = 0;
    while (i < qtd_ev) {
        g_angulo_atual = eventos[i].angulo; 

        int j = i;
        while (j < qtd_ev && fabs(eventos[j].angulo - g_angulo_atual) < EPSILON) {
            if (eventos[j].tipo == 0) {
                insere_arvore(ativos, eventos[j].seg);
            } else {
                remove_arvore(ativos, eventos[j].seg);
            }
            j++;
        }

        Anteparo ant_atual = (Anteparo)get_menor_dado(ativos);

        if (!primeira_passada) {
            if (ant_atual != ant_anterior) {
                if (ant_anterior != NULL) adiciona_ponto_interseccao(pol, ant_anterior, g_angulo_atual);
                if (ant_atual != NULL) adiciona_ponto_interseccao(pol, ant_atual, g_angulo_atual);
            } else {
                if (ant_atual != NULL) adiciona_ponto_interseccao(pol, ant_atual, g_angulo_atual);
            }
        } else {
            if (ant_atual != NULL) adiciona_ponto_interseccao(pol, ant_atual, g_angulo_atual);
            primeira_passada = 0;
        }

        ant_anterior = ant_atual;
        i = j;
    }

    free(eventos);
    kill_arvore(ativos);
    kill_lista(todos_anteparos, NULL); 
    for(int k=0; k<4; k++) free(box[k]);

    return pol;
}