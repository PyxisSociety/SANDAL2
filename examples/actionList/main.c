#include <stdio.h>

#include "../../SANDAL2.h"

void endAction(Element * e);

int main(){
    Element * objet;
    SDL_Surface * surface;
    SDL_Texture * texture;
    int run = 1;
    int tps = 0, ticks = 0;
    int noir[4] = {0,0,0,255};
    Uint32 rmask, gmask, bmask, amask;
  
    if(initAllSANDAL2(IMG_INIT_JPG)){
	fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
	exit(-1);
    }

    /* initialisation de la fenetre */
    if(!createWindow(400,400,"test",SDL_WINDOW_RESIZABLE,noir,1)){
	closeAllSANDAL2();
	fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
	exit(-1);
    }

    /* creation de l'element */
    objet = createBlock(100, 100, 200, 200, noir, 1, 0);

    /* creation de l'image block */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    surface = SDL_CreateRGBSurface(0, 100, 100, 32, rmask, gmask, bmask, amask);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
    }else{
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
        texture = SDL_CreateTextureFromSurface(_windows_SANDAL2->currentDisplay->renderer, surface);
        setImageTextureElement(objet, texture);
    }

    /* definition des comportements de l'element */
    endAction(objet);
    setEndActionElement(objet, endAction);
    
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
    
    closeAllSANDAL2();

    return 0;
}

void translateW(Element * e, void * data, float time){
    float * arr = (float*)data;
    float w;

    if(arr[1] > arr[2]){
        w = arr[1] - (time / arr[0]) * (arr[1] - arr[2]);
    }else{
        w = (time / arr[0]) * (arr[2] - arr[1]) + arr[1];
    }

    setWidthElement(e, w);
}

void translateH(Element * e, void * data, float time){
    float * arr = (float*)data;
    float w;

    if(arr[1] > arr[2]){
        w = arr[1] - (time / arr[0]) * (arr[1] - arr[2]);
    }else{
        w = (time / arr[0]) * (arr[2] - arr[1]) + arr[1];
    }

    setHeightElement(e, w);
}

void endAction(Element * e){
    /* as they are not modified, we can pass the arrays as static */
    static float data1[] = {2, 100, 100};
    static float data2[] = {2, 100, 100};

    getWidthElement(e, data1 + 1);
    getWidthElement(e, data2 + 2);
    
    /* creating the action list and passing it to the element */
    setActionListElement(
        e,
        generateParallelAction(
            generateChainedAction(
                actionAsList(setDataAction(initAction(translateW, data1[0]), data1)),
                actionAsList(setDataAction(initAction(translateW, data2[0]), data2)),
                NULL),
            generateChainedAction(
                actionAsList(setDataAction(initAction(translateH, data1[0]), data1)),
                actionAsList(setDataAction(initAction(translateH, data2[0]), data2)),
                NULL),
            NULL)
        );
}
