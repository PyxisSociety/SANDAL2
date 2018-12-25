#include "../../SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

#include <string.h>

TEST_SECTION(Element){
    static Element e = {0}; // static not to be reinitialized if a test case failed

    TEST_CASE(set){
	// set font
	int color[4] = {255};
	const char * fontPath = "../../downloadable/arial.ttf";
	e.font = createFont(fontPath, "txt", color, SANDAL2_SOLID);
	REQUIRE_NOT_NULL(e.font);

	REQUIRE(setFontElement(NULL, NULL));
	REQUIRE(setFontElement(NULL, fontPath));
	REQUIRE(setFontElement(&e, "font/path/that/do/not/exist"));
	REQUIRE(!setFontElement(&e, fontPath));
	REQUIRE_NOT_NULL(e.font);

	// set text
	REQUIRE(setTextElement(NULL, NULL));
	REQUIRE(setTextElement(&e, NULL));
	REQUIRE(setTextElement(NULL, ""));
	REQUIRE(!setTextElement(&e, "coucou"));
	REQUIRE(!strcmp(e.font->text, "coucou"));

	// set text style
	REQUIRE(setTextStyleElement(NULL, SANDAL2_BOLD));
	REQUIRE(!setTextStyleElement(&e, SANDAL2_BOLD));
    }

    TEST_CASE(get){
    }

    if(e.codes){
	freeListDisplayCode(e.codes);
	e.codes = NULL;
    }
    if(e.image){
	SDL_DestroyTexture(e.image);
	e.image = NULL;
    }
    if(e.animation){
	freeListAnimation(e.animation);
	e.animation = NULL;
    }
    if(e.font){
	freeFont(e.font);
	e.font = NULL;
    }
    if(e.entry){
	free(e.entry);
	e.entry = NULL;
    }
    if(e.interactions){
	free(e.interactions);
	e.interactions = NULL;
    }
    if(e.hitboxes){
	freeListClickable(e.hitboxes);
	e.hitboxes = NULL;
    }
}

TEST_SECTION(ListElement){
    static Element * e = NULL; // static not to be reinitialized if a test case failed

    TEST_CASE(creation){
    }

    // not to do other test cases if e failed to be initialized
    REQUIRE_NOT_NULL(e);
}

int main(){
    int rc    = 0;
    int bg[4] = {0};
    
    if(initAllSANDAL2(IMG_INIT_JPG)){
	rc = 1;
    }else{
	if(createWindow(10, 10, "w", 0, bg, 0)){
	    rc = 2;
	}else{
	    RUN_SECTION(Element);
	    RUN_SECTION(ListElement);
	}
    
	closeAllSANDAL2();
    }
    
    return rc;
}
