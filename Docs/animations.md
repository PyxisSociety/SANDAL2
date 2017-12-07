# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [catching user events](events.md)
* go to the next tutorial about [display codes and plans handling](dc_plan.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Creating an animation

In the following code, I use this [spritesheet](https://github.com/Klevh/SANDAL2/raw/master/downloadable/spritesheet.jpg) of lswbeast.deviantart.com.

```c
#include <stdio.h>

#include <SANDAL2/SANDAL2.h>

void touch(Element *this){
    /* if the image is clicked, we go to the next animation */
    nextAnimationElement(this);
}

void endJump(Element *this,int code){
    if(code==1) /* if we end a jump, we go back to walk */
	setAnimationElement(this,0); /* we set the first animation here */
}

int main(){
    Element * object;
    int run = 1;
    int black[4] = {0,0,0,0};
    int i;

    /* initializing SANDAL2 */
    if(initAllSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* initializing the window */
    if(createWindow(400,400,"SANDAL2 - Klevh",0,black,0)){
        puts("Failed to open the window");
	closeAllSANDAL2();
	return -1;
    }

    /* creation of the image */
    object = createImage(150.f,100.f,100.f,200.f,"spritesheet.jpg",0,0);

    /* ----- creation of the animation ----- */
    /* WARNING : first animation set by default */
    /* creating a new animation : walking */
    addAnimationElement(object, /* element to add an animation to */
			   0); /* id of the animation, to get/modify/set it later *

    /* associating locations of the image to the animation */
    for(i=0;i<4;++i)
	if(addSpriteAnimationElement(object,
			             0, /* index of the animation to add the sprite to */
				     55*i, /* x coordinate of the top left corner of the sprite in the image */
				     0, /* y coordinate of the top left corner of the sprite in the image */
				     55, /* width of the sprite in the image */
				     75, /* height of the sprite in the image */
				     10, /* number of upgradeWindow() calls for the animation to go from this sprite to the next one */
				     i)) /* index of the sprite in the animation, the last one added is the first one to run in normal way */
	    printf("Error adding sprite %d to animation 0\n",i);
    /* setting the animation to automatically run forward (1) when it is launched (can be set to manual (0) or automatic backward (-1)) */
    setWaySpriteAnimationElement(object, /* object to be set */
				 0, /* id of the animation */
				 1); /* way to run it */

    /* creating a new animation : jumping */
    addAnimationElement(object,1);
    for(i=0;i<4;++i)
	if(addSpriteAnimationElement(object,1,259+i*72,0,72,75,10,i))
	    printf("Error adding sprite %d to animation 1\n",i);
    /* setting the animation to automatically run when it is launched */
    setWaySpriteAnimationElement(object,1,1);
    /* ------------------------------------- */

    /* setting the behavior on click */
    addClickableElement(object,rectangleClickable(0.f,0.f,1.f,1.f),0);
    setOnClickElement(object,touch);

    /* setting the behavior when an animation end */
    setEndSpriteElement(object,endJump);
    
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

## What next ?

There is still one major thing to learn, and that is [Display code and Plan manipulation](dc_plan.md) !