#ifndef _DISPLAYCODE_SDL2TK_KLEVH_
#define _DISPLAYCODE_SDL2TK_KLEVH_

#include <stdio.h>
#include <stdlib.h>

/* code d'affichage */
typedef struct DisplayCode{
  /* element suivant */
  struct DisplayCode *next;
  /* code d'affichage */
  int code;
  /* flag vallant 1 si l'element doit etre affiche, 0 sinon */
  int isDisplaied;
  /* plan relie au code d'affichage */
  int plan;
}DisplayCode;

/* liste de code d'affichage */
typedef struct{
  /* premier element de la liste */
  DisplayCode *first;
}ListDisplayCode;

/* -------------------------------------------------------
 * Liste de code d'affichage
 */
/* renvoi une liste de code d'affichage vide */
ListDisplayCode* initListDisplayCode();
/* libere la liste passe en parametre */
void freeListDisplayCode(ListDisplayCode*);
/* ajout d'un code d'affichage a la liste passe en parametre */
void addDisplayCode(ListDisplayCode*,int,int,int);
/* ------------------------------------------------------- */

#endif
