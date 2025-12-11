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

typedef struct { Poligono pol; char cor[20]; float opacidade; } DesenhoBomba;
static int g_id_anteparo = 0;

   
void transformar_forma_em_anteparos(void* forma, LISTA lista_ant, char parametro_extra, FILE* f_txt) {
    char tipo = get_tipo_da_forma(forma);
    if (tipo == 'l') {
        LINHA l = (LINHA) forma;
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, get_X1L(l), get_Y1L(l), get_X2L(l), get_Y2L(l)));
    }
    else if (tipo == 'r') {
        RETANGULO r = (RETANGULO) forma;
        float x = get_XR(r), y = get_YR(r), w = get_WR(r), h = get_HR(r);
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x, y, x+w, y));
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x, y+h, x+w, y+h));
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x, y, x, y+h));
        inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, x+w, y, x+w, y+h));
    }
    else if (tipo == 'c') {
        CIRCULO c = (CIRCULO) forma;
        float cx = get_XC(c), cy = get_YC(c), r = get_RC(c);
        if (parametro_extra == 'h') inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, cx-r, cy, cx+r, cy));
        else inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, cx, cy-r, cx, cy+r));
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO) forma;
        float xt = get_xT(t), yt = get_yT(t);
        char* conteudo = get_txtT(t);
        float len = strlen(conteudo) * 10.0; 
        if (get_aT(t) == 'i') inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, xt, yt, xt+len, yt));
        else if (get_aT(t) == 'f') inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, xt-len, yt, xt, yt));
        else inserir_na_lista(lista_ant, cria_anteparo(g_id_anteparo++, xt-len/2, yt, xt+len/2, yt));
    }
}

void processar_svg_sufixo(char* base_path, char* sufixo, LISTA lista_formas, Poligono pol, char* cor) {
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
        svg_desenha_poligono(extra, pol, cor, 0.7);
        finalizar_svg(extra);
    }
}

void ler_qry(char* caminho_qry, LISTA lista_formas, LISTA lista_segmentos, char* caminho_saida_txt, char* caminho_saida_svg, char tipo_sort) {
    FILE* f_qry = fopen(caminho_qry, "r");
    if (!f_qry) return;

    FILE* f_txt = fopen(caminho_saida_txt, "w");
    if (f_txt) fprintf(f_txt, "Parametro de Ordenacao: %s\n", (tipo_sort == 'm') ? "MergeSort" : "QSort");

    LISTA desenhos_bombas = criar_lista();
    char comando[100];
    while (fscanf(f_qry, "%s", comando) != EOF) {
        if (strcmp(comando, "a") == 0) {
            int id_ini, id_fim; char param_extra[10] = "v"; 
            if(fscanf(f_qry, "%d", &id_ini)){}; if (fscanf(f_qry, "%d", &id_fim) != 1) id_fim = id_ini;
            char c; if(fscanf(f_qry, " %c", &c)){}; if (c == 'v' || c == 'h') param_extra[0] = c; else ungetc(c, f_qry);
            POSIC no = get_primeiro_no(lista_formas);
            while(no != NULL) {
                void* f = get_info_do_no(lista_formas, no);
                int id = get_id_da_forma(f);
                if (id >= id_ini && id <= id_fim) transformar_forma_em_anteparos(f, lista_segmentos, param_extra[0], f_txt);
                no = get_proximo_no(lista_formas, no);
            }
        }
        else if (strcmp(comando, "d") == 0) {
            float x, y; char sufixo[100];
            if(fscanf(f_qry, "%f %f %s", &x, &y, sufixo)){};
            Poligono pol = calcular_visibilidade(x, y, lista_segmentos);
            
            POSIC no = get_primeiro_no(lista_formas);
            while (no != NULL) {
                POSIC atual = no; no = get_proximo_no(lista_formas, no);
                void* f = get_info_do_no(lista_formas, atual);
                if (ponto_dentro_poligono(pol, get_x_da_forma(f), get_y_da_forma(f))) {
                    if (f_txt) fprintf(f_txt, "ID %d destruido\n", get_id_da_forma(f));
                    remover_da_lista(lista_formas, atual);
                }
            }
            if (strcmp(sufixo, "-") == 0) {
                DesenhoBomba* db = malloc(sizeof(DesenhoBomba));
                db->pol = pol; strcpy(db->cor, "yellow"); db->opacidade = 0.7;
                inserir_na_lista(desenhos_bombas, db);
            } else if (caminho_saida_svg) {
                processar_svg_sufixo(caminho_saida_svg, sufixo, lista_formas, pol, "yellow");
                kill_poligono(pol);
            } else kill_poligono(pol);
        }
        else if (strcmp(comando, "P") == 0) {
            float x, y; char cb[50], cp[50], sufixo[100];
            if(fscanf(f_qry, "%f %f %s %s %s", &x, &y, cb, cp, sufixo)){};
            Poligono pol = calcular_visibilidade(x, y, lista_segmentos);
            POSIC no = get_primeiro_no(lista_formas);
            while (no != NULL) {
                void* f = get_info_do_no(lista_formas, no);
                if (ponto_dentro_poligono(pol, get_x_da_forma(f), get_y_da_forma(f))) {
                    set_corb_da_forma(f, cb); set_cp_da_forma(f, cp);
                }
                no = get_proximo_no(lista_formas, no);
            }
            if (strcmp(sufixo, "-") == 0) {
                DesenhoBomba* db = malloc(sizeof(DesenhoBomba));
                db->pol = pol; strcpy(db->cor, "green"); db->opacidade = 0.7;
                inserir_na_lista(desenhos_bombas, db);
            } else if (caminho_saida_svg) {
                processar_svg_sufixo(caminho_saida_svg, sufixo, lista_formas, pol, "green");
                kill_poligono(pol);
            } else kill_poligono(pol);
        }
        else if (strcmp(comando, "cln") == 0) {
            float x, y, dx, dy; char sufixo[100];
            if(fscanf(f_qry, "%f %f %f %f %s", &x, &y, &dx, &dy, sufixo)){};
            Poligono pol = calcular_visibilidade(x, y, lista_segmentos);
            LISTA clones = criar_lista();
            POSIC no = get_primeiro_no(lista_formas);
            while (no != NULL) {
                void* f = get_info_do_no(lista_formas, no);
                if (ponto_dentro_poligono(pol, get_x_da_forma(f), get_y_da_forma(f))) {
                    void* c = clone_forma(f);
                    set_posicao_da_forma(c, get_x_da_forma(c)+dx, get_y_da_forma(c)+dy);
                    inserir_na_lista(clones, c);
                }
                no = get_proximo_no(lista_formas, no);
            }
            while(!lista_esta_vazia(clones)) inserir_na_lista(lista_formas, remover_da_lista(clones, get_primeiro_no(clones)));
            kill_lista(clones, NULL);
            if (strcmp(sufixo, "-") == 0) {
                DesenhoBomba* db = malloc(sizeof(DesenhoBomba));
                db->pol = pol; strcpy(db->cor, "blue"); db->opacidade = 0.7;
                inserir_na_lista(desenhos_bombas, db);
            } else if (caminho_saida_svg) {
                processar_svg_sufixo(caminho_saida_svg, sufixo, lista_formas, pol, "blue");
                kill_poligono(pol);
            } else kill_poligono(pol);
        }
        else if (comando[0] == '#') { char buffer[1024]; fgets(buffer, 1024, f_qry); }
    }
    
    // DESENHA TUDO NO FINAL
    if (caminho_saida_svg) {
        FILE* f_svg = iniciar_svg(caminho_saida_svg, lista_formas);
        if (f_svg) {
            desenhar_lista_formas(f_svg, lista_formas); 
            while (!lista_esta_vazia(desenhos_bombas)) {
                POSIC p = get_primeiro_no(desenhos_bombas);
                DesenhoBomba* db = (DesenhoBomba*) remover_da_lista(desenhos_bombas, p);
                svg_desenha_poligono(f_svg, db->pol, db->cor, db->opacidade);
                kill_poligono(db->pol);
                free(db);
            }
            finalizar_svg(f_svg);
        }
    }
    kill_lista(desenhos_bombas, NULL);
    fclose(f_qry);
    if (f_txt) fclose(f_txt);
}