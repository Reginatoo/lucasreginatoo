#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "lista.h"

int maior_id_global = 0; 

char get_tipo_da_forma(void* forma) {
    if (forma == NULL) return '\0';
    return *((char*)forma);
}

void* encontrar_forma_por_id(LISTA f, int id) {
    POSIC no_atual = get_primeiro_no(f);
    
    while (no_atual != NULL) {
        void* forma_atual = get_info_do_no(f, no_atual);
        int id_da_forma = get_id_da_forma(forma_atual);
        
        if (id_da_forma == id) {
            return forma_atual; 
        }
        
        no_atual = get_proximo_no(f, no_atual);
    }
    return NULL; 
}

int get_id_da_forma(void* forma) {
    if (forma == NULL) return -1; 

    switch (get_tipo_da_forma(forma)) {
        case 'c': return get_idC(forma);
        case 'r': return get_idR(forma);
        case 'l': return get_idL(forma);
        case 't': return get_idT(forma);
    }
    
    return -1;
}

float get_area_da_forma(void* forma) {
    if (forma == NULL) return 0;
    switch (get_tipo_da_forma(forma)) {
        case 'c': return get_areaC(forma);
        case 'r': return get_areaR(forma);
        case 'l': return get_areaL(forma);
        case 't': return get_areaT(forma);
    }
    return 0;
}

float get_x_da_forma(void* forma) {
    if (forma == NULL) return 0;
    switch (get_tipo_da_forma(forma)) {
        case 'c': return get_XC(forma);
        case 'r': return get_XR(forma);
        case 'l': return get_X1L(forma); 
        case 't': return get_xT(forma);
    }
    return 0;
}

float get_y_da_forma(void* forma) {
    if (forma == NULL) return 0;
    switch (get_tipo_da_forma(forma)) {
        case 'c': return get_YC(forma);
        case 'r': return get_YR(forma);
        case 'l': return get_Y1L(forma); 
        case 't': return get_yT(forma);
    }
    return 0;
}

void set_corb_da_forma(void* forma, char* nova_cor) {
    if (forma == NULL) return;
    switch (get_tipo_da_forma(forma)) {
        case 'c': set_cbC(forma, nova_cor); break;
        case 'r': set_cbR(forma, nova_cor); break;
        case 'l': set_CorL(forma, nova_cor); break;
        case 't': set_cbT(forma, nova_cor);  break; 
    }
}

char* get_corp_da_forma(void* forma) {
    if (forma == NULL) return "black";
    switch (get_tipo_da_forma(forma)) {
        case 'c': return get_cpC(forma);
        case 'r': return get_cpR(forma);
        case 't': return get_cpT(forma);
    }
    return "black"; 
} 

void set_cp_da_forma(void* forma, char* nova_cor) {
    if (forma == NULL) return;
    switch (get_tipo_da_forma(forma)) {
        case 'c': set_cpC(forma, nova_cor); break;
        case 'r': set_cpR(forma, nova_cor); break;
        case 't': set_cpT(forma, nova_cor); break;
    }
}

void destruir_forma_generica(void* forma) {
    if (forma == NULL) return;
    switch (get_tipo_da_forma(forma)) {
        case 'c': kill_circ(forma); break;
        case 'r': kill_retang(forma); break;
        case 'l': kill_linha(forma); break;
        case 't': kill_texto(forma); break;
    }
}

void set_id_da_forma(void* forma, int id) {
    if (forma == NULL) return;
    switch (get_tipo_da_forma(forma)) {
        case 'c': set_idC(forma, id); break;
        case 'r': set_idR(forma, id); break;
        case 'l': set_idL(forma, id); break;
        case 't': set_idT(forma, id); break;
    }
}

form clone_forma(void* forma) {
    if (forma == NULL) return NULL;
    
    char tipo = get_tipo_da_forma(forma);
    
    switch (tipo) {
        case 'c': 
            return clone_circulo(forma); 
        case 'r': 
            return clone_retangulo(forma);
        case 'l': 
            return clone_linha(forma);
        case 't': 
            return clone_texto(forma);
        default:
            return NULL;
    }
}

char* get_corb_da_forma(void* forma) {
    if (forma == NULL) return "black";
    switch (get_tipo_da_forma(forma)) {
        case 'c': return get_cbC(forma);
        case 'r': return get_cbR(forma);
        case 'l': return get_CorL(forma);
        case 't': return get_cbT(forma);
    }
    return "black";
}

void set_posicao_da_forma(void* forma, float x, float y) {
    if (forma == NULL) return;
    char tipo = get_tipo_da_forma(forma);
    
    switch (tipo) {
        case 'c': 
            set_posicaoC(forma, x, y); 
            break;
        case 'r': 
            set_posicaoR(forma, x, y); 
            break;
        case 'l': 
            set_posicaoL(forma, x, y); 
            break;
        case 't': 
            set_posicaoT(forma, x, y); 
            break;
    }
}

void imprimir_dados_forma(FILE* arq_txt, void* forma) {
    if (forma == NULL) {
        fprintf(arq_txt, "  > Forma NULA\n");
        return;
    }
    
    char tipo = get_tipo_da_forma(forma);

    switch (tipo) {
        case 'c':
            fprintf(arq_txt, " Circulo ID:%d, X:%.2f, Y:%.2f, R:%.2f, Borda:%s, Preench:%s\n",
                    get_idC(forma), get_XC(forma), get_YC(forma), get_RC(forma),
                    get_cbC(forma), get_cpC(forma));
            break;
        case 'r':
            fprintf(arq_txt, " Retangulo ID:%d, X:%.2f, Y:%.2f, W:%.2f, H:%.2f, Borda:%s, Preench:%s\n",
                    get_idR(forma), get_XR(forma), get_YR(forma), get_WR(forma), get_HR(forma),
                    get_cbR(forma), get_cpR(forma));
            break;
           case 'l':
            fprintf(arq_txt, " Linha ID:%d, X1:%.2f, Y1:%.2f, X2:%.2f, Y2:%.2f, Cor:%s\n",
                    get_idL(forma), get_X1L(forma), get_Y1L(forma), get_X2L(forma), get_Y2L(forma),
                    get_CorL(forma));
            break;
        case 't':
            fprintf(arq_txt, " Texto ID:%d, X:%.2f, Y:%.2f, Borda:%s, Preench:%s, Ancora:'%c', Conteudo:\"%s\"\n",
                    get_idT(forma), get_xT(forma), get_yT(forma), get_cbT(forma), get_cpT(forma),
                    get_aT(forma), get_txtT(forma));
            break;
    }
}