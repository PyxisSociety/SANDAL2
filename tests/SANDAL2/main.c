#include "SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

int data[] = {0, 0, 0, 0};

TEST_SECTION(WindowEvent){
    int i = 0;
    SDL_Event e = {0};
    
    unsigned long error;
    Uint32 windowIDs[4] = {1, 2, 3};
    
    TEST_CASE(after_init){
	i = 0;
	
	REQUIRE(initIteratorWindow());

	// testing if only first window is focused
	while(i < 4){
	    REQUIRE_NOT_NULL(_windows_SANDAL2->current);
	    REQUIRE(_windows_SANDAL2->current->focused == (i == 3),
		    "%d: is focused ? %d\n", i, _windows_SANDAL2->current->focused);
	    
	    ++i;
	    if(i < 4) REQUIRE(nextWindow(), "Failed on %d\n", i);
	}
    }

    TEST_CASE(changing_focus){
	int supposed[] = {-1, -1, -1, 1};
	
	PollEvent(NULL); // to raise all focus changed done during window creation

	for(i = 0; i < 4; ++i)
	    REQUIRE(supposed[i] == data[i],
		    "supposed[%d]==%d && data[%d]==%d\n",i, supposed[i], i, data[i]);
    }

    TEST_CASE(click_unclick){
        // click, unclick, clickAll, unclickAll
    }

    TEST_CASE(mouseMotion){
        // onMouse
    }

    TEST_CASE(key_event){
        // keyPressed, keyReleased, keyPressedAll, keyReleasedAll
    }

    TEST_CASE(wheel){
        // wheel
    }

    TEST_CASE(SDL_CloseEvent){
    }
}

TEST_SECTION(WindowManagement){
    TEST_CASE(setters){
        // toggle full screen
        _windows_SANDAL2->current = _windows_SANDAL2->first;
        int isFullScreen = _windows_SANDAL2->current->state;
        REQUIRE(!toggleFullScreenWindow());
        REQUIRE(isFullScreen != _windows_SANDAL2->current->state);
        REQUIRE(!toggleFullScreenWindow());
        REQUIRE(isFullScreen == _windows_SANDAL2->current->state);
    }

    TEST_CASE(getters){
        // is full screen
        _windows_SANDAL2->current = _windows_SANDAL2->first;
        _windows_SANDAL2->current->state = 0;
        REQUIRE(isFullScreenWindow() == 0);
        _windows_SANDAL2->current->state = SDL_WINDOW_FULLSCREEN;
        REQUIRE(isFullScreenWindow() == 1);
    }

    TEST_CASE(close){
        // should close
        Window * w = _windows_SANDAL2->current;
        REQUIRE(!shouldCloseWindow());
        updateAllWindow();
        REQUIRE(w != _windows_SANDAL2->current);

        // close
        _windows_SANDAL2->current = _windows_SANDAL2->first;
        w = _windows_SANDAL2->current;
        REQUIRE(!closeWindow());
        REQUIRE(w != _windows_SANDAL2->current);

        // close all
        REQUIRE(!closeAllWindow());
        REQUIRE(_windows_SANDAL2 == NULL);

        // fail should close, close and close all
        REQUIRE(shouldCloseWindow());
        REQUIRE(closeWindow());
        REQUIRE(closeAllWindow());
    }
}

void onFocus(void);
void unFocus(void);

int main(){
    int rc     = 0;
    int bg[4]  = {0};
    int i;
    
    if(!initAllSANDAL2(0)){
	rc = 2;
	for(i = 0; i < 4 && rc; ++i){
	    rc = createWindow(10, 10, "w", 0, bg, 0);
	    if(rc){
		setDataWindow((void*)(data + i));
		setOnFocusedWindow(onFocus);
		setUnFocusedWindow(unFocus);
	    }
	}

	if(rc){
	    RUN_SECTION(WindowEvent);
	    RUN_SECTION(WindowManagement);
	    rc = 0;
	}else{
	    rc = 2;
	    printf("%s\n", SDL_GetError());
	}
	
	closeAllSANDAL2();
    }else{
	rc = 1;
	printf("%s\n", SDL_GetError());
    }
    
    return rc;
}

static void setWindowDataValue(int j){
    int * i = NULL;

    getDataWindow((void**)&i);
    *i = j;
}

void onFocus(void){
    setWindowDataValue(1);
}

void unFocus(void){
    setWindowDataValue(-1);
}
