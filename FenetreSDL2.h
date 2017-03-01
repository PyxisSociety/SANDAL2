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
typedef struct{
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
}FenetreSDL2;

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/* redimensionnement de la fenetre si nescessaire */
void resizeFenetreSDL2(FenetreSDL2*,unsigned width,unsigned height);
/* change le code d'affichage de la fenetre passe en parametre */
void changeDisplayFenetreSDL2(FenetreSDL2*,int);
/* ------------------------------------------------------- */

int cmpCoul(int c1[4],int c2[4]);
void copyColor(int to[4],int from[4]);
#endif
