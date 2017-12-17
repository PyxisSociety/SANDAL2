#include <stdio.h>
#include <SANDAL2/SANDAL2.h> /* only header needed for SANDAL2 */

int main(){
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
