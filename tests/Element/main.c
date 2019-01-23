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

	// set color
	REQUIRE(setColorElement(NULL, color));
	REQUIRE(!setColorElement(&e, color));
	for(int i = 0; i < 4; ++i){
	    REQUIRE(e.coulBlock[i] == color[i]);
	}
	e.coulBlock[0] = -1;

	// set text color
	REQUIRE(setTextColorElement(NULL, color));
	REQUIRE(!setTextColorElement(&e, color));

	// set text quality
	REQUIRE(setTextQualityElement(NULL, 1));
	REQUIRE(!setTextQualityElement(&e, 1));
	REQUIRE(e.font->quality == 1);

	// set image
	REQUIRE(setImageElement(NULL, NULL));
	REQUIRE(setImageElement(NULL, ""));
	REQUIRE(setImageElement(&e, "image/path/that/do/not/exist"));
	REQUIRE(!setImageElement(&e, NULL));
	REQUIRE(!setImageElement(&e, "../../downloadable/img.jpg"));
	REQUIRE_NOT_NULL(e.image);

	// set image texture
	REQUIRE(setImageTextureElement(NULL, NULL));
	REQUIRE(!setImageTextureElement(&e, NULL));
	REQUIRE(e.image == NULL);

	// set dimension
	REQUIRE(setDimensionElement(NULL, 0, 0));
	REQUIRE(!setDimensionElement(&e, 1, 1));
	EQ(e.width, 1);
	EQ(e.height, 1);

	// set text size
	REQUIRE(setTextSize(NULL, 50.f));
	REQUIRE(!setTextSize(&e, 50.f));
	EQ(e.textSize, 0.5f);

	// set display code
	e.codes = initListDisplayCode();
	REQUIRE(!addDisplayCode(e.codes, 0, 0, 0));
	REQUIRE(setDisplayCodeElement(NULL, 0, 0));
	REQUIRE(setDisplayCodeElement(&e, 1, 1));
	REQUIRE(!setDisplayCodeElement(&e, 0, 1));
	REQUIRE(e.codes->first->isDisplaied == 1);

	// set event handlers
#       define TEST_HANDLER(name, eName)		\
	e.events.eName = (void*)1;			\
	REQUIRE(set##name##Element(NULL, NULL));	\
	REQUIRE(!set##name##Element(&e, NULL));		\
	REQUIRE(e.events.eName == NULL)

	TEST_HANDLER(Action, action);
	TEST_HANDLER(KeyPressed, keyPress);
	TEST_HANDLER(KeyReleased, keyReleased);
	TEST_HANDLER(OnClick, onClick);
	TEST_HANDLER(OnMouseMotion, onMouseMotion);
	TEST_HANDLER(UnMouseMotion, unMouseMotion);
	TEST_HANDLER(UnClick, unClick);
	TEST_HANDLER(UnSelect, unSelect);
	TEST_HANDLER(EndSprite, endSprite);
#       undef TEST_HANDLER

	// set rotation speed
	REQUIRE(setRotationSpeedElement(NULL, 10));
	REQUIRE(!setRotationSpeedElement(&e, 10));
	EQ(e.rotSpeed, 10);

	// set angle
	REQUIRE(setAngleElement(NULL, 10));
	REQUIRE(!setAngleElement(&e, 10));
	EQ(e.rotation, 10);

	// set rotation point
	REQUIRE(setRotationPointElement(NULL, 1, 1));
	REQUIRE(!setRotationPointElement(&e, 1, 1));
	EQ(e.prX, 1);
	EQ(e.prY, 1);

	// set data
	e.data = (void*)1;
	REQUIRE(setDataElement(NULL, NULL));
	REQUIRE(!setDataElement(&e, NULL));
	REQUIRE(e.data == NULL);

	// set free data
	e.freeData = (void*)1;
	REQUIRE(setFreeDataElement(NULL, NULL));
	REQUIRE(!setFreeDataElement(&e, NULL));
	REQUIRE(e.freeData == NULL);

	// set lifespan sprite animation
	e.animation = initListAnimation();
	REQUIRE_NOT_NULL(e.animation);
	REQUIRE(!createAnimation(e.animation, 0));
	REQUIRE(!addSpriteAnimation(e.animation, 0, 0, 0, 0, 0, 0, 0));
	
	REQUIRE(setLifeSpanSpriteAnimationElement(NULL, 0, 0, 0));
	REQUIRE(setLifeSpanSpriteAnimationElement(&e, 1, 0, 0));
	REQUIRE(setLifeSpanSpriteAnimationElement(&e, 0, 1, 0));
	REQUIRE(!setLifeSpanSpriteAnimationElement(&e, 0, 0, 1));
	REQUIRE(e.animation->first->first->lifespan == 1);

	// set way sprite animation
	REQUIRE(setWaySpriteAnimationElement(NULL, 0, 0));
	REQUIRE(setWaySpriteAnimationElement(&e, 1, 0));
	REQUIRE(!setWaySpriteAnimationElement(&e, 0, -1));
	REQUIRE(e.animation->first->side == -1);

	// set animation
	REQUIRE(setAnimationElement(NULL, 0));
	REQUIRE(setAnimationElement(&e, 1));
	REQUIRE(!setAnimationElement(&e, 0));

	// set sprite animation
	REQUIRE(setSpriteAnimationElement(NULL, 0));
	REQUIRE(setSpriteAnimationElement(&e, 1));
	REQUIRE(!setSpriteAnimationElement(&e, 0));
	freeListAnimation(e.animation);
	e.animation = NULL;

	// set flip state
	REQUIRE(setFlipStateElement(NULL, SANDAL2_FLIP_HOR));
	REQUIRE(!setFlipStateElement(&e, SANDAL2_FLIP_VER));
	REQUIRE(e.flip == SANDAL2_FLIP_VER);

	// set width / height / coord x / coord y
#       define TEST_UNARY(name, eName)		\
	REQUIRE(set##name##Element(NULL, 42));	\
	REQUIRE(!set##name##Element(&e, 42));	\
	EQ(e.eName, 42)

	TEST_UNARY(Width, width);
	TEST_UNARY(Height, height);
	TEST_UNARY(CoordX, x);
	TEST_UNARY(CoordY, y);
#       undef TEST_UNARY
    }

    TEST_CASE(get){
    }

    TEST_CASE(otherModifiers){
	// replace element
	REQUIRE(replaceElement(NULL, 0, 0));
	REQUIRE(!replaceElement(&e, 1, 1));
	EQ(e.x, 1);
	EQ(e.y, 1);

	// move element
	REQUIRE(moveElement(NULL, 0, 0));
	REQUIRE(!moveElement(&e, -1, -1));
	EQ(e.x, 0);
	EQ(e.y, 0);

	// add clickable
	e.hitboxes = initListClickable();
	REQUIRE(addClickableElement(NULL, NULL, 1));
	REQUIRE(addClickableElement(&e, NULL, 1));
	REQUIRE(!addClickableElement(&e, rectangleClickable(0, 0, 0, 0), 1));

	// add rotation speed
	REQUIRE(addRotationSpeedElement(NULL, 10));
	REQUIRE(!addRotationSpeedElement(&e, 10));
	EQ(e.rotSpeed, 20);

	// add angle
	REQUIRE(addAngleElement(NULL, 10));
	REQUIRE(!addAngleElement(&e, 10));
	EQ(e.rotation, 20);

	// add animation
	if(!e.animation){
	    e.animation = initListAnimation();
	    REQUIRE_NOT_NULL(e.animation);
	}
	REQUIRE(addAnimationElement(NULL, 0));
	REQUIRE(!addAnimationElement(&e, 0));

	// add sprite animation
	REQUIRE(addSpriteAnimationElement(NULL, 0, 0, 0, 0, 0, 0, 0));
	REQUIRE(addSpriteAnimationElement(&e, 1, 0, 0, 0, 0, 0, 0));
	REQUIRE(!addSpriteAnimationElement(&e, 0, 0, 0, 0, 0, 0, 0));

	// animation iterators
#       define TEST_ANIM_ITER(f)		\
	REQUIRE(f(NULL));			\
	REQUIRE(!f(&e))
	TEST_ANIM_ITER(nextSpriteElement);
	TEST_ANIM_ITER(previousSpriteElement);
	TEST_ANIM_ITER(nextAnimationElement);
	TEST_ANIM_ITER(previousAnimationElement);
#       undef TEST_ANIM_ITER

	// del sprite animation
	REQUIRE(delSpriteAnimationElement(NULL, 0, 0));
	REQUIRE(delSpriteAnimationElement(&e, 1, 0));
	REQUIRE(delSpriteAnimationElement(&e, 0, 1));
	REQUIRE(!delSpriteAnimationElement(&e, 0, 0));

	// del animation
	REQUIRE(delAnimationElement(NULL, 0));
	REQUIRE(delAnimationElement(&e, 1));
	REQUIRE(!delAnimationElement(&e, 0));
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
#       define TEST_ELEMENT(e, color, tsize, img, fnt, entr, dc, plane)	\
	REQUIRE_NOT_NULL(e);						\
	EQ(e->x, 0);							\
	EQ(e->y, 0);							\
	EQ(e->width, 1);						\
	EQ(e->height, 1);						\
	EQ(e->prX, 0.5f);						\
	EQ(e->prY, 0.5f);						\
	EQ(e->rotation, 0);						\
	EQ(e->rotSpeed, 0);						\
	EQ(e->flip, SANDAL2_FLIP_NONE);					\
	if(color[0] == -1){						\
	    REQUIRE(e->coulBlock[0] == -1);				\
        }else{								\
	    for(int i = 0; i < 4; ++i){					\
		REQUIRE(e->coulBlock[i] == color[i]);			\
	    }								\
	}								\
	if(tsize) EQ(e->textSize, tsize / 100.f);			\
	if(img){							\
	    REQUIRE_NOT_NULL(e->image);					\
	}else{								\
	    REQUIRE(e->image == NULL);					\
	}								\
	REQUIRE_NOT_NULL(e->animation);					\
	if(fnt){							\
	    REQUIRE_NOT_NULL(e->font);					\
	}else{								\
	    REQUIRE(e->font == NULL);					\
	}								\
	REQUIRE_NOT_NULL(e->hitboxes);					\
	REQUIRE(e->data == NULL);					\
	REQUIRE(e->freeData == NULL);					\
	REQUIRE(e->deleted == 0);					\
	REQUIRE(e->deleteCode == 0);					\
	REQUIRE(e->selected == 0);					\
	REQUIRE_NOT_NULL(e->parent);					\
	REQUIRE(e->interactions == NULL);				\
	/* e->codes */							\
	REQUIRE_NOT_NULL(e->codes);					\
	REQUIRE_NOT_NULL(e->codes->first);				\
	REQUIRE(e->codes->first->next == NULL);				\
	REQUIRE(e->codes->first->code == dc);				\
	REQUIRE(e->codes->first->plan == plane);			\
	REQUIRE(e->codes->size == 1);					\
	/* e->entry */							\
	if(entr){							\
	    REQUIRE_NOT_NULL(e->entry);					\
	    REQUIRE(e->entry->size_min == 0);				\
	    REQUIRE(e->entry->size_max == 10);				\
	    REQUIRE(e->entry->size == 6);				\
	    REQUIRE(e->entry->isSelect == 0);				\
	    REQUIRE(e->entry->isScripted == 0);				\
	}else{								\
	    REQUIRE(e->entry == NULL);					\
	}								\
	/* e->events */							\
	REQUIRE(e->events.action == NULL);				\
	REQUIRE(e->events.onClick == NULL);				\
	REQUIRE(e->events.unClick == NULL);				\
	REQUIRE(e->events.keyPress == NULL);				\
	REQUIRE(e->events.keyReleased == NULL);				\
	REQUIRE(e->events.unSelect == NULL);				\
	REQUIRE(e->events.endSprite == NULL);				\
	REQUIRE(e->events.onMouseMotion == NULL);			\
	REQUIRE(e->events.unMouseMotion == NULL)
#       define FONT "../../downloadable/arial.ttf", "coucou"
#       define IMG "../../downloadable/img.jpg"
#       define DIM 0, 0, 1, 1
#       define DC 0, 0
	
	int color[4] = {0};
	int noColor[4] = {-1};
	e = createEntryImage(DIM, 1, FONT, color, SANDAL2_SOLID, IMG, DC, 0, 10, 0);
	TEST_ELEMENT(e, noColor, 1, 1, 1, 1, 0, 0);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
	delElement(e);

	e = createEntry(DIM, 1, FONT, color, SANDAL2_SOLID, color, 0, 1, 0, 10, 0);
	TEST_ELEMENT(e, color, 1, 0, 1, 1, 0, 1);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
	delElement(e);

	e = createButtonImage(DIM, 1, FONT, color, SANDAL2_SOLID, IMG, 1, 0);
	TEST_ELEMENT(e, noColor, 1, 1, 1, 0, 1, 0);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
	delElement(e);

	e = createButton(DIM, 1, FONT, color, SANDAL2_SOLID, color, DC);
	TEST_ELEMENT(e, color, 1, 0, 1, 0, 0, 0);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
	delElement(e);

	e = createImage(DIM, IMG, DC);
	TEST_ELEMENT(e, noColor, 0, 1, 0, 0, 0, 0);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
	delElement(e);

	e = createText(DIM, 1, FONT, color, SANDAL2_SOLID, DC);
	TEST_ELEMENT(e, noColor, 1, 0, 1, 0, 0, 0);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
	delElement(e);

	e = createBlock(DIM, color, DC);
	TEST_ELEMENT(e, color, 0, 0, 0, 0, 0, 0);
	// element, block color, text size (0 if no test), image not NULL, font not NULL, entry not NULL
#       undef DIM
#       undef IMG
#       undef FONT
#       undef TEST_ELEMENT
	
	updateAllWindow(); // deleting all elements that should be deleted

	// testing if deletion was successful
	REQUIRE_NOT_NULL(_windows_SANDAL2);
	REQUIRE_NOT_NULL(_windows_SANDAL2->current);
	REQUIRE_NOT_NULL(_windows_SANDAL2->current->liste);
	ListElement * le = _windows_SANDAL2->current->liste;
	REQUIRE_NOT_NULL(le->first);
	REQUIRE_NOT_NULL(le->first->next);
	REQUIRE(le->first->next->next == NULL);
	REQUIRE(le->first->code == 0,
		"%d\n", le->first->code);
	REQUIRE(le->first->next->code == 1);
	REQUIRE_NOT_NULL(le->first->first);
	REQUIRE(le->first->first->next == NULL);
	REQUIRE(le->first->first->code == 0);
	REQUIRE_NOT_NULL(le->first->first->first);
	PtrElement * pe = le->first->first->first;
	REQUIRE(pe->next == NULL);
	REQUIRE(pe->element == e);
    }

    // not to do other test cases if e failed to be initialized
    REQUIRE_NOT_NULL(e);

    TEST_CASE(set){
	// set plan
    }

    TEST_CASE(otherModifiers){
	// add display code

	// del display code

	// clear plan

	// add element to element

	// del element to element

	// clear element to element

	// clear window
    }

    if(e){
	delElement(e);
	e = NULL;
    }
}

int main(){
    int rc    = 0;
    int bg[4] = {0};
    
    if(initAllSANDAL2(IMG_INIT_JPG)){
	rc = 1;
	printf("%s\n", SDL_GetError());
    }else{
	if(!createWindow(10, 10, "w", 0, bg, 0)){
	    rc = 2;
	    printf("%s\n", SDL_GetError());
	}else{
	    RUN_SECTION(Element);
	    RUN_SECTION(ListElement);
	}
    
	closeAllSANDAL2();
    }
    
    return rc;
}
