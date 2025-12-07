#ifndef QRY_H
#define QRY_H

#include "lista.h"

/**
 * @brief Le o arquivo .qry e processa os comandos
 * @param caminho_qry Caminho do arquivo de consulta
 * @param lista_formas A lista com todas as formas do .geo
 * @param lista_segmentos Uma lista onde vamos guardar os anteparos
 * @param caminho_saida_txt Caminho para gerar o.txt
 * @param caminho_saida_svg Caminho para gerar o svg final
 */
void ler_qry(char* caminho_qry, LISTA lista_formas, LISTA lista_segmentos, char* caminho_saida_txt, char* caminho_saida_svg);

#endif