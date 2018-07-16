#include "Element.h"

#include <limits.h>

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
 * Liste d'elements  avec display code commun
 */
static ListPtrElement* initListPtrElement(int plan){
    ListPtrElement *l=(ListPtrElement*)malloc(sizeof(*l));

    if(l){
        l->first=NULL;
        l->last=NULL;
        l->current=NULL;
        l->next=NULL;
        l->code=plan;
    }

    return l;
}

static void freeListPtrElement(ListPtrElement* l){
    PtrElement * ptr, * ptmp;
    
    if(l){
	ptr = l->first;
        while(ptr){
            ptmp=ptr->next;
	    free(ptr);
            ptr=ptmp;
        }
	free(l);
    }
}

static int addPtrElement(ListPtrElement* l,Element* e){
    DisplayCode *d;
    PtrElement *p;
    int error = 1;
  
    if(l && e){
        d=e->codes->first;
        while(d && d->plan > l->code){
            d=d->next;
        }
        if(d && d->plan==l->code){
            p=(PtrElement*)malloc(sizeof(*p));
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
static ListDCElement* initListDCElement(int displayCode){
    ListDCElement * l =(ListDCElement*)malloc(sizeof(*l));

    if(l){
        l->first=NULL;
        l->current=NULL;
        l->next=NULL;
        l->code=displayCode;
    }

    return l;
}

static void freeListDCElement(ListDCElement* l){
    ListPtrElement *lp,*lptmp;

    if(l){
        lp=l->first;
        while(lp){
            lptmp=lp->next;
            freeListPtrElement(lp);
            lp=lptmp;
        }
	free(l);
    }
}

/*static int delDCElement(ListDCElement** l,Element *e){
    ListPtrElement **lp;
    PtrElement **pe, *etmp, **pte;
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
}*/
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (code d'affichage) de liste (plan) 
 * d'element
 */
ListElement* _initListElement(){
    ListElement *l=(ListElement*)malloc(sizeof(*l));
  
    if(l){
        l->first=NULL;
        l->currentDCIterator=NULL;
        l->currentPIterator=NULL;
    }
  
    return l;
}

void _freeListElement(ListElement *l){
    ListDCElement *lp,*ltmp;

    if(l){
        lp=l->first;
        while(lp){
            ltmp=lp->next;
            freeListDCElement(lp);
            lp=ltmp;
        }
        free(l);
    }
}

int addElement(Element* e){
    DisplayCode *d;
    ListDCElement ** ldc, *dctmp;
    ListPtrElement ** lp, *ptmp;
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
                *ldc=initListDCElement(d->code);
                if(d->code == _windows_SANDAL2->current->displayCode && !(_windows_SANDAL2->current->current))
                    _windows_SANDAL2->current->current = *ldc;
                lp=&((*ldc)->first);
                *lp=initListPtrElement(d->plan);
            }else if((*ldc)->code!=d->code){
                dctmp=initListDCElement(d->code);
                if(d->code == _windows_SANDAL2->current->displayCode && !(_windows_SANDAL2->current->current))
                    _windows_SANDAL2->current->current = dctmp;
                dctmp->next=(*ldc);
                (*ldc)=dctmp;
                lp=&((*ldc)->first);
                *lp=initListPtrElement(d->plan);
            }else{
                lp=&((*ldc)->first);
                while(*lp && (*lp)->code > d->plan){
                    lp=&((*lp)->next);
                }
                if(!*lp){
                    *lp=initListPtrElement(d->plan);
                }else if((*lp)->code != d->plan){
                    ptmp=*lp;
                    *lp=initListPtrElement(d->plan);
                    (*lp)->next=ptmp;
                }
            }
            error |= addPtrElement(*lp,e);
            d=d->next;
        }
        e->parent=_windows_SANDAL2->current;
    }

    return error;
}

void _cleanElement(){
    PtrElement **e, *etmp, *prev;
    ListPtrElement **lp, *ptmp;
    ListDCElement **ldc, *dctmp;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
        ldc=&(_windows_SANDAL2->current->liste->first);
        while(*ldc && _windows_SANDAL2->current->toDelete){
            lp=&((*ldc)->first);
            while(*lp && _windows_SANDAL2->current->toDelete){
                e=&((*lp)->first);
		prev = NULL;
                while(e && *e && _windows_SANDAL2->current->toDelete){
                    switch((*e)->element->deleted-((*e)->element->deleted==2 && (*e)->element->codes->size==1)){
                    case 1:
                    case 2:
                        if((*ldc)->code==(*e)->element->deleteCode){
                            etmp=*e;
			    delDisplayCode((*e)->element->codes, (*ldc)->code);
			    if(!((*e)->element->codes->first))
				_freeElement((*e)->element);
                            *e=(*e)->next;
			    if(etmp == (*lp)->last)
				(*lp)->last = prev;
                            free(etmp);
                            _windows_SANDAL2->current->toDelete--;
                        }else{
			    prev = *e;
                            e=&((*e)->next);
                        }
                        break;
                    case 3:
                        if((*lp)->code==(*e)->element->deleteCode){
                            etmp=*e;
                            *e=(*e)->next;
			    if(etmp == (*lp)->last)
				(*lp)->last = prev;
                            free(etmp);
                            _windows_SANDAL2->current->toDelete--;
                        }else{
			    prev = *e;
                            e=&((*e)->next);
                        }
                        break;
                    default:
			prev = *e;
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

int delElement(Element *e){
    int error = 1;
  
    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        e->deleted=1;
        e->parent->toDelete++;
        error = 0;
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element creation, freeing and informations
 */
void _freeElement(Element *e){
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
            freeFont(e->font);
        }
        if(e->interactions){
            freeListPtrElement(e->interactions);
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

Element* createBlock(float x,float y,float width,float height,int couleur[4],int displayCode,int plan){
    Element *e = NULL;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=(Element*)malloc(sizeof(*e));
        if(e){
            e->deleted=0;
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
	    e->flip = SANDAL2_FLIP_NONE;
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
	    e->events.onMouseMotion=NULL;
	    e->events.unMouseMotion=NULL;
            e->font=NULL;
            e->entry=NULL;
            e->interactions=NULL;
            e->image=NULL;
            e->hitboxes = initListClickable();
            e->data=NULL;
            if(addElement(e)){
                _freeElement(e);
                e=NULL;
            }
        }
    }

    return e;
}

Element* createText(float x,float y,float width,float height,float textSize, const char * font,const char * text,int textColor[4],int quality,int displayCode,int plan){
    Element *e=NULL;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=(Element*)malloc(sizeof(*e));
        if(e){
            e->deleted=0;
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
	    e->flip = SANDAL2_FLIP_NONE;
            e->textSize=textSize/100.f;
            e->animation=initListAnimation();
            e->image=NULL;
            e->entry=NULL;
            e->interactions=NULL;
            e->hitboxes = initListClickable();
            e->codes=NULL;
            e->font=createFont(font,text,textColor,quality);
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
		e->events.onMouseMotion=NULL;
		e->events.unMouseMotion=NULL;
                if(addElement(e)){
                    _freeElement(e);
                    e=NULL;
                }
            }else{
                _freeElement(e);
                e=NULL;
            }
        }
    }

    return e;
}

Element* createImage(float x,float y,float width,float height,const char *image,int displayCode,int plan){
    Element *e=NULL;
    SDL_Surface *s;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        s=IMG_Load(image);
  
        if(s){
            e=(Element*)malloc(sizeof(*e));
            if(e){
                e->deleted=0;
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
		e->flip = SANDAL2_FLIP_NONE;
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
		e->events.onMouseMotion=NULL;
		e->events.unMouseMotion=NULL;
                e->freeData=NULL;
                e->font=NULL;
                e->entry=NULL;
                e->interactions=NULL;
                e->hitboxes = initListClickable();
                e->data=NULL;
                if(addElement(e)){
                    _freeElement(e);
                    e=NULL;
                }
            }
            SDL_FreeSurface(s);
        }
    }

    return e;
}

Element* createButton(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,int couleurBlock[4],int displayCode,int plan){
    Element *e = NULL;
    Font * f;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createBlock(x,y,width,height,couleurBlock,displayCode,plan);
        if(e){
            e->textSize=texteSize/100.f;
            f=createFont(font,text,textColor,quality);
            if(f){
                e->font=f;
            }else{
                delElement(e);
                _freeElement(e);
                e=NULL;
            }
        }
    }

    return e;
}

Element* createButtonImage(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,const char *image,int displayCode,int plan){
    Element *e = NULL;
    Font * f;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createImage(x,y,width,height,image,displayCode,plan);
        if(e){
            e->textSize=texteSize/100.f;
            f=createFont(font,text,textColor,quality);
            if(f){
                e->font=f;
            }else{
                delElement(e);
                _freeElement(e);
                e=NULL;
            }
        }
    }

    return e;
}

Element* createEntry(float x,float y,float width,float height,float texteSize,const char * font, const char * text,int textColor[4],int quality,int couleurBlock[4],int displayCode,int plan,int min,int max,int isScripted){
    Element *e = NULL;
    Entry *ent;
    int i;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createButton(x,y,width,height,texteSize,font,text,textColor,quality,couleurBlock,displayCode,plan);
        if(e){
            ent=(Entry*)malloc(sizeof(*ent));
            if(ent){
                ent->size_min=min;
                ent->size_max=max;
                ent->isSelect=0;
                ent->isScripted=isScripted;
                PFREE(e->font->text);
                e->font->text=(char*)malloc((max*2+1)*sizeof(*(e->font->text)));
                if(e->font->text){
                    for(i=0;i<max*2;++i){
                        e->font->text[i]=' ';
                    }
                    e->font->text[max]='\0';
                    e->entry=ent;
                    ent->size=0;
                }else{
                    delElement(e);
                    _freeElement(e);
                    e=NULL;
                }
            }else{
                delElement(e);
                _freeElement(e);
                e=NULL;
            }
        }
    }
  
    return e;  
}

Element* createEntryImage(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,const char *image,int displayCode,int plan,int min,int max,int isScripted){
    Element *e = NULL;
    Entry *ent;
    int i;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        e=createButtonImage(x,y,width,height,texteSize,font,text,textColor,quality,image,displayCode,plan);
        if(e){
            ent=(Entry*)malloc(sizeof(*ent));
            if(ent){
                ent->size_min=min;
                ent->size_max=max;
                ent->isSelect=0;
                ent->isScripted=isScripted;
                PFREE(e->font->text);
                e->font->text=(char*)malloc((max*2+1)*sizeof(*(e->font->text)));
                if(e->font->text){
                    for(i=0;i<max*2;++i){
                        e->font->text[i]=' ';
                    }
                    e->font->text[max]='\0';
                    e->entry=ent;
                    ent->size=0;
                }else{
                    delElement(e);
                    _freeElement(e);
                    e=NULL;
                }
            }else{
                delElement(e);
                _freeElement(e);
                e=NULL;
            }
        }
    }
  
    return e;  
}

int isDisplaiedElement(Element *e){
    int display = (e && !(e->deleted) && _windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current == e->parent && e->codes);
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

int clearDisplayCode(int code){
    ListPtrElement * lptr;
    ListDCElement ** ldc;
    PtrElement * ptr;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
	ldc = &(_windows_SANDAL2->current->liste->first);
	while(*ldc && (*ldc)->code < code)
	    ldc = &((*ldc)->next);
	if(*ldc && (*ldc)->code == code){
	    error = 0;
	    lptr = (*ldc)->first;
	    while(lptr){
		ptr = lptr->first;
		while(ptr){
                    ptr->element->deleted=2;
                    ptr->element->deleteCode=code;
                    _windows_SANDAL2->current->toDelete++;
		    ptr = ptr->next;
		}
		lptr = lptr->next;
	    }
	}
    }

    return error;
}

int getFlipStateElement(Element * e,SANDAL2_FLIP * flip){
    if(e && flip)
	*flip = e->flip;

    return !e;
}

int getCoordElement(Element* e,float* x,float* y){
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

int getAngleElement(Element* e,float* a){
    int error = 1;

    if(e){
        if(a){
            *a=e->rotation;
        }
        error=0;
    }

    return error;
}

int getDimensionElement(Element* e,float* w,float * h){
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

int getRotationPointElement(Element* e,float *x,float *y){
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

int getRotationSpeedElement(Element* e,float* s){
    int error = 1;

    if(e){
        if(s){
            *s=e->rotSpeed;
        }
        error = 0;
    }

    return error;
}

int getDataElement(Element* e,void ** data){
    int error = 1;

    if(e){
        error = 0;
        if(data){
            *data=e->data;
        }
    }

    return error;
}

int isSelectedElement(Element *e, int * select){
    int error = 1;

    if(e){
        error = 0;
        if(select){
            *select = e->selected;
        }
    }

    return error;
}

int getTextStyleElement(Element *e,int * style){
    int error = 1;

    if(e && e->font){
        error=getStyleFont(e->font,style);
    }

    return error;
}

int getTextElement(Element *e,char **s){
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

int getColorElement(Element * e, int color[4]){
    int error = 1;

    if(e && color){
	error = 0;
	copyColor(color,e->coulBlock);
    }

    return error;
}

int getWidthElement(Element * e,float * w){
    int error = 1;

    if(e && w){
	error = 0;
	*w = e->width;
    }

    return error;
}

int getHeightElement(Element * e,float * h){
    int error = 1;

    if(e && h){
	error = 0;
	*h = e->height;
    }

    return error;
}

int getCoordXElement(Element * e,float * x){
    int error = 1;

    if(e && x){
	error = 0;
	*x = e->x;
    }

    return error;
}

int getCoordYElement(Element * e,float * y){
    int error = 1;

    if(e && y){
	error = 0;
	*y = e->y;
    }

    return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element modifications
 */
int setFontElement(Element *e,const char * font){
    Font *f;
    int color[4];
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current){
        if(e && font && e->font){
            color[0]=e->font->color.r;
            color[1]=e->font->color.g;
            color[2]=e->font->color.b;
            color[3]=e->font->color.a;
            f=createFont(font,e->font->text,color,e->font->quality);
            if(f){
                freeFont(e->font);
                e->font=f;
                error = 0;
            }
        }
    }

    return error;
}

int setTextElement(Element *e,const char * text){
    int error = 1;
    int size;
    int i;
    
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && text && e->font){
	if(e->entry){
	    size = strlen(text);
	    if(size > e->entry->size_max){
		strncpy(e->font->text,text,e->entry->size_max);
		e->font->text[e->entry->size_max] = 0;
	    }else{
		strncpy(e->font->text,text,size);
		for(i = size; i < e->entry->size_max - size; ++i){
		    e->font->text[i] = ' ';
		}
		e->font->text[i] = 0;
	    }
	    error = setTextFont(e->font,e->font->text);
	    e->entry->size = (size >= e->entry->size_max ? e->entry->size_max : size);
	}else
	    error=setTextFont(e->font,text);
    }

    return error;
}

int setTextStyleElement(Element *e,int style){
    int error = 1;

    if(e && e->font){
        error=setStyleFont(e->font,style);
    }

    return error;
}

int setColorElement(Element *e,int color[4]){
    int error = 1;
  
    if(e){
        error = 0;
        copyColor(e->coulBlock,color);
    }

    return error;
}

int setTextColorElement(Element *e, int color[4]){
    int error = 1;

    if(e && e->font){
        error=setColorFont(e->font,color);
    }

    return error;
}

int setTextQualityElement(Element *e, int quality){
    int error = 1;

    if(e && e->font){
        error = 0;
        e->font->quality=quality;
    }

    return error;
}

int setImageElement(Element *e,const char *image){
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

int setImageTextureElement(Element *e,SDL_Texture * image){
    int error = 1;

    if(e){
        error = 0;
        e->image=image;
    }

    return error;
}

int replaceElement(Element *e,float x,float y){
    int error = 1;

    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        e->x=x;
        e->y=y;
        error = 0;
    }

    return error;
}

int moveElement(Element *e,float x,float y){
    int error = 1;

    if(e && _windows_SANDAL2 && _windows_SANDAL2->current){
        e->x+=x;
        e->y+=y;
        error = 0;
    }

    return error;
}

int setDimensionElement(Element *e,float width,float height){
    int error = 1;

    if(e){
        e->width=width;
        e->height=height;
        error = 0;
    }

    return error;
}

int setTextSize(Element *e,float textSize){
    int error = 1;

    if(e){
        e->textSize=textSize/100.0f;
        error = 0;
    }

    return error;
}

int addDisplayCodeElement(Element *e,int displayCode, int plan){
    DisplayCode **d, *tmp;
    ListDCElement **ldc, *dctmp;
    ListPtrElement **lp, *ptmp;
    PtrElement *el;
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
                    dctmp=initListDCElement(displayCode);
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
                    ptmp=initListPtrElement(plan);
                    ptmp->next=*lp;
                    *lp=ptmp;
                }
                el=(PtrElement*)malloc(sizeof(*el));
                if(el){
                    error = 0;
                    el->next=NULL;
                    el->element=e;
		    ++e->codes;
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

int delDisplayCodeElement(Element *e,int displayCode){
    DisplayCode **d, *tmp;
    ListDCElement **ldc;
    ListPtrElement **lp;
    PtrElement **cour;
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
                        (*cour)->element->deleted=2;
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

int setDisplayCodeElement(Element *e,int displayCode,int isDisplaied){
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

int setPlanElement(Element *e,int displayCode,int plan){
    int old;
    DisplayCode *d;
    ListDCElement *ldc;
    ListPtrElement **lp, *ptmp, **lpNew = NULL;
    PtrElement **cour,*tmp;
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
                    (*cour)->element->deleted=3;
                    (*cour)->element->deleteCode=old;
                    _windows_SANDAL2->current->toDelete++;
                }
                if(!lpNew){
                    lpNew=lp;
                    while(*lpNew && (*lpNew)->code > plan){
                        lpNew=&((*lpNew)->next);
                    }
                    if(!*lpNew || (*lpNew)->code != plan){
                        ptmp=initListPtrElement(plan);
                        ptmp->next=*lpNew;
                        *lpNew=ptmp;
                    }
                }
                tmp=(PtrElement*)malloc(sizeof(*tmp));
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

int clearPlanDisplayCode(int code, int plan){
    ListDCElement * ldc;
    ListPtrElement * lptr;
    PtrElement * ptr;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
	ldc = _windows_SANDAL2->current->liste->first;
	while(ldc && ldc->code < code)
	    ldc = ldc->next;
	if(ldc && ldc->code == code){
	    lptr = ldc->first;
	    while(lptr && lptr->code > plan)
		lptr = lptr->next;
	    if(lptr && lptr->code == plan){
		error = 0;
		ptr = lptr->first;
		while(ptr){
                    ptr->element->deleted=3;
                    ptr->element->deleteCode=plan;
                    _windows_SANDAL2->current->toDelete++;
		    ptr = ptr->next;
		}
	    }
	}
    }

    return error;
}

int setActionElement(Element *e,void (*action)(Element*)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.action=action;
    }

    return error;
}

int setKeyPressedElement(Element *e,void (*keyPress)(Element*,SDL_Keycode c)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.keyPress=keyPress;
    }

    return error;
}

int setKeyReleasedElement(Element *e,void (*keyReleased)(Element*,SDL_Keycode c)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.keyReleased=keyReleased;
    }

    return error;
}

int setUnClickElement(Element *e,void (*unCLick)(Element*, int)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.unClick=unCLick;
    }

    return error;
}

int setOnClickElement(Element *e,void (*onCLick)(Element*, int)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.onClick=onCLick;
    }

    return error;
}

int setOnMouseMotionElement(Element *e, void (*onMouseMotion)(Element*)){
  int error = 1;

  if(e){
    error = 0;
    e->events.onMouseMotion=onMouseMotion;
  }

  return error;
}

int setUnMouseMotionElement(Element *e, void (*unMouseMotion)(Element*)){
  int error = 1;

  if(e){
    error = 0;
    e->events.unMouseMotion=unMouseMotion;
  }

  return error;
}

int setUnSelectElement(Element *e,void (*unSelect)(Element*)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.unSelect=unSelect;
    }

    return error;
}

int setEndSpriteElement(Element *e,void (*endSprite)(Element*,int)){
    int error = 1;
  
    if(e){
        error=0;
        e->events.endSprite=endSprite;
    }

    return error;
}

int addElementToElement(Element *e,Element *add){
    PtrElement *pe;
    int error = 1;
  
    if(e && add){
        pe=(PtrElement*)malloc(sizeof(*pe));
        pe->element=add;
        pe->next=NULL;
    
        if(!e->interactions){
            e->interactions=(ListPtrElement*)malloc(sizeof(*(e->interactions)));
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

int delElementToElement(Element *e,Element *del){
    PtrElement **pe, *rm, **tmp=NULL;
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

int clearElementToElement(Element * e){
    int error = 1;
    PtrElement * pe, * tmp;

    if(e && e->interactions){
	pe = e->interactions->first;

	while(pe){
	    tmp = pe->next;
	    free(pe);
	    pe = tmp;
	}

	e->interactions->first   = NULL;
	e->interactions->last    = NULL;
	e->interactions->current = NULL;
    }

    return error;
}

int addClickableElement(Element *e,Clickable *hb,int blocking){
    int error = 1;

    if(e && hb){
        error=addClickable(e->hitboxes,hb,blocking);
    }

    return error;
}

int addRotationSpeedElement(Element *e,float s){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotSpeed+=s;
        error = 0;
    }

    return error;
}

int setRotationSpeedElement(Element *e,float s){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotSpeed=s;
        error = 0;
    }

    return error;
}

int addAngleElement(Element *e,float a){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotation+=a;
        error = 0;
    }

    return error;
}

int setAngleElement(Element *e,float a){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->rotation=a;
        error = 0;
    }

    return error;
}

int setRotationPointElement(Element *e,float x,float y){
    int error = 1;

    if(e && e->coulBlock[0]==-1){
        e->prX=x;
        e->prY=y;
        error = 0;
    }

    return error;
}

int setDataElement(Element *e,void *data){
    int error = 1;

    if(e){
        error = 0;
        e->data=data;
    }

    return error;
}

int setFreeDataElement(Element *e,void (*freeData)(void*)){
    int error = 1;

    if(e && freeData){
        e->freeData=freeData;
        error = 0;
    }

    return error;
}

int freeDataElement(Element *e){
    int error = 1;

    if(e && e->data && e->freeData){
        e->freeData(e->data);
        e->data=NULL;
        error=0;
    }

    return error;
}

int addAnimationElement(Element *e,int code){
    int error = 1;

    if(e){
        error=createAnimation(e->animation,code);
    }

    return error;
}

int delAnimationElement(Element *e,int code){
    int error = 1;

    if(e){
        error=delAnimation(e->animation,code);
    }

    return error;
}

int addSpriteAnimationElement(Element *e,int code,int x,int y,int width,int height,int lifespan,int codeS){
    int error = 1;

    if(e){
        error = addSpriteAnimation(e->animation,code,x,y,width,height,lifespan,codeS);
    }
  
    return error;
}

int delSpriteAnimationElement(Element *e,int code,int codeS){
    int error = 1;

    if(e){
        error = delSpriteAnimation(e->animation,code,codeS);
    }

    return error;
}

int setLifeSpanSpriteAnimationElement(Element * e,int code,int codeS,unsigned lifespan){
    int error = 1;

    if(e){
        error = setLifeSpanSpriteAnimation(e->animation,code,codeS,lifespan);
    }

    return error;
}

int nextSpriteElement(Element * e){
    int error = 1;

    if(e && e->animation->size && e->animation->current->size){
        e->animation->current->current = e->animation->current->current->next;
        e->animation->current->wasChanged=0;
        error = 0;
    }

    return error;
}

int previousSpriteElement(Element * e){
    int error = 1;

    if(e && e->animation->size && e->animation->current->size){
        e->animation->current->current = e->animation->current->current->prev;
        e->animation->current->wasChanged=0;
        error = 0;
    }

    return error;
}

int setWaySpriteAnimationElement(Element * e,int code, int sens){
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

int nextAnimationElement(Element * e){
    int error=1;

    if(e && e->animation->size){
        e->animation->current=e->animation->current->next;
        error = 0;
    }

    return error;
}

int previousAnimationElement(Element * e){
    int error=1;

    if(e && e->animation->size){
        e->animation->current=e->animation->current->prev;
        error = 0;
    }

    return error;
}

int setAnimationElement(Element *e,int code){
    int error = 1;

    if(e && e->animation){
        error = setAnimation(e->animation,code);
    }

    return error;
}

int setSpriteAnimationElement(Element *e,int codeS){
    int error = 1;

    if(e && e->animation){
        error = setSpriteAnimation(e->animation,codeS);
    }

    return error;
}

int clearWindow(void){
    ListDCElement * ldc, * ltmp;
    int error = 1;

    if(_windows_SANDAL2 && _windows_SANDAL2->current && _windows_SANDAL2->current->liste){
	error = 0;

	ldc = _windows_SANDAL2->current->liste->first;
	while(ldc){
	    ltmp = ldc->next;
	    freeListDCElement(ldc);
	    ldc = ltmp;
	}
	_windows_SANDAL2->current->stop = 1;
	_windows_SANDAL2->current->liste->first = NULL;
	_windows_SANDAL2->current->liste->currentDCIterator = NULL;
	_windows_SANDAL2->current->liste->currentPIterator = NULL;
    }

    return error;
}

int setFlipStateElement(Element * e, SANDAL2_FLIP flip){
    if(e)
	e->flip = flip;

    return !e;
}

int setWidthElement(Element * e, float width){
    if(e)
	e->width = width;

    return !e;
}

int setHeightElement(Element * e, float height){
    if(e)
	e->height = height;

    return !e;
}

int setCoordXElement(Element * e, float x){
    if(e)
	e->x = x;

    return !e;
}

int setCoordYElement(Element * e, float y){
    if(e)
	e->y = y;

    return !e;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element's list binded to an Element's iterator
 */
int initIteratorElement(Element *e){
    int succes = 0;
  
    if(e && e->interactions && e->interactions->first){
        e->interactions->current=e->interactions->first;
        succes = 1;
    }

    return succes;
}

Element* nextIteratorElement(Element *e){
    Element* next=NULL;
  
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
    ListDCElement *lp;
  
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

Element* nextElement(){
    Element *res = NULL;
    PtrElement *pres;

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
int setSizeEntry(Element *e,int size_min,int size_max){
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
                error=actualizeTextFont(e->font,e->entry->isScripted);
            }
        }
    }

    return error;
}

int setScriptedEntry(Element *e,int isScripted){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->entry->isScripted!=isScripted){
        e->entry->isScripted=isScripted;
        error=actualizeTextFont(e->font,e->entry->isScripted);
    }

    return error;
}

int addCharEntry(Element *e,char c){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->font && e->font->text && e->entry->size < e->entry->size_max){
        e->font->text[e->entry->size]=c;
	e->font->text[e->entry->size_max*2 - e->entry->size] = 0;
        ++e->entry->size;
        error=actualizeTextFont(e->font,e->entry->isScripted);
    }

    return error;
}

int delCharEntry(Element *e){
    int error = 1;
  
    if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->font && e->font->text && e->entry->size){
        --e->entry->size;
	if(e->entry->size < e->entry->size_max*2 - e->entry->size)
	    e->font->text[e->entry->size_max*2 - e->entry->size] = ' ';
        e->font->text[e->entry->size]=' ';
        error=actualizeTextFont(e->font,e->entry->isScripted);
    }

    return error;
}
/* ------------------------------------------------------- */
