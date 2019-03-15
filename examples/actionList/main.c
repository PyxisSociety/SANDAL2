#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void endAction(Element * e);

int main(){
    Element * objet;
    int run = 1;
    int tps = 0, ticks = 0;
    int noir[4] = {0,0,0,255};
    int rouge[4] = {255, 0, 0, 255};
  
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
                scaleByAction(e, -0.5, 0, 2),
                scaleByAction(e, 1, 0, 2),
                NULL),
            generateChainedAction(
                scaleByAction(e, 0, -0.5, 2),
                scaleByAction(e, 0, 1, 2),
                NULL),
            NULL)
        );
}
