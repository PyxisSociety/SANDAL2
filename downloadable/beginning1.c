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
