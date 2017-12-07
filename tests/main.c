#include <stdio.h>
#include <SANDAL2/SANDAL2.h>

void click(Element * this, SDL_Keycode c);

int main(){
    int       run      = 1;
    int       black[4] = {0,0,0,0};
    int       white[4] = {255,255,255,0};
    Element * e;
  
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

    /* creating our first element (which will controle all others) */
    e = createBlock(175,0,50,50,white,0,0);

    /* we set its behavior on click */
    setKeyPressedElement(e,click);
    
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

void click(Element * this, SDL_Keycode c){
    static int number_of_element = 1;
    Element * e, * next, * tmp;
    int white[4] = {255,255,255,0};
    float x, y, w, h;
    int w_w, w_h;

    switch(c){
    case 80: /* left arrow */
	break;
    case 79: /* right arrow */
	break;
    case 'a':
	if(number_of_element < 8 && initIteratorElement(this)){ /* initialize the iterator that allows to go through the list of binded objects to 'this' */
	    e = NULL;
	    while((next = nextIteratorElement(this))) /* we get the next element binded to 'this' in 'next', if there is no element left, next will have the value NULL */
		e = next;

	    if(e){ /* if there is an element */
		getDimensionElement(e, &w, &h);
		getCoordElement(e, &x, &y);
		printf("%f - %f - %f - %f\n",x,y+h,w,h);

		e = createBlock(x, y + h, w, h, white, 0, 0);
		if(e){
		    /* we bind 'e' to 'this' (e will be added at the end of the list) */
		    addElementToElement(this, /* element on which we want to bind another element */
					e); /* element to be binded */
		    ++number_of_element;
		}else
		    puts("failed to create an element");
	    }
	}else{
	    getDimensionElement(this, &w, &h);
	    getCoordElement(this, &x, &y);

	    e = createBlock(x, y + h, w, h, white, 0, 0);
	    if(e){
		/* we bind 'e' to 'this' (e will be added at the end of the list) */
		addElementToElement(this, /* element on which we want to bind another element */
				    e); /* element to be binded */
		++number_of_element;
	    }else
		puts("failed to create an element");
	}
	printf("%u\n",number_of_element);
	break;
    case 'd':
	if(number_of_element > 1 && initIteratorElement(this)){ /* initialize the iterator that allows to go through the list of binded objects to 'this' */
	    e = NULL;
	    while((next = nextIteratorElement(this))) /* we get the next element binded to 'this' in 'next', if there is no element left, next will have the value NULL */
		e = next;

	    if(e){ /* if there is an element */
		delElementToElement(this,/* element on which we want to unbind another element */
				    e);/* element to be unbinded */
		delElement(e); /* now, we remove the element from the window */
		--number_of_element;
	    }else
		puts("list empty");
	}else if(number_of_element > 1)
	    puts("failed to initialize list");
	printf("%u\n",number_of_element);
	break;
    }
}
