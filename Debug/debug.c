#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../SANDAL2.h"

void block(ElementSDL2 * this){
  printf("Block\n");
}

void action(ElementSDL2 * this){
  static int i=0;
  static int j = 10;
  static int colors[7][4]={{255,255,255,0},
			   {255,0,0,0},
			   {0,255,0,0},
			   {0,0,255,0},
			   {255,255,0,0},
			   {255,0,255,0},
			   {0,255,255,0}};
  ElementSDL2 *cour, *tmp;
  float x;
  int nb = 0;

  initIterateurElementSDL2(this);

  cour=nextIterateurElementSDL2(this);
  while(cour){
    tmp=nextIterateurElementSDL2(this);
    moveElementSDL2(cour,10.f,0.f);
    getCoordElementSDL2(cour,&x,NULL);
    if(x>800.f){
      delElementToElementSDL2(this,cour);
      removeElementSDL2(cour);
    }
    cour=tmp;
  }

  /*initIterateur(1);
  cour=nextElementSDL2();
  while((cour=nextElementSDL2())){
    ++nb;
    printf("(%f,%f)\n",cour->x,cour->y);
  }
  printf("total : %d\n",nb);
  */
  if(j){
    --j;
  }else{
    cour=createBlock(0.f,(float)((i*50)%750),50.f,50.f,colors[i%7],1,1);
    printf("New block\n");
    ++i;
    setActionElementSDL2(cour,block);
    addElementToElementSDL2(this,cour);
    j=100;
  }
}

int main(){
  ElementSDL2 * objet;
  int run = 1;
  int tps = 0, ticks = 0;
  int noir[4] = {0,0,0,0};
  int blanc[4] = {255,255,255,0};
  SDL_Event event;
  
  if(initAllSDL2(IMG_INIT_JPG)){
    fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
    exit(-1);
  }

  /* initialisation de la fenetre */
  initFenetreSDL2(800,800,"test",SDL_WINDOW_RESIZABLE,noir,1);
  if(initIteratorFenetreSDL2()){
    closeAllSDL2();
    fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
    exit(-1);
  }

  objet = createButtonImage(-300.f,200.f,200.f,300.f,0.8f,"arial.ttf","NSFW",blanc,"lion.jpg",1,1);
  setActionElementSDL2(objet,action);
  
  /* display de la fenetre */
  while(run){
    tps = SDL_GetTicks();
    /* gestion d'evenement */
    while(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_WINDOWEVENT:
	if(event.window.event == SDL_WINDOWEVENT_CLOSE)  {
	  run = 0;
	}
	break;
      case SDL_QUIT :   
	run = 0;
      case SDL_KEYUP:
	keyReleasedFenetreSDL2(event.key.keysym.sym);
	break;
      case SDL_KEYDOWN:
	keyPressedFenetreSDL2(event.key.keysym.sym);
	break;
      case SDL_MOUSEBUTTONDOWN:
	clickFenetreSDL2(event.button.x,event.button.y);
	break;
      }
    }

    /* update de la fenetre */
    updateFenetreSDL2();
    /* affichage de la fenetre */
    displayFenetreSDL2();
    /* delai pour 60 frames/secondes */
    ticks = 16 - SDL_GetTicks() + tps;
    if(ticks>0){
      SDL_Delay(ticks);
    }
  }

  return 0;
}
