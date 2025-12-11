#include <stdio.h>
#include <stdlib.h>
#include "anteparo.h"
typedef struct {
    int id;
    float x1, y1, x2, y2;
} StAnteparo;

Anteparo cria_anteparo(int id, float x1, float y1, float x2, float y2) {
    StAnteparo* seg = (StAnteparo*) malloc(sizeof(StAnteparo));
    
    if (seg == NULL) {
        return NULL; 
    }
    seg->id = id;
    seg->x1 = x1;
    seg->y1 = y1;
    seg->x2 = x2;
    seg->y2 = y2;
    return (Anteparo) seg;
}
int get_ant_id(Anteparo a) {
    StAnteparo* s = (StAnteparo*) a;
    return s->id;
}
float get_ant_x1(Anteparo a) {
    StAnteparo* seg = (StAnteparo*) a;
    return seg->x1;
}

float get_ant_y1(Anteparo a) {
    StAnteparo* seg = (StAnteparo*) a;
    return seg->y1;
}

float get_ant_x2(Anteparo a) {
    StAnteparo* seg = (StAnteparo*) a;
    return seg->x2;
}

float get_ant_y2(Anteparo a) {
    StAnteparo* seg = (StAnteparo*) a;
    return seg->y2;
}

void kill_anteparo(Anteparo a) {
    if (a != NULL) {
        free(a);
    }
}