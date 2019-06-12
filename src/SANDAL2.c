#include "SANDAL2.h"
/* -------------------------------------------------------
 * Other functions
 */
static int cmpCoul(int c1[4],int c2[4]){
    int res=1,i;

    for(i=0;i<4;++i){
        res=res && c1[i]==c2[i];
        c1[i]=c2[i];
    }

    return res;
}

static void copyColor(int to[4],int from[4]){
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
static void fake_SDL_DestroyWindow(Window * w){
    (void)w;
}

static void fake_SDL_DestroyRenderer(SDL_Renderer * r){
    (void)r;
}

static unsigned fake_SDL_GetWindowID(Window * w){
    return w ? w->id : 0;
}

static Uint32 fake_SDL_GetWindowFlags(Window * w){
    return w->state;
}

static void fake_SDL_GetWindowSize(Window * w, int * wi, int * he){
    if(w){
	if(wi)
	    *wi = w->width;
	if(he)
	    *he = w->height;
    }
}

static void fake_SDL_SetWindowFullscreen(Window * w, Uint32 fullScreen){
    if(w){
	w->state = !!fullScreen * SDL_WINDOW_FULLSCREEN;
    }
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

#  define SDL_DestroyWindow fake_SDL_DestroyWindow
#  define SDL_DestroyRenderer fake_SDL_DestroyRenderer
#  define SDL_GetWindowID fake_SDL_GetWindowID
#  define SDL_GetWindowFlags fake_SDL_GetWindowFlags
#  define SDL_GetWindowSize fake_SDL_GetWindowSize
#  define SDL_SetWindowFullscreen fake_SDL_SetWindowFullscreen

#endif
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Initialisation et fermeture des outils SDL2
 */
int initAllSANDAL2(int imageFlags){
    int failedInit=0;

    if(initSANDAL2()){
        failedInit=1;
    }else if(initTextSANDAL2()){
        SDL_Quit();
        failedInit=3;
    }else if(initImageSANDAL2(imageFlags)){
        failedInit=2;
        TTF_Quit();
        SDL_Quit();
    }

    return failedInit;
}

void closeAllSANDAL2(){
    closeAllWindow();
    closeImageSANDAL2();
    closeTextSANDAL2();
    closeSANDAL2();
}

int initSANDAL2(){
    int failedInit = 0;

#ifndef DEBUG_SDL2_NO_VIDEO
    if(SDL_Init(SDL_INIT_VIDEO)){
        failedInit=1;
    }
#else
    if(SDL_Init(SDL_INIT_EVENTS)){
        failedInit=1;
    }
#endif

    return failedInit;
}

int initImageSANDAL2(int imageFlags){
    int failedInit = 0;
  
    if((IMG_Init(imageFlags)&imageFlags)!=imageFlags){
        failedInit=1;
    }

    return failedInit;
}

int initTextSANDAL2(){
    int failedInit = 0;
  
    if(TTF_Init()){
        failedInit=1;
    }

    return failedInit;
}

void closeSANDAL2(){
    SDL_Quit();
}

void closeImageSANDAL2(){
    IMG_Quit();
}

void closeTextSANDAL2(){
    TTF_Quit();
}
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Creation, modification et suppression des fenetres
 */
static void freeWindow(Window *fen){
    if(fen){
        if(fen->liste){
            _freeListElement(fen->liste);
        }
        if(fen->renderer){
            SDL_DestroyRenderer(fen->renderer);
        }
        if(fen->window){
            SDL_DestroyWindow(fen->window);
        }
    }
}

Uint32 createWindow(int width,int height,const char *title,int SDLFlags,int background[4],int displayCode){
    Window *fen=(Window*)malloc(sizeof(*fen));
    Window * tmp = NULL;
    Uint32 error = 0;
#ifdef DEBUG_SDL2_NO_VIDEO
    static unsigned id = 0;
#endif

    if(fen){
#ifdef DEBUG_SDL2_NO_VIDEO
	fen->window = fen;
#else
	fen->window=SDL_CreateWindow(title,
				     SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED,
				     width, height,
				     SDLFlags);
#endif
    
	if(fen->window){
#ifndef DEBUG_SDL2_NO_VIDEO
	    fen->renderer=SDL_CreateRenderer(fen->window,
					     -1,
					     SDL_RENDERER_ACCELERATED);

	    if(fen->renderer)
#else
	    fen->renderer = NULL;
	    if(1)
#endif
            {
		fen->height=height;
		fen->width=width;
		fen->close=0;
		fen->initHeight=height;
		fen->initWidth=width;
		fen->displayCode=displayCode;
		fen->newDisplayCode=0;
		fen->displayToChange=0;
		fen->origin[0] = 0;
		fen->origin[1] = 0;
		fen->next = NULL;
		fen->data = NULL;
		fen->events.action = NULL;
		fen->events.onClick = NULL;
		fen->events.unClick = NULL;
		fen->events.keyPress = NULL;
		fen->events.keyReleased = NULL;
		fen->events.onWheel = NULL;
		fen->events.onMouseMotion = NULL;
		fen->events.onFocus = NULL;
		fen->events.unFocus = NULL;
		fen->toDelete=0;
		copyColor(fen->background,background);
		fen->liste = _initListElement();
		fen->current = NULL;
		fen->stop = 0;
		fen->state = SDLFlags&SDL_WINDOW_FULLSCREEN;
		fen->focused = 1;
#ifndef DEBUG_SDL2_NO_VIDEO
		SDL_SetRenderDrawBlendMode(fen->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(fen->renderer,background[0],background[1],background[2],background[3]);
		SDL_RenderClear(fen->renderer);
		SDL_RenderPresent(fen->renderer);
#else
		fen->id = ++id;
		currentDisplaied = fen->id;
		fen->posX = 0;
		fen->posY = 0;
#endif
                fen->ticks = SDL_GetTicks();
		if(!fen->liste){
		    SDL_DestroyWindow(fen->window);
		    SDL_DestroyRenderer(fen->renderer);
		    free(fen);
		}else{
		    if(!_windows_SANDAL2){
			_windows_SANDAL2 = (ListWindow*)malloc(sizeof(*_windows_SANDAL2));
			if(_windows_SANDAL2){
			    _windows_SANDAL2->first = fen;
			    _windows_SANDAL2->last = fen;
			    _windows_SANDAL2->current = fen;
			    _windows_SANDAL2->currentDisplay = fen;
			    _windows_SANDAL2->count = 1;
			}else{
			    SDL_DestroyWindow(fen->window);
			    SDL_DestroyRenderer(fen->renderer);
			    free(fen);
			    fen = NULL;
			}
		    }else{
			tmp = _windows_SANDAL2->first;
			while(tmp){
			    tmp->focused = 0;
			    tmp = tmp->next;
			}
			_windows_SANDAL2->last->next=fen;
			_windows_SANDAL2->last=fen;
			_windows_SANDAL2->current = fen;
			_windows_SANDAL2->currentDisplay = fen;
			++_windows_SANDAL2->count;
		    }
		    if(fen){
#ifdef DEBUG_SDL2_NO_VIDEO
			fake_SDL_RaiseWindow(fen);
#endif
			error = SDL_GetWindowID(fen->window);
		    }
		}
	    }else{
#ifndef DEBUG_SDL2_NO_VIDEO
		SDL_DestroyWindow(fen->window);
#endif
		free(fen);
	    }
	}else{
	    free(fen);
	}
    }

    return error;
}

int closeWindow(){
    Window * f, * tmp;
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        f = _windows_SANDAL2->current;
	
        if(f == _windows_SANDAL2->first){
            _windows_SANDAL2->first = _windows_SANDAL2->first->next;
        }else{
            tmp=_windows_SANDAL2->first;
            while(tmp && tmp->next!=f){
                tmp=tmp->next;
            }
            if(tmp){
                tmp->next=f->next;
            }
        }
        error = 0;
        _windows_SANDAL2->current=_windows_SANDAL2->current->next;
        freeWindow(f);
        if(!_windows_SANDAL2->first){
            free(_windows_SANDAL2);
            _windows_SANDAL2 = NULL;
        }

	if(_windows_SANDAL2 && f == _windows_SANDAL2->currentDisplay){
	    tmp = _windows_SANDAL2->first;
	    while(tmp && !(SDL_GetWindowFlags(tmp->window) & (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS))){
		tmp = tmp->next;
	    }
	    if(tmp){
		_windows_SANDAL2->currentDisplay = tmp;
	    }
	}
    }

    return error;
}

int shouldCloseWindow(){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->close=1;
        error=0;
    }

    return error;
}

int closeAllWindow(){
    Window *f, *tmp;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        f=_windows_SANDAL2->first;
        while(f){
            tmp=f;
            f=f->next;
            freeWindow(tmp);
        }
        free(_windows_SANDAL2);
        _windows_SANDAL2=NULL;
    }

    return error;
}

int toggleFullScreenWindow(void){
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	if(_windows_SANDAL2->current->state == SDL_WINDOW_FULLSCREEN){
	    SDL_SetWindowFullscreen(_windows_SANDAL2->current->window, 0);
	    _windows_SANDAL2->current->state &= ~SDL_WINDOW_FULLSCREEN;
	}else{
	    SDL_SetWindowFullscreen(_windows_SANDAL2->current->window, SDL_WINDOW_FULLSCREEN);
	    _windows_SANDAL2->current->state |= SDL_WINDOW_FULLSCREEN;
	}
    }

    return !_windows_SANDAL2 || !_windows_SANDAL2->current;
}

int isFullScreenWindow(void){
    return _windows_SANDAL2 && _windows_SANDAL2->current && (_windows_SANDAL2->current->state & SDL_WINDOW_FULLSCREEN);
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Fenetre 
 */
int updateWindow(){
    PtrElement **ele;
    ListPtrElement *lp;
    ListDCElement *ldc;
    unsigned i;
    int error=1;
    Uint32 time = SDL_GetTicks();

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error = 0;
        /* update de la taille de la fenetre */
        SDL_GetWindowSize(_windows_SANDAL2->currentDisplay->window,&(_windows_SANDAL2->currentDisplay->width),&(_windows_SANDAL2->currentDisplay->height));

        /* update le code d'affichage et la liste courante a afficher */
        if(_windows_SANDAL2->currentDisplay->displayToChange){
            ldc = _windows_SANDAL2->currentDisplay->liste->first;
            while(ldc && ldc->code < _windows_SANDAL2->currentDisplay->newDisplayCode)
                ldc = ldc->next;
            if(ldc && ldc->code == _windows_SANDAL2->currentDisplay->newDisplayCode)
                _windows_SANDAL2->currentDisplay->current = ldc;
            else
                _windows_SANDAL2->currentDisplay->current = NULL;
            _windows_SANDAL2->currentDisplay->displayToChange = 0;
            _windows_SANDAL2->currentDisplay->displayCode = _windows_SANDAL2->currentDisplay->newDisplayCode;
        }

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->currentDisplay->events.action){
            _windows_SANDAL2->currentDisplay->events.action();
        }
    
        /* recherche de la liste d'element ayant le bon code de display */
        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->currentDisplay->close){
                ele=&(lp->first);
                while(*ele && !_windows_SANDAL2->currentDisplay->close){
                    if(!(*ele)->deleted && isDisplaiedElement((*ele)->element)){
                        // exec action on element
                        if((*ele)->element->events.action){
                            (*ele)->element->events.action((*ele)->element);
                        }

                        // exec action list on element
                        if((*ele)->element->actions){
                            if(executeListAction((*ele)->element->actions, (*ele)->element, (double)(time - _windows_SANDAL2->currentDisplay->ticks) / 1000.f)){
                                freeListAction((*ele)->element->actions);
                                (*ele)->element->actions = NULL;
                                if((*ele)->element->events.endAction){
                                    (*ele)->element->events.endAction((*ele)->element);
                                }
                            }
                        }

                        // update animation
                        if((*ele)->element->animation->size && (*ele)->element->animation->size){
                            (*ele)->element->animation->current->wasChanged++;
                            if((*ele)->element->animation->current->side && (*ele)->element->animation->current->wasChanged >= (*ele)->element->animation->current->current->lifespan){
                                i=0;
                                do{
                                    if((*ele)->element->animation->current->side == -1){
                                        previousSpriteElement((*ele)->element);
                                    }else{
                                        nextSpriteElement((*ele)->element);
                                    }
                                    ++i;
                                }while(i<(*ele)->element->animation->current->size && !(*ele)->element->animation->current->current->lifespan);
                                if((*ele)->element->animation->current->current == (*ele)->element->animation->current->first && (*ele)->element->events.endSprite){
                                    (*ele)->element->events.endSprite((*ele)->element,(*ele)->element->animation->current->code);
                                }
                                (*ele)->element->animation->current->wasChanged = 0;
                            }
                        }
                    }
		    if(_windows_SANDAL2->currentDisplay->stop)
			break;
		    else
			ele=&((*ele)->next);
                }
		if(_windows_SANDAL2->currentDisplay->stop)
		    break;
		else
		    lp=lp->next;
            }
            _windows_SANDAL2->currentDisplay->ticks = time;
	    _windows_SANDAL2->currentDisplay->stop = 0;
        }
        if(_windows_SANDAL2->currentDisplay->close){
            closeWindow();
        }else{
            _cleanElement();
        }
    }

    return error;
}

int displayWindow(){
    PtrElement *ele;
    ListPtrElement * lp;
    ListDCElement * ldc;
    SDL_Rect r,sr, *srect;
    int coul[4];
    SDL_Point p;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error=0;
        /* fond de la fenetre */
        copyColor(coul,_windows_SANDAL2->currentDisplay->background);
        SDL_SetRenderDrawColor(_windows_SANDAL2->currentDisplay->renderer,coul[0],coul[1],coul[2],coul[3]);
        SDL_RenderClear(_windows_SANDAL2->currentDisplay->renderer);
        
        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp){
                /* affichage des elements */
                ele=lp->first;
                while(ele){
                    if(!ele->deleted && isDisplaiedElement(ele->element)){
                        r.x=(ele->element->x - _windows_SANDAL2->currentDisplay->origin[0])*_windows_SANDAL2->currentDisplay->width/_windows_SANDAL2->currentDisplay->initWidth;
                        r.y=(ele->element->y - _windows_SANDAL2->currentDisplay->origin[1])*_windows_SANDAL2->currentDisplay->height/_windows_SANDAL2->currentDisplay->initHeight;
                        r.w=ele->element->width*_windows_SANDAL2->currentDisplay->width/_windows_SANDAL2->currentDisplay->initWidth;
                        r.h=ele->element->height*_windows_SANDAL2->currentDisplay->height/_windows_SANDAL2->currentDisplay->initHeight;
                        /* affichage du block */
                        if(ele->element->coulBlock[0]!=-1 && !ele->element->image){
                            if(!cmpCoul(coul,ele->element->coulBlock)){
                                SDL_SetRenderDrawColor(_windows_SANDAL2->currentDisplay->renderer,coul[0],coul[1],coul[2],coul[3]);
                            }
                            SDL_RenderFillRect(_windows_SANDAL2->currentDisplay->renderer,&r);
                        }
                        /* affichage de l'image */
                        if(ele->element->image){
                            if(ele->element->animation->size && ele->element->animation->current->size){
                                sr.x=ele->element->animation->current->current->coords[0];
                                sr.y=ele->element->animation->current->current->coords[1];
                                sr.w=ele->element->animation->current->current->coords[2];
                                sr.h=ele->element->animation->current->current->coords[3];
                                srect=&sr;
                            }else{
                                srect=NULL;
                            }
                            if(ele->element->rotation == 0.f && ele->element->flip == SANDAL2_FLIP_NONE){
                                SDL_RenderCopy(_windows_SANDAL2->currentDisplay->renderer,ele->element->image,srect,&r);
                            }else{
                                p.x=(int)(ele->element->prX*ele->element->width*_windows_SANDAL2->currentDisplay->width/_windows_SANDAL2->currentDisplay->initWidth);
                                p.y=(int)(ele->element->prY*ele->element->height*_windows_SANDAL2->currentDisplay->height/_windows_SANDAL2->currentDisplay->initHeight);
                                SDL_RenderCopyEx(_windows_SANDAL2->currentDisplay->renderer,ele->element->image,srect,&r,(double)ele->element->rotation,&p,ele->element->flip);
                            }
                        }
                        /* affichage du texte */
                        if(ele->element->font){
                            r.x+=r.w*(1.0-ele->element->textSize)/2;
                            r.y+=r.h*(1.0-ele->element->textSize)/2;
                            r.w*=ele->element->textSize;
                            r.h*=ele->element->textSize;
                            if(ele->element->rotation == 0.f || (ele->element->coulBlock[0]!=-1 && !ele->element->image)){
                                SDL_RenderCopy(_windows_SANDAL2->currentDisplay->renderer,ele->element->font->texture,NULL,&r);
                            }else{
                                p.x=(int)(ele->element->textSize*ele->element->prX*ele->element->width*_windows_SANDAL2->currentDisplay->width/_windows_SANDAL2->currentDisplay->initWidth);
                                p.y=(int)(ele->element->textSize*ele->element->prY*ele->element->height*_windows_SANDAL2->currentDisplay->height/_windows_SANDAL2->currentDisplay->initHeight);
                                SDL_RenderCopyEx(_windows_SANDAL2->currentDisplay->renderer,ele->element->font->texture,NULL,&r,(double)ele->element->rotation,&p,SDL_FLIP_NONE);
                            }
                        }
                    }
                    ele=ele->next;
                }
                lp=lp->next;
            }
        }
        SDL_RenderPresent(_windows_SANDAL2->currentDisplay->renderer);
    }

    return error;
}

int clickWindow(SDL_MouseButtonEvent button){
    PtrElement *e;
    ListPtrElement *lp;
    ListDCElement *ldc;
    double newX,newY,c = 1,s = 0,xtmp,prX,prY;
    double rot = 0.f;
    int error = 1;
    int x = button.x, y = button.y;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->currentDisplay->events.onClick){
            _windows_SANDAL2->currentDisplay->events.onClick(button.button);
        }
    
        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->currentDisplay->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->currentDisplay->close){
                    if(!e->deleted && isDisplaiedElement(e->element)){
                        newX=x*_windows_SANDAL2->currentDisplay->initWidth/_windows_SANDAL2->currentDisplay->width + _windows_SANDAL2->currentDisplay->origin[0];
                        newY=y*_windows_SANDAL2->currentDisplay->initHeight/_windows_SANDAL2->currentDisplay->height + _windows_SANDAL2->currentDisplay->origin[1];
                        if(e->element->rotation != 0. && e->element->coulBlock[0]==-1){
                            if(e->element->rotation != rot){
                                c=cos(-M_PI*e->element->rotation/180.);
                                s=sin(-M_PI*e->element->rotation/180.);
                                rot=e->element->rotation;
                            }
                            prX=e->element->prX*e->element->width+e->element->x;
                            prY=e->element->prY*e->element->height+e->element->y;
                            xtmp=prX+(newX-prX)*c-(newY-prY)*s;
                            newY=prY+(newX-prX)*s+(newY-prY)*c;
                            newX=xtmp;
                        }
                        newX=(newX-e->element->x)/(e->element->width);
                        newY=(newY-e->element->y)/(e->element->height);
                        if(hitListClickable(e->element->hitboxes,newX,newY)){
                            e->element->selected=1;
                            if(e->element->entry){
                                e->element->entry->isSelect=1;
                            }
                            if(e->element->events.onClick){
			      e->element->events.onClick(e->element, button.button);
                            }
                        }else{
			    if(e->element->selected && e->element->events.unSelect){
				e->element->events.unSelect(e->element);
			    }
			    e->element->selected=0;
			    if(e->element->entry){
				e->element->entry->isSelect=0;
			    }
			}
                    }else{
                        if(e->element->selected && e->element->events.unSelect){
                            e->element->events.unSelect(e->element);
                        }
                        e->element->selected=0;
                        if(e->element->entry){
                            e->element->entry->isSelect=0;
                        }
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
        }
        if(_windows_SANDAL2->currentDisplay->close){
            closeWindow();
        }else
            _cleanElement();
    }

    return error;
}

int unclickWindow(SDL_MouseButtonEvent button){
    PtrElement *e;
    ListPtrElement *lp;
    ListDCElement *ldc;
    double newX,newY,c = 1,s = 0,xtmp;
    double rot = 0.f;
    int error = 1;
    int x = button.x, y = button.y;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->currentDisplay->events.unClick){
            _windows_SANDAL2->currentDisplay->events.unClick(button.button);
        }

        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->currentDisplay->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->currentDisplay->close){
                    if(!e->deleted && isDisplaiedElement(e->element)){
                        newX=(x*_windows_SANDAL2->currentDisplay->initWidth/_windows_SANDAL2->currentDisplay->width-e->element->x)/(e->element->width) + _windows_SANDAL2->currentDisplay->origin[0];
                        newY=(y*_windows_SANDAL2->currentDisplay->initHeight/_windows_SANDAL2->currentDisplay->height-e->element->y)/(e->element->height) + _windows_SANDAL2->currentDisplay->origin[1];
                        if(e->element->rotation != 0.f && e->element->coulBlock[0]==-1){
                            if(e->element->rotation != rot){
                                c=cosf(-M_PI*e->element->rotation/180);
                                s=sinf(-M_PI*e->element->rotation/18);
                                rot=e->element->rotation;
                            }
                            xtmp=e->element->prX+(newX-e->element->prX)*c-(newY-e->element->prY)*s;
                            newY=e->element->prY+(newX-e->element->prX)*s+(newY-e->element->prY)*c;
                            newX=xtmp;
                        }
                        if(hitListClickable(e->element->hitboxes,newX,newY)){
                            if(e->element->events.unClick){
			      e->element->events.unClick(e->element,button.button);
                            }
                        }
                    }else if(e->element->entry){
                        if(e->element->selected && e->element->events.unSelect){
                            e->element->events.unSelect(e->element);
                        }
                        e->element->selected=0;
                        e->element->entry->isSelect=0;
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
        }
        if(_windows_SANDAL2->currentDisplay->close){
            closeWindow();
        }else
            _cleanElement();
    }

    return error;
}

int keyPressedWindow(int c){
    PtrElement *e;
    ListPtrElement *lp;
    ListDCElement *ldc;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->currentDisplay->events.keyPress){
            _windows_SANDAL2->currentDisplay->events.keyPress(c);
        }
    
        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->currentDisplay->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->currentDisplay->close){
                    if(!e->deleted && e->element->events.keyPress && (!e->element->entry || e->element->entry->isSelect)){
                        e->element->events.keyPress(e->element,c);
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
        }
        if(_windows_SANDAL2->currentDisplay->close){
            closeWindow();
        }else
            _cleanElement();
    }

    return error;
}

int keyReleasedWindow(int c){
    PtrElement *e;
    ListPtrElement *lp;
    ListDCElement *ldc;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->currentDisplay->events.keyReleased){
            _windows_SANDAL2->currentDisplay->events.keyReleased(c);
        }

        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->currentDisplay->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->currentDisplay->close){
                    if(!e->deleted && e->element->events.keyReleased && (!e->element->entry || e->element->entry->isSelect)){
                        e->element->events.keyReleased(e->element,c);
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
        }
        if(_windows_SANDAL2->currentDisplay->close){
            closeWindow();
        }else
            _cleanElement();
    }

    return error;
}

int onMouseMotionWindow(int x, int y){
    PtrElement *e;
    ListPtrElement *lp;
    ListDCElement *ldc;
    double newX,newY,c = 1,s = 0,xtmp,prX,prY;
    double rot = 0.f;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay && _windows_SANDAL2->currentDisplay->liste){
        error = 0;

        if(_windows_SANDAL2->currentDisplay->events.onMouseMotion){
            _windows_SANDAL2->currentDisplay->events.onMouseMotion(x, y);
        }

        ldc = _windows_SANDAL2->currentDisplay->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->currentDisplay->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->currentDisplay->close){
                    if(!e->deleted && isDisplaiedElement(e->element)){
                        newX=x*_windows_SANDAL2->currentDisplay->initWidth/_windows_SANDAL2->currentDisplay->width + _windows_SANDAL2->currentDisplay->origin[0];
                        newY=y*_windows_SANDAL2->currentDisplay->initHeight/_windows_SANDAL2->currentDisplay->height + _windows_SANDAL2->currentDisplay->origin[1];
                        if(e->element->rotation != 0.f && e->element->coulBlock[0]==-1){
                            if(e->element->rotation != rot){
                                c=cosf(-M_PI*e->element->rotation/180.f);
                                s=sinf(-M_PI*e->element->rotation/180.f);
                                rot=e->element->rotation;
                            }
                            prX=e->element->prX*e->element->width+e->element->x;
                            prY=e->element->prY*e->element->height+e->element->y;
                            xtmp=prX+(newX-prX)*c-(newY-prY)*s;
                            newY=prY+(newX-prX)*s+(newY-prY)*c;
                            newX=xtmp;
                        }
                        newX=(newX-e->element->x)/(e->element->width);
                        newY=(newY-e->element->y)/(e->element->height);
                        if(hitListClickable(e->element->hitboxes,newX,newY)){
                            e->element->selected=1;
                            if(e->element->entry){
                                e->element->entry->isSelect=1;
                            }
                            if(e->element->events.onMouseMotion){
			      e->element->events.onMouseMotion(e->element);
                            }
                        }else{
			    if(e->element->selected && e->element->events.unMouseMotion){
				e->element->events.unMouseMotion(e->element);
			    }
			    e->element->selected=0;
			    if(e->element->entry){
				e->element->entry->isSelect=0;
			    }
			}
                    }else{
                        if(e->element->selected && e->element->events.unSelect){
                            e->element->events.unSelect(e->element);
                        }
                        e->element->selected=0;
                        if(e->element->entry){
                            e->element->entry->isSelect=0;
                        }
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
        }
        if(_windows_SANDAL2->currentDisplay->close){
            closeWindow();
        }else
            _cleanElement();
    }

    return error;
}


int onWheelWindow(int y){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay){
	error = 0;

	/* fait l'action de la fenetre courante */
	if(_windows_SANDAL2->currentDisplay->events.onWheel){
	    _windows_SANDAL2->currentDisplay->events.onWheel(y);
	}
    }
  
    return error;
}

int onFocusedWindow(){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay){
	error = 0;

	/* fait l'action de la fenetre courante */
	if(_windows_SANDAL2->currentDisplay->events.onFocus){
	    _windows_SANDAL2->currentDisplay->events.onFocus();
	}

	_windows_SANDAL2->currentDisplay->focused = 1;
	_windows_SANDAL2->currentDisplay->ticks = SDL_GetTicks();
    }

    return error;
}

int unFocusedWindow(){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->currentDisplay){
	error = 0;

	/* fait l'action de la fenetre courante */
	if(_windows_SANDAL2->currentDisplay->events.unFocus){
	    _windows_SANDAL2->currentDisplay->events.unFocus();
	}
	
	_windows_SANDAL2->currentDisplay->focused = 0;
    }

    return error;
}

unsigned long updateAllWindow(){
    Window * w, * tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        w = _windows_SANDAL2->first;
	tmp = _windows_SANDAL2->currentDisplay;
        do{
            _windows_SANDAL2->currentDisplay = w;
            err = updateWindow() * bit;
            if(!error && err){
                error=1;
            }
            error += (unsigned)err * bit;
            bit *= 2;
            if(w != _windows_SANDAL2->currentDisplay){
		tmp = _windows_SANDAL2->currentDisplay;
            }
	    w = w->next;
        }while(w);
        _windows_SANDAL2->currentDisplay = tmp;
    }

    return error;
}

unsigned long displayAllWindow(){
    Window * w, * tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        w = _windows_SANDAL2->first;
	tmp = _windows_SANDAL2->currentDisplay;
        do{
            _windows_SANDAL2->currentDisplay = w;
            err = displayWindow()*bit;
            if(!error && err){
                error=1;
            }
            error += (unsigned)err*bit;
            bit *= 2;
	    w = w->next;
        }while(w);
        _windows_SANDAL2->currentDisplay = tmp;
    }

    return error;
}
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Gestion d'evenement
 */
static int handleWindowClose(SDL_Event event){
    int quit = 0;
    Window * w;
    Window * tmp = NULL;
    
    if(_windows_SANDAL2 && _windows_SANDAL2->count){
        if(event.type == SDL_QUIT){
            closeAllWindow();
            quit = 1;
        }else{
            w = _windows_SANDAL2->first;
            while(w && SDL_GetWindowID(w->window) != event.window.windowID){
                w = w->next;
            }
            if(w){
                --_windows_SANDAL2->count;
                if(w != _windows_SANDAL2->current){
                    tmp = _windows_SANDAL2->current;
                    _windows_SANDAL2->current = w;
                }
                closeWindow();
                if(tmp){
                    _windows_SANDAL2->current = tmp;
                }
            }
        }
    }else{
	quit = 1;
    }

    return quit;
}
int PollEvent(unsigned long * error){
    SDL_Event       event;
    int             quit    = 0;
    unsigned long   err     = 0;
    Window        * w       = NULL;
    Window        * focused = NULL;

    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_WINDOWEVENT:
	    switch(event.window.event){
	    case SDL_WINDOWEVENT_CLOSE:
	        quit = handleWindowClose(event);
		break;
	    case SDL_WINDOWEVENT_FOCUS_GAINED:
		if(_windows_SANDAL2 && _windows_SANDAL2->first){
		    w = _windows_SANDAL2->first;
		    while(w && SDL_GetWindowID(w->window) != event.window.windowID){
			w = w->next;
		    }
		    if(w){
			_windows_SANDAL2->current = w;
			_windows_SANDAL2->currentDisplay = w;
			err = err|onFocusedWindow();
		    }
		}
		break;
	    case SDL_WINDOWEVENT_FOCUS_LOST:
		if(_windows_SANDAL2 && _windows_SANDAL2->first){
		    w = _windows_SANDAL2->first;
		    while(w && SDL_GetWindowID(w->window) != event.window.windowID){
			w = w->next;
		    }
		    if(w){
			focused = _windows_SANDAL2->first;
			while(focused && !(SDL_GetWindowFlags(focused->window) & (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS))){
			    focused = focused->next;
			}
			_windows_SANDAL2->currentDisplay = w;
			err = err|unFocusedWindow();
			_windows_SANDAL2->current = focused;
			_windows_SANDAL2->currentDisplay = focused;
		    }
		}
		break;
	    }
            break;
        case SDL_QUIT :
	    quit = handleWindowClose(event);
            break;
        case SDL_KEYUP:
            err=err|keyReleasedWindow(event.key.keysym.sym);
            break;
        case SDL_KEYDOWN:
            err=err|keyPressedWindow(event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            err=err|clickWindow(event.button);
            break;
        case SDL_MOUSEBUTTONUP:
            err=err|unclickWindow(event.button);
            break;
	case SDL_MOUSEMOTION:
	  err=err|onMouseMotionWindow(event.motion.x, event.motion.y);
	  break;
	case SDL_MOUSEWHEEL:
	  err=err|onWheelWindow(event.wheel.y);
	  break;
        }
    }

    if(error){
        *error=err;
    }

    return quit;
}
/* ------------------------------------------------------- */
