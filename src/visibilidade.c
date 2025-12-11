#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "visibilidade.h"
#include "anteparo.h"
#include "arvore.h"
#include "poligono.h"
#include "lista.h" 

#define MUNDO_MIN -1000.0
#define MUNDO_MAX 15000.0

#define PI 3.1415926
#define infinito 999999.0

typedef struct {
    float angulo;
    int tipo; 
    Anteparo seg;
} Evento;

static float g_x_bomba;
static float g_y_bomba;
static float g_angulo_atual; 

float normaliza_angulo(float ang) {
    while (ang < 0) ang += 2 * PI;
    while (ang >= 2 * PI) ang -= 2 * PI;
    return ang;
}

float dist_intersecao_raio(Anteparo ant, float angulo_raio) {
    float x1 = get_ant_x1(ant);
    float y1 = get_ant_y1(ant);
    float x2 = get_ant_x2(ant);
    float y2 = get_ant_y2(ant);
    float dx_seg = x2 - x1;
    float dy_seg = y2 - y1;
    
    float dx_raio = cos(angulo_raio);
    float dy_raio = sin(angulo_raio);
    
    float denom = dx_raio * dy_seg - dy_raio * dx_seg;
    if (fabs(denom) < 1e-9) return infinito; 
    float s = ((g_x_bomba - x1) * dy_seg - (g_y_bomba - y1) * dx_seg) / denom;
    if (s < -1e-4) return infinito; 
    
    return s; 
}

int cmp_eventos(const void* a, const void* b) {
    Evento* ea = (Evento*) a;
    Evento* eb = (Evento*) b;

    if (ea->angulo < eb->angulo - 1e-5) return -1;
    if (ea->angulo > eb->angulo + 1e-5) return 1;
    if (ea->tipo < eb->tipo) return -1;
    if (ea->tipo > eb->tipo) return 1;
    
    return 0; 
}

int cmp_segmentos_ativos(void* a, void* b) {
    Anteparo antA = (Anteparo) a;
    Anteparo antB = (Anteparo) b;
    if (antA == antB) return 0;
    
    float distA = dist_intersecao_raio(antA, g_angulo_atual);
    float distB = dist_intersecao_raio(antB, g_angulo_atual);

    if (fabs(distA - distB) < 1e-5) {
        if (get_ant_id(antA) < get_ant_id(antB)) return -1;
        else return 1;
    }
    return (distA < distB) ? -1 : 1;
}

Poligono calcular_visibilidade(float x_bomba, float y_bomba, LISTA lista_anteparos) {
    g_x_bomba = x_bomba;
    g_y_bomba = y_bomba;
    Poligono pol_vis = cria_poligono();
    LISTA lista_com_bordas = criar_lista();

    POSIC p = get_primeiro_no(lista_anteparos);
    while(p) {
        inserir_na_lista(lista_com_bordas, get_info_do_no(lista_anteparos, p));
        p = get_proximo_no(lista_anteparos, p);
    }

    Anteparo b1 = cria_anteparo(-1, MUNDO_MIN, MUNDO_MIN, MUNDO_MAX, MUNDO_MIN);
    Anteparo b2 = cria_anteparo(-2, MUNDO_MAX, MUNDO_MIN, MUNDO_MAX, MUNDO_MAX);
    Anteparo b3 = cria_anteparo(-3, MUNDO_MAX, MUNDO_MAX, MUNDO_MIN, MUNDO_MAX);
    Anteparo b4 = cria_anteparo(-4, MUNDO_MIN, MUNDO_MAX, MUNDO_MIN, MUNDO_MIN);
    
    inserir_na_lista(lista_com_bordas, b1);
    inserir_na_lista(lista_com_bordas, b2);
    inserir_na_lista(lista_com_bordas, b3);
    inserir_na_lista(lista_com_bordas, b4);
    
    int tam_lista = tamanho_lista(lista_com_bordas); 
    int cap_eventos = 100;
    if (tam_lista > 0) {
        cap_eventos = tam_lista * 2 + 10;
    }

    Evento* eventos = (Evento*) malloc(cap_eventos * sizeof(Evento));
    int qtd_eventos = 0;
    POSIC no = get_primeiro_no(lista_com_bordas); 
    
    while (no != NULL) {
        Anteparo ant = (Anteparo) get_info_do_no(lista_com_bordas, no);
        
        if (ant != NULL) {
            float x1 = get_ant_x1(ant);
            float y1 = get_ant_y1(ant);
            float x2 = get_ant_x2(ant);
            float y2 = get_ant_y2(ant);
            
            float ang1 = normaliza_angulo(atan2(y1 - y_bomba, x1 - x_bomba));
            float ang2 = normaliza_angulo(atan2(y2 - y_bomba, x2 - x_bomba));
            
            float ang_ini = ang1;
            float ang_fim = ang2;
            float diff = ang_fim - ang_ini;
            if (diff > PI) ang_ini += 2*PI; 
            else if (diff < -PI) ang_fim += 2*PI;
            
            if (ang_ini > ang_fim) {
                float temp = ang_ini; ang_ini = ang_fim; ang_fim = temp;
            }

            if (qtd_eventos + 2 >= cap_eventos) {
                cap_eventos *= 2;
                eventos = (Evento*) realloc(eventos, cap_eventos * sizeof(Evento));
            }
            
            eventos[qtd_eventos].angulo = normaliza_angulo(ang_ini);
            eventos[qtd_eventos].tipo = 0;
            eventos[qtd_eventos].seg = ant;
            qtd_eventos++;
            
            eventos[qtd_eventos].angulo = normaliza_angulo(ang_fim);
            eventos[qtd_eventos].tipo = 1; 
            eventos[qtd_eventos].seg = ant;
            qtd_eventos++;
        }
        no = get_proximo_no(lista_com_bordas, no); 
    }
    qsort(eventos, qtd_eventos, sizeof(Evento), cmp_eventos);
    
    Arvore segmentos_ativos = cria_arvore(cmp_segmentos_ativos);

    int i;
    for (i = 0; i < qtd_eventos; i++) {
        g_angulo_atual = eventos[i].angulo;
        Anteparo seg_evento = eventos[i].seg;

        if (eventos[i].tipo == 0) { 
            insere_arvore(segmentos_ativos, seg_evento);
        } else { 
            remove_arvore(segmentos_ativos, seg_evento);
        }
        
        Anteparo mais_proximo = (Anteparo) get_menor_dado(segmentos_ativos);

        if (mais_proximo != NULL) {
            float dist = dist_intersecao_raio(mais_proximo, g_angulo_atual);
            
            if (dist >= infinito - 1.0) dist = MUNDO_MAX;

            float px = g_x_bomba + dist * cos(g_angulo_atual);
            float py = g_y_bomba + dist * sin(g_angulo_atual);

            insere_vertice(pol_vis, px, py);
        }
    }
    kill_arvore(segmentos_ativos);
    free(eventos);
    free(b1); free(b2); free(b3); free(b4); 
    kill_lista(lista_com_bordas, NULL); 

    return pol_vis;
}