#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../SANDAL2.h"

void keyElement(Element * this, SDL_Keycode c){
    static unsigned   i     = 0;
    int             * val;
    
    c = (char)c;

    switch(c){
    case 27: /* ESCAP */
	if(!getDataWindow((void **)&val) && val)
	    *val = 0;
	break;
    case 95: /* 7 pave numerique */
	i = (i + 1) % 5;
	setPlanElement(this, 0, i);
	break;
    }
}

int main(){
    Element * e            = NULL;
    int       run          = 1;
    int       tps          = 0;
    int       ticks        = 0;
    int       noir[4]      = {0,0,0,0};
    int       i            = 0;
    int       colors[5][4] = {
	{255,0,0,125},
	{0,255,0,125},
	{0,0,255,125},
	{255,0,255,125},
	{255,255,255,255}
    };

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

    /* initializing blocks */
    for(i = 0; i < 4; ++i)
	createBlock(20 + i * 60, 200, 50, 50, colors[i], 0, i);
    e = createBlock(20, 150, 60 * i, 60, colors[i], 0, 0);
    if(!e){
	run = 0;
    }else{
	setKeyPressedElement(e, keyElement);
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
