# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [elements creation](element.md)

## Catching events

To catch user events, you need to use the same method as we did before : using `PollEventSDL2()`.
You may ask why it has no effect then. To that I will answer : you already caught a user event, the cross button of the window.
You will need to learn how to define a behavior that should happen when an event occure.

## Defining event behavior and simple modifications of an element

To make it simplier, we will only use a block, but all elements behave the same way.
All event functions follow the same pattern :
`function_name(element, behavior)`
Behavior functions have the same prototype expect for the key pressed and released ones :
* void function(ElementSDL2 * e) : all but keyboard
* void function(ElementSDL2 * e, SDL_Keycode c) : keyboard

```c
#include <stdio.h>
#include <SANDAL2/SANDAL2.h>

void key_behavior(ElementSDL2 * this, SDL_Keycode c);
void action(ElementSDL2 * this);
void click(ElementSDL2 * this);

int main(){
    int           red[]   = {255,0,0,0};
    int           blue[]  = {0,255,0,0};
    int           green[] = {0,0,255,0};
    int           white[] = {255,255,255,0};
    int           black[] = {0,0,0,0};
    ElementSDL2 * e;
    
    if(initAllSDL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* creation of your window */
    if(initWindowSDL2(400,400,"SANDAL2 - Klevh",0,black,0)){
        puts("Failed to open the window");
	closeAllSDL2();
    }

    /* creating our block */
    e = createBlock(20,175,50,50,green,0,0);
    if(!e){
        puts("Element creation failed");
	closeAllWindowSDL2();
	closeAllSDL2();
	return -1;
    }

    /* adding key press/released behavior */
    setKeyPressElementSDL2(e,key_behavior);
    setKeyReleasedElementSDL2(e,key_behavior);

    /* adding continuous behavior */
    setActionElementSDL2(e,action);

    /* --- adding an on click behavior --- */
    /* adding the clickable zone so that we can click on our element */
    addClickableElementSDL2(e, /* element */
    			    /*
				clickable zone which is a pointer of Clickable, here we use a rectangle clickable
				the coordinates we use to define a clickable in the object are :
				(0,0) for the top left corner
				(1,1) for the bottom right corner
			    */
    			    rectangleClickable(0.f,  /* x coordinate of the top left corner of the rectangle clickable zone */
					       0.f,  /* y coordinate of the top left corner of the rectangle clickable zone */
					       1.f,  /* width of the rectangle */
					       1.f), /* height of the rectangle */
			    0); /* telling wether or not this zone is forbidden (used to add unclickable holes in a clickable zone) */
    setOnClickElementSDL2(e,click);
    /* ----------------------------------- */

    /* PollEventSDL2 : function to catch events, return 1 when the user clicked on the cross to close the window, we will speak about it later */
    while(!PollEventSDL2(NULL)){ 
	/* updating the window content, mandatory when you change things in your window while running */
	updateWindowSDL2();
	/* displaying the window */
	displayWindowSDL2();

	/* this delay is to have about 60fps */
	SDL_Delay(16);
    }

    closeAllWindowSDL2();
    closeAllSDL2();
    return 0;
}

void key_behavior(ElementSDL2 * this, SDL_Keycode c){
    printf("%d : %c\n",c,c);
}

void action(ElementSDL2 * this){
    float x, y;
    float w, h;
    int w_w, w_h;

    getCoordElementSDL2(this, /* element */
			&x, /* where to store x coordinate, can be NULL */
			&y); /* where to store y coordinate, can be NULL */
			
    getDimensionElementSDL2(this, /* element */
			    &w, /* where to store width, can be NULL */
			    &h); /* where to store height, can be NULL */
			    
    getDimensionWindowSDL2(&w_w, /* where to store width, can be NULL */
			   &w_h); /* where to store height, can be NULL */

    if(x + w + 20 >= w_w)
        replaceElementSDL2(this, /* element to be replaced */
			   20, /* new x coordinate */
			   y); /* new y coordinate */

    moveElementSDL2(this, /* element to be moved */
		    3, /* x offset to be added */
		    0); /* y offset to be added */
	
}

void click(ElementSDL2 * this){
     puts("Clicked !");
}
```
They are some events that I did not mentioned but here is a list of all the one you can use :
* action : done each updateWindowSDL2() call
* onClick : each time you click on your element
* unClick : each time you unclick on your element
* keyPressed : each time you pressed a key
* keyReleased : each time you release a key
* unSelect : each time your element is unselected (you click or unclick elsewhere)
* endSprite : each time an animation end (we will see animations later)


If you want to modify your element further, go to the [Element's documentation](https://klevh.github.io/SANDAL2_Documentation/ElementSDL2_8h.html#a9295ff1478c109fe4bd5a22aa48e0e49).

## Defining a global event behavior

Window event work nearly exactly the same. The main difference is that the first parameter is omitted as SANDAL2 know which window is the current one (you will learn more about this subtility when you will see how to handle more than one window).
Here are the events you can define for a window :
* action
* onClick
* unClick
* keyPressed
* keyReleased

## More tutorials coming soon ...