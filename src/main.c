#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "geo.h"
#include "qry.h"
#include "svg.h" 
#include "forma.h"
#include <locale.h>

void extrair_nome_base(const char* path, char* nome_base) {
    const char* barra = strrchr(path, '/');
    if (barra) path = barra + 1;

    strcpy(nome_base, path);
    
    char* ponto = strrchr(nome_base, '.');
    if (ponto) *ponto = '\0';
}

int main(int argc, char* argv[]) {
    setlocale(LC_NUMERIC, "C");
    char* dir_entrada = NULL;
    char* arq_geo = NULL;
    char* dir_saida = NULL;
    char* arq_qry = NULL; 
    char tipo_sort = 'q';

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            i++;
            if (i < argc) dir_entrada = argv[i];
        } else if (strcmp(argv[i], "-f") == 0) {
            i++;
            if (i < argc) arq_geo = argv[i];
        } else if (strcmp(argv[i], "-o") == 0) {
            i++;
            if (i < argc) dir_saida = argv[i];
        } 
         else if (strcmp(argv[i], "-q") == 0) {
            i++;
            if (i < argc) arq_qry = argv[i];
        } 
        else if (strcmp(argv[i], "-to") == 0) {
            i++;
            if (i < argc) tipo_sort = argv[i][0]; 
        }
    }

    if (arq_geo == NULL || dir_saida == NULL) {
        printf("Erro: Parametros obrigatorios faltando!\n");
        printf("Uso correto: ./ted -f <arquivo.geo> -o <diretorio_saida> [-e <dir_entrada>]\n");
        return 1;
    }
    LISTA lista_formas = criar_lista();

    char caminho_geo[512];
    if (dir_entrada != NULL) {
        sprintf(caminho_geo, "%s/%s", dir_entrada, arq_geo);
    } else {
        strcpy(caminho_geo, arq_geo);
    }
ler_geo(caminho_geo, lista_formas);
    printf(" Lendo arquivo GEO: %s\n", caminho_geo);
    if (lista_esta_vazia(lista_formas)) {
        printf(" A lista de formas esta vazia.\n");
    } else {
        printf(" %d formas carregadas.\n", tamanho_lista(lista_formas));
    }

    char nome_base_geo[100];
    extrair_nome_base(arq_geo, nome_base_geo);

    char caminho_svg_base[512];
    if (dir_saida[strlen(dir_saida)-1] == '/') 
        sprintf(caminho_svg_base, "%s%s.svg", dir_saida, nome_base_geo);
    else 
        sprintf(caminho_svg_base, "%s/%s.svg", dir_saida, nome_base_geo);

    printf(" Gerando SVG Base (Geo): %s\n", caminho_svg_base);
    
    FILE* svg = iniciar_svg(caminho_svg_base, lista_formas);
    if (svg) {
        desenhar_lista_formas(svg, lista_formas);
        finalizar_svg(svg);
    }

    if (arq_qry != NULL) {
        char caminho_qry[512];
        if (dir_entrada != NULL) sprintf(caminho_qry, "%s/%s", dir_entrada, arq_qry);
        else strcpy(caminho_qry, arq_qry);
        
        char nome_base_qry[100];
        extrair_nome_base(arq_qry, nome_base_qry);
        
        char nome_txt[256];
        sprintf(nome_txt, "%s-%s.txt", nome_base_geo, nome_base_qry);
        
        char caminho_txt[512];
        if (dir_saida[strlen(dir_saida)-1] == '/') sprintf(caminho_txt, "%s%s", dir_saida, nome_txt);
        else sprintf(caminho_txt, "%s/%s", dir_saida, nome_txt);
        char nome_svg_qry[256];
        sprintf(nome_svg_qry, "%s-%s.svg", nome_base_geo, nome_base_qry);
        
        char caminho_svg_qry[512];
        if (dir_saida[strlen(dir_saida)-1] == '/') sprintf(caminho_svg_qry, "%s%s", dir_saida, nome_svg_qry);
        else sprintf(caminho_svg_qry, "%s/%s", dir_saida, nome_svg_qry);

        LISTA lista_segmentos = criar_lista();
        
        printf(" Processando QRY: %s\n", caminho_qry);
        printf(" Saida QRY SVG:   %s\n", caminho_svg_qry);
        ler_qry(caminho_qry, lista_formas, lista_segmentos, caminho_txt, caminho_svg_qry, tipo_sort);
    } 

    printf(" Limpando memoria...\n");

    printf(" Concluido com sucesso.\n");
    return 0;
}