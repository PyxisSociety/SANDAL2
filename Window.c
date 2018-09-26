#include "Window.h"

ListWindow * _windows_SANDAL2 = NULL;



/* -------------------------------------------------------
 * Other functions
 */
static void copyColor(int to[4],const int from[4]){
    to[0]=from[0];
    to[1]=from[1];
    to[2]=from[2];
    to[3]=from[3];
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Window 
 */
int resizeWindow(unsigned width,unsigned height){
    int error = 1;
    
    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->window){
        SDL_SetWindowSize(_windows_SANDAL2->current->window,width,height);
        _windows_SANDAL2->current->width=width;
        _windows_SANDAL2->current->height=height;
        error=0;
    }

    return error;
}

int setDisplayCodeWindow(int displayCode){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->displayCode != displayCode){
        _windows_SANDAL2->current->newDisplayCode = displayCode;
        _windows_SANDAL2->current->displayToChange = 1;
        error = 0;
    }

    return error;
}

int initIteratorWindow(){
    int error = 1;

    if(_windows_SANDAL2){
        _windows_SANDAL2->current = _windows_SANDAL2->first;
        error = 0;
    }

    return error;
}

int nextWindow(){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current = _windows_SANDAL2->current->next;
        error = 0;
    }
  
    return error;
}

int getDimensionWindow(int * w,int * h){
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

int getDisplayCodeWindow(int * d){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        if(d){
            *d=_windows_SANDAL2->current->displayCode;
        }
        error=0;
    }

    return error;
}

int getColorWindow(int color[4]){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        copyColor(color,_windows_SANDAL2->current->background);
        error = 0;
    }

    return error;
}

int setColorWindow(const int color[4]){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        copyColor(_windows_SANDAL2->current->background,color);
        error = 0;
    }

    return error;
}

int getCoordWindow(int *x,int *y){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        SDL_GetWindowPosition(_windows_SANDAL2->current->window,x,y);
    }

    return error;
}

int setCoordWindow(int x,int y){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        SDL_SetWindowPosition(_windows_SANDAL2->current->window,x,y);
    }

    return error;
}

int getRealDimensionWindow(int *width,int *height){
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

int getIDWindow(Uint32 *ID){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        if(ID){
            *ID=SDL_GetWindowID(_windows_SANDAL2->current->window);
        }
    }

    return error;
}

int setIconWindow(const char * icon_path){
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

int setActionWindow(void (*action)(void)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.action=action;
        error=0;
    }

    return error;
}

int setKeyPressedWindow(void (*keyPress)(SDL_Keycode c)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.keyPress=keyPress;
        error=0;
    }

    return error;
}

int setKeyReleasedWindow(void (*keyReleased)(SDL_Keycode c)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.keyReleased=keyReleased;
        error=0;
    }

    return error;
}

int setOnClickWindow(void (*onClick)(int)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.onClick=onClick;
        error=0;
    }

    return error;
}

int setUnClickWindow(void (*unClick)(int)){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->events.unClick=unClick;
        error=0;
    }

    return error;
}

int setWheelWindow(void (*wheel)(int))
{
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    _windows_SANDAL2->current->events.wheel=wheel;
  }

  return error;
}

int getOriginWindow(int * x,int * y){
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	if(x)
	    *x = _windows_SANDAL2->current->origin[0];
	if(y)
	    *y = _windows_SANDAL2->current->origin[1];
    }

    return _windows_SANDAL2 && _windows_SANDAL2->current;
}

int setOriginWindow(int x,int y){
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	_windows_SANDAL2->current->origin[0] = x;
	_windows_SANDAL2->current->origin[1] = y;
    }
    
    return !(_windows_SANDAL2 && _windows_SANDAL2->current);
}

int setXOriginWindow(int x){
    if(_windows_SANDAL2 && _windows_SANDAL2->current)
	_windows_SANDAL2->current->origin[0] = x;

    return !(_windows_SANDAL2 && _windows_SANDAL2->current);
}

int setYOriginWindow(int y){
    if(_windows_SANDAL2 && _windows_SANDAL2->current)
	_windows_SANDAL2->current->origin[1] = y;

    return !(_windows_SANDAL2 && _windows_SANDAL2->current);
}

int setDataWindow(void * data){
    if(_windows_SANDAL2 && _windows_SANDAL2->current)
	_windows_SANDAL2->current->data = data;

    return !(_windows_SANDAL2 && _windows_SANDAL2->current);
}

int getDataWindow(void ** data){
    if(_windows_SANDAL2 && _windows_SANDAL2->current)
	if(data)
	    *data = _windows_SANDAL2->current->data;

    return !(_windows_SANDAL2 && _windows_SANDAL2->current);
}
/* ------------------------------------------------------- */
