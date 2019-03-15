#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SANDAL2/SANDAL2.h>

void keyWindow(SDL_Keycode c){
    static int start = 1;
    Uint32 id;

    if(start){
	printf("start: %u\n", initIteratorWindow());
	start = 0;
    }

    switch(c){
    case SDLK_a:
	id = nextWindow();
	if(id){
	    printf("next: %u\n", id);
	}else{
	    printf("start again: %u\n", initIteratorWindow());
	}
	break;
    case SDLK_b:
	setDisplayWindow(rand() % 4 + 2);
	break;
    }
}

int main(){
    int       run          = 1;
    int       tps          = 0;
    int       ticks        = 0;
    int       noir[4]      = {0,0,0,0};
    int       i            = 0;

    srand(time(0));
  
    if(initAllSANDAL2(IMG_INIT_JPG)){
	fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
	exit(-1);
    }

    for(i = 0; i < 4; ++i){
	/* initialisation des fenetres */
	if(!createWindow(400,400,"test",SDL_WINDOW_RESIZABLE,noir,0)){
	    closeAllWindow();
	    closeAllSANDAL2();
	    fprintf(stderr,"Erreur d'ouverture des fenetres.\n");
	    exit(-1);
	}else{
	    setKeyPressedWindow(keyWindow);
	}
    }
    
    /* display de la fenetre */
    while(run){
	tps = SDL_GetTicks();
	/* gestion d'evenement */
	run=!PollEvent(NULL) && run;

	/* update de la fenetre */
	updateWindow();
	/* affichage de la fenetre */
	displayWindow();
	/* delai pour 60 frames/secondes */
	ticks = 16 - SDL_GetTicks() + tps;
	if(ticks>0)
	    SDL_Delay(ticks);
    }

    closeAllWindow();
    closeAllSANDAL2();

    return 0;
}
