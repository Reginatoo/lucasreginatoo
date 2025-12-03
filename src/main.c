#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "geo.h"
#include "svg.h"
#include "forma.h"

void extrair_nome_base(const char* path, char* nome_base) {
    const char* barra = strrchr(path, '/');
    if (barra) path = barra + 1;

    strcpy(nome_base, path);
    
    char* ponto = strrchr(nome_base, '.');
    if (ponto) *ponto = '\0';
}

int main(int argc, char* argv[]) {
    char* dir_entrada = NULL;
    char* arq_geo = NULL;
    char* dir_saida = NULL;
    char* arq_qry = NULL; 

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

    printf(" Lendo arquivo GEO: %s\n", caminho_geo);
    ler_geo(caminho_geo, lista_formas);

    if (lista_esta_vazia(lista_formas)) {
        printf(" A lista de formas esta vazia. Verifique se o arquivo .geo tem conteudo.\n");
    } else {
        printf(" %d formas carregadas com sucesso.\n", tamanho_lista(lista_formas));
    }

    char nome_base_geo[100];
    extrair_nome_base(arq_geo, nome_base_geo);

    char caminho_svg_inicial[512];
    if (dir_saida[strlen(dir_saida)-1] == '/')
        sprintf(caminho_svg_inicial, "%s%s.svg", dir_saida, nome_base_geo);
    else
        sprintf(caminho_svg_inicial, "%s/%s.svg", dir_saida, nome_base_geo);
    
    printf("Gerando SVG inicial: %s\n", caminho_svg_inicial);
    desenhar_svg(caminho_svg_inicial, lista_formas);

    printf("Limpando memoria...\n");
    kill_lista(lista_formas, destruir_forma_generica);

    printf("Concluido com sucesso.\n");
    return 0;
}