#include "SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

TEST_SECTION(Window){
    TEST_CASE(setters){
	// set display code
	REQUIRE(setDisplayCodeWindow(4));
	REQUIRE(!setDisplayCodeWindow(3));
	REQUIRE_NOT_NULL(_windows_SANDAL2);
	REQUIRE_NOT_NULL(_windows_SANDAL2->current);
	REQUIRE(_windows_SANDAL2->current->newDisplayCode == 3);

	// set color
	int bg[4] = {255, 255, 255, 255};
	int i;
	REQUIRE(!setColorWindow(bg));
	for(i = 0; i < 4; ++i){
	    REQUIRE(_windows_SANDAL2->current->background[i] == bg[i]);
	}

	// set coord
	REQUIRE(!setCoordWindow(0, 0));
	REQUIRE(_windows_SANDAL2->current->posX == 0);
	REQUIRE(_windows_SANDAL2->current->posY == 0);

	// set icon
	REQUIRE(setIconWindow(NULL));
	REQUIRE(setIconWindow("not/foundable/image"));
	REQUIRE(!setIconWindow("../../downloadable/img.jpg"));

	// set origin
	REQUIRE(!setOriginWindow(25, 25));
	for(i = 0; i < 2; ++i){
	    REQUIRE(_windows_SANDAL2->current->origin[i] == 25);
	}

	// set X origin
	REQUIRE(!setXOriginWindow(42));
	REQUIRE(_windows_SANDAL2->current->origin[0] == 42);

	// set Y origin
	REQUIRE(!setYOriginWindow(42));
	REQUIRE(_windows_SANDAL2->current->origin[1] == 42);

	// set data
	REQUIRE(!setDataWindow((void*)25));
	REQUIRE(_windows_SANDAL2->current->data == (void*)25);
	REQUIRE(!setDataWindow(NULL));

	// set display
	REQUIRE(setDisplayWindow(25));
	REQUIRE(!setDisplayWindow(1));
	REQUIRE(_windows_SANDAL2->currentDisplay == _windows_SANDAL2->first);
    }

    TEST_CASE(setters_action){
#       define TEST_ACTION(name, action)				\
	REQUIRE(!set##name##Window((void*)1));				\
	REQUIRE(_windows_SANDAL2->current->events.action == (void*)1);	\
	REQUIRE(!set##name##Window(NULL))
	
	// set action
	TEST_ACTION(Action, action);

	// set key pressed
	TEST_ACTION(KeyPressed, keyPress);

	// set key released
	TEST_ACTION(KeyReleased, keyReleased);

	// set on click
	TEST_ACTION(OnClick, onClick);

	// set unclick
	TEST_ACTION(UnClick, unClick);

	// set wheel
	TEST_ACTION(Wheel, wheel);

	// set on focused
	TEST_ACTION(OnFocused, onFocus);

	// set un focused
	TEST_ACTION(UnFocused, unFocus);
    }

    TEST_CASE(getters){
	// get dimension
	int w, h;
	REQUIRE(!getDimensionWindow(&w, &h));
	REQUIRE(w == 100);
	REQUIRE(h == 100);

	// get display code
	REQUIRE(!getDisplayCodeWindow(&w));
	REQUIRE(w == 0);

	// get color
	int bg[4];
	REQUIRE(!getColorWindow(bg));
	for(w = 0; w < 4; ++w){
	    REQUIRE(_windows_SANDAL2->current->background[w] == bg[w]);
	}

	// get coord
	REQUIRE(!getCoordWindow(&w, &h));
	REQUIRE(w == 0);
	REQUIRE(h == 0);

	// get real dimension
	REQUIRE(!getRealDimensionWindow(&w, &h));
	REQUIRE(w == 100);
	REQUIRE(h == 100);

	// get id
	Uint32 id;
	REQUIRE(!getIDWindow(&id));
	REQUIRE(id == 1);

	// get id current
	REQUIRE(!getIDCurrentWindow(&id));
	REQUIRE(id == 1);

	// get origin
	REQUIRE(!getOriginWindow(&w, &h));
	REQUIRE(w == 0);
	REQUIRE(h == 0);

	// get data
	void * data = (void*)1;
	REQUIRE(!getDataWindow(&data));
	REQUIRE(data == NULL);
    }

    TEST_CASE(others){
	// resize
	int w, h;
	REQUIRE(!resizeWindow(20, 20));
	REQUIRE(!getRealDimensionWindow(&w, &h));
	REQUIRE(w == 20);
	REQUIRE(h == 20);

	// iterators
	int i, j;
	REQUIRE(initIteratorWindow() == 1);
	for(i = 0; i < 4; ++i){
	    j = nextWindow();
	    REQUIRE(j == i + 2,
		    "%d == %d\n", i + 2, j);
	}
	REQUIRE(nextWindow() == 0);
    }
}

int main(){
    int rc    = 0;
    int bg[4] = {0};
    int i     = 0;
    
    if(initAllSANDAL2(IMG_INIT_JPG)){
	rc = 1;
	printf("%s\n", SDL_GetError());
    }else{
	for(i = 0; i < 5; ++i){
	    if(!createWindow(100, 100, "it", 0, bg, i)){
		printf("%s\n", SDL_GetError());
		rc = i + 2;
	    }
	}

	if(!rc){
	    RUN_SECTION(Window);
	}

	closeAllSANDAL2();
    }
    
    return rc;
}

