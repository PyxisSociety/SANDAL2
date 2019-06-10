#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void endAction1(Element * e);
void endAction2(Element * e);
void endAction3(Element * e);
void endAction4(Element * e);

int main(){
    Element * object;
    int run = 1;
    int tps = 0, ticks = 0;
    int black[4] = {0,0,0,255};
    int red[4] = {255, 0, 0, 255};
    int i, j;
    void (*action[4])(Element *) = {endAction1, endAction2, endAction3, endAction4};
  
    if(initAllSANDAL2(IMG_INIT_JPG)){
        fputs("SANDAL2 Initializing error.\n", stderr);
	exit(-1);
    }

    /* initializing window */
    if(!createWindow(400,400,"test",SDL_WINDOW_RESIZABLE,black,1)){
	closeAllSANDAL2();
	fputs("Error while opening the window.\n", stderr);
	exit(-1);
    }

    for(i = 0; i < 2; ++i){
        for(j = 0; j < 2; ++j){
            /* creation of the element */
            object = createImageBlock(60 + i * 200, 60 + j * 200, 80, 80, red, 1, 0);

            /* defining the element's behavior */
            action[i * 2 + j](object);
            if(action[i * 2 + j] != endAction2){
                printf("Setting end action event for element %d\n", i * 2 + j);
                setEndActionElement(object, action[i * 2 + j]);
            }
        }
    }
    
    /* display the window */
    while(run){
	tps = SDL_GetTicks();
        
	/* event handling */
	run=!PollEvent(NULL) && run;

	/* update the window */
	updateWindow();
	/* display it */
	displayWindow();
        
	/* 60 frames/secondes delay */
	ticks = 16 - SDL_GetTicks() + tps;
	if(ticks>0){
	    SDL_Delay(ticks);
        }
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
                scaleByAction(-0.5, 0, 1),
                scaleByAction(1, 0, 1),
                NULL),
            generateChainedAction(
                scaleToAction(0, h / 2, 1),
                scaleToAction(0, h, 1),
                NULL),
            generateChainedAction(
                moveByAction(w / 4, 0, 1),
                moveByAction(-w / 4, 0, 1),
                NULL),
            generateChainedAction(
                moveToAction(0, y + h / 4, 1),
                moveToAction(0, y, 1),
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
        setForeverAction(rotateByAction(360, 2), 1)
        );
}


void endAction3(Element * e){
    float h;
    long long id;
    
    getHeightElement(e, &h);
    
    /* creating the action list and passing it to the element */
    setActionListElement(
        e,
        generateChainedAction(
            rotateToAction(360, 2),
            rotateToAction(0, 2),
            NULL)
        );

    id = addActionToElement(e, scaleByAction(10, 10, 4));

    addActionToElement(
        e,
        generateChainedAction(
            moveByAction(-100, 0, 2),
            moveByAction(100, 0, 2),
            NULL)
        );

    // if you see the element being over sized, this line failed
    delActionToElement(e, id);
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
