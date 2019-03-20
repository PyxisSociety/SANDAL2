#include "Window.h"

ListWindow * _windows_SANDAL2 = NULL;

#ifdef DEBUG_SDL2_NO_VIDEO
Uint32 currentDisplaied = 0;
#endif



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
 * Other functions
 */
#ifdef DEBUG_SDL2_NO_VIDEO
static unsigned fake_SDL_GetWindowID(Window * w){
    return w ? w->id : 0;
}

static void fake_SDL_GetWindowSize(Window * w, int * wi, int * he){
    if(w){
	if(wi)
	    *wi = w->width;
	if(he)
	    *he = w->height;
    }
}

static void fake_SDL_SetWindowSize(Window * w, int width, int height){
    (void)w;
    (void)width;
    (void)height;
}

static void fake_SDL_GetWindowPosition(Window * w, int * x, int * y){
    if(w){
	if(x)
	    *x = w->posX;
	if(y)
	    *y = w->posY;
    }
}

static void fake_SDL_SetWindowPosition(Window * w, int x, int y){
    if(w){
	w->posX = x;
	w->posY = y;
    }
}

static void fake_SDL_SetWindowIcon(Window * w, SDL_Surface * s){
    (void)w;
    (void)s;
}

static void fake_SDL_RaiseWindow(Window * w){
    SDL_Event * e = NULL;

    if(w){
	e = (SDL_Event*)malloc(sizeof(*e));

	if(e){
	    e->type = SDL_WINDOWEVENT;
	    e->window.event = SDL_WINDOWEVENT_FOCUS_LOST;
	    e->window.windowID = currentDisplaied;
	    SDL_PushEvent(e);
	}

	e = (SDL_Event*)malloc(sizeof(*e));
	if(e){
	    e->type = SDL_WINDOWEVENT;
	    e->window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
	    e->window.windowID = w->id;
	    SDL_PushEvent(e);
	}

	currentDisplaied = w->id;
    }
}

#  define SDL_GetWindowID fake_SDL_GetWindowID
#  define SDL_GetWindowSize fake_SDL_GetWindowSize
#  define SDL_SetWindowSize fake_SDL_SetWindowSize
#  define SDL_GetWindowPosition fake_SDL_GetWindowPosition
#  define SDL_SetWindowPosition fake_SDL_SetWindowPosition
#  define SDL_SetWindowIcon fake_SDL_SetWindowIcon
#  define SDL_RaiseWindow fake_SDL_RaiseWindow

#endif
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

Uint32 initIteratorWindow(){
    Uint32 error = 0;

    if(_windows_SANDAL2){
        _windows_SANDAL2->current = _windows_SANDAL2->first;
        error = SDL_GetWindowID(_windows_SANDAL2->current->window);
    }

    return error;
}

Uint32 nextWindow(){
    Uint32 error = 0;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current = _windows_SANDAL2->current->next;
	if(_windows_SANDAL2->current){
	    error = SDL_GetWindowID(_windows_SANDAL2->current->window);
	}
    }
  
    return error;
}

int getDimensionWindow(int * w,int * h){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        if(w){
            *w=_windows_SANDAL2->current->initWidth;
        }
        if(h){
            *h=_windows_SANDAL2->current->initHeight;
        }
        error = 0;
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

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay){
        error = 0;
        if(ID){
            *ID=SDL_GetWindowID(_windows_SANDAL2->currentDisplay->window);
        }
    }

    return error;
}

int getIDCurrentWindow(Uint32 *ID){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
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

int setOnWheelWindow(void (*onWheel)(int)){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	error = 0;
	_windows_SANDAL2->current->events.onWheel = onWheel;
    }

    return error;
}

int setOnMouseMotionWindow(void (*onMouseMotion)(int, int)){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        error = 0;
        _windows_SANDAL2->current->events.onMouseMotion = onMouseMotion;
    }

    return error;
}

int setOnFocusedWindow(void (*onFocus)(void)){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	error = 0;
	_windows_SANDAL2->current->events.onFocus = onFocus;
    }

    return error;
}

int setUnFocusedWindow(void (*unFocus)(void)){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	error = 0;
	_windows_SANDAL2->current->events.unFocus = unFocus;
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

    return !(_windows_SANDAL2 && _windows_SANDAL2->current);
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

int setDisplayWindow(Uint32 windowID){
    Window * window = NULL;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay){
	window = _windows_SANDAL2->first;
	while(window && SDL_GetWindowID(window->window) != windowID){
	    window = window->next;
	}

	if(window){
	    error = 0;
	    _windows_SANDAL2->currentDisplay = window;
	    _windows_SANDAL2->current = window;
	    SDL_RaiseWindow(_windows_SANDAL2->currentDisplay->window);
	}
    }

    return error;
}
/* ------------------------------------------------------- */
