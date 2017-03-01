#include "FenetreSDL2.h"

/* -------------------------------------------------------
 * Fenetre SDL2
 */
void resizeFenetreSDL2(FenetreSDL2 *f,unsigned width,unsigned height){
  if(f && f->window){
    SDL_SetWindowSize(f->window,width,height);
    f->width=width;
    f->height=height;
  }
}

void changeDisplayFenetreSDL2(FenetreSDL2 *f,int displayCode){
  if(f){
    f->displayCode=displayCode;
  }
}
/* ------------------------------------------------------- */

int cmpCoul(int c1[4],int c2[4]){
  int res=1,i;

  for(i=0;i<4;++i){
    res=res && c1[i]==c2[i];
    c1[i]=c2[i];
  }
}

void copyColor(int to[4],int from[4]){
  to[0]=from[0];
  to[1]=from[1];
  to[2]=from[2];
  to[3]=from[3];
}
