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
