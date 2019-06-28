#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

int main(){
    Element * parent, * child, * otherChild;
    int black[4] = {0,0,0,255};
    int red[4] = {255, 0, 0, 255};
    int order = 1;
    int i, j, k;
    unsigned long error;
    
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


    
    /* initializing rotating elements */
    parent = createImageBlock(70, 150, 100, 100, red, 0, 0);
    
    setActionListElement(
        parent,
        setForeverAction(rotateByAction(360, 10), 1));
    
    child = createImageBlock(220, 190, 20, 20, red, 0, 0);
    setParentElement(parent, child);
    setActionListElement(child,
                         setForeverAction(rotateByAction(360, 10), 1)
        );
    
    otherChild = createImageBlock(220, 220, 20, 20, red, 0, 0);
    setParentElement(child, otherChild);



    /* initializing redimensionning elements */
    parent = createImageBlock(270, 180, 40, 40, red, 0, 0);
    setActionListElement(
        parent,
        setForeverAction(
            generateChainedAction(
                scaleByAction(1, 1, 2),
                scaleByAction(-0.5, -0.5, 2),
                NULL),
            1));
    
    for(i = 0; i < 2; ++i){
        for(j = 0; j < 2; ++j){
            child = createImageBlock(250 + 60 * i, 160 + 60 * j, 20, 20, red, 0, 0);
            k = setParentElement(parent, child);
            printf("set parent worked ? %d\n", !k);
        }
    }
    
    /* display the window */
    error = mainLoop(60);
    if(error){ // error occured ?
        printf("Error occured with code %ull\n", error);
    }
    
    closeAllSANDAL2();
    
    return 0;
}
