#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

#include <math.h>

typedef struct L{
    struct L son;
    struct L brother;
    float x;
    float y;
    float w;
    float h;
    float a;
}list;

void rotate(list * l, float a);

#define p(l) printf(#l "\n\tx: %f\n\ty: %f\n\tw: %f\n\th: %f\n\ta: %f\n", l->x, l->y, l->w, l->h, l->a)

int main(){
    list grandson = {NULL, NULL, 15, 15, 3, 3, 45.f};
    list son = {&grandson, NULL, 5, 5, 6, 6, 0.f};
    list daughter = {NULL, &son, 0, 0, 4, 4, 0.f};
    list parent = {&daughter, 25, 25, 10, 10, 0.f};

    // rotation / translation tests
    rotate(&parent, 45.f);

    p(parent);
    p(daughter);
    p(son);
    p(grandson);
    
    return 0;
}

static void rotateAround(list * l, float a, float x, float y){

    if(l->brother){
        rotateAround(l->brother, a, x, y);
    }
    if(l->son){
        rotateAround(l->son, a, x, y);
    }
}
void rotate(list * l, float a){
    if(!l) return;
    rotateAround(l, a, l->x + l->w / 2, l->y + l->h / 2);
}
