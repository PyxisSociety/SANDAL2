# SANDAL2

* go back to [Tutorial](Tutorial.md)
* go back to the [main read-me](../README.md)
* go back to the previous tutorial about [Display Code and Plan handling](dc_plan.md)
* report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new)

## Modifying an Element in another's event function

On each Element, there is a list of elements it can modify. You can remove an element from the list, add an element to it and go through the list. Here is how.

In the code below, each time you click on a, it will create a new block just below the last one created (if there is enough space). You can delete the last block placed by clicking on d. You can move all the blocks together with left and right arrows.

```c
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

    /* we set its behavior when a key is pressed */
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
    Element * e, * next;
    int white[4] = {255,255,255,0};
    float x, y, w, h;
    int w_w;

    switch(c){
    case 80: /* left arrow */
	getCoordElement(this,&x,NULL);

	if(x - 3 >= 0){
	    moveElement(this,-3,0);

	    if(initIteratorElement(this)) /* initialize the iterator that allows to go through the list of binded objects to 'this' */
		while((e = nextIteratorElement(this)))/* we get the next element binded to 'this' in 'next', if there is no element left, next will have the value NULL */
		    moveElement(e,-3,0);
	    e = NULL;
	}
	break;
    case 79: /* right arrow */
	getCoordElement(this,&x,NULL);
	getDimensionElement(this,&w,NULL);
	getDimensionWindow(&w_w,NULL);

	if(x + w + 3 < w_w){
	    moveElement(this,3,0);

	    if(initIteratorElement(this)) /* initialize the iterator that allows to go through the list of binded objects to 'this' */
		while((e = nextIteratorElement(this)))/* we get the next element binded to 'this' in 'next', if there is no element left, next will have the value NULL */
		    moveElement(e,3,0);
	    e = NULL;
	}
	break;
    case 'a':
	if(number_of_element < 8 && initIteratorElement(this)){ /* initialize the iterator that allows to go through the list of binded objects to 'this' */
	    e = NULL;
	    while((next = nextIteratorElement(this))) /* we get the next element binded to 'this' in 'next', if there is no element left, next will have the value NULL */
		e = next;

	    if(e){ /* if there is an element */
		getDimensionElement(e, &w, &h);
		getCoordElement(e, &x, &y);

		e = createBlock(x, y + h, w, h, white, 0, 0);
		if(e){
		    /* we bind 'e' to 'this' (e will be added at the end of the list) */
		    addElementToElement(this, /* element on which we want to bind another element */
					e); /* element to be binded */
		    ++number_of_element;
		}else
		    puts("failed to create an element");
	    }
	}else if(number_of_element < 8){
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
	break;
    }
}
```
You can download this code [here](https://github.com/Klevh/SANDAL2/raw/master/downloadable/element_to_element.zip).

## New tutorials coming soon ...