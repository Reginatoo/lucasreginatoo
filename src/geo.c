#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "lista.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

void ler_geo(char* caminho_geo, LISTA chao) {
    FILE* arquivo_geo = fopen(caminho_geo, "r");
    
    if (arquivo_geo == NULL) {
        printf("Erro: não foi possível abrir o arquivo %s!\n", caminho_geo);
        exit(1);
    }

    char estilo_familia[50] = "Arial";
    char estilo_peso[50] = "normal";
    char estilo_tam[50] = "12px";

    char linha[1024]; 
    char comando[10];

    while (fgets(linha, sizeof(linha), arquivo_geo)) {
        sscanf(linha, "%s", comando);

        if (strcmp(comando, "c") == 0) {
            int id;
            float r, x, y;
            char corb[50], corp[50];
            
            sscanf(linha, "c %d %f %f %f %s %s", &id, &x, &y, &r, corb, corp);
            
            FORMA novo_circulo = cria_circulo(id, x, y, r, corb, corp);
            inserir_na_lista(chao, novo_circulo);
        }
        else if (strcmp(comando, "r") == 0) {
            int id;
            float x, y, w, h;
            char corb[50], corp[50];
            
            sscanf(linha, "r %d %f %f %f %f %s %s", &id, &x, &y, &w, &h, corb, corp);
            
            FORMA novo_retangulo = cria_retangulo(id, x, y, w, h, corb, corp);
            inserir_na_lista(chao, novo_retangulo);
        }
        else if (strcmp(comando, "l") == 0) {
            int id;
            float x1, y1, x2, y2;
            char cor[50];
            
            sscanf(linha, "l %d %f %f %f %f %s", &id, &x1, &y1, &x2, &y2, cor);
            
            FORMA nova_linha = cria_linha(id, x1, y1, x2, y2, cor);
            inserir_na_lista(chao, nova_linha);
        }
        else if (strcmp(comando, "ts") == 0) {
            sscanf(linha, "ts %s %s %s", estilo_familia, estilo_peso, estilo_tam);
        }
        else if (strcmp(comando, "t") == 0) {
            int id;
            float x, y;
            char corb[50], corp[50];
            char a;
            int num_caracteres_lidos = 0;
            sscanf(linha, "t %d %f %f %s %s %c%n", &id, &x, &y, corb, corp, &a, &num_caracteres_lidos);
            char* conteudo_bruto = linha + num_caracteres_lidos;
            conteudo_bruto[strcspn(conteudo_bruto, "\n")] = 0;
            if (conteudo_bruto[0] == ' ') conteudo_bruto++;

            FORMA novo_texto = cria_texto(id, x, y, corb, corp, a, conteudo_bruto, estilo_familia, estilo_peso, estilo_tam);
            inserir_na_lista(chao, novo_texto);
        }
    }

    fclose(arquivo_geo);
}