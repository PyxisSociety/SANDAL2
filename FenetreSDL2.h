#ifndef _FENETRE_SDL2_BY_KLEVH_
#define _FENETRE_SDL2_BY_KLEVH_

#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define absolu(a) ((a>0)?a:-a)
#define PFREE(p){				\
    if(p){					\
      free(p);					\
    }						\
  }

struct ListElementSDL2;

/* fenetre SDL2 */
typedef struct FenetreSDL2{
  /* dimensions de la fenetre */
  int height;
  int width;
  /* dimensions initiales de la fenetre */
  int initHeight;
  int initWidth;
  /* code d'affichage de la fenetre */
  int displayCode;
  /* couleur de fond */
  int background[4];
  /* Fenetre SDL2 (l'originale) */
  SDL_Window *window;
  /* zone de dessin SDL2 (l'original) */
  SDL_Renderer *renderer;
  /* liste d'element associe a la fenetre */
  struct ListElementSDL2 * liste;
  /* fenetre suivante */
  struct FenetreSDL2 * next;
}FenetreSDL2;

typedef struct{
  FenetreSDL2 * first;
  FenetreSDL2 * last;
  FenetreSDL2 * current;
}ListFenetreSDL2;

extern ListFenetreSDL2 * _windows_SDL2TK;

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/* redimensionnement de la fenetre si nescessaire */
void resizeFenetreSDL2(unsigned width,unsigned height);
/* change le code d'affichage de la fenetre passe en parametre */
void changeDisplayFenetreSDL2(int);
/* initialise l'iterateur de structure sur les Fenetres */
int initIteratorFenetreSDL2();
/* passe a la fenetre suivante */
int nextFenetreSDL2();
/* recupere les dimensions de la fenetre courante */
int getDimensionFenetreSDL2(int * w,int * h);
/* recupere le code d'affichage de la fenetre courante */
int getDisplayCodeFenetreSDL2(int * d);
/* recupere la couleur de fond de la fenetre courante */
int getColorFenetreSDL2(int color[4]);
/* change la couleur de fond de la fenetre courante */
int setColorFenetreSDL2(int color[4]);
/* ------------------------------------------------------- */

int cmpCoul(int c1[4],int c2[4]);
void copyColor(int to[4],int from[4]);
#endif
