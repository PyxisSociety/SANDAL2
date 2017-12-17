#include <stdio.h>
#include <SANDAL2/SANDAL2.h>

void key_behavior(Element * this, SDL_Keycode c);
void action(Element * this);
void click(Element * this);

int main(){
    int       red[]   = {255,0,0,0};
    int       green[]  = {0,255,0,0};
    int       blue[] = {0,0,255,0};
    int       white[] = {255,255,255,0};
    int       black[] = {0,0,0,0};
    Element * e;
    
    if(initAllSANDAL2(IMG_INIT_JPG)){
	puts("Failed to init SANDAL2");
	return -1;
    }

    /* creation of your window */
    if(createWindow(400,400,"SANDAL2 - Klevh",0,black,0)){
        puts("Failed to open the window");
	closeAllSANDAL2();
    }

    /* creating our block */
    e = createBlock(20,175,50,50,green,0,0);
    if(!e){
        puts("Element creation failed");
	closeAllWindow();
	closeAllSANDAL2();
	return -1;
    }

    /* adding key press/released behavior */
    setKeyPressedElement(e,key_behavior);
    setKeyReleasedElement(e,key_behavior);

    /* adding continuous behavior */
    setActionElement(e,action);

    /* --- adding an on click behavior --- */
    /* adding the clickable zone so that we can click on our element */
    addClickableElement(e, /* element */
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
    setOnClickElement(e,click);
    /* ----------------------------------- */

    /* PollEvent : function to catch events, return 1 when the user clicked on the cross to close the window */
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

void key_behavior(Element * this, SDL_Keycode c){
    printf("%d : %c\n",c,c);
}

void action(Element * this){
    float x, y;
    float w, h;
    int w_w, w_h;

    getCoordElement(this, /* element */
		    &x, /* where to store x coordinate, can be NULL */
		    &y); /* where to store y coordinate, can be NULL */
			
    getDimensionElement(this, /* element */
			&w, /* where to store width, can be NULL */
			&h); /* where to store height, can be NULL */
			    
    getDimensionWindow(&w_w, /* where to store width, can be NULL */
		       &w_h); /* where to store height, can be NULL */

    if(x + w + 20 >= w_w)
        replaceElement(this, /* element to be replaced */
		       20, /* new x coordinate */
		       y); /* new y coordinate */

    moveElement(this, /* element to be moved */
		3, /* x offset to be added */
		0); /* y offset to be added */
	
}

void click(Element * this){
     puts("Clicked !");
}
