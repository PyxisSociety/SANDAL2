#ifndef _HITBOX_SDL2TK_KLEVH_
#define _HITBOX_SDL2TK_KLEVH_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct LineSDL2{
  struct LineSDL2 * next;
  /* equation of the line ax+by=c */
  float a;
  float b;
  float c;
  /* side of the line that count (-1 : ax+by<c, 1 : ax+by>c)*/
  int sens;
}LineSDL2;

typedef struct CircleSDL2{
  struct CircleSDL2 * next;
  /* center of the ellipse */
  float x;
  float y;
  /* taille du rayon parallele a l'axe Oy */
  float rY;
  /* taille du rayon parallele a l'axe Ox */
  float rX;
  /* degree of rotation */
  float theta;
}CircleSDL2;

typedef struct HitBox{
  LineSDL2 * firstL;
  CircleSDL2 * firstC;
  struct HitBox * next;
}HitBox;

typedef struct{
  HitBox * first;
  HitBox * current;
}ListHitBox;

/* ----------------------------------------------------------
 * HitBox
 */
/* return an empty hitbox */
HitBox * initHitBox();
/* add a line to the hitbox sens*(ax+by) > sens*c */
int addLineSDL2(HitBox * hb,float a,float b,float c,int sens);
/* add an ellipse to the hitbox */
int addCircleSDL2(HitBox * hb,float x,float y,float rX,float rY,float theta);
/* remove a line from the hitbox */
int removeLineSDL2(HitBox * hb,float a,float b,float c,int sens);
/* remove an ellipse from the hitbox*/
int removeCircleSDL2(HitBox * hb,float x,float y,float rX,float rY,float theta);
/* tells if (x,y) touch the hitbox */
int hitHitBox(HitBox * hb,float x,float y);
/* generate a rectangulare shapped HitBox */
HitBox * rectangleHitBox(float x1,float y1,float x2,float y2);
/* generate an ellipse shapped HitBox */
HitBox * ellipseHitBox(float x,float y,float rX,float rY,float theta);
/* libere une hit box */
void freeHitBox(HitBox * hb);
/* ---------------------------------------------------------- */


/* ----------------------------------------------------------
 * ListHitBox
 */
/* initialise une liste d'hit box vide */
ListHitBox * initListHitBox();
/* ajoute un element a la liste */
int addHitBox(ListHitBox * l,HitBox * hb);
/* supprime un element de la liste */
int removeHitBox(ListHitBox * l,HitBox * hb);
/* initialise l'iterateur de la liste */
int initIteratorListHitBox(ListHitBox * l);
/* retourne l'element courant et passe a l'element suivant */
HitBox * nextHitBox(ListHitBox * l);
/* ---------------------------------------------------------- */

#endif
