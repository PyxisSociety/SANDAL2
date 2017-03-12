#include "SANDAL2.h"

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

int initTexte(){
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

void closeTexte(){
  TTF_Quit();
}
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Fenetre SDL2
 */
void freeFenetreSDL2(FenetreSDL2 *fen){
  if(fen){
    if(fen->liste){
      freeListElementSDL2(fen->liste);
    }
    if(fen->window){
      SDL_DestroyWindow(fen->window);
    }
    if(fen->renderer){
      SDL_DestroyRenderer(fen->renderer);
    }
  }
}

void initFenetreSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode){
  FenetreSDL2 *fen=malloc(sizeof(*fen));
  int erreur = 0;

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
      fen->initHeight=height;
      fen->initWidth=width;
      fen->displayCode=displayCode;
      fen->next = NULL;
      copyColor(fen->background,background);
      fen->liste = initListElementSDL2();
      if(!fen->liste){
	SDL_DestroyWindow(fen->window);
	SDL_DestroyRenderer(fen->renderer);
	free(fen);
      }else{
	if(!_windows_SDL2TK){
	  _windows_SDL2TK = malloc(sizeof(*_windows_SDL2TK));
	  if(_windows_SDL2TK){
	    _windows_SDL2TK->first = fen;
	    _windows_SDL2TK->last = fen;
	    _windows_SDL2TK->current = fen;
	  }else{
	    SDL_DestroyWindow(fen->window);
	    SDL_DestroyRenderer(fen->renderer);
	    free(fen);
	  }
	}else{
	  _windows_SDL2TK->last->next=fen;
	  _windows_SDL2TK->last=fen;
	}
      }
    }else{
      SDL_DestroyWindow(fen->window);
      free(fen);
    }
  }else{
    free(fen);
  }
}

void updateFenetreSDL2(){
  PtrElementSDL2 **ele;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;

  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->liste){
    /* update de la taille de la fenetre */
    SDL_GetWindowSize(_windows_SDL2TK->current->window,&(_windows_SDL2TK->current->width),&(_windows_SDL2TK->current->height));
    
    /* recherche de la liste d'element ayant le bon code de display */
    if(_windows_SDL2TK->current->liste->currentDCIterator && _windows_SDL2TK->current->liste->currentDCIterator->code<=_windows_SDL2TK->current->displayCode){
      ldc=_windows_SDL2TK->current->liste->currentDCIterator;
    }else{
      ldc=_windows_SDL2TK->current->liste->first;
    }
    while(ldc && ldc->code<_windows_SDL2TK->current->displayCode){
      ldc=ldc->next;
    }
    if(ldc && ldc->code==_windows_SDL2TK->current->displayCode){
      lp=ldc->first;
      while(lp){
	ele=&(lp->first);
	while(*ele){
	  if(isDisplaied((*ele)->element)){
	    if((*ele)->element->action){
	      (*ele)->element->action((*ele)->element);
	    }
	    if((*ele)->element->rotSpeed != 0.f){
	      (*ele)->element->rotation = ((*ele)->element->rotation + (*ele)->element->rotSpeed > 360.f ? (*ele)->element->rotation + (*ele)->element->rotSpeed - 360.f : (*ele)->element->rotation + (*ele)->element->rotSpeed);
	    }
	  }
	  ele=&((*ele)->next);
	}
	lp=lp->next;
      }
      cleanElementSDL2();
    }
  }
}

void displayFenetreSDL2(){
  PtrElementSDL2 *ele;
  ListPtrElementSDL2 * lp;
  ListDCElementSDL2 * ldc;
  SDL_Rect r;
  int coul[4],iH,iW,i,j;
  SDL_Point p;

  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->liste){
    /* fond de la fenetre */
    copyColor(coul,_windows_SDL2TK->current->background);
    SDL_SetRenderDrawColor(_windows_SDL2TK->current->renderer,coul[0],coul[1],coul[2],coul[3]);
    SDL_RenderClear(_windows_SDL2TK->current->renderer);
    /* recherche de la liste d'element ayant le bon code de display */
    if(_windows_SDL2TK->current->liste->currentDCIterator && _windows_SDL2TK->current->liste->currentDCIterator->code<=_windows_SDL2TK->current->displayCode){
      ldc=_windows_SDL2TK->current->liste->currentDCIterator;
    }else{
      ldc=_windows_SDL2TK->current->liste->first;
    }
    while(ldc && ldc->code<_windows_SDL2TK->current->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==_windows_SDL2TK->current->displayCode){
      lp=ldc->first;
      while(lp){
	/* affichage des elements */
	ele=lp->first;
	while(ele){
	  if(isDisplaied(ele->element)){
	    r.x=ele->element->x*_windows_SDL2TK->current->width/_windows_SDL2TK->current->initWidth;
	    r.y=ele->element->y*_windows_SDL2TK->current->height/_windows_SDL2TK->current->initHeight;
	    r.w=ele->element->width*_windows_SDL2TK->current->width/_windows_SDL2TK->current->initWidth;
	    r.h=ele->element->height*_windows_SDL2TK->current->height/_windows_SDL2TK->current->initHeight;
	    /* affichage du block */
	    if(ele->element->coulBlock[0]!=-1 && !ele->element->image){
	      if(!cmpCoul(coul,ele->element->coulBlock)){
		SDL_SetRenderDrawColor(_windows_SDL2TK->current->renderer,coul[0],coul[1],coul[2],coul[3]);
	      }
	      SDL_RenderFillRect(_windows_SDL2TK->current->renderer,&r);
	    }
	    /* affichage de l'image */
	    if(ele->element->image){
	      if(ele->element->rotation == 0.f){
		SDL_RenderCopy(_windows_SDL2TK->current->renderer,ele->element->image,NULL,&r);
	      }else{
		p.x=(int)(ele->element->prX*ele->element->width*_windows_SDL2TK->current->width/_windows_SDL2TK->current->initWidth);
		p.y=(int)(ele->element->prY*ele->element->height*_windows_SDL2TK->current->height/_windows_SDL2TK->current->initHeight);
		SDL_RenderCopyEx(_windows_SDL2TK->current->renderer,ele->element->image,NULL,&r,(double)ele->element->rotation,&p,SDL_FLIP_NONE);
	      }
	    }
	    /* affichage du texte */
	    if(ele->element->police){
	      r.x+=r.w*(1.0-ele->element->textSize)/2;
	      r.y+=r.h*(1.0-ele->element->textSize)/2;
	      r.w*=ele->element->textSize;
	      r.h*=ele->element->textSize;
	      SDL_QueryTexture(ele->element->police->texture,NULL,NULL,&iW,&iH);
	      if(ele->element->rotation == 0.f || (ele->element->coulBlock[0]!=-1 && !ele->element->image)){
		SDL_RenderCopy(_windows_SDL2TK->current->renderer,ele->element->police->texture,NULL,&r);
	      }else{
		p.x=(int)(ele->element->textSize*ele->element->prX*ele->element->width*_windows_SDL2TK->current->width/_windows_SDL2TK->current->initWidth);
		p.y=(int)(ele->element->textSize*ele->element->prY*ele->element->height*_windows_SDL2TK->current->height/_windows_SDL2TK->current->initHeight);
		SDL_RenderCopyEx(_windows_SDL2TK->current->renderer,ele->element->police->texture,NULL,&r,(double)ele->element->rotation,&p,SDL_FLIP_NONE);
	      }
	    }
	  }
	  ele=ele->next;
	}
	lp=lp->next;
      }
    }
    SDL_RenderPresent(_windows_SDL2TK->current->renderer);
  }
}

void clickFenetreSDL2(int x,int y){
  PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;
  float newX,newY,c,s,xtmp,prX,prY;
  float rot = 0.f;
  int red[4] = {255,0,0,0};

  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(_windows_SDL2TK->current->liste->currentDCIterator && _windows_SDL2TK->current->liste->currentDCIterator->code<=_windows_SDL2TK->current->displayCode){
      ldc=_windows_SDL2TK->current->liste->currentDCIterator;
    }else{
      ldc=_windows_SDL2TK->current->liste->first;
    }
    while(ldc && ldc->code<_windows_SDL2TK->current->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==_windows_SDL2TK->current->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  if(isDisplaied(e->element)){
	    newX=x*_windows_SDL2TK->current->initWidth/_windows_SDL2TK->current->width;
	    newY=y*_windows_SDL2TK->current->initHeight/_windows_SDL2TK->current->height;
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
	    //printf("%f - %f\n",newX,newY);
	    if(hitListHitBox(e->element->hitboxes,newX,newY)){
	      //createBlock((float)x,(float)y,5.f,5.f,red,1,0,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	      if(e->element->entry){
		e->element->entry->isSelect=1;
	      }
	      if(e->element->onClick){
		e->element->onClick(e->element);
	      }
	    }
	  }else if(e->element->entry){
	    e->element->entry->isSelect=0;
	  }
	  e=e->next;
	}
	lp=lp->next;
      }
    }
  }
}

void unclickFenetreSDL2(int x,int y){
  PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;
  float newX,newY,c,s,xtmp;
  float rot = 0.f;

  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(_windows_SDL2TK->current->liste->currentDCIterator && _windows_SDL2TK->current->liste->currentDCIterator->code<=_windows_SDL2TK->current->displayCode){
      ldc=_windows_SDL2TK->current->liste->currentDCIterator;
    }else{
      ldc=_windows_SDL2TK->current->liste->first;
    }
    while(ldc && ldc->code<_windows_SDL2TK->current->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==_windows_SDL2TK->current->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  if(isDisplaied(e->element)){
	    newX=(x*_windows_SDL2TK->current->initWidth/_windows_SDL2TK->current->width-e->element->x)/(e->element->width);
	    newY=(y*_windows_SDL2TK->current->initHeight/_windows_SDL2TK->current->height-e->element->y)/(e->element->height);
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
	    if(hitListHitBox(e->element->hitboxes,newX,newY)){
	      if(e->element->entry){
		e->element->entry->isSelect=1;
	      }
	      if(e->element->unClick){
		e->element->unClick(e->element);
	      }
	    }
	  }else if(e->element->entry){
	    e->element->entry->isSelect=0;
	  }
	  e=e->next;
	}
	lp=lp->next;
      }
    }
  }
}

void keyPressedFenetreSDL2(char c){
  PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;

  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(_windows_SDL2TK->current->liste->currentDCIterator && _windows_SDL2TK->current->liste->currentDCIterator->code<=_windows_SDL2TK->current->displayCode){
      ldc=_windows_SDL2TK->current->liste->currentDCIterator;
    }else{
      ldc=_windows_SDL2TK->current->liste->first;
    }
    while(ldc && ldc->code<_windows_SDL2TK->current->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==_windows_SDL2TK->current->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  if(e->element->keyPress && (!e->element->entry || e->element->entry->isSelect)){
	    e->element->keyPress(e->element,c);
	  }
	  e=e->next;
	}
	lp=lp->next;
      }
    }
  }
}

void keyReleasedFenetreSDL2(char c){
  PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;

  if(_windows_SDL2TK && _windows_SDL2TK->current && _windows_SDL2TK->current->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(_windows_SDL2TK->current->liste->currentDCIterator && _windows_SDL2TK->current->liste->currentDCIterator->code<=_windows_SDL2TK->current->displayCode){
      ldc=_windows_SDL2TK->current->liste->currentDCIterator;
    }else{
      ldc=_windows_SDL2TK->current->liste->first;
    }
    while(ldc && ldc->code<_windows_SDL2TK->current->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==_windows_SDL2TK->current->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  if(e->element->keyReleased && (!e->element->entry || e->element->entry->isSelect)){
	    e->element->keyReleased(e->element,c);
	  }
	  e=e->next;
	}
	lp=lp->next;
      }
    }
  }
}


void updateAllFenetreSDL2(){
  if(initIteratorFenetreSDL2()){
    do{
      updateFenetreSDL2();
    }while(nextFenetreSDL2());
  }
}

void displayAllFenetreSDL2(){
  if(initIteratorFenetreSDL2()){
    do{
      displayFenetreSDL2();
    }while(nextFenetreSDL2());
  }
}

void clickAllFenetreSDL2(int x,int y){
  if(initIteratorFenetreSDL2()){
    do{
      clickFenetreSDL2(x,y);
    }while(nextFenetreSDL2());
  }
}

void unclickAllFenetreSDL2(int x,int y){
  if(initIteratorFenetreSDL2()){
    do{
      unclickFenetreSDL2(x,y);
    }while(nextFenetreSDL2());
  }
}

void keyPressedAllFenetreSDL2(char c){
  if(initIteratorFenetreSDL2()){
    do{
      keyPressedFenetreSDL2(c);
    }while(nextFenetreSDL2());
  }
}

void keyReleasedAllFenetreSDL2(char c){
  if(initIteratorFenetreSDL2()){
    do{
      keyReleasedFenetreSDL2(c);
    }while(nextFenetreSDL2());
  }
}

void closeFenetreSDL2(){
  FenetreSDL2 * f, * tmp;
  
  if(_windows_SDL2TK && _windows_SDL2TK->current){
    f=_windows_SDL2TK->current;
    if(f == _windows_SDL2TK->first){
      _windows_SDL2TK->first = _windows_SDL2TK->first->next;
    }else{
      tmp=_windows_SDL2TK->first;
      while(tmp && tmp->next!=f){
	tmp=tmp->next;
      }
      if(tmp){
	tmp->next=f->next;
      }
    }
    _windows_SDL2TK->current=_windows_SDL2TK->current->next;
    freeFenetreSDL2(f);
    if(!_windows_SDL2TK->first){
      free(_windows_SDL2TK);
      _windows_SDL2TK = NULL;
    }
  }
}

void closeAllFenetreSDL2(){
  FenetreSDL2 *f, *tmp;

  if(_windows_SDL2TK && _windows_SDL2TK->first){
    f=_windows_SDL2TK->first;
    while(f){
      tmp=f;
      f=f->next;
      freeFenetreSDL2(tmp);
    }
    free(_windows_SDL2TK);
    _windows_SDL2TK=NULL;
  }
}
/* ------------------------------------------------------- */
