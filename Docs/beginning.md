# SANDAL2

* go back to [Tutorial page](Tutorial.md)
* go back to the [main read-me](../README.md)
* go to the next [tutorial](element.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Initialising SANDAL2

```c
#include <stdio.h>
#include <SANDAL2/SANDAL2.h> /* only header needed for SANDAL2 */

int main(){
    if(initSANDAL2()){
	puts("Failed to init SDL2");
	return -1;
    }

    if(initTextSANDAL2()){
	puts("Failed to init the Text");
	closeSDL2();
	return -1;
    }

    if(initImageSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init the image");
	closeText();
	closeSDL2();
	return -1;
    }

    /* your code */

    closeImageSANDAL2();
    closeTextSANDAL2();
    closeSANDAL2();

    return 0;
}
```
You can download this code [here](https://github.com/Klevh/SANDAL2/raw/master/downloadable/beginning1.zip).

```c
#include <stdio.h>
#include <SANDAL2/SANDAL2.h> /* only header needed for SANDAL2 */

int main(){
    if(initAllSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* your code */

    closeAllSANDAL2();
    
    return 0;
}
```
You can download this code [here](https://github.com/Klevh/SANDAL2/raw/master/downloadable/beginning2.zip).
  
The first method has the advantage that the image and text initialisations can be omitted if you do not use those features while the second one is way shorter.

The parameter of initImageSANDAL2() (same for initAllSANDAL2()) is either IMG_INIT_JPG, IMG_INIT_PNG or IMG_INIT_TIF or a combination of those flags to tell which type of image you want to open (here jpg/jpeg images). For example : `IMG_INIT_PNG | IMG_INIT_TIF` for png and tif image files.

## Window Creation

```c
#include <stdio.h>
#include <SANDAL2/SANDAL2.h> /* only header needed for SANDAL2 */

int main(){
    int black[4] = {0, 0, 0, 0};
    
    if(initAllSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* creation of your window */
    createWindow(400, /* width of the window */
	        400, /* height of the window */
	        "SANDAL2 - Klevh", /* title */
	        0, /* Options (see below) */
	        black, /* background color */
	        0); /* Default display code of the window (we will see more about them later) */

    /* your code */

    closeAllWindow(); /* close all windows */
    closeAllSANDAL2();
    
    return 0;
}
```
You can download this code [here](https://github.com/Klevh/SANDAL2/raw/master/downloadable/first_window.zip).
  
&nbsp;&nbsp;&nbsp;Options can be :
* SDL_WINDOW_FULLSCREEN : fullscreen window
* SDL_WINDOW_FULLSCREEN_DESKTOP : fullscreen window at the current desktop resolution
* SDL_WINDOW_BORDERLESS : no window decoration
* SDL_WINDOW_RESIZABLE : window can be resized
* SDL_WINDOW_MINIMIZED : window is minimized
* SDL_WINDOW_MAXIMIZED : window is maximized
* SDL_WINDOW_INPUT_GRABBED : window has grabbed input focus
* SDL_WINDOW_ALLOW_HIGHDPI : window should be created in high-DPI mode if supported

## What next ?

After learning how to initialize SANDAL2 and create a window, you will need to add elements in it. You can learn it [here](element.md).
