#include <stdio.h>

#include "../SANDAL2.h"

int main(){
  ElementSDL2 * objet;
  int run = 1;
  int tps = 0, ticks = 0;
  int noir[4] = {0,0,0,0};
  int i;
  SDL_Event event;
  
  if(initAllSDL2(IMG_INIT_PNG)){
    fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
    exit(-1);
  }

  /* initialisation de la fenetre */
  initWindowSDL2(400,400,"test",SDL_WINDOW_RESIZABLE,noir,1);
  if(initIteratorWindowSDL2()){
    closeAllSDL2();
    fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
    exit(-1);
  }

  objet = createImage(150.f,100.f,100.f,200.f,"spritesheet.png",1,0);
  for(i=0;i<6;++i){
    addSpriteElementSDL2(objet,400*i+100,0,200,400,10);
  }
  setWaySpriteElementSDL2(objet,1);
  addRotationSpeedElementSDL2(objet,1.f);
  
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
	keyReleasedWindowSDL2(event.key.keysym.sym);
	break;
      case SDL_KEYDOWN:
	keyPressedWindowSDL2(event.key.keysym.sym);
	break;
      case SDL_MOUSEBUTTONDOWN:
	clickWindowSDL2(event.button.x,event.button.y);
	break;
      case SDL_MOUSEBUTTONUP:
	unclickWindowSDL2(event.button.x,event.button.y);
	break;
      }
    }

    /* update de la fenetre */
    updateWindowSDL2();
    /* affichage de la fenetre */
    displayWindowSDL2();
    /* delai pour 60 frames/secondes */
    ticks = 16 - SDL_GetTicks() + tps;
    if(ticks>0){
      SDL_Delay(ticks);
    }
  }

  return 0;
}
