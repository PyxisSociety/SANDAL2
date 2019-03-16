# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [binding an element to another one](element_to_element.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Add automatic actions to an element

You can define behaviors on your element with a certain timing, for example, you can say that you want your element to rotate by 50° in 2 seconds. Those are possible thanks to `ListAction`. You can define parallel actions, chained actions and even more complex behaviors such as: `parallel(A, chained(B, C, parallel(D, E)), F)`.
An action function needs to have to following prototype: `void(Element * element, void * data, float time)`. Its parameters coresponds to:
* element: the element to be impacted by the action
* data: data used during the action
* time: time spent since the beginning of the action

You then can generate an action like this:
```c
Action * action = initAction(actionFunction, duration);
//optional: setDataAction(action, data, 0); // 0 means data should not be freed when the action is destroied
ListAction * listAction = actionAsList(action);

// one line equivalent
ListAction * otherListAction = actionAsList(setDataAction(initAction(actionFunction, duration), data, 0));
```
Note that `setDataAction` returns the action passed as its first parameter to enable one line such as shown upon.

## Pre made automatic actions

The following code show some simple availables pre made actions that you can use as is:

```c
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
            fadeOutToAction(255, 2),
            NULL)
        );
}
```

Here is the list of all used actions:
* scaleTo: redimension the element to a new value (0 on either value if you do not want it to change)
* scaleBy: redimension the element depending on its current dimension (1.0 == +100%)
* moveTo: move the element to a certain location
* moveBy: move the element of a certain offset
* rotateTo: rotate the element until it reach a certain angle
* rotateBy: rotate the element by a certain angle
* fadeIn: reduce the element opacity by a certain value
* fadeOut: increase the element opacity by a certain value

## New tutorials coming soon ...