#include "SDL2TK.h"

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

FenetreSDL2* initFenetreSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode){
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
      copyColor(fen->background,background);
      fen->liste = initListElementSDL2();
      if(!fen->liste){
	SDL_DestroyWindow(fen->window);
	SDL_DestroyRenderer(fen->renderer);
	free(fen);
	fen=NULL;
      }
    }else{
      SDL_DestroyWindow(fen->window);
      free(fen);
      fen=NULL;
    }
  }else{
    free(fen);
    fen=NULL;
  }

  return fen;
}

void updateFenetreSDL2(FenetreSDL2* fen){
  PtrElementSDL2 *ele;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;

  if(fen && fen->liste){
    /* update de la taille de la fenetre */
    SDL_GetWindowSize(fen->window,&(fen->width),&(fen->height));
    
    /* recherche de la liste d'element ayant le bon code de display */
    if(fen->liste->currentDCIterator && fen->liste->currentDCIterator->code<=fen->displayCode){
      ldc=fen->liste->currentDCIterator;
    }else{
      ldc=fen->liste->first;
    }
    while(ldc && ldc->code<fen->displayCode){
      ldc=ldc->next;
    }
    if(ldc && ldc->code==fen->displayCode){
      lp=ldc->first;
      while(lp){
	ele=lp->first;
	while(ele){
	  if(isDisplaied(fen,ele->element)){
	    if(ele->element->action){
	      ele->element->action(fen,ele->element);
	    }
	  }
	  ele=ele->next;
	}
	lp=lp->next;
      }
    }
  }
}

void displayFenetreSDL2(FenetreSDL2* fen){
  PtrElementSDL2 *ele;
  ListPtrElementSDL2 * lp;
  ListDCElementSDL2 * ldc;
  SDL_Rect r;
  int coul[4],iH,iW;

  if(fen && fen->liste){
    /* fond de la fenetre */
    copyColor(coul,fen->background);
    SDL_SetRenderDrawColor(fen->renderer,coul[0],coul[1],coul[2],coul[3]);
    SDL_RenderClear(fen->renderer);
    /* recherche de la liste d'element ayant le bon code de display */
    if(fen->liste->currentDCIterator && fen->liste->currentDCIterator->code<=fen->displayCode){
      ldc=fen->liste->currentDCIterator;
    }else{
      ldc=fen->liste->first;
    }
    while(ldc && ldc->code<fen->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==fen->displayCode){
      lp=ldc->first;
      while(lp){
	/* affichage des elements */
	ele=lp->first;
	while(ele){
	  if(isDisplaied(fen,ele->element)){
	    r.x=ele->element->x*fen->width/fen->initWidth;
	    r.y=ele->element->y*fen->height/fen->initHeight;
	    r.w=ele->element->width*fen->width/fen->initWidth;
	    r.h=ele->element->height*fen->height/fen->initHeight;
	    /* affichage du block */
	    if(ele->element->coulBlock[0]!=-1){
	      if(!cmpCoul(coul,ele->element->coulBlock)){
		SDL_SetRenderDrawColor(fen->renderer,coul[0],coul[1],coul[2],coul[3]);
	      }
	      SDL_RenderFillRect(fen->renderer,&r);
	    }
	    /* affichage de l'image */
	    if(ele->element->image){
	      SDL_RenderCopy(fen->renderer,ele->element->image,NULL,&r);
	    }
	    /* affichage du texte */
	    if(ele->element->police){
	      r.x+=r.w*(1.0-ele->element->textSize)/2;
	      r.y+=r.h*(1.0-ele->element->textSize)/2;
	      r.w*=ele->element->textSize;
	      r.h*=ele->element->textSize;
	      SDL_QueryTexture(ele->element->police->texture,NULL,NULL,&iW,&iH);
	      SDL_RenderCopy(fen->renderer,ele->element->police->texture,NULL,&r);
	    }
	  }
	  ele=ele->next;
	}
	lp=lp->next;
      }
    }
    SDL_RenderPresent(fen->renderer);
  }
}

void clickFenetreSDL2(FenetreSDL2* f,int x,int y){
  PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;
  int xE,yE;

  if(f && f->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(f->liste->currentDCIterator && f->liste->currentDCIterator->code<=f->displayCode){
      ldc=f->liste->currentDCIterator;
    }else{
      ldc=f->liste->first;
    }
    while(ldc && ldc->code<f->displayCode){
      ldc=ldc->next;
    }

    if(ldc && ldc->code==f->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  xE=e->element->x*f->width/f->initWidth;
	  yE=e->element->y*f->height/f->initHeight;
	  if(isDisplaied(f,e->element) && x>=xE && x<=xE+e->element->width*f->width/f->initWidth && y>=yE && y<=yE+e->element->height*f->height/f->initHeight){
	    if(e->element->entry){
	      e->element->entry->isSelect=1;
	    }
	    if(e->element->onClick){
	      e->element->onClick(f,e->element);
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

void keyPressFenetreSDL2(FenetreSDL2* f,char c){
  PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;

  if(f && f->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(f->liste->currentDCIterator && f->liste->currentDCIterator->code<=f->displayCode){
      ldc=f->liste->currentDCIterator;
    }else{
      ldc=f->liste->first;
    }
    while(ldc && ldc->code<f->displayCode){
      lp=lp->next;
    }

    if(ldc && ldc->code==f->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  if(e->element->keyPress && (!e->element->entry || e->element->entry->isSelect)){
	    e->element->keyPress(f,e->element,c);
	  }
	  e=e->next;
	}
	lp=lp->next;
      }
    }
  }
}

void keyReleasedFenetreSDL2(FenetreSDL2* f,char c){
    PtrElementSDL2 *e;
  ListPtrElementSDL2 *lp;
  ListDCElementSDL2 *ldc;

  if(f && f->liste){
    /* recherche de la liste d'element ayant le bon code de display */
    if(f->liste->currentDCIterator && f->liste->currentDCIterator->code<=f->displayCode){
      ldc=f->liste->currentDCIterator;
    }else{
      ldc=f->liste->first;
    }
    while(ldc && ldc->code<f->displayCode){
      lp=lp->next;
    }

    if(ldc && ldc->code==f->displayCode){
      lp=ldc->first;
      while(lp){
	e=lp->first;
	while(e){
	  if(e->element->keyReleased && (!e->element->entry || e->element->entry->isSelect)){
	    e->element->keyReleased(f,e->element,c);
	  }
	  e=e->next;
	}
	lp=lp->next;
      }
    }
  }
}
/* ------------------------------------------------------- */
