# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [SANDAL2 initialisation and window creation](beginning.md)
* go to the next tutorial about [user events](events.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Creating some elements

In the code bellow, you'll need to have an image named img.jpg and a font named arial.ttf for it to run.
You can download those I used at :
* [font](https://github.com/Klevh/SANDAL2/raw/master/downloadable/arial.ttf)
* [image](https://github.com/Klevh/SANDAL2/raw/master/downloadable/img.jpg)
  
```c
#include <stdio.h>
#include <SANDAL2/SANDAL2.h>

int main(){
    int red[]   = {255,0,0,0};
    int green[]  = {0,255,0,0};
    int blue[] = {0,0,255,0};
    int white[] = {255,255,255,0};
    int black[] = {0,0,0,0};
    
    if(initAllSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* creation of your window */
    if(createWindow(400,400,"SANDAL2 - Klevh",0,black,0)){
        puts("Failed to open the window");
	closeAllSANDAL2();
	return -1;
    }

    /* ----------------------creating some elements-------------------------- */
    /*    creating a block */
    if(!createBlock(100, /* x coordinate */
		    0, /* y coordinate */
		    40, /* width */
		    40, /* height */
		    red, /* color */
		    0, /* display code */
		    0)) /* plan, the lower the nearer */
        puts("Failed to create the block");

    /*    creating a text */
    if(!createText(100, /* x coordinate */
		   50, /* y coordinate */
		   100, /* width */
		   40, /* height */
		   "arial.ttf", /* font to be used */
		   "SANDAL2", /* the text */
		   blue, /* color of the text */
		   SANDAL2_BLENDED, /* quality of the text, can be either SANDAL2_SOLID, SANDAL2_SHADED and SANDAL2_BLENDED */
		   0, /* display code */
		   0)) /* plan, the lower the nearer */
        puts("Failed to create the text");
	
    /*    creating an image */
    if(!createImage(100, /* x coordinate */
		    100, /* y coordinate */
		    40, /* width */
		    40, /* height */
		    "img.jpg", /* image to be loaded */
		    0, /* display code */
		    0)) /* plan, the lower the nearer */
        puts("Failed to create the image");
	
    /*    creating a button */
    if(!createButton(100, /* x coordinate */
		     150, /* y coordinate */
		     100, /* width */
		     40, /* height */
		     80.f, /* proportion of the text in the button, here 80% */
	   	     "arial.ttf", /* font to be used */
		     "SANDAL2", /* the text */
		     white, /* color of the text */
		     SANDAL2_BLENDED, /* quality of the text, can be either SANDAL2_SOLID, SANDAL2_SHADED and SANDAL2_BLENDED */
		     green, /* color of the block */
		     0, /* display code */
		     0)) /* plan, the lower the nearer */
        puts("Failed to create the button");
	
    /*    creating an image button */
    if(!createButtonImage(100, /* x coordinate */
		          200, /* y coordinate */
		     	  100, /* width */
		    	  40, /* height */
		          80.f, /* proportion of the text in the button, here 80% */
	   	          "arial.ttf", /* font to be used */
		          "SANDAL2", /* the text */
		          white, /* color of the text */
		          SANDAL2_BLENDED, /* quality of the text, can be either SANDAL2_SOLID, SANDAL2_SHADED and SANDAL2_BLENDED */
		    	  "img.jpg", /* image to be loaded */
		          0, /* display code */
		          0)) /* plan, the lower the nearer */
        puts("Failed to create the image button");

    /* creating an entry bar */
    if(!createEntry(100, /* x coordinate */
		    250, /* y coordinate */
		    100, /* width */
		    40, /* height */
		    80.f, /* proportion of the text in the button, here 80% */
	   	    "arial.ttf", /* font to be used */
		    "SANDAL2", /* the text */
		    red, /* color of the text */
		    SANDAL2_BLENDED, /* quality of the text, can be either SANDAL2_SOLID, SANDAL2_SHADED and SANDAL2_BLENDED */
		    white, /* color of the block */
		    0, /* display code */
		    0, /* plan, the lower the nearer */
		    0, /* minimum character for the prompt to be validate */
		    10, /* maximum character for the prompt to be validate */
		    0)) /* "boolean" to tell whether or not the text should be replaced by starts ('*') */
        puts("Failed to create the entry bar");

    /* creating an image entry bar */
    if(!createEntryImage(100, /* x coordinate */
		         300, /* y coordinate */
		         100, /* width */
		         40, /* height */
		         80.f, /* proportion of the text in the button, here 80% */
	   	         "arial.ttf", /* font to be used */
		         "SANDAL2", /* the text */
		         red, /* color of the text */
		         SANDAL2_BLENDED, /* quality of the text, can be either SANDAL2_SOLID, SANDAL2_SHADED and SANDAL2_BLENDED */
		    	 "img.jpg", /* image to be loaded */
		         0, /* display code */
		         0, /* plan, the lower the nearer */
		         0, /* minimum character for the prompt to be validate */
		         10, /* maximum character for the prompt to be validate */
		         0)) /* "boolean" to tell whether or not the text should be replaced by starts ('*') */
        puts("Failed to create the image entry bar");
    /* ----------------------------------------------------------------------- */



    /* PollEvent : function to catch events, return 1 when the user clicked on the cross to close the window, we will speak about it later */
    while(!PollEvent(NULL)){ 
	/* updating the window content, mandatory when you change things in your window while running */
	updateWindow();
	/* displaying the window */
	displayWindow();

	/* this delay is to have about 60fps */
	SDL_Delay(16);
    }

    closeAllWindow();
    closeAllSANDAL2();
    return 0;
}
```
You can download this code [here](https://github.com/Klevh/SANDAL2/raw/master/downloadable/element.zip).

With all that, you can create a lot of different elements and ... do nothing with it.

## What's next ?

Next, you will need to learn how to catch [user events](events.md) and define behaviors according to them.