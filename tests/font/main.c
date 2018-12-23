#include "../../SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

#include <string.h>

TEST_SECTION(Font){
    int color[] = {0, 0, 0, 0};
    int newColor[] = {255, 255, 255, 255};
    static Font * font = NULL; // static not to be reinitialized if a test case failed

    TEST_CASE(FontCreation){
	Font * dumb = NULL;

	dumb = createFont("path/that/do/not/exist", "nope", color, SANDAL2_SOLID);

	REQUIRE(!dumb);

	font = createFont("../../downloadable/arial.ttf", "yes", color, SANDAL2_SOLID);

	REQUIRE_NOT_NULL(font);
	
	REQUIRE_NOT_NULL(font->text);
	REQUIRE(!strcmp(font->text, "yes"));
	
	REQUIRE(color[0] == font->color.r);
	REQUIRE(color[1] == font->color.g);
	REQUIRE(color[2] == font->color.b);
	REQUIRE(color[3] == font->color.a);
	
	REQUIRE(SANDAL2_SOLID == font->quality);
	
	REQUIRE_NOT_NULL(font->font);
	REQUIRE_NOT_NULL(font->texture);
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(font);

    TEST_CASE(Setters){
	REQUIRE(!setTextFont(font, "polo"));
	REQUIRE_NOT_NULL(font->text);
	REQUIRE(!strcmp(font->text, "polo"));

	REQUIRE(!setColorFont(font, newColor));
	REQUIRE(newColor[0] == font->color.r);
	REQUIRE(newColor[1] == font->color.g);
	REQUIRE(newColor[2] == font->color.b);
	REQUIRE(newColor[3] == font->color.a);

	REQUIRE(!setStyleFont(font, SANDAL2_BOLD));
	REQUIRE_NOT_NULL(font->font);
	REQUIRE(SANDAL2_BOLD == TTF_GetFontStyle(font->font));
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(font);

    TEST_CASE(Getters){
	int style;
	
	REQUIRE(!getStyleFont(font, &style));
	REQUIRE(style == SANDAL2_BOLD);
    }

    freeFont(font);
}

int main(){
    int rc     = 0;
    int bg[4]  = {0};
    
    if(!initAllSANDAL2(IMG_INIT_JPG)){
	rc = 2 * createWindow(10, 10, "w", 0, bg, 0);

	if(!rc){
	    RUN_SECTION(Font);
	}
	
	closeAllSANDAL2();
    }else rc = 1;
    
    return rc;
}
