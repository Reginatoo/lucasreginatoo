#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "forma.h"
#include "lista.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "poligono.h"

void calcular_dimensoes_mundo(LISTA lista, float* max_x, float* max_y) {
    *max_x = 500.0; 
    *max_y = 500.0; 

    if (lista == NULL) return;

    POSIC no = get_primeiro_no(lista);
    while (no != NULL) {
        void* forma = get_info_do_no(lista, no);
        char tipo = get_tipo_da_forma(forma);
        
        float x_atual = 0, y_atual = 0;

        if (tipo == 'c') {
            CIRCULO c = (CIRCULO)forma;
            x_atual = get_XC(c) + get_RC(c);
            y_atual = get_YC(c) + get_RC(c);
        } else if (tipo == 'r') {
            RETANGULO r = (RETANGULO)forma;
            x_atual = get_XR(r) + get_WR(r);
            y_atual = get_YR(r) + get_HR(r);
        } else if (tipo == 'l') {
            LINHA l = (LINHA)forma;
            x_atual = (get_X1L(l) > get_X2L(l)) ? get_X1L(l) : get_X2L(l);
            y_atual = (get_Y1L(l) > get_Y2L(l)) ? get_Y1L(l) : get_Y2L(l);
        } else if (tipo == 't') {
            TEXTO t = (TEXTO)forma;
            x_atual = get_xT(t) + 100; 
            y_atual = get_yT(t) + 20;
        }

        if (x_atual > *max_x) *max_x = x_atual;
        if (y_atual > *max_y) *max_y = y_atual;

        no = get_proximo_no(lista, no);
    }
    *max_x += 50.0;
    *max_y += 50.0;
}

FILE* iniciar_svg(char* caminho_svg, LISTA lista_para_zoom) {
    FILE* svg = fopen(caminho_svg, "w");
    if (svg == NULL) {
        printf("Erro ao criar o arquivo SVG %s!\n", caminho_svg);
        return NULL;
    }

    float largura, altura;
    calcular_dimensoes_mundo(lista_para_zoom, &largura, &altura);

    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg, "<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 %.2f %.2f\" xmlns=\"http://www.w3.org/2000/svg\">\n", largura, altura);
    return svg;
}

void finalizar_svg(FILE* svg) {
    if (svg == NULL) return;
    fprintf(svg, "</svg>\n");
    fclose(svg);
}

void desenhar_circulo(FILE* svg, void* forma) {
    fprintf(svg, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1\" opacity=\"0.6\" />\n",
            get_XC(forma), get_YC(forma), get_RC(forma), 
            get_cbC(forma), get_cpC(forma));
}

void desenhar_retangulo(FILE* svg, void* forma) {
    fprintf(svg, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"1\" opacity=\"0.6\" />\n",
            get_XR(forma), get_YR(forma), get_WR(forma), get_HR(forma),
            get_cbR(forma), get_cpR(forma));
}

void desenhar_linha(FILE* svg, void* forma) {
    fprintf(svg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"1\" />\n", 
            get_X1L(forma), get_Y1L(forma), get_X2L(forma), get_Y2L(forma),
            get_CorL(forma));
}

void desenhar_texto(FILE* svg, void* forma) {
    char a = get_aT(forma);
    char anchor[20] = "start"; 

    if (a == 'm') {
        strcpy(anchor, "middle");
    } else if (a == 'f') {
        strcpy(anchor, "end");
    }
    
    char* cor_preenchimento = get_cpT(forma);
    char* cor_borda = get_cbT(forma);
    char* cor_stroke = cor_borda;

    if (strcmp(cor_borda, "none") == 0) {
        cor_stroke = cor_preenchimento; 
    }
    
    fprintf(svg, "\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"0.5\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" text-anchor=\"%s\">%s</text>\n",
            get_xT(forma), get_yT(forma), 
            cor_preenchimento, cor_stroke,
            get_familiaT(forma), get_pesoT(forma), get_tamT(forma),
            anchor,
            get_txtT(forma));
}

void desenhar_forma_generica(FILE* svg, void* forma) {
    if (forma == NULL) return;
    
    char tipo = get_tipo_da_forma(forma); 

    switch (tipo) {
        case 'c': desenhar_circulo(svg, forma); break;
        case 'r': desenhar_retangulo(svg, forma); break;
        case 'l': desenhar_linha(svg, forma); break;
        case 't': desenhar_texto(svg, forma); break;
        default:
            break;
    }
}


void desenhar_lista_formas(FILE* svg, LISTA chao) {
    if (svg == NULL || chao == NULL) return;

    POSIC no_atual = get_primeiro_no(chao);
    while (no_atual != NULL) {
        void* forma = get_info_do_no(chao, no_atual);
        desenhar_forma_generica(svg, forma); // Essa você já tem, mantém ela!
        no_atual = get_proximo_no(chao, no_atual);
    }
}
void svg_desenha_poligono(FILE* svg, Poligono p, char* cor, float opacidade) {
    if (svg == NULL || p == NULL) return;

    fprintf(svg, "\t<polygon points=\"");

    int qtd = get_qtd_vertices(p);
    float x, y;
    for (int i = 0; i < qtd; i++) {
        if (get_vertice(p, i, &x, &y)) {
            fprintf(svg, "%.2f,%.2f ", x, y);
        }
    }

    fprintf(svg, "\" fill=\"%s\" stroke=\"none\" opacity=\"%.2f\" />\n", cor, opacidade);
}
