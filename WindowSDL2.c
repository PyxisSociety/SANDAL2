#include "WindowSDL2.h"

ListWindowSDL2 * _windows_SDL2TK = NULL;

/* -------------------------------------------------------
 * Window SDL2
 */
void resizeWindowSDL2(unsigned width,unsigned height){
  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->window){
    SDL_SetWindowSize(_windows_SDL2TK->current->window,width,height);
    _windows_SDL2TK->current->width=width;
    _windows_SDL2TK->current->height=height;
  }
}

void changeDisplayWindowSDL2(int displayCode){
  if(_windows_SDL2TK && _windows_SDL2TK->current){
    _windows_SDL2TK->current->displayCode=displayCode;
  }
}

int initIteratorWindowSDL2(){
  int error = 1;

  if(_windows_SDL2TK){
    _windows_SDL2TK->current = _windows_SDL2TK->first;
    error = 0;
  }

  return error;
}

int nextWindowSDL2(){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    _windows_SDL2TK->current = _windows_SDL2TK->current->next;
    error = 0;
  }
  
  return error;
}

int getDimensionWindowSDL2(int * w,int * h){
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

int getDisplayCodeWindowSDL2(int * d){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    if(d){
      *d=_windows_SDL2TK->current->displayCode;
    }
    error=0;
  }

  return error;
}

int getColorWindowSDL2(int color[4]){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    copyColor(color,_windows_SDL2TK->current->background);
    error = 0;
  }

  return error;
}

int setColorWindowSDL2(int color[4]){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->current){
    copyColor(_windows_SDL2TK->current->background,color);
    error = 0;
  }

  return error;
}

int getCoordWindowSDL2(int *x,int *y){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->first){
    error = 0;
    SDL_GetWindowPosition(_windows_SDL2TK->current->window,x,y);
  }

  return error;
}

int setCoordWindowSDL2(int x,int y){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->first){
    error = 0;
    SDL_SetWindowPosition(_windows_SDL2TK->current->window,x,y);
  }

  return error;
}

int getRealDimensionWindowSDL2(int *width,int *height){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->first){
    error = 0;
    if(width){
      *width=_windows_SDL2TK->current->width;
    }
    if(height){
      *height=_windows_SDL2TK->current->height;
    }
  }

  return error;
}

int getIDWindowSDL2(Uint32 *ID){
  int error = 1;

  if(_windows_SDL2TK && _windows_SDL2TK->first){
    error = 0;
    if(ID){
      *ID=SDL_GetWindowID(_windows_SDL2TK->current->window);
    }
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

  return res;
}

void copyColor(int to[4],int from[4]){
  to[0]=from[0];
  to[1]=from[1];
  to[2]=from[2];
  to[3]=from[3];
}
/* ------------------------------------------------------- */
