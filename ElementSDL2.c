#include "ElementSDL2.h"

/* -------------------------------------------------------
 * Liste d'elements SDL2 avec display code commun
 */
ListPtrElementSDL2* initListPtrElementSDL2(int plan){
  ListPtrElementSDL2 *l=malloc(sizeof(*l));

  if(l){
    l->first=NULL;
    l->last=NULL;
    l->current=NULL;
    l->next=NULL;
    l->code=plan;
  }

  return l;
}

void freeListPtrElementSDL2(ListPtrElementSDL2* l){
  if(l){
    while(l->first){
      l->current=l->first->next;
      free(l->first);
      l->first=l->current;
    }
    free(l);
  }
}

int addPtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e){
  DisplayCode *d;
  PtrElementSDL2 *p;
  int error = 1;
  
  if(l && e){
    d=e->codes->first;
    while(d && d->plan > l->code){
      d=d->next;
    }
    if(d && d->plan==l->code){
      p=malloc(sizeof(*p));
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

int removePtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e){
  PtrElementSDL2 ** p, ** tmp, * ttmp;
  int error = 1;
  
  if(l && e){
    p=&(l->first);
    tmp=NULL;
    while(*p && (*p)->element!=e){
      tmp=p;
      p=&((*p)->next);
    }
    if(*p){
      if(*p==l->current){
	l->current=(*p)->next;
      }
      if((*p)==l->last){
	l->last=*tmp;
      }
      if(*p==l->first){
	l->first=(*p)->next;
      }
      if(*tmp){
	(*tmp)->next=(*p)->next;
      }
      ttmp=(*p)->next;
      free(*p);
      *p=ttmp;
      error = 0;
    }
  }

  return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (plan) d'element, contenant le code 
 * d'affichage
 */
ListDCElementSDL2* initListDCElementSDL2(int displayCode){
  ListDCElementSDL2 * l =malloc(sizeof(*l));

  if(l){
    l->first=NULL;
    l->current=NULL;
    l->next=NULL;
    l->code=displayCode;
  }

  return l;
}

void freeListDCElementSDL2(ListDCElementSDL2* l){
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

int addListPtrElementSDL2(ListDCElementSDL2* l, ListPtrElementSDL2 *lp){
  ListPtrElementSDL2 **cour;
  int error = 1;

  if(l && lp){
    cour = &(l->first);
    while(*cour && (*cour)->code > lp->code){
      *cour=(*cour)->next;
    }
    if(lp->code != (*cour)->code){
      lp->next=*cour;
      *cour=lp;
      error = 0;
    }
  }

  return error;
}

int removeListPtrElementSDL2(ListDCElementSDL2* l,ListPtrElementSDL2 *lp){
  ListPtrElementSDL2 **cour, *tmp;
  int error = 1;

  if(l && lp){
    cour = &(l->first);
    while(*cour && (*cour)->code < lp->code){
      *cour=(*cour)->next;
    }
    if(lp == *cour){
      tmp=(*cour)->next;
      freeListPtrElementSDL2(*cour);
      *cour=tmp;
      error = 0;
    }
  }

  return error;
}

int removeDCElementSDL2(ListDCElementSDL2** l,ElementSDL2 *e){
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
ListElementSDL2* initListElementSDL2(){
  ListElementSDL2 *l=malloc(sizeof(*l));
  
  if(l){
    l->first=NULL;
    l->currentDCIterator=NULL;
    l->currentPIterator=NULL;
  }
  
  return l;
}

void freeListElementSDL2(ListElementSDL2 *l){
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
	lp=&((*ldc)->first);
	*lp=initListPtrElementSDL2(d->plan);
      }else if((*ldc)->code!=d->code){
	dctmp=initListDCElementSDL2(d->code);
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

void cleanElementSDL2(){
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
	    freeElementSDL2(ee);
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
 * Element SDL2
 */
void freeElementSDL2(ElementSDL2 *e){
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
    if(e->data){
      free(e->data);
    }
    if(e->police){
      freeFontSDL2(e->police);
    }
    if(e->interactions){
      freeListPtrElementSDL2(e->interactions);
    }
    if(e->hitboxes){
      freeListHitBox(e->hitboxes);
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
    e=malloc(sizeof(*e));
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
      e->action=NULL;
      e->onClick=NULL;
      e->unClick=NULL;
      e->keyPress=NULL;
      e->keyReleased=NULL;
      e->unSelect=NULL;
      e->endSprite=NULL;
      e->police=NULL;
      e->entry=NULL;
      e->interactions=NULL;
      e->image=NULL;
      e->hitboxes = initListHitBox();
      e->data=NULL;
      if(addElementSDL2(e)){
	freeElementSDL2(e);
	e=NULL;
      }
    }
  }

  return e;
}

ElementSDL2* createTexte(float x,float y,float width,float height,char * font,char * text,int textColor[4],int quality,int displayCode,int plan){
  ElementSDL2 *e=NULL;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    e=malloc(sizeof(*e));
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
      e->hitboxes = initListHitBox();
      e->codes=NULL;
      e->police=createFontSDL2(font,text,textColor,quality);
      e->data=NULL;
      if(e->police){
	e->codes=initListDisplayCode();
	addDisplayCode(e->codes,displayCode,1,plan);
	e->coulBlock[0]=-1;
	e->action=NULL;
	e->onClick=NULL;
	e->unClick=NULL;
	e->keyPress=NULL;
	e->keyReleased=NULL;
	e->unSelect=NULL;
	e->endSprite=NULL;
	e->data=NULL;
	if(addElementSDL2(e)){
	  freeElementSDL2(e);
	  e=NULL;
	}
      }else{
	freeElementSDL2(e);
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
      e=malloc(sizeof(*e));
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
	e->action=NULL;
	e->onClick=NULL;
	e->unClick=NULL;
	e->keyPress=NULL;
	e->keyReleased=NULL;
	e->unSelect=NULL;
	e->endSprite=NULL;
	e->police=NULL;
	e->entry=NULL;
	e->interactions=NULL;
	e->hitboxes = initListHitBox();
	e->data=NULL;
	if(addElementSDL2(e)){
	  freeElementSDL2(e);
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
	e->police=f;
      }else{
	removeElementSDL2(e);
	freeElementSDL2(e);
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
	e->police=f;
      }else{
	removeElementSDL2(e);
	freeElementSDL2(e);
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
      ent=malloc(sizeof(*ent));
      if(ent){
	ent->size_min=min;
	ent->size_max=max;
	ent->isSelect=0;
	ent->isScripted=isScripted;
	PFREE(e->police->text);
	e->police->text=malloc((max+1)*sizeof(*(e->police->text)));
	if(e->police->text){
	  for(i=0;i<max;++i){
	    e->police->text[i]=' ';
	  }
	  e->police->text[max]='\0';
	  e->entry=ent;
	  ent->size=0;
	}else{
	  removeElementSDL2(e);
	  freeElementSDL2(e);
	  e=NULL;
	}
      }else{
	removeElementSDL2(e);
	freeElementSDL2(e);
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
      ent=malloc(sizeof(*ent));
      if(ent){
	ent->size_min=min;
	ent->size_max=max;
	ent->isSelect=0;
	ent->isScripted=isScripted;
	PFREE(e->police->text);
	e->police->text=malloc((max+1)*sizeof(*(e->police->text)));
	if(e->police->text){
	  for(i=0;i<max;++i){
	    e->police->text[i]=' ';
	  }
	  e->police->text[max]='\0';
	  e->entry=ent;
	  ent->size=0;
	}else{
	  removeElementSDL2(e);
	  freeElementSDL2(e);
	  e=NULL;
	}
      }else{
	removeElementSDL2(e);
	freeElementSDL2(e);
	e=NULL;
      }
    }
  }
  
  return e;  
}

int isDisplaied(ElementSDL2 *e){
  return (e && !(e->delete) && _windows_SANDAL2 && _windows_SANDAL2->current == e->parent);
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

int getDimensionElementSDL2(ElementSDL2* e,int* w,int * h){
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
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2
 */
int setFontElementSDL2(ElementSDL2 *e,char * font){
  FontSDL2 *f;
  int color[4];
  int error = 1;

  if(_windows_SANDAL2 && _windows_SANDAL2->current){
    if(e && font && e->police){
      color[0]=e->police->color.r;
      color[1]=e->police->color.g;
      color[2]=e->police->color.b;
      color[3]=e->police->color.a;
      f=createFontSDL2(font,e->police->text,color,e->police->quality);
      if(f){
	freeFontSDL2(e->police);
	e->police=f;
	error = 0;
      }
    }
  }

  return error;
}

int setTextElementSDL2(ElementSDL2 *e,char * text){
  int error = 1;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && e && text && e->police){
    error=changeTextFontSDL2(e->police,text);
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

  if(e && e->police){
    error=changeColorFontSDL2(e->police,color);
  }

  return error;
}

int setTextQualityElementSDL2(ElementSDL2 *e, int quality){
  int error = 1;

  if(e && e->police){
    error = 0;
    e->police->quality=quality;
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
	tmp=malloc(sizeof(*tmp));
	tmp->code=displayCode;
	tmp->plan = plan;
	tmp->next=*d;
	*d=tmp;
	ldc=&(_windows_SANDAL2->current->liste->first);
	while(*ldc && (*ldc)->code < displayCode){
	  ldc=&((*ldc)->next);
	}
	if(!*ldc || (*ldc)->code != displayCode){
	  dctmp=initListDCElementSDL2(displayCode);
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
	el=malloc(sizeof(*el));
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

  if(e){
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
	tmp=malloc(sizeof(*tmp));
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
    e->action=action;
  }

  return error;
}

int setKeyPressElementSDL2(ElementSDL2 *e,void (*keyPress)(ElementSDL2*,SDL_Keycode c)){
  int error = 1;
  
  if(e){
    error=0;
    e->keyPress=keyPress;
  }

  return error;
}

int setKeyReleasedElementSDL2(ElementSDL2 *e,void (*keyReleased)(ElementSDL2*,SDL_Keycode c)){
  int error = 1;
  
  if(e){
    error=0;
    e->keyReleased=keyReleased;
  }

  return error;
}

int setUnClickElementSDL2(ElementSDL2 *e,void (*unCLick)(ElementSDL2*)){
  int error = 1;
  
  if(e){
    error=0;
    e->unClick=unCLick;
  }

  return error;
}

int setOnClickElementSDL2(ElementSDL2 *e,void (*onCLick)(ElementSDL2*)){
  int error = 1;
  
  if(e){
    error=0;
    e->onClick=onCLick;
  }

  return error;
}

int setUnSelectElementSDL2(ElementSDL2 *e,void (*unSelect)(ElementSDL2*)){
  int error = 1;
  
  if(e){
    error=0;
    e->unSelect=unSelect;
  }

  return error;
}

int setEndSpriteElementSDL2(ElementSDL2 *e,void (*endSprite)(ElementSDL2*,int)){
  int error = 1;
  
  if(e){
    error=0;
    e->endSprite=endSprite;
  }

  return error;
}

int addElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *add){
  PtrElementSDL2 *pe;
  int error = 1;
  
  if(e && add){
    pe=malloc(sizeof(*pe));
    pe->element=add;
    pe->next=NULL;
    
    if(!e->interactions){
      e->interactions=malloc(sizeof(*(e->interactions)));
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

int addHitBoxElementSDL2(ElementSDL2 *e,HitBox *hb,int blocking){
  int error = 1;

  if(e && hb){
    error=addHitBox(e->hitboxes,hb,blocking);
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

int addSpriteAnimationElementSDL2(ElementSDL2 *e,int code,int x,int y,int width,int height,int lifespan){
  int error = 1;

  if(e){
    error = addSpriteAnimation(e->animation,code,x,y,width,height,lifespan);
  }
  
  return error;
}

int removeSpriteAnimationElementSDL2(ElementSDL2 *e,int code,int x,int y,int width,int height){
  int error = 1;

  if(e){
    error = removeSpriteAnimation(e->animation,code,x,y,width,height);
  }

  return error;
}

int setLifeSpanSpriteAnimationElementSDL2(ElementSDL2 * e,int code,int x,int y,int width,int height,unsigned lifespan){
  int error = 1;

  if(e){
    error = setLifeSpanSpriteAnimation(e->animation,code,x,y,width,height,lifespan);
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
  ListSprite *ls;
  unsigned i=0;

  if(e && e->animation->size){
    ls=e->animation->first;
    while(i<e->animation->size && ls->code != code){
      ls=ls->next;
      ++i;
    }
    if(i<e->animation->size){
      e->animation->current=ls;
      error = 0;
    }
  }

  return error;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Iterateur de structure sur la liste d'ElementSDL2 lié a un autre ElementSL2
 */
int initIterateurElementSDL2(ElementSDL2 *e){
  int succes = 0;
  
  if(e && e->interactions){
    e->interactions->current=e->interactions->first;
    succes = 1;
  }

  return succes;
}

ElementSDL2* nextIterateurElementSDL2(ElementSDL2 *e){
  ElementSDL2* next=NULL;
  
  if(e && e->interactions && e->interactions->current){
    next=e->interactions->current->element;
    e->interactions->current=e->interactions->current->next;
  }

  return next;
}
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Iterateur de structure sur la liste d'ElementSDL2
 */
int initIterateur(int displayCode){
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
 * modification d'un Element SDL2 spécifique aux Entry
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
      s=malloc((size_max+1)*sizeof(*s));
      error = 1;
      if(s){
	strncpy(s,e->police->text,size_max);
	s[size_max]='\0';
	PFREE(e->police->text);
	e->police->text=s;
	e->entry->size_max=size_max;
	error=actualizeTextFontSDL2(e->police,e->entry->isScripted);
      }
    }
  }

  return error;
}

int setScriptedEntrySDL2(ElementSDL2 *e,int isScripted){
  int error = 1;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->entry->isScripted!=isScripted){
    e->entry->isScripted=isScripted;
    error=actualizeTextFontSDL2(e->police,e->entry->isScripted);
  }

  return error;
}

int addCharEntrySDL2(ElementSDL2 *e,char c){
  int error = 1;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->police && e->police->text && e->entry->size < e->entry->size_max){
    *(e->police->text+e->entry->size)=c;
    ++e->entry->size;
    error=actualizeTextFontSDL2(e->police,e->entry->isScripted);
  }

  return error;
}

int removeCharEntrySDL2(ElementSDL2 *e){
  int error = 1;
  
  if(_windows_SANDAL2 && _windows_SANDAL2->current && e && e->entry && e->police && e->police->text && e->entry->size){
    --e->entry->size;
    *(e->police->text+e->entry->size)=' ';
    error=actualizeTextFontSDL2(e->police,e->entry->isScripted);
  }

  return error;
}
/* ------------------------------------------------------- */
