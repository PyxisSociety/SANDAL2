#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void endAction(Element * e);

int main(){
    Element * objet;
    SDL_Surface * surface;
    int run = 1;
    int tps = 0, ticks = 0;
    int noir[4] = {0,0,0,255};
    int rouge[4] = {255, 0, 0, 255};
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
    objet = createImageBlock(100, 100, 200, 200, rouge, 1, 0);
    if(!objet){
        puts("ERROR");
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
