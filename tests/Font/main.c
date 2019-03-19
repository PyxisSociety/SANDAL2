#include "SANDAL2.h"

#define LASSERT_MANUAL_MAIN
#include "../LAssert/LAssert.h"

#include <string.h>

TEST_SECTION(Font){
    int color[] = {0, 0, 0, 0};
    int newColor[] = {255, 255, 255, 255};
    static Font * font = NULL; // static not to be reinitialized if a test case failed

    TEST_CASE(FontCreation){
	int qualities[3] = {SANDAL2_SOLID, SANDAL2_SHADED, SANDAL2_BLENDED};
	int i;
	Font * dumb = NULL;

	for(i = 0; i < 3; ++i){
	    dumb = createFont("path/that/do/not/exist", "nope", color, qualities[i]);

	    REQUIRE(!dumb);

	    font = createFont("downloadable/arial.ttf", "yes", color, qualities[i]);

	    REQUIRE_NOT_NULL(font);
	
	    REQUIRE_NOT_NULL(font->text);
	    REQUIRE(!strcmp(font->text, "yes"));
	
	    REQUIRE(color[0] == font->color.r);
	    REQUIRE(color[1] == font->color.g);
	    REQUIRE(color[2] == font->color.b);
	    REQUIRE(color[3] == font->color.a);
	
	    REQUIRE(qualities[i] == font->quality);
	
	    REQUIRE_NOT_NULL(font->font);
	}
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(font);

    TEST_CASE(Setters){
	int qualities[] = {SANDAL2_SOLID, SANDAL2_SHADED, SANDAL2_BLENDED};
	int i = 0;

	for(i = 0; i < 3; ++i){
	    REQUIRE(!setStyleFont(font, qualities[i]));
	    REQUIRE_NOT_NULL(font->font);
	    REQUIRE(qualities[i] == TTF_GetFontStyle(font->font));
	    REQUIRE(qualities[i] == font->quality);
	
	    REQUIRE(!setTextFont(font, "polo"));
	    REQUIRE_NOT_NULL(font->text);
	    REQUIRE(!strcmp(font->text, "polo"));

	    REQUIRE(!setColorFont(font, newColor));
	    REQUIRE(newColor[0] == font->color.r);
	    REQUIRE(newColor[1] == font->color.g);
	    REQUIRE(newColor[2] == font->color.b);
	    REQUIRE(newColor[3] == font->color.a);
	}
    }

    // not to do other test cases if font failed to be initialized
    REQUIRE_NOT_NULL(font);

    TEST_CASE(Getters){
	int style;
	
	REQUIRE(!getStyleFont(font, &style));
	REQUIRE(style == SANDAL2_BLENDED);
    }

    TEST_CASE(OtherMethods){
	int qualities[3] = {SANDAL2_SOLID, SANDAL2_SHADED, SANDAL2_BLENDED};
	unsigned long i = 0;
	unsigned long j;

	REQUIRE(actualizeTextFont(NULL, 0));
	for(i = 0; i < 3; ++i){
	    REQUIRE(!setStyleFont(font, qualities[i]));
	    REQUIRE(font->quality == qualities[i]);
	    for(j = 0; j < 2; ++j){
		REQUIRE(!actualizeTextFont(font, 1 - j));
		REQUIRE(font->texture == (SDL_Texture*)(1 - j),
			"%d: %p\n", 1 - j, font->texture);
	    }
	}
    }

    freeFont(font);
}

int main(){
    int rc     = 0;
    int bg[4]  = {0};
    
    if(!initAllSANDAL2(IMG_INIT_JPG)){
	rc = createWindow(10, 10, "w", 0, bg, 0);

	if(rc){
	    RUN_SECTION(Font);
	    rc = 0;
	}else rc = 2;
	
	closeAllSANDAL2();
    }else{
	rc = 1;
	printf("%s\n", SDL_GetError());
    }
    
    return rc;
}
