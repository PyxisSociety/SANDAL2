#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../SDL2TK.h"

void click(ElementSDL2 * this){
  static int i=0;
  //printf("%d\n",++i);
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
  initFenetreSDL2(800,800,"teste rotation continue",SDL_WINDOW_RESIZABLE,noir,1);
  if(initIteratorFenetreSDL2()){
    closeAllSDL2();
    fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
    exit(-1);
  }

  objet = createButtonImage(300.f,200.f,200.f,300.f,0.8f,"arial.ttf","NSFW",blanc,"lion.jpg",1,1,click,NULL,NULL,NULL,NULL,rectangleHitBox(0.f,0.f,1.f,1.f),NULL);
  if(objet){
    addAngleElementSDL2(objet,45.f);
  }else{
    run = 0;
  }
  
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
