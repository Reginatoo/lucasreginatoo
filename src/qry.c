#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "lista.h"
#include "anteparo.h"
#include "visibilidade.h"
#include "poligono.h"
#include "forma.h"
#include "svg.h" 
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

static int g_id_anteparo = 0;

void desenhar_bomba(FILE* svg, float x, float y) {
    if (!svg) return;
    fprintf(svg, "\t<circle cx=\"%.2f\" cy=\"%.2f\" r=\"5\" fill=\"#d35fbc\" stroke=\"#501644\" stroke-width=\"2\" />\n", x, y);
    
    fprintf(svg, "\t<circle cx=\"%.2f\" cy=\"%.2f\" r=\"1\" fill=\"black\" />\n", x, y);
}

void transformar_forma_em_anteparos(void* forma, LISTA lista_ant, char parametro_extra, FILE* f_txt) {
    char tipo = get_tipo_da_forma(forma);
    int id_orig = get_id_da_forma(forma);

    if (f_txt) fprintf(f_txt, "Transformando Forma ID: %d Tipo: %c\n", id_orig, tipo);

    if (tipo == 'l') {
        LINHA l = (LINHA) forma;
        Anteparo a = cria_anteparo(g_id_anteparo++, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l));
        inserir_na_lista(lista_ant, a);
        if (f_txt) fprintf(f_txt, " -> Segmento ID %d\n", get_ant_id(a));
    }
    else if (tipo == 'r') {
        RETANGULO r = (RETANGULO) forma;
        float x = get_XR(r), y = get_YR(r), w = get_WR(r), h = get_HR(r);
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x, y, x + w, y));
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x, y + h, x + w, y + h));
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x, y, x, y + h));
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x + w, y, x + w, y + h));
    }
    else if (tipo == 'c') {
        CIRCULO c = (CIRCULO) forma;
        float x1, y1, x2, y2, cx = get_XC(c), cy = get_YC(c), r = get_RC(c);
        if (parametro_extra == 'h') { x1 = cx - r; y1 = cy; x2 = cx + r; y2 = cy; } 
        else { x1 = cx; y1 = cy - r; x2 = cx; y2 = cy + r; }
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x1, y1, x2, y2));
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO) forma;
        float xt = get_xT(t), yt = get_yT(t);
        char ancora = get_aT(t);
        float len = strlen(get_txtT(t)) * 10.0;
        float x1, x2;
        if (ancora == 'i') { x1 = xt; x2 = xt + len; }
        else if (ancora == 'f') { x1 = xt - len; x2 = xt; }
        else { x1 = xt - len/2.0; x2 = xt + len/2.0; }
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x1, yt, x2, yt));
    }
}

void processar_svg_sufixo(char* base_path, char* sufixo, LISTA lista_formas, Poligono pol, float bx, float by) {
    if (strcmp(sufixo, "-") == 0) return;
    
    char nome_arq[200];
    char base_sem_ext[200];
    strcpy(base_sem_ext, base_path);
    char* ponto = strrchr(base_sem_ext, '.');
    if (ponto) *ponto = '\0';
    
    sprintf(nome_arq, "%s-%s.svg", base_sem_ext, sufixo);
    
    FILE* extra = iniciar_svg(nome_arq, lista_formas);
    if (extra) {
        desenhar_lista_formas(extra, lista_formas);
        
        desenhar_bomba(extra, bx, by);
        
        finalizar_svg(extra);
    }
}

void ler_qry(char* caminho_qry, LISTA lista_formas, LISTA lista_segmentos, char* caminho_saida_txt, char* caminho_saida_svg, char tipo_sort) {
    FILE* f_qry = fopen(caminho_qry, "r");
    if (!f_qry) return;

    FILE* f_txt = fopen(caminho_saida_txt, "w");
    if (f_txt) fprintf(f_txt, "Parametro de Ordenacao: %s\n", (tipo_sort == 'm') ? "MergeSort" : "QSort");

    FILE* f_svg = NULL;
    if (caminho_saida_svg != NULL) {
        f_svg = iniciar_svg(caminho_saida_svg, lista_formas);
        if (f_svg) desenhar_lista_formas(f_svg, lista_formas);
    }

    char comando[100];
    while (fscanf(f_qry, "%s", comando) != EOF) {
        
        if (strcmp(comando, "a") == 0) {
            int id_ini, id_fim;
            char param_extra[10] = "v"; 
            fscanf(f_qry, "%d", &id_ini);
            if (fscanf(f_qry, "%d", &id_fim) != 1) id_fim = id_ini;

            char c;
            fscanf(f_qry, " %c", &c);
            if (c == 'v' || c == 'h') param_extra[0] = c;
            else ungetc(c, f_qry);

            if (f_txt) fprintf(f_txt, "\n[*] Comando 'a': Intervalo [%d, %d] Param: %c\n", id_ini, id_fim, param_extra[0]);

            POSIC no = get_primeiro_no(lista_formas);
            while(no != NULL) {
                void* forma = get_info_do_no(lista_formas, no);
                int id_atual = get_id_da_forma(forma);
                if (id_atual >= id_ini && id_atual <= id_fim) {
                      transformar_forma_em_anteparos(forma, lista_segmentos, param_extra[0], f_txt);
                }
                no = get_proximo_no(lista_formas, no);
            }
        }
        else if (strcmp(comando, "d") == 0) {
            float x, y;
            char sufixo[100];
            fscanf(f_qry, "%f %f %s", &x, &y, sufixo);
            
            if (f_txt) fprintf(f_txt, "\n[*] Comando 'd': Destruicao em (%.2f, %.2f)\n", x, y);
            
            Poligono pol_luz = calcular_visibilidade(x, y, lista_segmentos);
            
            if (f_svg && strcmp(sufixo, "-") == 0) {
                desenhar_bomba(f_svg, x, y);
            } else if (caminho_saida_svg) {
                processar_svg_sufixo(caminho_saida_svg, sufixo, lista_formas, pol_luz, x, y);
            }

            POSIC no = get_primeiro_no(lista_formas);
            while (no != NULL) {
                POSIC aux = no;
                no = get_proximo_no(lista_formas, no); 
                
                void* forma = get_info_do_no(lista_formas, aux);
                float fx = get_x_da_forma(forma);
                float fy = get_y_da_forma(forma);
                
                if (ponto_dentro_poligono(pol_luz, fx, fy)) {
                    if (f_txt) fprintf(f_txt, "Forma Destruida - ID: %d\n", get_id_da_forma(forma));
                }
            }
            kill_poligono(pol_luz);
        }
        else if (strcmp(comando, "P") == 0) {
            float x, y;
            char corb[50], corp[50], sufixo[100];
            fscanf(f_qry, "%f %f %s %s %s", &x, &y, corb, corp, sufixo);
            
            Poligono pol_luz = calcular_visibilidade(x, y, lista_segmentos);
            
            if (f_svg && strcmp(sufixo, "-") == 0) {
                desenhar_bomba(f_svg, x, y);
            } else if (caminho_saida_svg) {
                processar_svg_sufixo(caminho_saida_svg, sufixo, lista_formas, pol_luz, x, y);
            }
            kill_poligono(pol_luz);
        }
        else if (strcmp(comando, "cln") == 0) {
             float x, y, dx, dy;
             char sufixo[100];
             fscanf(f_qry, "%f %f %f %f %s", &x, &y, &dx, &dy, sufixo);
             Poligono pol_luz = calcular_visibilidade(x, y, lista_segmentos);
             
             if (f_svg && strcmp(sufixo, "-") == 0) {
                desenhar_bomba(f_svg, x, y);
             } else if (caminho_saida_svg) {
                processar_svg_sufixo(caminho_saida_svg, sufixo, lista_formas, pol_luz, x, y);
             }
             kill_poligono(pol_luz);
        }
    }
    fclose(f_qry);
    if (f_txt) fclose(f_txt);
    if (f_svg) finalizar_svg(f_svg);
}