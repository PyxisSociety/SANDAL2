# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [animations](animations.md)
* go to the next tutorial about [modifying an element in another's event function](element_to_element.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Manipulating Display code and Plan

A display code is the index of a page. You can have more than one page and switch with them whenever you want. With this principle, you can have your first menu in a page and the game in another.

When an object is on a plan with a greater index than another one, this first object will be displaied behind the second one. If both of them have the same plan index, they will follow the rule of last added on top.


With the code bellow, try playing with keys 1, 2, 3, 4, 5 and 6 (1, 2, 3 first, then 4, 5, 6 where all the random squares were added).

If your keyboard has different codes than mine, you can find generic flags [here](https://wiki.libsdl.org/SDL_Keycode).

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SANDAL2/SANDAL2.h>

void generate(int plan){
    int ww,wh;
    int x, y, w, h;
    int i;
    int color[5][4] = {
    	{255,255,255,0},
	{255,0,0,0},
	{0,255,0,0},
	{0,0,255,0},
	{255,0,255}
    };

    getDimensionWindow(&ww,&wh);

    ww *= .8;
    wh *= .8;

    for(i = 0; i < 5; ++i){
	x = rand()%ww;
	y = rand()%wh;
	w = ww / .8 * .2;
	h = wh / .8 * .2;
	if(!createBlock(x,y,w,h,color[i],0,plan))
	    printf("Failed to create block :\n\tDim : %d - %d\n\tCoord : %d - %d\n",w,h,x,y);
    }
}

void keyWindow(SDL_Keycode c){
    int * val;
    int d;

    switch(c){
    case 27: /* ESCAP */
	if(!getDataWindow((void **)&val) && val)
	    *val = 0;
	break;
    case 38:
    case 89: /* 1 */
    	/* adding an element to the plan 1 */
	generate(1);
	break;
    case -23:
    case 90: /* 2 */
    	/* adding an element to the plan 2 */
	generate(2);
	break;
    case 39:
    case 92: /* 4 */
    	/* clearing the plan 1 of the display code 0 */
        clearPlanDisplayCode(0, /* display code */
	                     1); /* plan */
	break;
    case 40:
    case 93: /* 5 */
    	/* clearing the plan 2 of the display code 0 */
        clearPlanDisplayCode(0,2);
	break;
    case 45:
    case 94: /* 6 */
	clearDisplayCode(0);
	break;
    case 34:
    case 91: /* 3 */
        getDisplayCodeWindow(&d); /* getting the display code of the window */
	setDisplayCodeWindow(1 - d); /* setting the display code of the window */
	break;
    }
}

int main(){
    int run      = 1;
    int black[4] = {0,0,0,0};
    int white[4] = {255,255,255,0};

    srand(time(0));
  
    /* initializing SANDAL2 */
    if(initAllSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* initializing the window */
    createWindow(400,400,"SANDAL2 - Klevh",SDL_WINDOW_RESIZABLE,black,0);
    if(initIteratorWindow()){
        puts("Failed to open the window");
	closeAllSANDAL2();
	return -1;
    }
    
    /* adding a void * to the window, you can do the same to an element */
    setDataWindow(&run);

    /* setting the window behavior when a key is pressed */
    setKeyPressedWindow(keyWindow);

    /* creating a simple block on another display code */
    createBlock(100,100,200,200,white,1,0);
    
    /* main loop */
    while(run){
	run=!PollEvent(NULL) && run;

	updateWindow();
	displayWindow();
	
	SDL_Delay(16);
    }

    closeAllWindow();
    closeAllSANDAL2();

    return 0;
}
```
You can download this code [here](https://github.com/Klevh/SANDAL2/raw/master/downloadable/dc_plan.zip).

## What's next ?

Now, there is still one problem that I did not mentioned earlier. When you bind a behavior to an element, you can't modify another one in the function. If you want to know how to correct that, click [here](element_to_element.md) !