#include "WindowSDL2.h"

ListWindowSDL2 * _windows_SANDAL2 = NULL;



/* -------------------------------------------------------
 * Other functions
 */
static void copyColor(int to[4],int from[4]){
    to[0]=from[0];
    to[1]=from[1];
    to[2]=from[2];
    to[3]=from[3];
}
/* ------------------------------------------------------- */



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

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->displayCode != displayCode){
        _windows_SANDAL2->current->newDisplayCode = displayCode;
        _windows_SANDAL2->current->displayToChange = 1;
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

int setActionWindowSDL2(void (*action)(void)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.action=action;
        error=0;
    }

    return error;
}

int setKeyPressWindowSDL2(void (*keyPress)(SDL_Keycode c)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.keyPress=keyPress;
        error=0;
    }

    return error;
}

int setKeyReleasedWindowSDL2(void (*keyReleased)(SDL_Keycode c)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.keyReleased=keyReleased;
        error=0;
    }

    return error;
}

int setOnClickWindowSDL2(void (*onClick)(void)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.onClick=onClick;
        error=0;
    }

    return error;
}

int setUnClickWindowSDL2(void (*unClick)(void)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.unClick=unClick;
        error=0;
    }

    return error;
}
/* ------------------------------------------------------- */
