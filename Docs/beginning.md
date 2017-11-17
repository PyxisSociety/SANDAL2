# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)

## Initialasing SANDAL2

&nbsp;&nbsp;&nbsp;To initialize SANDAL2, you will need to use either of those two methods :

```c
#include <stdio.h>
#include "SANDAL2/SANDAL2.h" /* only header needed for SANDAL2 */

int main(){
    if(initSDL2()){
	puts("Failed to init SDL2");
	return -1;
    }

    if(initText()){
	puts("Failed to init the Text");
	closeSDL2();
	return -1;
    }

    if(initImage(IMG_INIT_JPG)){
	puts("Failed to init the image");
	closeText();
	closeSDL2();
	return -1;
    }

    /* your code */

    closeImage();
    closeText();
    closeSDL2();

    return 0;
}
```

```c
#include <stdio.h>
#include "SANDAL2/SANDAL2.h" /* only header needed for SANDAL2 */

int main(){
    if(initAllSDL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* your code */

    closeAllSDL2();
    
    return 0;
}
```
  
The first method has the advantage that the image and text initialisations can be omitted if you do not use those features while the second one is way shorter.

The parameter of initImage() (same for initAllSDL2()) is the SDL2_image flag to tell which type of image you want to open (here jpg/jpeg images).

# This Tutorial is in progress