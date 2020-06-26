#ifndef MYGL_H
#define MYGL_H

#include "core.h"
#include "frame_buffer.h"


//
// >>> Declare aqui as funções que você implementar <<<
//
typedef struct {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;

}Color;

typedef struct {
    int x1;
    int x2;
    int x3;
    int y1;
    int y2;
    int y3;

}Coordinates;

void MyGlDraw(void);

void PutPixel(int x1, int y1, Color *reference);
void DrawLine (Coordinates *p, Color *A, Color *B, Color *Color_reference);
void DrawTriangle(Coordinates *p, Color *A, Color *B, Color *C, Color *Color_reference);

#endif  // MYGL_H
