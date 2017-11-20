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
 * Initialisation et fermeture des outils SDL2
 */
int initAllSDL2(int imageFlags){
    int failedInit=0;

    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        failedInit=1;
    }else if(TTF_Init()){
        SDL_Quit();
        failedInit=3;
    }else if((IMG_Init(imageFlags)&imageFlags)!=imageFlags){
        failedInit=2;
        TTF_Quit();
        SDL_Quit();
    }

    return failedInit;
}

void closeAllSDL2(){
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int initSDL2(){
    int failedInit = 0;
  
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        failedInit=1;
    }

    return failedInit;
}

int initImage(int imageFlags){
    int failedInit = 0;
  
    if((IMG_Init(imageFlags)&imageFlags)!=imageFlags){
        failedInit=1;
    }

    return failedInit;
}

int initText(){
    int failedInit = 0;
  
    if(TTF_Init()){
        failedInit=1;
    }

    return failedInit;
}

void closeSDL2(){
    SDL_Quit();
}

void closeImage(){
    IMG_Quit();
}

void closeText(){
    TTF_Quit();
}
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Creation, modification et suppression des fenetres
 */
static void freeWindowSDL2(WindowSDL2 *fen){
    if(fen){
        if(fen->liste){
            _freeListElementSDL2(fen->liste);
        }
        if(fen->renderer){
            SDL_DestroyRenderer(fen->renderer);
        }
        if(fen->window){
            SDL_DestroyWindow(fen->window);
        }
    }
}

int initWindowSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode){
    WindowSDL2 *fen=(WindowSDL2*)malloc(sizeof(*fen));
    int error = 1;

    fen->window=SDL_CreateWindow(title,
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 width, height,
                                 SDLFlags);
  
    if(fen->window){
        fen->renderer=SDL_CreateRenderer(fen->window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED);

        if(fen->renderer){
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
            fen->events.action=NULL;
            fen->events.onClick=NULL;
            fen->events.unClick=NULL;
            fen->events.keyPress=NULL;
            fen->events.keyReleased=NULL;
            fen->toDelete=0;
            copyColor(fen->background,background);
            fen->liste = _initListElementSDL2();
            fen->current = NULL;
	    fen->stop = 0;
	    fen->state = SDLFlags&SDL_WINDOW_FULLSCREEN;
            if(!fen->liste){
                SDL_DestroyWindow(fen->window);
                SDL_DestroyRenderer(fen->renderer);
                free(fen);
            }else{
                if(!_windows_SANDAL2){
                    _windows_SANDAL2 = (ListWindowSDL2*)malloc(sizeof(*_windows_SANDAL2));
                    if(_windows_SANDAL2){
                        _windows_SANDAL2->first = fen;
                        _windows_SANDAL2->last = fen;
                        _windows_SANDAL2->current = fen;
                        error = 0;
                    }else{
                        SDL_DestroyWindow(fen->window);
                        SDL_DestroyRenderer(fen->renderer);
                        free(fen);
                    }
                }else{
                    _windows_SANDAL2->last->next=fen;
                    _windows_SANDAL2->last=fen;
                }
            }
        }else{
            SDL_DestroyWindow(fen->window);
            free(fen);
        }
    }else{
        free(fen);
    }

    return error;
}

int closeWindowSDL2(){
    WindowSDL2 * f, * tmp;
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        f=_windows_SANDAL2->current;
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
        freeWindowSDL2(f);
        if(!_windows_SANDAL2->first){
            free(_windows_SANDAL2);
            _windows_SANDAL2 = NULL;
        }
    }

    return error;
}

int shouldCloseWindowSDL2(){
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        _windows_SANDAL2->current->close=1;
        error=0;
    }

    return error;
}

int closeAllWindowSDL2(){
    WindowSDL2 *f, *tmp;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->first){
        error = 0;
        f=_windows_SANDAL2->first;
        while(f){
            tmp=f;
            f=f->next;
            freeWindowSDL2(tmp);
        }
        free(_windows_SANDAL2);
        _windows_SANDAL2=NULL;
    }

    return error;
}

int toggleFullScreenWindowSDL2(void){
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
	if(_windows_SANDAL2->current->state == SDL_WINDOW_FULLSCREEN){
	    SDL_SetWindowFullscreen(_windows_SANDAL2->current->window, 0);
	    _windows_SANDAL2->current->state = 0;
	}else{
	    SDL_SetWindowFullscreen(_windows_SANDAL2->current->window, SDL_WINDOW_FULLSCREEN);
	    _windows_SANDAL2->current->state = SDL_WINDOW_FULLSCREEN;
	}
    }

    return _windows_SANDAL2 && _windows_SANDAL2->current;
}

int isFullScreenWindowSDL2(void){
    return _windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->state == SDL_WINDOW_FULLSCREEN;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Fenetre SDL2
 */
int updateWindowSDL2(){
    PtrElementSDL2 **ele;
    ListPtrElementSDL2 *lp;
    ListDCElementSDL2 *ldc;
    unsigned i;
    int error=1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        error = 0;
        /* update de la taille de la fenetre */
        SDL_GetWindowSize(_windows_SANDAL2->current->window,&(_windows_SANDAL2->current->width),&(_windows_SANDAL2->current->height));

        /* update le code d'affichage et la liste courante a afficher */
        if(_windows_SANDAL2->current->displayToChange){
            ldc = _windows_SANDAL2->current->liste->first;
            while(ldc && ldc->code < _windows_SANDAL2->current->newDisplayCode)
                ldc = ldc->next;
            if(ldc && ldc->code == _windows_SANDAL2->current->newDisplayCode)
                _windows_SANDAL2->current->current = ldc;
            else
                _windows_SANDAL2->current->current = NULL;
            _windows_SANDAL2->current->displayToChange = 0;
            _windows_SANDAL2->current->displayCode = _windows_SANDAL2->current->newDisplayCode;
        }

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->current->events.action){
            _windows_SANDAL2->current->events.action();
        }
    
        /* recherche de la liste d'element ayant le bon code de display */
        ldc = _windows_SANDAL2->current->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->current->close){
                ele=&(lp->first);
                while(*ele && !_windows_SANDAL2->current->close){
                    if(isDisplaied((*ele)->element)){
                        if((*ele)->element->events.action){
                            (*ele)->element->events.action((*ele)->element);
                        }
                        if((*ele)->element->animation->size && (*ele)->element->animation->size){
                            (*ele)->element->animation->current->wasChanged++;
                            if((*ele)->element->animation->current->sens && (*ele)->element->animation->current->wasChanged >= (*ele)->element->animation->current->current->lifespan){
                                i=0;
                                do{
                                    if((*ele)->element->animation->current->sens == -1){
                                        previousSpriteElementSDL2((*ele)->element);
                                    }else{
                                        nextSpriteElementSDL2((*ele)->element);
                                    }
                                    ++i;
                                }while(i<(*ele)->element->animation->current->size && !(*ele)->element->animation->current->current->lifespan);
                                if((*ele)->element->animation->current->current == (*ele)->element->animation->current->first && (*ele)->element->events.endSprite){
                                    (*ele)->element->events.endSprite((*ele)->element,(*ele)->element->animation->current->code);
                                }
                                (*ele)->element->animation->current->wasChanged = 0;
                            }
                        }
                        if((*ele)->element->rotSpeed != 0.f){
                            (*ele)->element->rotation = ((*ele)->element->rotation + (*ele)->element->rotSpeed > 360.f ? (*ele)->element->rotation + (*ele)->element->rotSpeed - 360.f : (*ele)->element->rotation + (*ele)->element->rotSpeed);
                        }
                    }
		    if(_windows_SANDAL2->current->stop)
			break;
		    else
			ele=&((*ele)->next);
                }
		if(_windows_SANDAL2->current->stop)
		    break;
		else
		    lp=lp->next;
            }
	    _windows_SANDAL2->current->stop = 0;
            if(_windows_SANDAL2->current->close){
                closeWindowSDL2();
            }else{
                _cleanElementSDL2();
            }
        }
    }

    return error;
}

int displayWindowSDL2(){
    PtrElementSDL2 *ele;
    ListPtrElementSDL2 * lp;
    ListDCElementSDL2 * ldc;
    SDL_Rect r,sr, *srect;
    int coul[4];
    SDL_Point p;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        error=0;
        /* fond de la fenetre */
        copyColor(coul,_windows_SANDAL2->current->background);
        SDL_SetRenderDrawColor(_windows_SANDAL2->current->renderer,coul[0],coul[1],coul[2],coul[3]);
        SDL_RenderClear(_windows_SANDAL2->current->renderer);
        
        ldc = _windows_SANDAL2->current->current;
        if(ldc){
            lp=ldc->first;
            while(lp){
                /* affichage des elements */
                ele=lp->first;
                while(ele){
                    if(isDisplaied(ele->element)){
                        r.x=(ele->element->x - _windows_SANDAL2->current->origin[0])*_windows_SANDAL2->current->width/_windows_SANDAL2->current->initWidth;
                        r.y=(ele->element->y - _windows_SANDAL2->current->origin[1])*_windows_SANDAL2->current->height/_windows_SANDAL2->current->initHeight;
                        r.w=ele->element->width*_windows_SANDAL2->current->width/_windows_SANDAL2->current->initWidth;
                        r.h=ele->element->height*_windows_SANDAL2->current->height/_windows_SANDAL2->current->initHeight;
                        /* affichage du block */
                        if(ele->element->coulBlock[0]!=-1 && !ele->element->image){
                            if(!cmpCoul(coul,ele->element->coulBlock)){
                                SDL_SetRenderDrawColor(_windows_SANDAL2->current->renderer,coul[0],coul[1],coul[2],coul[3]);
                            }
                            SDL_RenderFillRect(_windows_SANDAL2->current->renderer,&r);
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
                            if(ele->element->rotation == 0.f){
                                SDL_RenderCopy(_windows_SANDAL2->current->renderer,ele->element->image,srect,&r);
                            }else{
                                p.x=(int)(ele->element->prX*ele->element->width*_windows_SANDAL2->current->width/_windows_SANDAL2->current->initWidth);
                                p.y=(int)(ele->element->prY*ele->element->height*_windows_SANDAL2->current->height/_windows_SANDAL2->current->initHeight);
                                SDL_RenderCopyEx(_windows_SANDAL2->current->renderer,ele->element->image,srect,&r,(double)ele->element->rotation,&p,SDL_FLIP_NONE);
                            }
                        }
                        /* affichage du texte */
                        if(ele->element->font){
                            r.x+=r.w*(1.0-ele->element->textSize)/2;
                            r.y+=r.h*(1.0-ele->element->textSize)/2;
                            r.w*=ele->element->textSize;
                            r.h*=ele->element->textSize;
                            if(ele->element->rotation == 0.f || (ele->element->coulBlock[0]!=-1 && !ele->element->image)){
                                SDL_RenderCopy(_windows_SANDAL2->current->renderer,ele->element->font->texture,NULL,&r);
                            }else{
                                p.x=(int)(ele->element->textSize*ele->element->prX*ele->element->width*_windows_SANDAL2->current->width/_windows_SANDAL2->current->initWidth);
                                p.y=(int)(ele->element->textSize*ele->element->prY*ele->element->height*_windows_SANDAL2->current->height/_windows_SANDAL2->current->initHeight);
                                SDL_RenderCopyEx(_windows_SANDAL2->current->renderer,ele->element->font->texture,NULL,&r,(double)ele->element->rotation,&p,SDL_FLIP_NONE);
                            }
                        }
                    }
                    ele=ele->next;
                }
                lp=lp->next;
            }
        }
        SDL_RenderPresent(_windows_SANDAL2->current->renderer);
    }

    return error;
}

int clickWindowSDL2(int x,int y){
    PtrElementSDL2 *e;
    ListPtrElementSDL2 *lp;
    ListDCElementSDL2 *ldc;
    float newX,newY,c,s,xtmp,prX,prY;
    float rot = 0.f;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->current->events.onClick){
            _windows_SANDAL2->current->events.onClick();
        }
    
        ldc = _windows_SANDAL2->current->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->current->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->current->close){
                    if(e->element && isDisplaied(e->element)){
                        newX=x*_windows_SANDAL2->current->initWidth/_windows_SANDAL2->current->width + _windows_SANDAL2->current->origin[0];
                        newY=y*_windows_SANDAL2->current->initHeight/_windows_SANDAL2->current->height + _windows_SANDAL2->current->origin[1];
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
                            if(e->element->events.onClick){
                                e->element->events.onClick(e->element);
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
            if(_windows_SANDAL2->current->close){
                closeWindowSDL2();
            }
        }
    }

    return error;
}

int unclickWindowSDL2(int x,int y){
    PtrElementSDL2 *e;
    ListPtrElementSDL2 *lp;
    ListDCElementSDL2 *ldc;
    float newX,newY,c,s,xtmp;
    float rot = 0.f;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->current->events.unClick){
            _windows_SANDAL2->current->events.unClick();
        }

        ldc = _windows_SANDAL2->current->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->current->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->current->close){
                    if(isDisplaied(e->element)){
                        newX=(x*_windows_SANDAL2->current->initWidth/_windows_SANDAL2->current->width-e->element->x)/(e->element->width) + _windows_SANDAL2->current->origin[0];
                        newY=(y*_windows_SANDAL2->current->initHeight/_windows_SANDAL2->current->height-e->element->y)/(e->element->height) + _windows_SANDAL2->current->origin[1];
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
                                e->element->events.unClick(e->element);
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
            if(_windows_SANDAL2->current->close){
                closeWindowSDL2();
            }
        }
    }

    return error;
}

int keyPressedWindowSDL2(char c){
    PtrElementSDL2 *e;
    ListPtrElementSDL2 *lp;
    ListDCElementSDL2 *ldc;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->current->events.keyPress){
            _windows_SANDAL2->current->events.keyPress(c);
        }
    
        ldc = _windows_SANDAL2->current->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->current->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->current->close){
                    if(e->element->events.keyPress && (!e->element->entry || e->element->entry->isSelect)){
                        e->element->events.keyPress(e->element,c);
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
            if(_windows_SANDAL2->current->close){
                closeWindowSDL2();
            }
        }
    }

    return error;
}

int keyReleasedWindowSDL2(char c){
    PtrElementSDL2 *e;
    ListPtrElementSDL2 *lp;
    ListDCElementSDL2 *ldc;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        error = 0;

        /* fait l'action de la fenetre courante */
        if(_windows_SANDAL2->current->events.keyReleased){
            _windows_SANDAL2->current->events.keyReleased(c);
        }

        ldc = _windows_SANDAL2->current->current;
        if(ldc){
            lp=ldc->first;
            while(lp && !_windows_SANDAL2->current->close){
                e=lp->first;
                while(e && !_windows_SANDAL2->current->close){
                    if(e->element->events.keyReleased && (!e->element->entry || e->element->entry->isSelect)){
                        e->element->events.keyReleased(e->element,c);
                    }
                    e=e->next;
                }
                lp=lp->next;
            }
            if(_windows_SANDAL2->current->close){
                closeWindowSDL2();
            }
        }
    }

    return error;
}


unsigned long updateAllWindowSDL2(){
    WindowSDL2 * w, * tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2){
        error = 0;
        w=_windows_SANDAL2->current;
        initIteratorWindowSDL2();
        do{
            tmp=_windows_SANDAL2->current;
            err=updateWindowSDL2()*bit;
            if(!error && err){
                error=1;
            }
            error+=(unsigned)err*bit;
            bit*=2;
            if(tmp==_windows_SANDAL2->current){
                nextWindowSDL2();
            }
        }while(_windows_SANDAL2->current);
        _windows_SANDAL2->current=w;
    }

    return error;
}

unsigned long displayAllWindowSDL2(){
    WindowSDL2 * w;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2){
        error = 0;
        w=_windows_SANDAL2->current;
        initIteratorWindowSDL2();
        do{
            err=displayWindowSDL2()*bit;
            if(!error && err){
                error=1;
            }
            error+=(unsigned)err*bit;
            bit*=2;
        }while(!nextWindowSDL2());
        _windows_SANDAL2->current=w;
    }

    return error;
}

unsigned long clickAllWindowSDL2(int x,int y){
    WindowSDL2 * w,* tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2){
        error = 0;
        w=_windows_SANDAL2->current;
        initIteratorWindowSDL2();
        do{
            tmp=_windows_SANDAL2->current;
            err=clickWindowSDL2(x,y)*bit;
            if(!error && err){
                error=1;
            }
            error+=(unsigned)err*bit;
            bit*=2;
            if(tmp==_windows_SANDAL2->current){
                nextWindowSDL2();
            }
        }while(_windows_SANDAL2->current);
        _windows_SANDAL2->current=w;
    }

    return error;
}

unsigned long unclickAllWindowSDL2(int x,int y){
    WindowSDL2 * w, *tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2){
        error = 0;
        w=_windows_SANDAL2->current;
        initIteratorWindowSDL2();
        do{
            tmp=_windows_SANDAL2->current;
            err=unclickWindowSDL2(x,y)*bit;
            if(!error && err){
                error=1;
            }
            error+=(unsigned)err*bit;
            bit*=2;
            if(tmp==_windows_SANDAL2->current){
                nextWindowSDL2();
            }
        }while(_windows_SANDAL2->current);
        _windows_SANDAL2->current=w;
    }

    return error;
}

unsigned long keyPressedAllWindowSDL2(char c){
    WindowSDL2 * w, *tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2){
        error = 0;
        w=_windows_SANDAL2->current;
        initIteratorWindowSDL2();
        do{
            tmp=_windows_SANDAL2->current;
            err=keyPressedWindowSDL2(c)*bit;
            if(!error && err){
                error=1;
            }
            error+=(unsigned)err*bit;
            bit*=2;
            if(tmp==_windows_SANDAL2->current){
                nextWindowSDL2();
            }
        }while(_windows_SANDAL2->current);
        _windows_SANDAL2->current=w;
    }

    return error;
}

unsigned long keyReleasedAllWindowSDL2(char c){
    WindowSDL2 * w, *tmp;
    unsigned long error = 1;
    int err;
    int bit = 2;
  
    if(_windows_SANDAL2){
        error = 0;
        w=_windows_SANDAL2->current;
        initIteratorWindowSDL2();
        do{
            tmp=_windows_SANDAL2->current;
            err=keyReleasedWindowSDL2(c)*bit;
            if(!error && err){
                error=1;
            }
            error+=(unsigned)err*bit;
            bit*=2;
            if(tmp==_windows_SANDAL2->current){
                nextWindowSDL2();
            }
        }while(_windows_SANDAL2->current);
        _windows_SANDAL2->current=w;
    }

    return error;
}
/* ------------------------------------------------------- */




/* ------------------------------------------------------- 
 * Gestion d'evenement
 */
int PollEventSDL2(unsigned long * error){
    SDL_Event event;
    int quit = 0;
    unsigned long err = 0;

    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_CLOSE)  {
                quit = 1;
            }
            break;
        case SDL_QUIT :   
            quit = 1;
            break;
        case SDL_KEYUP:
            err=err|keyReleasedWindowSDL2(event.key.keysym.sym);
            break;
        case SDL_KEYDOWN:
            err=err|keyPressedWindowSDL2(event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            err=err|clickWindowSDL2(event.button.x,event.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            err=err|unclickWindowSDL2(event.button.x,event.button.y);
            break;
        }
    }

    if(error){
        *error=err;
    }

    return quit;
}
/* ------------------------------------------------------- */
