#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../SANDAL2.h"

void generate(int plan){
    int ww,wh;
    int x, y, w, h;
    int i;
    int color[5][4] = {{255,255,255,255},
		       {255,0,0,255},
		       {0,255,0,255},
		       {0,0,255,255},
		       {255,0,255,255}};

    getDimensionWindow(&ww,&wh);

    ww *= .8;
    wh *= .8;

    for(i = 0; i < 5; ++i){
	x = rand()%ww;
	y = rand()%wh;
	w = ww / .8 * .2;
	h = wh / .8 * .2;
	if(!createBlock(x,y,w,h,color[i],0,plan))
	    fprintf(stderr,"Failed to create block :\n\tDim : %d - %d\n\tCoord : %d - %d\n",w,h,x,y);
    }
}

void keyWindow(SDL_Keycode c){
    int * val;

    printf("%d : %c\n",c,c);

    switch(c){
    case SDLK_ESCAPE: /* ESCAP */
	if(!getDataWindow((void **)&val) && val)
	    *val = 0;
	break;
    case SDLK_a: /* a */
	generate(1);
	break;
    case SDLK_z: /* z */
	generate(2);
	break;
    case SDLK_q: /* q */
        clearPlanDisplayCode(0,1);
	break;
    case SDLK_s: /* s */
        clearPlanDisplayCode(0,2);
	break;
    case SDLK_w: /* w */
	clearDisplayCode(0);
	break;
    }
}

int main(){
    int run     = 1;
    int tps     = 0;
    int ticks   = 0;
    int noir[4] = {0,0,0,255};

    srand(time(0));
  
    if(initAllSANDAL2(IMG_INIT_JPG)){
	fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
	exit(-1);
    }

    /* initialisation de la fenetre */
    if(!createWindow(400,400,"test",SDL_WINDOW_RESIZABLE,noir,0)){
	closeAllSANDAL2();
	fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
	exit(-1);
    }
    setDataWindow(&run);
    setKeyPressedWindow(keyWindow);
    
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
