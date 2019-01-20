#include "../../SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

int data[] = {0, 0, 0};

TEST_SECTION(WindowEvent_Focus){
    int i = 0;
    SDL_Event e = {0};
    
    unsigned long error;
    Uint32 windowIDs[3] = {0};
    
    TEST_CASE(after_init){
	i = 0;
	
	REQUIRE(!initIteratorWindow());

	// testing if only first window is focused
	while(i < 3){
	    REQUIRE_NOT_NULL(_windows_SANDAL2->current);
	    REQUIRE(_windows_SANDAL2->current->focused == (i == 2),
		    "%d: is focused ? %d\n", i, _windows_SANDAL2->current->focused);

	    windowIDs[i] = SDL_GetWindowID(_windows_SANDAL2->current->window);
	    
	    ++i;
	    if(i < 3) REQUIRE(!nextWindow(), "Failed on %d\n", i);
	}
    }

    TEST_CASE(changing_focus){
	int supposed[] = {-1, -1, 1};
	
	PollEvent(NULL); // to raise all focus changed done during window creation

	for(i = 0; i < 3; ++i)
	    REQUIRE(supposed[i] == data[i],
		    "supposed[%d]==%d && data[%d]==%d\n",i, supposed[i], i, data[i]);
    }
}

void onFocus(void);
void unFocus(void);

int main(){
    int rc     = 0;
    int bg[4]  = {0};
    int i;
    
    if(!initSANDAL2()){
	for(i = 0; i < 3 && rc; ++i){
	    rc = createWindow(10, 10, "w", 0, bg, 0);
	    if(rc){
		setDataWindow((void*)(data + i));
		setOnFocusedWindow(onFocus);
		setUnFocusedWindow(unFocus);
	    }
	}

	if(rc){
	    RUN_SECTION(WindowEvent_Focus);
	    rc = 0;
	}else rc = 2;
	
	closeSANDAL2();
    }else rc = 1;
    
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
