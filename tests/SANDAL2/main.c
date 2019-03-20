#include "SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

// global datas
int data[] = {0, 0, 0, 0};
typedef enum{
    KEYUP,
    KEYDOWN,
    MOUSEBUTTONDOWN,
    MOUSEBUTTONUP,
    MOUSEMOTION,
    MOUSEWHEEL,
    ACTION,
    COUNT
} EVENT_MARKERS;
int markers[COUNT] = {0};
// -----------

void onFocus(void);
void unFocus(void);
void onKeyUp(SDL_Keycode c);
void onKeyDown(SDL_Keycode c);
void onClick(int button);
void unClick(int button);
void onMouseMotion(int x, int y);
void onMouseWheel(int y);
void onAction(void);

void onKeyUpElement(Element * e, SDL_Keycode c);
void onKeyDownElement(Element * e, SDL_Keycode c);
void onClickElement(Element * e, int button);
void unClickElement(Element * e, int button);
void onMouseMotionElement(Element * e);
void unMouseMotionElement(Element * e);
void onActionElement(Element * e);





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


    
    TEST_CASE(simple_events){
        SDL_Event event = {0};
        int count = 0;
        
#       define TEST_EVENT(index)                                        \
        count = markers[index];                                         \
        event.type = SDL_##index;                                       \
        REQUIRE(SDL_PeepEvents(&event, 1, SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) >= 0); \
        REQUIRE(!PollEvent(NULL));                                      \
        REQUIRE(markers[index] == count + 1)
        
        // click
        TEST_EVENT(MOUSEBUTTONDOWN);

        // unclick
        TEST_EVENT(MOUSEBUTTONUP);

        // onMouse
        TEST_EVENT(MOUSEMOTION);

        // keyPressed
        TEST_EVENT(KEYUP);

        // keyReleased
        TEST_EVENT(KEYDOWN);

        // onWheel
        TEST_EVENT(MOUSEWHEEL);
        
#       undef TEST_EVENT

        // action
        count = markers[ACTION];
        REQUIRE(!updateWindow());
        REQUIRE(markers[ACTION] == count + 1);
    }


    
    TEST_CASE(SDL_CloseEvent){
        // window close
        SDL_Event event = {0};
        unsigned count = _windows_SANDAL2->count;
        event.type = SDL_WINDOWEVENT;
        event.window.event = SDL_WINDOWEVENT_CLOSE;
        event.window.windowID = 1;
        
        REQUIRE(SDL_PeepEvents(&event, 1, SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) >= 0);
        REQUIRE(!PollEvent(NULL));
        REQUIRE_NOT_NULL(_windows_SANDAL2);
        REQUIRE(_windows_SANDAL2->count == count - 1);
        
        // sdl quit
        event.type = SDL_QUIT;

        REQUIRE(SDL_PeepEvents(&event, 1, SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) >= 0);
        REQUIRE(PollEvent(NULL) == 1);
        REQUIRE(!_windows_SANDAL2);
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
        _windows_SANDAL2->current = _windows_SANDAL2->first->next;
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





TEST_SECTION(FunctionalTests){
    int bg[4]  = {0};
    ONCE REQUIRE(createWindow(100, 100, "w", 0, bg, 0));
    static Element * e1 = NULL;
    static Element * e2 = NULL;

    ONCE { // elements creation
        e1 = createBlock(0, 0, 10, 10, bg, 0, 0);
        e2 = createBlock(-1, -1, 10, 10, bg, 1, 0);
    }

    REQUIRE_NOT_NULL(e1);
    REQUIRE_NOT_NULL(e2);

    ONCE { // elements initialisation
        setOnClickElement(e2, onClickElement);
        setUnClickElement(e2, unClickElement);
        setKeyPressedElement(e2, onKeyDownElement);
        setKeyReleasedElement(e2, onKeyUpElement);
        setOnMouseMotionElement(e2, onMouseMotionElement);
        setActionElement(e2, onActionElement);

        addClickableElement(e2, rectangleClickable(0, 0, 1, 1), 0);
        e2->rotation = 90.f;
        e2->coulBlock[0] = -1;
    }

    ONCE { // graphic parts, ignored by UT
        displayWindow();
        displayAllWindow();
    }

    TEST_CASE(on_window){
        // set dc on window
        REQUIRE(!setDisplayCodeWindow(1));
        REQUIRE(!updateAllWindow());
        REQUIRE(_windows_SANDAL2->current->current->code == 1);
    }

    TEST_CASE(on_element){
        SDL_Event event = {0};
        int count = 0;

        _windows_SANDAL2->currentDisplay = _windows_SANDAL2->current;
        
#       define TEST_EVENT(index)                                        \
        count = markers[index];                                         \
        event.type = SDL_##index;                                       \
        REQUIRE(SDL_PeepEvents(&event, 1, SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) >= 0); \
        REQUIRE(!PollEvent(NULL));                                      \
        REQUIRE(markers[index] == count + 1,                            \
                #index " : expected (%d) != result (%d)\n", count + 1, markers[index])
        
        // click
        TEST_EVENT(MOUSEBUTTONDOWN);

        // unclick
        TEST_EVENT(MOUSEBUTTONUP);

        // onMouse
        TEST_EVENT(MOUSEMOTION);

        // keyPressed
        TEST_EVENT(KEYUP);

        // keyReleased
        TEST_EVENT(KEYDOWN);
#       undef TEST_EVENT

        // action
        count = markers[ACTION];
        REQUIRE(!updateAllWindow());
        REQUIRE(markers[ACTION] == count + 1);
    }
}





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
                setOnClickWindow(onClick);
                setUnClickWindow(unClick);
                setKeyPressedWindow(onKeyDown);
                setKeyReleasedWindow(onKeyUp);
                setOnWheelWindow(onMouseWheel);
                setOnMouseMotionWindow(onMouseMotion);
                setActionWindow(onAction);
	    }
	}

	if(rc){
	    RUN_SECTION(WindowEvent);
            
            for(i = 0; i < 4 && rc; ++i){
                rc = createWindow(10, 10, "w", 0, bg, 0);
            }

            if(rc){
                RUN_SECTION(WindowManagement);
                RUN_SECTION(FunctionalTests);
                rc = 0;
            }else{
                rc += 10;
                printf("a createWindow call failed: %s\n", SDL_GetError());
            }
	}else{
	    rc = 2;
	    printf("a createWindow call failed: %s\n", SDL_GetError());
	}
	
	closeAllSANDAL2();
    }else{
	rc = 1;
	printf("initAllSANDAL2 failed: %s\n", SDL_GetError());
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

void onKeyUp(SDL_Keycode c){
    (void)c;
    ++markers[KEYUP];
}

void onKeyDown(SDL_Keycode c){
    (void)c;
    ++markers[KEYDOWN];
}

void onClick(int button){
    (void)button;
    ++markers[MOUSEBUTTONDOWN];
}

void unClick(int button){
    (void)button;
    ++markers[MOUSEBUTTONUP];
}

void onMouseMotion(int x, int y){
    (void)x;
    (void)y;
    ++markers[MOUSEMOTION];
}

void onMouseWheel(int y){
    (void)y;
    ++markers[MOUSEWHEEL];
}

void onAction(){
    ++markers[ACTION];
}





void onKeyUpElement(Element * e, SDL_Keycode c){
    (void)e;
    onKeyUp(c);
}

void onKeyDownElement(Element * e, SDL_Keycode c){
    (void)e;
    onKeyDown(c);
}

void onClickElement(Element * e, int button){
    (void)e;
    onClick(button);
}

void unClickElement(Element * e, int button){
    (void)e;
    unClick(button);
}

void onMouseMotionElement(Element * e){
    (void)e;
    onMouseMotion(0, 0);
}

void unMouseMotionElement(Element * e){
    (void)e;
    onMouseMotion(0, 0);
}

void onActionElement(Element * e){
    (void)e;
    onAction();
}
