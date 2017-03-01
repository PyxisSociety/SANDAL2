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

void addPtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e){
  DisplayCode *d;
  PtrElementSDL2 *p;
  
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
      }
    }
  }
}

void removePtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e){
  PtrElementSDL2 * p, * tmp;
  
  if(l && e){
    p=l->first;
    tmp=NULL;
    while(p && p->element!=e){
      tmp=p;
      p=p->next;
    }
    if(p){
      if(p==l->current){
	l->current=l->current->next;
      }
      if(p==l->last){
	l->last=p;
      }
      if(p==l->first){
	l->first=l->first->next;
      }
      if(tmp){
	tmp->next=p->next;
      }
      free(p);
    }
  }
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

void addListPtrElementSDL2(ListDCElementSDL2* l, ListPtrElementSDL2 *lp){
  ListPtrElementSDL2 **cour;

  if(l && lp){
    cour = &(l->first);
    while(*cour && (*cour)->code > lp->code){
      *cour=(*cour)->next;
    }
    if(lp->code != (*cour)->code){
      lp->next=*cour;
      *cour=lp;
    }
  }
}

void removeListPtrElementSDL2(ListDCElementSDL2* l,ListPtrElementSDL2 *lp){
  ListPtrElementSDL2 **cour, *tmp;

  if(l && lp){
    cour = &(l->first);
    while(*cour && (*cour)->code < lp->code){
      *cour=(*cour)->next;
    }
    if(lp == *cour){
      tmp=(*cour)->next;
      freeListPtrElementSDL2(*cour);
      *cour=tmp;
    }
  }
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

void addElementSDL2(FenetreSDL2* f,ElementSDL2* e){
  DisplayCode *d;
  ListDCElementSDL2 ** ldc, *dctmp;
  ListPtrElementSDL2 ** lp, *ptmp;
  
  if(f && f->liste && e && e->codes){
    d=e->codes->first;
    ldc=&(f->liste->first);
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
	dctmp->next=(*ldc)->next;
	(*ldc)->next=dctmp;
	*ldc=(*ldc)->next;
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
  }
}

void removeElementSDL2(FenetreSDL2* f,ElementSDL2* e){
  DisplayCode ** d, *tmp;
  ListPtrElementSDL2 ** lp, *ptmp;
  ListDCElementSDL2 ** ldc, *dctmp;
  
  if(f && f->liste && e && e->codes){
    d=&(e->codes->first);
    ldc=&(f->liste->first);
    while(*d && *ldc){
      while(*ldc && (*ldc)->code<(*d)->code){
	ldc=&((*ldc)->next);
      }
      if(*ldc && (*ldc)->code==(*d)->code){
	lp=&((*ldc)->first);
	while(*lp && (*lp)->code > (*d)->plan){
	  lp=&((*lp)->next);
	}
	if(*lp && (*lp)->code == (*d)->plan){
	  removePtrElementSDL2(*lp,e);
	  tmp=*d;
	  *d=(*d)->next;
	  free(tmp);
	  if(!e->codes || !e->codes->first){
	    freeElementSDL2(e);
	    *d=NULL;
	  }
	  if(!(*lp)->first){
	    ptmp=*lp;
	    *lp=(*lp)->next;
	    free(ptmp);
	  }
	  if(!(*ldc)->first){
	    dctmp=*ldc;
	    *ldc=(*ldc)->next;
	    free(dctmp);
	  }
	}
      }
      if(*d){
	d=&((*d)->next);
      }
    }
  }
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element SDL2
 */
void freeElementSDL2(ElementSDL2 *e){
  if(e){
    freeListDisplayCode(e->codes);
    if(e->image){
      SDL_DestroyTexture(e->image);
    }
    freeFontSDL2(e->police);
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
    free(e);
  }    
}

ElementSDL2* createBlock(FenetreSDL2 *window,float x,float y,float width,float height,int couleur[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),void * data){
  ElementSDL2 *e=malloc(sizeof(*e));
  if(e){
    e->x=x;
    e->y=y;
    e->width=width;
    e->height=height;
    copyColor(e->coulBlock,couleur);
    e->codes=initListDisplayCode();
    addDisplayCode(e->codes,displayCode,1,plan);
    e->action=action;
    e->onClick=onClick;
    e->keyPress=keyPress;
    e->keyReleased=keyReleased;
    e->image=NULL;
    e->police=NULL;
    e->entry=NULL;
    e->interactions=NULL;
    e->data=data;
  }

  return e;
}

ElementSDL2* createTexte(FenetreSDL2 *window,float x,float y,float width,float height,char * font,char * text,int textColor[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),void * data){
  ElementSDL2 *e=malloc(sizeof(*e));
  FontSDL2 * f;

  if(e && window){
    e->x=x;
    e->y=y;
    e->width=width;
    e->height=height;
    e->textSize=1.0f;
    e->image=NULL;
    e->entry=NULL;
    e->interactions=NULL;
    e->data=NULL;
    e->codes=NULL;
    f=createFontSDL2(window,font,text,textColor);
    if(f){
      e->police=f;
      e->codes=initListDisplayCode();
      addDisplayCode(e->codes,displayCode,1,plan);
      e->coulBlock[0]=-1;
      e->action=action;
      e->onClick=onClick;
      e->keyPress=keyPress;
      e->keyReleased=keyReleased;
      e->data=data;
    }else{
      freeElementSDL2(e);
      e=NULL;
    }
  }

  return e;
}

ElementSDL2* createImage(FenetreSDL2 *window,float x,float y,float width,float height,char *image,int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),void * data){
  ElementSDL2 *e=NULL;
  SDL_Surface *s;

  s=IMG_Load(image);
  
  if(s){
    e=malloc(sizeof(*e));
    if(e && window){
      e->x=x;
      e->y=y;
      e->width=width;
      e->height=height;
      e->image=SDL_CreateTextureFromSurface(window->renderer,s);
      e->codes=initListDisplayCode();
      addDisplayCode(e->codes,displayCode,1,plan);
      e->coulBlock[0]=-1;
      e->action=action;
      e->onClick=onClick;
      e->keyPress=keyPress;
      e->keyReleased=keyReleased;
      e->police=NULL;
      e->entry=NULL;
      e->interactions=NULL;
      e->data=data;
    }
    SDL_FreeSurface(s);
  }

  return e;
}

ElementSDL2* createButton(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),void * data){
  ElementSDL2 *e=createBlock(window,x,y,width,height,couleurBlock,displayCode,plan,onClick,keyPress,keyReleased,action,data);
  FontSDL2 * f;

  if(e){
    e->textSize=texteSize/100.0f;
    f=createFontSDL2(window,font,e->police->text,textColor);
    if(f){
      e->police=f;
    }else{
      freeElementSDL2(e);
      e=NULL;
    }
  }

  return e;
}

ElementSDL2* createButtonImage(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),void * data){
  ElementSDL2 *e=createImage(window,x,y,width,height,image,displayCode,plan,onClick,keyPress,keyReleased,action,data);
  FontSDL2 * f;

  if(e){
    e->textSize=texteSize/100.0f;
    f=createFontSDL2(window,font,e->police->text,textColor);
    if(f){
      e->police=f;
    }else{
      freeElementSDL2(e);
      e=NULL;
    }
  }

  return e;
}

ElementSDL2* createEntry(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),int min,int max,int isScripted,void * data){
  ElementSDL2 *e=createButton(window,x,y,width,height,texteSize,font,text,textColor,couleurBlock,displayCode,plan,onClick,keyPress,keyReleased,action,data);
  EntrySDL2 *ent;
  int i;

  if(e){
    ent=malloc(sizeof(*ent));
    if(ent){
      ent->size_min=min;
      ent->size_max=max;
      ent->isSelect=0;
      ent->isScripted=isScripted;
      PFREE(e->police->text);
      e->police->text=malloc((max+1)*sizeof(*(e->police->text)));
      for(i=0;i<max;++i){
	e->police->text[i]=' ';
      }
      e->police->text[max]='\0';
      e->entry=ent;
      ent->size=0;
    }else{
      freeElementSDL2(e);
      e=NULL;
    }
  }
  
  return e;  
}

ElementSDL2* createEntryImage(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),int min,int max,int isScripted,void * data){
  ElementSDL2 *e=createButtonImage(window,x,y,width,height,texteSize,font,text,textColor,image,displayCode,plan,onClick,keyPress,keyReleased,action,data);
  EntrySDL2 *ent;
  int i;

  if(e){
    ent=malloc(sizeof(*ent));
    if(ent){
      ent->size_min=min;
      ent->size_max=max;
      ent->isSelect=0;
      ent->isScripted=isScripted;
      PFREE(e->police->text);
      e->police->text=malloc((max+1)*sizeof(*(e->police->text)));
      for(i=0;i<max;++i){
	e->police->text[i]=' ';
      }
      e->police->text[max]='\0';
      e->entry=ent;
      ent->size=0;
    }else{
      freeElementSDL2(e);
      e=NULL;
    }
  }
  
  return e;  
}

int isDisplaied(FenetreSDL2 *f,ElementSDL2 *e){
  DisplayCode *d;
  int resultat = 0;

  if(e && f){
    d=e->codes->first;
    while(d && d->code<f->displayCode){
      d=d->next;
    }
    resultat = d && d->code==f->displayCode;
  }

  return resultat;
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2
 */
void changeFontElementSDL2(FenetreSDL2 * fen,ElementSDL2 *e,char * font){
  FontSDL2 *f;
  int color[4];

  if(e && font && e->police){
    color[0]=e->police->color.r;
    color[1]=e->police->color.g;
    color[2]=e->police->color.b;
    color[3]=e->police->color.a;
    f=createFontSDL2(fen,font,e->police->text,color);
    freeFontSDL2(e->police);
    e->police=f;
  }
}

void changeTextElementSDL2(FenetreSDL2 * fen,ElementSDL2 *e,char * text){
  if(fen && e && text && e->police){
    changeTextFontSDL2(fen,e->police,text);
  }
}

void changeColorElementSDL2(ElementSDL2 *e,int color[4]){
  if(e){
    copyColor(e->coulBlock,color);
  }
}

int changeImageElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,char *image){
  SDL_Surface *s;
  int changed=0;
  
  if(e && f){
    if(image){
      s=IMG_Load(image);
      if(s){
	e->image=SDL_CreateTextureFromSurface(f->renderer,s);
	SDL_FreeSurface(s);
	changed=1;
      }
    }else{
      if(e->image){
	SDL_DestroyTexture(e->image);
      }
      e->image=NULL;
      changed=1;
    }
  }

  return changed;
}

void replaceElementSDL2(FenetreSDL2 *window,ElementSDL2 *e,float x,float y){
  if(e && window){
    e->x=x;
    e->y=y;
  }
}

void moveElementSDL2(FenetreSDL2 *window,ElementSDL2 *e,float x,float y){
  if(e && window){
    e->x+=x;
    e->y+=y;
  }
}

void resizeElementSDL2(ElementSDL2 *e,float width,float height){
  if(e){
    e->width=width;
    e->height=height;
  }
}

void changeTextSize(ElementSDL2 *e,float textSize){
  if(e){
    e->textSize=textSize/100.0;
  }
}

void addDisplayCodeElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,int displayCode, int plan){
  int suppr = 0, was;
  DisplayCode **d, *tmp;
  ListDCElementSDL2 **ldc, *dctmp;
  ListPtrElementSDL2 **lp, *ptmp,**lpDel = NULL;
  PtrElementSDL2 **cour, *el;

  if(f && f->liste && e && e->codes){
    d=&(e->codes->first);
    while(*d && (*d)->code<displayCode){
      d=&((*d)->next);
    }
    if(!(*d && (*d)->code==displayCode && (*d)->plan==plan)){ 
      if(*d && (*d)->code == displayCode){
	suppr=1;
	was = (*d)->plan;
	(*d)->plan=plan;
      }else{
	tmp=malloc(sizeof(*tmp));
	tmp->code=displayCode;
	tmp->plan = plan;
	tmp->next=*d;
	*d=tmp;
      }
      ldc=&(f->liste->first);
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
	if(suppr && (*lp)->code == was){
	  lpDel=lp;
	}
	lp=&((*lp)->next);
      }
      if((!*lp || (*lp)->code != plan)){
	ptmp=initListPtrElementSDL2(plan);
	ptmp->next=*lp;
	*lp=ptmp;
      }
      el=malloc(sizeof(*el));
      el->next=NULL;
      el->element=e;
      if((*lp)->last){
	(*lp)->last->next=el;
      }else{
	(*lp)->first=el;
      }
      (*lp)->last=el;
      if(suppr){
	if(!lpDel){
	  lpDel=lp;
	  while(*lpDel && (*lpDel)->code > plan){
	    lpDel=&((*lpDel)->next);
	  }
	}
	if(*lpDel){
	  cour=&((*lp)->first);
	  while(*cour && (*cour)->element!=e){
	    cour=&((*cour)->next);
	  }
	  if(*cour && (*cour)->element==e){
	    el=(*cour)->next;
	    free(*cour);
	    *cour=el;
	  }
	}
      }
    }
  }
}

void removeDisplayCodeElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,int displayCode){
  DisplayCode **d, *tmp;
  ListDCElementSDL2 **ldc, *dctmp;
  ListPtrElementSDL2 **lp, *ptmp;
  PtrElementSDL2 **cour, *etmp;

  if(f && f->liste && e && e->codes){
    d=&(e->codes->first);
    while(*d && (*d)->code < displayCode){
      d=&((*d)->next);
    }
    if(*d && (*d)->code==displayCode){
      ldc=&(f->liste->first);
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
	  if(*cour && (*cour)->element){
	    etmp=(*cour)->next;
	    free(*cour);
	    *cour=etmp;
	  }
	}
      }
      tmp=(*d)->next;
      free(*d);
      *d=tmp;
      if(!e->codes->first){
	freeElementSDL2(e);
      }
    }
  }
}

void setDisplayElementSDL2(ElementSDL2 *e,int displayCode,int isDisplaied){
  DisplayCode *d;

  if(e){
    d=e->codes->first;
    while(d && d->code<displayCode){
      d=d->next;
    }
    if(d && d->code==displayCode){
      d->isDisplaied=isDisplaied;
    }
  }
}

void setPlanElementSDL2(FenetreSDL2 * f,ElementSDL2 *e,int displayCode,int plan){
  int found = 0, old;
  DisplayCode *d;
  ListDCElementSDL2 *ldc;
  ListPtrElementSDL2 **lp, *ptmp, **lpNew = NULL;
  PtrElementSDL2 **cour,*tmp;

  if(e){
    d=e->codes->first;
    while(d && d->code<displayCode){
      d=d->next;
    }
    if(d && d->code==displayCode && d->plan != plan){
      old = d->plan;
      d->plan = plan;
      if(f && f->liste){
	ldc=f->liste->first;
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
	  if(*cour && (*cour)->element==e){
	    tmp=(*cour)->next;
	    free(*cour);
	    *cour=tmp;
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
	  tmp->element=e;
	  tmp->next=(*lpNew)->last;
	  (*lpNew)->last=tmp;
	}
      }
    }
  }
}

void changeActionElementSDL2(ElementSDL2 *e,void (*action)(FenetreSDL2 *,ElementSDL2*)){
  if(e){
    e->action=action;
  }
}

void changeKeyPressElementSDL2(ElementSDL2 *e,void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode c)){
  if(e){
    e->keyPress=keyPress;
  }
}

void changeKeyReleasedElementSDL2(ElementSDL2 *e,void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode c)){
  if(e){
    e->keyReleased=keyReleased;
  }
}

void changeOnClickElementSDL2(ElementSDL2 *e,void (*onCLick)(FenetreSDL2 *,ElementSDL2*)){
  if(e){
    e->onClick=onCLick;
  }
}

void addElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *add){
  PtrElementSDL2 *pe;
  if(e && add){
    pe=malloc(sizeof(*pe));
    pe->element=add;
    pe->next=NULL;
    
    if(!e->interactions){
      e->interactions=malloc(sizeof(*(e->interactions)));
      e->interactions->first=pe;
      e->interactions->last=pe;
      e->interactions->current=pe;
    }else{
      e->interactions->last->next=pe;
      e->interactions->last=pe;
    }
  }
}

void delElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *del){
  PtrElementSDL2 **pe, *tmp;

  if(e && del){
    pe=&(e->interactions->first);

    while(*pe!=e->interactions->last && (*pe)->element!=del){
      pe=&((*pe)->next);
    }

    if(*pe && (*pe)->element==del){
      tmp=*pe;
      *pe=(*pe)->next;
      free(tmp);
    }
  }
      
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
int initIterateur(FenetreSDL2 *f, int displayCode){
  int succes = 0;
  ListDCElementSDL2 *lp;
  
  if(f && f->liste){
    if(f->liste->currentDCIterator && f->liste->currentDCIterator->code == displayCode){
      f->liste->currentPIterator=f->liste->currentDCIterator->first;
      f->liste->currentPIterator->current=f->liste->currentPIterator->first;
    }else{
      if(f->liste->currentDCIterator && f->liste->currentDCIterator->code < displayCode){
	lp=f->liste->currentDCIterator;
      }else{
	lp=f->liste->first;
      }
      while(lp->code < displayCode){
	lp=lp->next;
      }
      if(lp && lp->code==displayCode){
	f->liste->currentDCIterator=lp;
	f->liste->currentPIterator=lp->first;
	lp->first->current=lp->first->first;
	succes=1;
      }
    }
  }

  return succes;
}

ElementSDL2* nextElementSDL2(FenetreSDL2 *f){
  ListPtrElementSDL2 *lp;
  ElementSDL2 *res = NULL;
  PtrElementSDL2 *pres;
  
  if(f && f->liste && f->liste->currentDCIterator){
    if(f->liste->currentPIterator){
      pres=f->liste->currentPIterator->current;
      if(pres){
	f->liste->currentPIterator->current = f->liste->currentPIterator->current->next;
	res=pres->element;
      }else{
	f->liste->currentPIterator = f->liste->currentPIterator->next;
	if(f->liste->currentPIterator){
	  f->liste->currentPIterator->current=f->liste->currentPIterator->first->next;
	  res=f->liste->currentPIterator->first->element;
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
void changeSizeEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e,int size_min,int size_max){
  char *s;
  if(e && e->entry){
    if(size_min>-1 && size_min<=size_max){
      e->entry->size_min=size_min;
    }
    if(size_max>-1 && size_max>=size_min && size_max!=e->entry->size_max){
      s=malloc((size_max+1)*sizeof(*s));
      strncpy(s,e->police->text,size_max);
      s[size_max]='\0';
      PFREE(e->police->text);
      e->police->text=s;
      e->entry->size_max=size_max;
      actualizeTextFontSDL2(f,e->police,e->entry->isScripted);
    }
  }
}

void setScriptedEntrySDL2(FenetreSDL2* f,ElementSDL2 *e,int isScripted){
  if(e && e->entry && e->entry->isScripted!=isScripted){
    e->entry->isScripted=isScripted;
    actualizeTextFontSDL2(f,e->police,e->entry->isScripted);
  }
}

void addCharEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e,char c){
  if(e && e->entry && e->police && e->police->text && e->entry->size < e->entry->size_max){
    *(e->police->text+e->entry->size)=c;
    ++e->entry->size;
    actualizeTextFontSDL2(f,e->police,e->entry->isScripted);
  }
}

void removeCharEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e){
  if(e && e->entry && e->police && e->police->text && e->entry->size){
    --e->entry->size;
    *(e->police->text+e->entry->size)=' ';
    actualizeTextFontSDL2(f,e->police,e->entry->isScripted);
  }
}
/* ------------------------------------------------------- */
