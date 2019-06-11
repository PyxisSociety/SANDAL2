#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void onClick(Element * e, int b){
    addAngleElement(e, 5);
    (void)b;
}

int main(){
    Element * parent, * child;
    int run = 1;
    int tps = 0, ticks = 0;
    int black[4] = {0,0,0,255};
    int red[4] = {255, 0, 0, 255};
    int order = 1;
    
    if(initAllSANDAL2(0)){
        fputs("SANDAL2 Initializing error.\n", stderr);
        exit(-1);
    }

    /* initializing window */
    if(!createWindow(400, 400, "test", 0, black, 0)){
	closeAllSANDAL2();
	fputs("Error while opening the window.\n", stderr);
	exit(-1);
    }

    /* initializing elements */
    parent = createImageBlock(150, 150, 100, 100, red, 0, 0);
    /*
      setActionListElement(parent,
                         setForeverAction(rotateByAction(360, 2), 1)
                         );
    */
    child = createImageBlock(80, 80, 20, 20, red, 0, 0);
    setParentElement(parent, child);

    addClickableElement(parent, rectangleClickable(0, 0, 1, 1), 0);
    setOnClickElement(parent, onClick);
    
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
