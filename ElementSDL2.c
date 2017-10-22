#include "ElementSDL2.h"

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
 * Liste d'elements SDL2 avec display code commun
 */
static ListPtrElementSDL2* initListPtrElementSDL2(int plan){
    ListPtrElementSDL2 *l=(ListPtrElementSDL2*)malloc(sizeof(*l));

    if(l){
        l->first=NULL;
        l->last=NULL;
        l->current=NULL;
        l->next=NULL;
        l->code=plan;
    }

    return l;
}

static void freeListPtrElementSDL2(ListPtrElementSDL2* l){
    if(l){
        while(l->first){
            l->current=l->first->next;
            free(l->first);
            l->first=l->current;
        }
        free(l);
    }
}

static int addPtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e){
    DisplayCode *d;
    PtrElementSDL2 *p;
    int error = 1;
  
    if(l && e){
        d=e->codes->first;
        while(d && d->plan > l->code){
            d=d->next;
        }
        if(d && d->plan==l->code){
            p=(PtrElementSDL2*)malloc(sizeof(*p));
            if(p){
                if(l->last){
                    l->last->next=p;
                }else{
                    l->first=p;
                }
                l->last=p;
                p->next=NULL;
                p->element=e;
                error = 0;
            }
        }
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (plan) d'element, contenant le code 
 * d'affichage
 */
static ListDCElementSDL2* initListDCElementSDL2(int displayCode){
    ListDCElementSDL2 * l =(ListDCElementSDL2*)malloc(sizeof(*l));

    if(l){
        l->first=NULL;
        l->current=NULL;
        l->next=NULL;
        l->code=displayCode;
    }

    return l;
}

static void freeListDCElementSDL2(ListDCElementSDL2* l){
    ListPtrElementSDL2 *lp,*lptmp;

    if(l){
        lp=l->first;
        while(lp){
            lptmp=lp->next;
            freeListPtrElementSDL2(lp);
            lp=lptmp;
        }
    }
}

static int removeDCElementSDL2(ListDCElementSDL2** l,ElementSDL2 *e){
    ListPtrElementSDL2 **lp;
    PtrElementSDL2 **pe, *etmp, **pte;
    int error = 1;
  
    if(e && l){
        error = 0;
        while(*l){
            lp=&((*l)->first);
            while(*lp){
                pte=NULL;
                pe=&((*lp)->first);
                while(*pe){
                    if((*pe)->element==e){
                        if(*pe==(*lp)->last){
                            if(pte){
                                (*lp)->last=*pte;
                            }else{
                                (*lp)->last=NULL;
                            }
                        }
                        if(*pe==(*lp)->current){
                            (*lp)->current=(*pe)->next;
                        }
                        etmp=(*pe)->next;
                        free(*pe);
                        *pe=etmp;
                    }else{
                        pte=pe;
                        pe=&((*pe)->next);
                    }
                }
                lp=&((*lp)->next);
            }
            l=&((*l)->next);
        }
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (code d'affichage) de liste (plan) 
 * d'element
 */
ListElementSDL2* _initListElementSDL2(){
    ListElementSDL2 *l=(ListElementSDL2*)malloc(sizeof(*l));
  
    if(l){
        l->first=NULL;
        l->currentDCIterator=NULL;
        l->currentPIterator=NULL;
    }
  
    return l;
}

void _freeListElementSDL2(ListElementSDL2 *l){
    ListDCElementSDL2 *lp,*ltmp;

    if(l){
        lp=l->first;
        while(lp){
            ltmp=lp->next;
            freeListDCElementSDL2(lp);
            lp=ltmp;
        }
        free(l);
    }
}

int addElementSDL2(ElementSDL2* e){
    DisplayCode *d;
    ListDCElementSDL2 ** ldc, *dctmp;
    ListPtrElementSDL2 ** lp, *ptmp;
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste && e && e->codes){
        error = 0;
        d=e->codes->first;
        ldc=&(_windows_SANDAL2->current->liste->first);
        while(d){
            while(*ldc && (*ldc)->code < d->code){
                ldc=&((*ldc)->next);
            }
            if(!*ldc){
                *ldc=initListDCElementSDL2(d->code);
                if(d->code == _windows_SANDAL2->current->displayCode && !(_windows_SANDAL2->current->current))
                    _windows_SANDAL2->current->current = *ldc;
                lp=&((*ldc)->first);
                *lp=initListPtrElementSDL2(d->plan);
            }else if((*ldc)->code!=d->code){
                dctmp=initListDCElementSDL2(d->code);
                if(d->code == _windows_SANDAL2->current->displayCode && !(_windows_SANDAL2->current->current))
                    _windows_SANDAL2->current->current = dctmp;
                dctmp->next=(*ldc);
                (*ldc)=dctmp;
                lp=&((*ldc)->first);
                *lp=initListPtrElementSDL2(d->plan);
            }else{
                lp=&((*ldc)->first);
                while(*lp && (*lp)->code > d->plan){
                    lp=&((*lp)->next);
                }
                if(!*lp){
                    *lp=initListPtrElementSDL2(d->plan);
                }else if((*lp)->code != d->plan){
                    ptmp=*lp;
                    *lp=initListPtrElementSDL2(d->plan);
                    (*lp)->next=ptmp;
                }
            }
            addPtrElementSDL2(*lp,e);
            d=d->next;
        }
        e->parent=_windows_SANDAL2->current;
    }

    return error;
}

void _cleanElementSDL2(){
    PtrElementSDL2 **e, *etmp;
    ListPtrElementSDL2 **lp, *ptmp;
    ListDCElementSDL2 **ldc, *dctmp;
    ElementSDL2 *ee;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        ldc=&(_windows_SANDAL2->current->liste->first);
        while(*ldc && _windows_SANDAL2->current->toDelete){
            lp=&((*ldc)->first);
            while(*lp && _windows_SANDAL2->current->toDelete){
                e=&((*lp)->first);
                while(*e && _windows_SANDAL2->current->toDelete){
                    switch((*e)->element->delete-((*e)->element->delete==2 && (*e)->element->codes->size==1)){
                    case 1:
                        ee=(*e)->element;
                        removeDCElementSDL2(ldc,ee);
                        _windows_SANDAL2->current->toDelete-=(ee->codes?ee->codes->size:1);
                        _freeElementSDL2(ee);
                        break;
                    case 2:
                        if((*ldc)->code==(*e)->element->deleteCode){
                            etmp=*e;
                            (*e)->element->codes->size--;
                            *e=(*e)->next;
                            free(etmp);
                            _windows_SANDAL2->current->toDelete--;
                        }else{
                            e=&((*e)->next);
                        }
                        break;
                    case 3:
                        if((*lp)->code==(*e)->element->deleteCode){
                            etmp=*e;
                            *e=(*e)->next;
                            free(etmp);
                            _windows_SANDAL2->current->toDelete--;
                        }else{
                            e=&((*e)->next);
                        }
                        break;
                    default:
                        e=&((*e)->next);
                    }
                }
                if(!(*lp)->first){
                    ptmp=(*lp)->next;
                    if(*lp == _windows_SANDAL2->current->liste->currentPIterator){
                        _windows_SANDAL2->current->liste->currentPIterator = ptmp;
                    }
                    free(*lp);
                    *lp=ptmp;
                }else{
                    lp=&((*lp)->next);
                }
            }
            if(!(*ldc)->first){
                if((*ldc)->code == _windows_SANDAL2->current->displayCode)
                    _windows_SANDAL2->current->current = NULL;
                dctmp=(*ldc)->next;
                if(*ldc == _windows_SANDAL2->current->liste->currentDCIterator){
                    _windows_SANDAL2->current->liste->currentDCIterator = dctmp;
                }
                free(*ldc);
                *ldc=dctmp;
            }else{
                ldc=&((*ldc)->next);
            }
        }
        _windows_SANDAL2->current->toDelete=0;
    }
}

int removeElementSDL2(ElementSDL2 *e){
    int error = 1;
  
    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        e->delete=1;
        e->parent->toDelete++;
        error = 0;
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element creation, freeing and informations
 */
void _freeElementSDL2(ElementSDL2 *e){
    if(e){
        if(e->codes){
            freeListDisplayCode(e->codes);
        }
        if(e->image){
            SDL_DestroyTexture(e->image);
        }
        if(e->entry){
            free(e->entry);
        }
        if(e->data && e->freeData){
            e->freeData(e->data);
        }
        if(e->font){
            freeFontSDL2(e->font);
        }
        if(e->interactions){
            freeListPtrElementSDL2(e->interactions);
        }
        if(e->hitboxes){
            freeListClickable(e->hitboxes);
        }
        if(e->animation){
            freeListAnimation(e->animation);
        }
        free(e);
    }    
}

ElementSDL2* createBlock(float x,float y,float width,float height,int couleur[4],int displayCode,int plan){
    ElementSDL2 *e = NULL;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=(ElementSDL2*)malloc(sizeof(*e));
        if(e){
            e->delete=0;
            e->deleteCode=0;
            e->selected=0;
            e->x=x;
            e->y=y;
            e->width=width;
            e->height=height;
            e->prX=.5f;
            e->prY=.5f;
            e->rotation=0.f;
            e->rotSpeed=0.f;
            copyColor(e->coulBlock,couleur);
            e->codes=initListDisplayCode();
            addDisplayCode(e->codes,displayCode,1,plan);
            e->animation=initListAnimation();
            e->freeData=NULL;
            e->events.action=NULL;
            e->events.onClick=NULL;
            e->events.unClick=NULL;
            e->events.keyPress=NULL;
            e->events.keyReleased=NULL;
            e->events.unSelect=NULL;
            e->events.endSprite=NULL;
            e->font=NULL;
            e->entry=NULL;
            e->interactions=NULL;
            e->image=NULL;
            e->hitboxes = initListClickable();
            e->data=NULL;
            if(addElementSDL2(e)){
                _freeElementSDL2(e);
                e=NULL;
            }
        }
    }

    return e;
}

ElementSDL2* createTexte(float x,float y,float width,float height,char * font,char * text,int textColor[4],int quality,int displayCode,int plan){
    ElementSDL2 *e=NULL;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=(ElementSDL2*)malloc(sizeof(*e));
        if(e){
            e->delete=0;
            e->deleteCode=0;
            e->selected=0;
            e->x=x;
            e->y=y;
            e->width=width;
            e->height=height;
            e->prX=.5f;
            e->prY=.5f;
            e->rotation=0.f;
            e->rotSpeed=0.f;
            e->textSize=1.0f;
            e->animation=initListAnimation();
            e->image=NULL;
            e->entry=NULL;
            e->interactions=NULL;
            e->hitboxes = initListClickable();
            e->codes=NULL;
            e->font=createFontSDL2(font,text,textColor,quality);
            e->data=NULL;
            if(e->font){
                e->codes=initListDisplayCode();
                addDisplayCode(e->codes,displayCode,1,plan);
                e->coulBlock[0]=-1;
                e->freeData=NULL;
                e->events.action=NULL;
                e->events.onClick=NULL;
                e->events.unClick=NULL;
                e->events.keyPress=NULL;
                e->events.keyReleased=NULL;
                e->events.unSelect=NULL;
                e->events.endSprite=NULL;
                e->data=NULL;
                if(addElementSDL2(e)){
                    _freeElementSDL2(e);
                    e=NULL;
                }
            }else{
                _freeElementSDL2(e);
                e=NULL;
            }
        }
    }

    return e;
}

ElementSDL2* createImage(float x,float y,float width,float height,char *image,int displayCode,int plan){
    ElementSDL2 *e=NULL;
    SDL_Surface *s;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        s=IMG_Load(image);
  
        if(s){
            e=(ElementSDL2*)malloc(sizeof(*e));
            if(e){
                e->delete=0;
                e->deleteCode=0;
                e->selected=0;
                e->x=x;
                e->y=y;
                e->width=width;
                e->height=height;
                e->prX=.5f;
                e->prY=.5f;
                e->rotation=0.f;
                e->rotSpeed=0.f;
                e->animation=initListAnimation();
                e->image=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
                e->codes=initListDisplayCode();
                addDisplayCode(e->codes,displayCode,1,plan);
                e->coulBlock[0]=-1;
                e->events.action=NULL;
                e->events.onClick=NULL;
                e->events.unClick=NULL;
                e->events.keyPress=NULL;
                e->events.keyReleased=NULL;
                e->events.unSelect=NULL;
                e->events.endSprite=NULL;
                e->freeData=NULL;
                e->font=NULL;
                e->entry=NULL;
                e->interactions=NULL;
                e->hitboxes = initListClickable();
                e->data=NULL;
                if(addElementSDL2(e)){
                    _freeElementSDL2(e);
                    e=NULL;
                }
            }
            SDL_FreeSurface(s);
        }
    }

    return e;
}

ElementSDL2* createButton(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int quality,int couleurBlock[4],int displayCode,int plan){
    ElementSDL2 *e = NULL;
    FontSDL2 * f;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createBlock(x,y,width,height,couleurBlock,displayCode,plan);
        if(e){
            e->textSize=texteSize/100.f;
            f=createFontSDL2(font,text,textColor,quality);
            if(f){
                e->font=f;
            }else{
                removeElementSDL2(e);
                _freeElementSDL2(e);
                e=NULL;
            }
        }
    }

    return e;
}

ElementSDL2* createButtonImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int quality,char *image,int displayCode,int plan){
    ElementSDL2 *e = NULL;
    FontSDL2 * f;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createImage(x,y,width,height,image,displayCode,plan);
        if(e){
            e->textSize=texteSize/100.f;
            f=createFontSDL2(font,text,textColor,quality);
            if(f){
                e->font=f;
            }else{
                removeElementSDL2(e);
                _freeElementSDL2(e);
                e=NULL;
            }
        }
    }

    return e;
}

ElementSDL2* createEntry(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int quality,int couleurBlock[4],int displayCode,int plan,int min,int max,int isScripted){
    ElementSDL2 *e = NULL;
    EntrySDL2 *ent;
    int i;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createButton(x,y,width,height,texteSize,font,text,textColor,quality,couleurBlock,displayCode,plan);
        if(e){
            ent=(EntrySDL2*)malloc(sizeof(*ent));
            if(ent){
                ent->size_min=min;
                ent->size_max=max;
                ent->isSelect=0;
                ent->isScripted=isScripted;
                PFREE(e->font->text);
                e->font->text=(char*)malloc((max+1)*sizeof(*(e->font->text)));
                if(e->font->text){
                    for(i=0;i<max;++i){
                        e->font->text[i]=' ';
                    }
                    e->font->text[max]='\0';
                    e->entry=ent;
                    ent->size=0;
                }else{
                    removeElementSDL2(e);
                    _freeElementSDL2(e);
                    e=NULL;
                }
            }else{
                removeElementSDL2(e);
                _freeElementSDL2(e);
                e=NULL;
            }
        }
    }
  
    return e;  
}

ElementSDL2* createEntryImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int quality,char *image,int displayCode,int plan,int min,int max,int isScripted){
    ElementSDL2 *e = NULL;
    EntrySDL2 *ent;
    int i;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createButtonImage(x,y,width,height,texteSize,font,text,textColor,quality,image,displayCode,plan);
        if(e){
            ent=(EntrySDL2*)malloc(sizeof(*ent));
            if(ent){
                ent->size_min=min;
                ent->size_max=max;
                ent->isSelect=0;
                ent->isScripted=isScripted;
                PFREE(e->font->text);
                e->font->text=(char*)malloc((max+1)*sizeof(*(e->font->text)));
                if(e->font->text){
                    for(i=0;i<max;++i){
                        e->font->text[i]=' ';
                    }
                    e->font->text[max]='\0';
                    e->entry=ent;
                    ent->size=0;
                }else{
                    removeElementSDL2(e);
                    _freeElementSDL2(e);
                    e=NULL;
                }
            }else{
                removeElementSDL2(e);
                _freeElementSDL2(e);
                e=NULL;
            }
        }
    }
  
    return e;  
}

int isDisplaied(ElementSDL2 *e){
    int display = (e && !(e->delete) && _windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current == e->parent && e->codes);
    DisplayCode *d;

    if(display){
        d=e->codes->first;
        while(d && d->code<_windows_SANDAL2->current->displayCode){
            d=d->next;
        }
        display=d && d->code==_windows_SANDAL2->current->displayCode && d->isDisplaied;
    }
  
    return display;
}

int getCoordElementSDL2(ElementSDL2* e,float* x,float* y){
    int error = 1;

    if(e){
        if(x){
            *x=e->x;
        }
        if(y){
            *y=e->y;
        }
        error = 0;
    }

    return error;
}

int getAngleElementSDL2(ElementSDL2* e,float* a){
    int error = 1;

    if(e){
        if(a){
            *a=e->rotation;
        }
        error=0;
    }

    return error;
}

int getDimensionElementSDL2(ElementSDL2* e,float* w,float * h){
    int error = 1;

    if(e){
        if(w){
            *w=e->width;
        }
        if(h){
            *h=e->height;
        }
        error=0;
    }

    return error;
}

int getRotationPointElementSDL2(ElementSDL2* e,float *x,float *y){
    int error = 1;

    if(e){
        if(x){
            *x=e->prX;
        }
        if(y){
            *y=e->prY;
        }
        error = 0;
    }

    return error;
}

int getRotationSpeedElementSDL2(ElementSDL2* e,float* s){
    int error = 1;

    if(e){
        if(s){
            *s=e->rotSpeed;
        }
        error = 0;
    }

    return error;
}

int getDataElementSDL2(ElementSDL2* e,void ** data){
    int error = 1;

    if(e){
        error = 0;
        if(data){
            *data=e->data;
        }
    }

    return error;
}

int isSelectedElementSDL2(ElementSDL2 *e, int * select){
    int error = 1;

    if(e){
        error = 0;
        if(select){
            *select = e->selected;
        }
    }

    return error;
}

int getTextStyleElementSDL2(ElementSDL2 *e,int * style){
    int error = 1;

    if(e && e->font){
        error=getStyleFontSDL2(e->font,style);
    }

    return error;
}

int getTextElementSDL2(ElementSDL2 *e,char **s){
    int error = 1;

    if(e && e->font && e->font->text){
        if(s){
	    if(e->entry && e->entry->size){
		*s=(char*)malloc((e->entry->size+1)*sizeof(**s));
		if(*s){
		    strncpy(*s,e->font->text,e->entry->size);
		    (*s)[e->entry->size] = 0;
		}
		error = *s && abs(strncmp(*s,e->font->text,e->entry->size));
	    }else{
		*s=(char*)malloc((strlen(e->font->text)+1)*sizeof(**s));
		strcpy(*s,e->font->text);
		error = *s && abs(strcmp(*s,e->font->text));
	    }
        }else{
            error = 0;
        }
    }

    return error;
}

int getColorElementSDL2(ElementSDL2 * e, int color[4]){
    int error = 1;

    if(e && color){
	error = 0;
	copyColor(color,e->coulBlock);
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * ElementSDL2 modifications
 */
int setFontElementSDL2(ElementSDL2 *e,char * font){
    FontSDL2 *f;
    int color[4];
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        if(e && font && e->font){
            color[0]=e->font->color.r;
            color[1]=e->font->color.g;
            color[2]=e->font->color.b;
            color[3]=e->font->color.a;
            f=createFontSDL2(font,e->font->text,color,e->font->quality);
            if(f){
                freeFontSDL2(e->font);
                e->font=f;
                error = 0;
            }
        }
    }

    return error;
}

int setTextElementSDL2(ElementSDL2 *e,char * text){
    int error = 1;
    int size;
    
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && text && e->font){
	if(e->entry){
	    size = strlen(text);
	    error = changeTextFontSDL2(e->font,(size > e->entry->size_max ? text + size - e->entry->size_max : text));
	    e->entry->size = (size >= e->entry->size_max ? e->entry->size_max : size);
	}else
	    error=changeTextFontSDL2(e->font,text);
    }

    return error;
}

int setTextStyleElementSDL2(ElementSDL2 *e,int style){
    int error = 1;

    if(e && e->font){
        error=setStyleFontSDL2(e->font,style);
    }

    return error;
}

int setColorElementSDL2(ElementSDL2 *e,int color[4]){
    int error = 1;
  
    if(e){
        error = 0;
        copyColor(e->coulBlock,color);
    }

    return error;
}

int setTextColorElementSDL2(ElementSDL2 *e, int color[4]){
    int error = 1;

    if(e && e->font){
        error=changeColorFontSDL2(e->font,color);
    }

    return error;
}

int setTextQualityElementSDL2(ElementSDL2 *e, int quality){
    int error = 1;

    if(e && e->font){
        error = 0;
        e->font->quality=quality;
    }

    return error;
}

int setImageElementSDL2(ElementSDL2 *e,char *image){
    SDL_Surface *s;
    int error=1;
  
    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        if(image){
            s=IMG_Load(image);
            if(s){
                e->image=SDL_CreateTextureFromSurface(_windows_SANDAL2->current->renderer,s);
                SDL_FreeSurface(s);
                error=0;
            }
        }else{
            if(e->image){
                SDL_DestroyTexture(e->image);
            }
            e->image=NULL;
            error=0;
        }
    }

    return error;
}

int setImageTextureElementSDL2(ElementSDL2 *e,SDL_Texture * image){
    int error = 1;

    if(e){
        error = 0;
        e->image=image;
    }

    return error;
}

int replaceElementSDL2(ElementSDL2 *e,float x,float y){
    int error = 1;

    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        e->x=x;
        e->y=y;
        error = 0;
    }

    return error;
}

int moveElementSDL2(ElementSDL2 *e,float x,float y){
    int error = 1;

    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        e->x+=x;
        e->y+=y;
        error = 0;
    }

    return error;
}

int resizeElementSDL2(ElementSDL2 *e,float width,float height){
    int error = 1;

    if(e){
        e->width=width;
        e->height=height;
        error = 0;
    }

    return error;
}

int setTextSize(ElementSDL2 *e,float textSize){
    int error = 1;

    if(e){
        e->textSize=textSize/100.0f;
        error = 0;
    }

    return error;
}

int addDisplayCodeElementSDL2(ElementSDL2 *e,int displayCode, int plan){
    DisplayCode **d, *tmp;
    ListDCElementSDL2 **ldc, *dctmp;
    ListPtrElementSDL2 **lp, *ptmp;
    PtrElementSDL2 *el;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste && e && e->codes){
        d=&(e->codes->first);
        while(*d && (*d)->code<displayCode){
            d=&((*d)->next);
        }
        if(!(*d && (*d)->code==displayCode && (*d)->plan==plan)){ 
            if(*d && (*d)->code == displayCode){
                (*d)->plan=plan;
            }else{
                tmp=(DisplayCode*)malloc(sizeof(*tmp));
                tmp->code=displayCode;
                tmp->plan = plan;
                tmp->isDisplaied = 1;
                tmp->next=*d;
                *d=tmp;
                ldc=&(_windows_SANDAL2->current->liste->first);
                while(*ldc && (*ldc)->code < displayCode){
                    ldc=&((*ldc)->next);
                }
                if(!*ldc || (*ldc)->code != displayCode){
                    dctmp=initListDCElementSDL2(displayCode);
                    if(!_windows_SANDAL2->current->current && _windows_SANDAL2->current->displayCode == displayCode)
                        _windows_SANDAL2->current->current = dctmp;
                    dctmp->next=*ldc;
                    *ldc=dctmp;
                }
                lp=&((*ldc)->first);
                while(*lp && (*lp)->code > plan){
                    lp=&((*lp)->next);
                }
                if((!*lp || (*lp)->code != plan)){
                    ptmp=initListPtrElementSDL2(plan);
                    ptmp->next=*lp;
                    *lp=ptmp;
                }
                el=(PtrElementSDL2*)malloc(sizeof(*el));
                if(el){
                    error = 0;
                    el->next=NULL;
                    el->element=e;
                    if((*lp)->last){
                        (*lp)->last->next=el;
                    }else{
                        (*lp)->first=el;
                    }
                    (*lp)->last=el;
                }
            }
        }
    }

    return error;
}

int removeDisplayCodeElementSDL2(ElementSDL2 *e,int displayCode){
    DisplayCode **d, *tmp;
    ListDCElementSDL2 **ldc;
    ListPtrElementSDL2 **lp;
    PtrElementSDL2 **cour;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste && e && e->codes){
        d=&(e->codes->first);
        while(*d && (*d)->code < displayCode){
            d=&((*d)->next);
        }
        if(*d && (*d)->code==displayCode){
            ldc=&(_windows_SANDAL2->current->liste->first);
            while(*ldc && (*ldc)->code < displayCode){
                ldc=&((*ldc)->next);
            }
            if(*ldc && (*ldc)->code == displayCode){
                lp=&((*ldc)->first);
                while(*lp && (*lp)->code > (*d)->plan){
                    lp = &((*lp)->next);
                }
                if(*lp && (*lp)->code == (*d)->plan){
                    cour=&((*lp)->first);
                    while(*cour && (*cour)->element!=e){
                        cour=&((*cour)->next);
                    }
                    if(*cour){
                        (*cour)->element->delete=2;
                        (*cour)->element->deleteCode=displayCode;
                        _windows_SANDAL2->current->toDelete++;
                        error = 0;
                    }
                }
            }
            tmp=(*d)->next;
            free(*d);
            *d=tmp;
        }
    }

    return error;
}

int setDisplayElementSDL2(ElementSDL2 *e,int displayCode,int isDisplaied){
    DisplayCode *d;
    int error = 1;

    if(e && e->codes){
        d=e->codes->first;
        while(d && d->code<displayCode){
            d=d->next;
        }
        if(d && d->code==displayCode){
            error = 0;
            d->isDisplaied=isDisplaied;
        }
    }

    return error;
}

int setPlanElementSDL2(ElementSDL2 *e,int displayCode,int plan){
    int old;
    DisplayCode *d;
    ListDCElementSDL2 *ldc;
    ListPtrElementSDL2 **lp, *ptmp, **lpNew = NULL;
    PtrElementSDL2 **cour,*tmp;
    int error = 1;

    if(e && _windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        d=e->codes->first;
        while(d && d->code<displayCode){
            d=d->next;
        }
        if(d && d->code==displayCode && d->plan != plan){
            old = d->plan;
            d->plan = plan;
            ldc=_windows_SANDAL2->current->liste->first;
            while(ldc && ldc->code < displayCode){
                ldc=ldc->next;
            }
            if(ldc && ldc->code == displayCode){
                lp=&(ldc->first);
                while(*lp && (*lp)->code > old){
                    if((*lp)->code ==plan){
                        lpNew=lp;
                    }
                    lp=&((*lp)->next);
                }
                cour=&((*lp)->first);
                while(*cour && (*cour)->element!=e){
                    cour=&((*cour)->next);
                }
                if(*cour){
                    (*cour)->element->delete=3;
                    (*cour)->element->deleteCode=old;
                    _windows_SANDAL2->current->toDelete++;
                }
                if(!lpNew){
                    lpNew=lp;
                    while(*lpNew && (*lpNew)->code > plan){
                        lpNew=&((*lpNew)->next);
                    }
                    if(!*lpNew || (*lpNew)->code != plan){
                        ptmp=initListPtrElementSDL2(plan);
                        ptmp->next=*lpNew;
                        *lpNew=ptmp;
                    }
                }
                tmp=(PtrElementSDL2*)malloc(sizeof(*tmp));
                if(tmp){
                    tmp->element=e;
                    tmp->next=(*lpNew)->last;
                    (*lpNew)->last=tmp;
                    error=0;
                }
            }
        }
    }

    return error;
}

int setActionElementSDL2(ElementSDL2 *e,void (*action)(ElementSDL2*)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.action=action;
    }

    return error;
}

int setKeyPressElementSDL2(ElementSDL2 *e,void (*keyPress)(ElementSDL2*,SDL_Keycode c)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.keyPress=keyPress;
    }

    return error;
}

int setKeyReleasedElementSDL2(ElementSDL2 *e,void (*keyReleased)(ElementSDL2*,SDL_Keycode c)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.keyReleased=keyReleased;
    }

    return error;
}

int setUnClickElementSDL2(ElementSDL2 *e,void (*unCLick)(ElementSDL2*)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.unClick=unCLick;
    }

    return error;
}

int setOnClickElementSDL2(ElementSDL2 *e,void (*onCLick)(ElementSDL2*)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.onClick=onCLick;
    }

    return error;
}

int setUnSelectElementSDL2(ElementSDL2 *e,void (*unSelect)(ElementSDL2*)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.unSelect=unSelect;
    }

    return error;
}

int setEndSpriteElementSDL2(ElementSDL2 *e,void (*endSprite)(ElementSDL2*,int)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.endSprite=endSprite;
    }

    return error;
}

int addElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *add){
    PtrElementSDL2 *pe;
    int error = 1;
  
    if(e && add){
        pe=(PtrElementSDL2*)malloc(sizeof(*pe));
        pe->element=add;
        pe->next=NULL;
    
        if(!e->interactions){
            e->interactions=(ListPtrElementSDL2*)malloc(sizeof(*(e->interactions)));
            if(e->interactions){
                e->interactions->first=pe;
                e->interactions->last=pe;
                e->interactions->current=pe;
                error = 0;
            }
        }else{
            if(!e->interactions->first){
                e->interactions->first=pe;
                e->interactions->current=pe;
            }else{
                e->interactions->last->next=pe;
            }
            e->interactions->last=pe;
            error = 0;
        }
    }

    return error;
}

int delElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *del){
    PtrElementSDL2 **pe, *rm, **tmp=NULL;
    int error = 1;

    if(e && e->interactions && del){
        pe=&(e->interactions->first);

        while(*pe && (*pe)->element!=del){
            tmp=pe;
            pe=&((*pe)->next);
        }

        if(*pe && (*pe)->element==del){
            error = 0;
            rm=*pe;
            *pe=(*pe)->next;
            free(rm);
            if(rm == e->interactions->current){
                e->interactions->current=*pe;
            }
            if(rm == e->interactions->last){
                if(tmp){
                    e->interactions->last=*tmp;
                }else{
                    e->interactions->last=NULL;
                }
            }
        }
    }

    return error;
}

int addClickableElementSDL2(ElementSDL2 *e,Clickable *hb,int blocking){
    int error = 1;

    if(e && hb){
        error=addClickable(e->hitboxes,hb,blocking);
    }

    return error;
}

int addRotationSpeedElementSDL2(ElementSDL2 *e,float s){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotSpeed+=s;
        error = 0;
    }

    return error;
}

int setRotationSpeedElementSDL2(ElementSDL2 *e,float s){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotSpeed=s;
        error = 0;
    }

    return error;
}

int addAngleElementSDL2(ElementSDL2 *e,float a){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotation+=a;
        error = 0;
    }

    return error;
}

int setAngleElementSDL2(ElementSDL2 *e,float a){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotation=a;
        error = 0;
    }

    return error;
}

int setRotationPointElementSDL2(ElementSDL2 *e,float x,float y){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->prX=x;
        e->prY=y;
        error = 0;
    }

    return error;
}

int setDataElementSDL2(ElementSDL2 *e,void *data){
    int error = 1;

    if(e){
        error = 0;
        e->data=data;
    }

    return error;
}

int setFreeDataElementSDL2(ElementSDL2 *e,void (*freeData)(void*)){
    int error = 1;

    if(e && freeData){
        e->freeData=freeData;
        error = 0;
    }

    return error;
}

int freeDataElementSDL2(ElementSDL2 *e){
    int error = 1;

    if(e && e->data && e->freeData){
        e->freeData(e->data);
        e->data=NULL;
        error=0;
    }

    return error;
}

int createAnimationElementSDL2(ElementSDL2 *e,int code){
    int error = 1;

    if(e){
        error=createAnimation(e->animation,code);
    }

    return error;
}

int removeAnimationElementSDL2(ElementSDL2 *e,int code){
    int error = 1;

    if(e){
        error=removeAnimation(e->animation,code);
    }

    return error;
}

int addSpriteAnimationElementSDL2(ElementSDL2 *e,int code,int x,int y,int width,int height,int lifespan,int codeS){
    int error = 1;

    if(e){
        error = addSpriteAnimation(e->animation,code,x,y,width,height,lifespan,codeS);
    }
  
    return error;
}

int removeSpriteAnimationElementSDL2(ElementSDL2 *e,int code,int codeS){
    int error = 1;

    if(e){
        error = removeSpriteAnimation(e->animation,code,codeS);
    }

    return error;
}

int setLifeSpanSpriteAnimationElementSDL2(ElementSDL2 * e,int code,int codeS,unsigned lifespan){
    int error = 1;

    if(e){
        error = setLifeSpanSpriteAnimation(e->animation,code,codeS,lifespan);
    }

    return error;
}

int nextSpriteElementSDL2(ElementSDL2 * e){
    int error = 1;

    if(e && e->animation->size && e->animation->current->size){
        e->animation->current->current = e->animation->current->current->next;
        e->animation->current->wasChanged=0;
        error = 0;
    }

    return error;
}

int previousSpriteElementSDL2(ElementSDL2 * e){
    int error = 1;

    if(e && e->animation->size && e->animation->current->size){
        e->animation->current->current = e->animation->current->current->prev;
        e->animation->current->wasChanged=0;
        error = 0;
    }

    return error;
}

int setWaySpriteAnimationElementSDL2(ElementSDL2 * e,int code, int sens){
    int error = 1;
    ListSprite *ls;
    unsigned i=0;

    if(e && (sens == 1 || !sens || sens == -1) && e->animation->size){
        ls=e->animation->first;
        while(i<e->animation->size && ls->code != code){
            ls=ls->next;
            ++i;
        }
        if(i<e->animation->size){
            error = 0;
            ls->sens=sens;
        }
    }

    return error;
}

int nextAnimationElementSDL2(ElementSDL2 * e){
    int error=1;

    if(e && e->animation->size){
        e->animation->current=e->animation->current->next;
        error = 0;
    }

    return error;
}

int previousAnimationElementSDL2(ElementSDL2 * e){
    int error=1;

    if(e && e->animation->size){
        e->animation->current=e->animation->current->prev;
        error = 0;
    }

    return error;
}

int setAnimationElementSDL2(ElementSDL2 *e,int code){
    int error = 1;

    if(e && e->animation){
        error = setAnimation(e->animation,code);
    }

    return error;
}

int setSpriteAnimationElementSDL2(ElementSDL2 *e,int codeS){
    int error = 1;

    if(e && e->animation){
        error = setSpriteAnimation(e->animation,codeS);
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element's list binded to an Element's iterator
 */
int initIteratorElementSDL2(ElementSDL2 *e){
    int succes = 0;
  
    if(e && e->interactions && e->interactions->first){
        e->interactions->current=e->interactions->first;
        succes = 1;
    }

    return succes;
}

ElementSDL2* nextIteratorElementSDL2(ElementSDL2 *e){
    ElementSDL2* next=NULL;
  
    if(e && e->interactions && e->interactions->current){
        next=e->interactions->current->element;
        e->interactions->current=e->interactions->current->next;
    }

    return next;
}
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Element's list iterator
 */
int initIterator(int displayCode){
    int succes = 0;
    ListDCElementSDL2 *lp;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        if(_windows_SANDAL2->current->liste->currentDCIterator && _windows_SANDAL2->current->liste->currentDCIterator->code == displayCode){
            _windows_SANDAL2->current->liste->currentPIterator=_windows_SANDAL2->current->liste->currentDCIterator->first;
            _windows_SANDAL2->current->liste->currentPIterator->current=_windows_SANDAL2->current->liste->currentPIterator->first;
            succes=1;
        }else{
            if(_windows_SANDAL2->current->liste->currentDCIterator && _windows_SANDAL2->current->liste->currentDCIterator->code < displayCode){
                lp=_windows_SANDAL2->current->liste->currentDCIterator;
            }else{
                lp=_windows_SANDAL2->current->liste->first;
            }
            while(lp->code < displayCode){
                lp=lp->next;
            }
            if(lp && lp->code==displayCode){
                _windows_SANDAL2->current->liste->currentDCIterator=lp;
                _windows_SANDAL2->current->liste->currentPIterator=lp->first;
                lp->first->current=lp->first->first;
                succes=1;
            }
        }
    }

    return succes;
}

ElementSDL2* nextElementSDL2(){
    ElementSDL2 *res = NULL;
    PtrElementSDL2 *pres;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste && _windows_SANDAL2->current->liste->currentDCIterator){
        if(_windows_SANDAL2->current->liste->currentPIterator){
            pres=_windows_SANDAL2->current->liste->currentPIterator->current;
            if(pres){
                _windows_SANDAL2->current->liste->currentPIterator->current = _windows_SANDAL2->current->liste->currentPIterator->current->next;
                res=pres->element;
            }else{
                _windows_SANDAL2->current->liste->currentPIterator = _windows_SANDAL2->current->liste->currentPIterator->next;
                if(_windows_SANDAL2->current->liste->currentPIterator){
                    _windows_SANDAL2->current->liste->currentPIterator->current=_windows_SANDAL2->current->liste->currentPIterator->first->next;
                    res=_windows_SANDAL2->current->liste->currentPIterator->first->element;
                }
            }
        }
    }

    return res;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Entry modifications
 */
int changeSizeEntrySDL2(ElementSDL2 *e,int size_min,int size_max){
    char *s;
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry){
        error = 0;
        if(size_min>-1 && size_min<=size_max){
            e->entry->size_min=size_min;
        }
        if(size_max>-1 && size_max>=size_min && size_max!=e->entry->size_max){
            s=(char*)malloc((size_max+1)*sizeof(*s));
            error = 1;
            if(s){
                strncpy(s,e->font->text,size_max);
                s[size_max]='\0';
                PFREE(e->font->text);
                e->font->text=s;
                e->entry->size_max=size_max;
                error=actualizeTextFontSDL2(e->font,e->entry->isScripted);
            }
        }
    }

    return error;
}

int setScriptedEntrySDL2(ElementSDL2 *e,int isScripted){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->entry->isScripted!=isScripted){
        e->entry->isScripted=isScripted;
        error=actualizeTextFontSDL2(e->font,e->entry->isScripted);
    }

    return error;
}

int addCharEntrySDL2(ElementSDL2 *e,char c){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->font && e->font->text && e->entry->size < e->entry->size_max){
        *(e->font->text+e->entry->size)=c;
        ++e->entry->size;
        error=actualizeTextFontSDL2(e->font,e->entry->isScripted);
    }

    return error;
}

int removeCharEntrySDL2(ElementSDL2 *e){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->font && e->font->text && e->entry->size){
        --e->entry->size;
        *(e->font->text+e->entry->size)=' ';
        error=actualizeTextFontSDL2(e->font,e->entry->isScripted);
    }

    return error;
}
/* ------------------------------------------------------- */
