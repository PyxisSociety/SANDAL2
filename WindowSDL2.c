#include "WindowSDL2.h"

ListWindowSDL2 * _windows_SANDAL2 = NULL;

/* -------------------------------------------------------
 * Window SDL2
 */
int resizeWindowSDL2(unsigned width,unsigned height){
  int error = 1;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->window){
    SDL_SetWindowSize(_windows_SANDAL2->current->window,width,height);
    _windows_SANDAL2->current->width=width;
    _windows_SANDAL2->current->height=height;
    error=0;
  }

  return error;
}

int changeDisplayWindowSDL2(int displayCode){
  int error = 1;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    _windows_SANDAL2->current->displayCode=displayCode;
    error = 0;
  }

  return error;
}

int initIteratorWindowSDL2(){
  int error = 1;

  if(_windows_SANDAL2){
    _windows_SANDAL2->current = _windows_SANDAL2->first;
    error = 0;
  }

  return error;
}

int nextWindowSDL2(){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    _windows_SANDAL2->current = _windows_SANDAL2->current->next;
    error = 0;
  }
  
  return error;
}

int getDimensionWindowSDL2(int * w,int * h){
  int error = 0;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    if(w){
      *w=_windows_SANDAL2->current->initWidth;
    }
    if(h){
      *h=_windows_SANDAL2->current->initHeight;
    }
    error =1;
  }

  return error;
}

int getDisplayCodeWindowSDL2(int * d){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    if(d){
      *d=_windows_SANDAL2->current->displayCode;
    }
    error=0;
  }

  return error;
}

int getColorWindowSDL2(int color[4]){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    copyColor(color,_windows_SANDAL2->current->background);
    error = 0;
  }

  return error;
}

int setColorWindowSDL2(int color[4]){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    copyColor(_windows_SANDAL2->current->background,color);
    error = 0;
  }

  return error;
}

int getCoordWindowSDL2(int *x,int *y){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->first){
    error = 0;
    SDL_GetWindowPosition(_windows_SANDAL2->current->window,x,y);
  }

  return error;
}

int setCoordWindowSDL2(int x,int y){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->first){
    error = 0;
    SDL_SetWindowPosition(_windows_SANDAL2->current->window,x,y);
  }

  return error;
}

int getRealDimensionWindowSDL2(int *width,int *height){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->first){
    error = 0;
    if(width){
      *width=_windows_SANDAL2->current->width;
    }
    if(height){
      *height=_windows_SANDAL2->current->height;
    }
  }

  return error;
}

int getIDWindowSDL2(Uint32 *ID){
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->first){
    error = 0;
    if(ID){
      *ID=SDL_GetWindowID(_windows_SANDAL2->current->window);
    }
  }

  return error;
}

int setIconWindowSDL2(char * icon_path){
  SDL_Surface *s;
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->window && icon_path){
    s=IMG_Load(icon_path);
    if(s){
      SDL_SetWindowIcon(_windows_SANDAL2->current->window,s);
      SDL_FreeSurface(s);
      error = 0;
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
