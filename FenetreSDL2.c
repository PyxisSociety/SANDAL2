#include "FenetreSDL2.h"
ListFenetreSDL2 * _windows_SDL2TK = NULL;

/* -------------------------------------------------------
 * Fenetre SDL2
 */
void resizeFenetreSDL2(unsigned width,unsigned height){
  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->window){
    SDL_SetWindowSize(_windows_SDL2TK->current->window,width,height);
    _windows_SDL2TK->current->width=width;
    _windows_SDL2TK->current->height=height;
  }
}

void changeDisplayFenetreSDL2(int displayCode){
  if(_windows_SDL2TK && _windows_SDL2TK->current){
    _windows_SDL2TK->current->displayCode=displayCode;
  }
}

int initIteratorFenetreSDL2(){
  int error = 1;

  if(_windows_SDL2TK){
    _windows_SDL2TK->current = _windows_SDL2TK->first;
    error = 0;
  }

  return error;
}

int nextFenetreSDL2(){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    _windows_SDL2TK->current = _windows_SDL2TK->current->next;
    error = 0;
  }
  
  return error;
}

int getDimensionFenetreSDL2(int * w,int * h){
  int error = 0;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    if(w){
      *w=_windows_SDL2TK->current->initWidth;
    }
    if(h){
      *h=_windows_SDL2TK->current->initHeight;
    }
    error =1;
  }

  return error;
}

int getDisplayCodeFenetreSDL2(int * d){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    if(d){
      *d=_windows_SDL2TK->current->displayCode;
    }
    error=0;
  }

  return error;
}

int getColorFenetreSDL2(int color[4]){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    copyColor(color,_windows_SDL2TK->current->background);
    error = 0;
  }

  return error;
}

int setColorFenetreSDL2(int color[4]){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    copyColor(_windows_SDL2TK->current->background,color);
    error = 0;
  }

  return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Other functions
 */
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
/* ------------------------------------------------------- */
