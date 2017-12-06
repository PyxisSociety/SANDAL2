# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [catching user events](events.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Creating an animation

In the following code, I use this [spritesheet](https://github.com/Klevh/SANDAL2/raw/master/downloadable/spritesheet.jpg) of lswbeast.deviantart.com.

```c
#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void touch(ElementSDL2 *this){
    /* if the image is clicked, we go to the next animation */
    nextAnimationElementSDL2(this);
}

void endJump(ElementSDL2 *this,int code){
    if(code==1) /* if we end a jump, we go back to walk */
	setAnimationElementSDL2(this,0); /* we set the first animation here */
}

int main(){
    ElementSDL2 * object;
    int run = 1;
    int black[4] = {0,0,0,0};
    int i;

    /* initializing SANDAL2 */
    if(initAllSDL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* initialisation de la fenetre */
    initWindowSDL2(400,400,"SANDAL2 - Klevh",0,black,0);
    if(initIteratorWindowSDL2()){
        puts("Failed to open the window");
	closeAllSDL2();
	return -1;
    }

    /* creation of the image */
    object = createImage(150.f,100.f,100.f,200.f,"spritesheet.jpg",0,0);

    /* ----- creation of the animation ----- */
    /* WARNING : first animation set by default */
    /* creating a new animation : walking */
    createAnimationElementSDL2(object, /* element to add an animation to */
			       0); /* id of the animation, to get/modify/set it later *

    /* associating locations of the image to the animation */
    for(i=0;i<4;++i)
	if(addSpriteAnimationElementSDL2(object,
			                 0, /* index of the animation to add the sprite to */
					 55*i, /* x coordinate of the top left corner of the sprite in the image */
					 0, /* y coordinate of the top left corner of the sprite in the image */
					 55, /* width of the sprite in the image */
					 75, /* height of the sprite in the image */
					 10, /* number of upgradeWindowSDL2() calls for the animation to go from this sprite to the next one */
					 i)) /* index of the sprite in the animation, the last one added is the first one to run in normal way */
	    printf("Error adding sprite %d to animation 0\n",i);
    /* setting the animation to automatically run forward (1) when it is launched (can be set to manual (0) or automatic backward (-1)) */
    setWaySpriteAnimationElementSDL2(object, /* object to be set */
				     0, /* id of the animation */
				     1); /* way to run it */

    /* creating a new animation : jumping */
    createAnimationElementSDL2(object,1);
    for(i=0;i<4;++i)
	if(addSpriteAnimationElementSDL2(object,1,259+i*72,0,72,75,10,i))
	    printf("Error adding sprite %d to animation 1\n",i);
    /* setting the animation to automatically run when it is launched */
    setWaySpriteAnimationElementSDL2(object,1,1);
    /* ------------------------------------- */

    /* setting the behavior on click */
    addClickableElementSDL2(object,rectangleClickable(0.f,0.f,1.f,1.f),0);
    setOnClickElementSDL2(object,touch);

    /* setting the behavior when an animation end */
    setEndSpriteElementSDL2(object,endJump);
    
    /* main loop */
    while(run){
	run=!PollEventSDL2(NULL) && run;

	updateWindowSDL2();
	displayWindowSDL2();
	
	SDL_Delay(16);
    }

    closeAllWindowSDL2();
    closeAllSDL2();

    return 0;
}
```

## More tutorials coming soon ...