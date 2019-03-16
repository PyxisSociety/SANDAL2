#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void endAction1(Element * e);
void endAction2(Element * e);
void endAction3(Element * e);
void endAction4(Element * e);

int main(){
    Element * objet;
    int run = 1;
    int tps = 0, ticks = 0;
    int noir[4] = {0,0,0,255};
    int rouge[4] = {255, 0, 0, 255};
    int i, j;
    void (*action[4])(Element *) = {endAction1, endAction2, endAction3, endAction4};
  
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

    for(i = 0; i < 2; ++i){
        for(j = 0; j < 2; ++j){
            /* creation de l'element */
            objet = createImageBlock(60 + i * 200, 60 + j * 200, 80, 80, rouge, 1, 0);

            /* definition des comportements de l'element */
            action[i * 2 + j](objet);
            setEndActionElement(objet, action[i * 2 + j]);
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
    
    closeAllSANDAL2();

    return 0;
}

void endAction1(Element * e){
    float h;
    float w;
    float y;
    
    getDimensionElement(e, &w, &h);
    getCoordYElement(e, &y);
    
    /* creating the action list and passing it to the element */
    setActionListElement(
        e,
        generateParallelAction(
            generateChainedAction(
                scaleByAction(-0.5, 0, 2),
                scaleByAction(1, 0, 2),
                NULL),
            generateChainedAction(
                scaleToAction(0, h / 2, 2),
                scaleToAction(0, h, 2),
                NULL),
            generateChainedAction(
                moveByAction(w / 4, 0, 2),
                moveByAction(-w / 4, 0, 2),
                NULL),
            generateChainedAction(
                moveToAction(0, y + h / 4, 2),
                moveToAction(0, y, 2),
                NULL),
            NULL)
        );
}

void endAction2(Element * e){
    float h;
    
    getHeightElement(e, &h);
    
    /* creating the action list and passing it to the element */
    setActionListElement(
        e,
        rotateByAction(360, 2)
        );
}


void endAction3(Element * e){
    float h;
    
    getHeightElement(e, &h);
    
    /* creating the action list and passing it to the element */
    setActionListElement(
        e,
        generateChainedAction(
            rotateToAction(360, 2),
            rotateToAction(0, 2),
            NULL)
        );
}

void endAction4(Element * e){
    float h;
    
    getHeightElement(e, &h);
    
    /* creating the action list and passing it to the element */
    setActionListElement(
        e,
        generateChainedAction(
            fadeInAction(255, 2),
            fadeOutAction(255, 2),
            NULL)
        );
}
