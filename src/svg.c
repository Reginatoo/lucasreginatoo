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

void desenhar_svg(char* caminho_svg, LISTA chao) {
    FILE* arq_svg = fopen(caminho_svg, "w");
    if (arq_svg == NULL) {
        printf("Erro ao criar o arquivo SVG %s!\n", caminho_svg);
        exit(1);
    }
    fprintf(arq_svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(arq_svg, "<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 5000 5000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(arq_svg, "\n\t\n");
    POSIC no_atual = get_primeiro_no(chao);
    
    while (no_atual != NULL) {
        void* forma = get_info_do_no(chao, no_atual);
        desenhar_forma_generica(arq_svg, forma);
        no_atual = get_proximo_no(chao, no_atual);
    }

    fprintf(arq_svg, "</svg>\n");
    fclose(arq_svg);
}