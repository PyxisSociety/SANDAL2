#ifndef ELEMENTSDL2_SANDAL2_KLEVH
#define ELEMENTSDL2_SANDAL2_KLEVH

#ifdef __cplusplus
extern "C" {
#endif
    
#include "Clickable.h"
#include "Font.h"
#include "Window.h"
#include "DisplayCode.h"
#include "Sprite.h"

#define SANDAL2_FLIP_HOR SDL_FLIP_HORIZONTAL
#define SANDAL2_FLIP_VER SDL_FLIP_VERTICAL
#define SANDAL2_FLIP_NONE SDL_FLIP_NONE
#define SANDAL2_FLIP SDL_RendererFlip

/**
 * @file Element.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Contains all structures related to Elements
 */

/**
 * @brief List of windows
 *   WARNING : Do not touch this list ... trust me
 */
extern ListWindow * _windows_SANDAL2;

/**
 * @struct Entry
 * @brief More informations about entry 
 */
typedef struct{
    int size_min;
    /**< minimum size of the text of the entry*/
    int size_max;
    /**< maximum size of the text of the entry*/
    int size;
    /**< actual size of the text of the entry*/
    int isSelect;
    /**< tells whether or not the Entry is selected (1 for yes, 0 for no)*/
    int isScripted;
    /**< tells whether or not the Entry is crypted (1 for yes, 0 for no)*/
}Entry;

struct ListPtrElement;
struct Element;

/**
 * @struct EventElement
 * @brief Behaviors of an element to  events
 */
typedef struct{
    void (*action)(struct Element*);
    /**< function called when update*/
    void (*onClick)(struct Element*, int);
    /**< function called when the element is clicked*/
    void (*unClick)(struct Element*, int);
    /**< function called when the element is unclicked*/
    void (*keyPress)(struct Element*,SDL_Keycode c);
    /**< function called when a key is pressed*/
    void (*keyReleased)(struct Element*,SDL_Keycode c);
    /**< function called when a key is released*/
    void (*unSelect)(struct Element*);
    /**< function called when the element is unselected*/
    void (*endSprite)(struct Element*,int code);
    /**< function called at the end of a sprite*/
    void (*onMouseMotion)(struct Element *);
    void (*unMouseMotion)(struct Element *);
}EventElement;

/**
 * @struct Element
 * @brief All the informations of an element
 */
typedef struct Element{
    float x;
    /**< abscissa coordinate of the top left of the element*/
    float y;
    /**< ordinate coordinate of the top left of the element*/
    float width;
    /**< width of the element*/
    float height;
    /**< height of the element*/
    float prX;
    /**< abscissa coordinate of the rotation point (if from 0 to 1, in the element)*/
    float prY;
    /**< ordinate coordinate of the rotation point (if from 0 to 1, in the element)*/
    float rotation;
    /**< rotation angle of the element*/
    float rotSpeed;
    /**< speed rotation (degree / update) of the element*/
    SANDAL2_FLIP flip;
    /**< tells whether or not the element should be flipped, can be SANDAL2_FLIP_VER, SANDAL2_FLIP_HOR, SANDAL2_FLIP_NONE or a combinaison of those  */
    int coulBlock[4];
    /**< color of the block of the element (if first value -1, there is no block)*/
    float textSize;
    /**< text proportion in the block*/
    ListDisplayCode *codes;
    /**< list of display code of the element*/
    EventElement events;
    /**< behavior of the element to  events*/
    SDL_Texture * image;
    /**< texture of the image (NULL if no image)*/
    ListAnimation * animation;
    /**< animation of the image*/
    Font *font;
    /**< informations about the text (NULL if no text)*/
    Entry *entry;
    /**< informations about the entry (NULL if no entry)*/
    struct ListPtrElement *interactions;
    /**< list of elements that this element can modifie*/
    ListClickable * hitboxes;
    /**< list of clickable zones*/
    void * data;
    /**< data available for the user*/
    void (*freeData)(void*);
    /**< function to be called to free the data */
    int deleted;
    /**< tells whether or not the element should be deleted (1 for completely deleted, 2 for display remove, 3 for plan change)*/
    int deleteCode;
    /**< plan or display code to be removed from*/
    int selected;
    /**< tells whether or not the element is selected*/
    Window * parent;
    /**< parent window of the element */
}Element;

/**
 * @struct PtrElement
 * @brief Structure used to store elements' pointers in a list of element
 */
typedef struct PtrElement{
    Element *element;
    /**< pointer of the element*/
    struct PtrElement *next;
    /**< next PtrElement in the list*/
}PtrElement;

/**
 * @struct ListPtrElement
 * @brief List of PtrElement
 */
typedef struct ListPtrElement{
    PtrElement *first;
    /**< first PtrElement of the list*/
    PtrElement *last;
    /**< last PtrElement of the list*/
    PtrElement *current;
    /**< current PtrElement of the list (used for iterator)*/
    struct ListPtrElement * next;
    /**< next List of PtrElement*/
    int code;
    /**< plan of the list*/
}ListPtrElement;

/**
 * @struct ListDCElement
 * @brief List (display code) of list (plan) of element
 */
typedef struct ListDCElement{
    ListPtrElement * first;
    /**< first list (plan) of element*/
    ListPtrElement * current;
    /**< current list (plan) of element (used for iterator)*/
    struct ListDCElement * next;
    /**< next list (display code) of list (plan) of element*/
    int code;
    /**< display code of this list*/
}ListDCElement;

/**
 * @struct ListElement
 * @brief List of list (display code) of list (plan) of elements
 */
typedef struct ListElement{
    ListDCElement *first;
    /**< first list (display code) of list (plan) of elements*/
    ListDCElement * currentDCIterator;
    /**< current list (display code) of list (plan) of elements (used for iterator)*/
    ListPtrElement *currentPIterator;
    /**< current list (plan) of elements (used for iterator)*/
}ListElement;



/* -------------------------------------------------------
 * Liste de liste (code d'affichage) de liste (plan) 
 * d'element
 */
/**
 * @brief Initialise a list of lists (display code) of lists (plan) of elements
 * @return An empty list  of lists (display code) of lists (plan) of elements
 */
ListElement* _initListElement(void);
/**
 * @brief free the memory of a list of lists (display code) of lists (plan) of elements
 * @param l : list to be freed
 */
void _freeListElement(ListElement* l);
/**
 * @brief add an element to a list of lists (display code) of lists (plan) of elements
 * @param e : element to be add
 * @return 0 if it could be done, 1 if not
 */
int addElement(Element* e);
/**
 * @brief remove all elements that are marked as deletable (do not use it yourself, used in update)
 */
void _cleanElement(void);
/**
 * @brief mark an element as removable
 * @param e : element to be removed
 * @return 0 if it could be done, 1 if not
 */
int delElement(Element *e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element creation, freeing and informations
 */
/**
 * @brief Free the memory used by an element
 * @param e : element to be freed
 */
void _freeElement(Element *e);
/**
 * @brief Generate a rectangle like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param couleur : color of the rectangle (RGBA)
 * @param displayCode : display code of the rectangle
 * @param plan : plan of the rectangle
 */
Element* createBlock(float x,float y,float width,float height,int couleur[4],int displayCode,int plan);
/**
 * @brief Generate a text like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param quality : quality of the text's texture (blended, shaded or solid)
 * @param displayCode : display code of the text
 * @param plan : plan of the text
 */
  Element* createText(float x,float y,float width,float height,float textSize, const char * font,const char * text,int textColor[4],int quality,int displayCode,int plan);
/**
 * @brief Generate an image like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the image
 * @param plan : plan of the image
 */
Element* createImage(float x,float y,float width,float height,const char *image,int displayCode,int plan);
/**
 * @brief Generate a button like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param quality : quality of the text's texture (blended, shaded or solid)
 * @param colorBlock : color of the rectangle (RGBA)
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 */
Element* createButton(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,int couleurBlock[4],int displayCode,int plan);
/**
 * @brief Generate a button like element with an image
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param quality : quality of the text's texture (blended, shaded or solid)
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 */
Element* createButtonImage(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,const char *image,int displayCode,int plan);
/**
 * @brief Generate a prompt like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param quality : quality of the text's texture (blended, shaded or solid)
 * @param colorBlock : color of the rectangle (RGBA)
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 * @param min : minimum number of character for the prompt to be validate
 * @param max : maximum number of character for the prompt to be validate
 * @param isScripted : flag which tells whether or not the prompt is cripted
 */
Element* createEntry(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,int couleurBlock[4],int displayCode,int plan,int min,int max, int isScripted);
/**
 * @brief Generate a prompt like element with an image
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param quality : quality of the text's texture (blended, shaded or solid)
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 * @param min : minimum number of character for the prompt to be validate
 * @param max : maximum number of character for the prompt to be validate
 * @param isScripted : flag which tells whether or not the prompt is cripted
 */
Element* createEntryImage(float x,float y,float width,float height,float texteSize,const char * font,const char * text,int textColor[4],int quality,const char *image,int displayCode,int plan,int min,int max,int isScripted);
/**
 * @brief tell whether or not the element can be displaied
 * @param e : element
 * @return 1 if the element is displaied (even outside the window), 0 if not
 */
int isDisplaiedElement(Element* e);
/**
 * @brief clear all elements of a display code in the current window
 * @param code : display code to be cleared
 * @return 1 if there was an error, 0 if not
 */
int clearDisplayCode(int code);
/**
 * @brief get the flip state of an element
 * @param e : element to get the flip state
 * @param flip : where to store the flip state
 * @return 0 if it succeeded, 1 if not
 */
int getFlipStateElement(Element * e,SANDAL2_FLIP * flip);
/**
 * @brief getter for the Element's coordinates
 * @param e : element to get the coordinates
 * @param x : where the abscissa coordinate will be store
 * @param y : where the ordinate coordinate will be store
 * @return 1 if there was an error, 0 if not
 */
int getCoordElement(Element* e,float* x,float* y);
/**
 * @brief getter for the Element's angle
 * @param e : element to get the angle
 * @param a : where the angle will be store
 * @return 1 if there was an error, 0 if not
 */
int getAngleElement(Element* e,float* a);
/**
 * @brief getter for the Element's dimensions
 * @param e : element to get the dimensions
 * @param w : where the width will be store
 * @param h : where the height will be store
 * @return 1 if there was an error, 0 if not
 */
int getDimensionElement(Element* e,float* w,float * h);
/**
 * @brief getter for the Element's rotation point
 * @param e : element to get the rotation point's coordinate
 * @param x : where the abscissa coordinate of the rotation point will be store 
 * @param y : where the ordinate coordinate of the rotation point will be store 
 * @return 1 if there was an error, 0 if not
 */
int getRotationPointElement(Element* e,float *x,float *y);
/**
 * @brief getter for the element's rotation speed
 * @param e : element to get the rotation speed
 * @param s : where the rotation speed will be store
 * @return 1 if there was an error, 0 if not
 */
int getRotationSpeedElement(Element* e,float* s);
/**
 * @brief getter for the element's data
 * @param e : element to get its data
 * @param data : where to store the element's data
 * @return 0 if it could be done, 1 if not
 */
int getDataElement(Element* e,void ** data);
/**
 * @brief tells whether or not the element is selected
 * @param e : element to get the information from
 * @param select : where to store the information
 * @return 1 if there was an error, 0 if not
 */
int isSelectedElement(Element *e, int * select);
/**
 * @breif get the element's text font style
 * @param e : the element to get the font style
 * @param style : where to store the style
 * @return 1 if there was an error, 0 if not
 */
int getTextStyleElement(Element *e,int * style);
/**
 * @brief get the text of an element
 * @param e : the element to get the text from
 * @param s : where to store the text
 * @return 1 if it failed, 0 if not
 */
int getTextElement(Element *e,char **s);
/**
 * @brief get the element's block color
 * @param e : element to get the informations from
 * @param color : where to store the block color
 * @return 1 if there was an error, 0 if not
 */
int getColorElement(Element *e,int color[4]);
/**
 * @brief get the element's width
 * @param e : element to get the informations from
 * @param w : where to store the width
 * @return 1 if there was an error, 0 if not
 */
int getWidthElement(Element * e,float * w);
/**
 * @brief get the element's height
 * @param e : element to get the informations from
 * @param h : where to store the height
 * @return 1 if there was an error, 0 if not
 */
int getHeightElement(Element * e,float * h);
/**
 * @brief get the element's x coordinate
 * @param e : element to get the informations from
 * @param x : where to store the x coordinate
 * @return 1 if there was an error, 0 if not
 */
int getCoordXElement(Element * e,float * x);
/**
 * @brief get the element's y coordinate
 * @param e : element to get the informations from
 * @param y : where to store the y coordinate
 * @return 1 if there was an error, 0 if not
 */
int getCoordYElement(Element * e,float * y);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element modifications
 */
/**
 * @brief set the element's font
 * @param e : element to be modified
 * @param font : path of the new font
 * @return 1 if there was an error, 0 if not
 */
int setFontElement(Element *e,const char * font);
/**
 * @brief set the element's text
 * @param e : element to be modified
 * @param text : the new text
 * @return 1 if there was an error, 0 if not
 */
int setTextElement(Element *e,const char * text);
/**
 * @brief set the element's text font style
 * @param e : the element to be modified
 * @param style : the style to apply
 * @return 1 if there was an error, 0 if not
 */
int setTextStyleElement(Element *e,int style);
/**
 * @brief set the element's block color
 * @param e : element to be modified
 * @param color : new block color
 * @return 1 if there was an error, 0 if not
 */
int setColorElement(Element *e,int color[4]);
/**
 * @brief set the element's text color
 * @param e : element to be modified
 * @param color : new text color
 * @return 1 if there was an error, 0 if not
 */
int setTextColorElement(Element *e, int color[4]);
/**
 * @brief set the element's text color
 * @param e : element to be modified
 * @param quality : new text quality
 * @return 1 if there was an error, 0 if not
 */
int setTextQualityElement(Element *e, int quality);
/**
 * @brief set the element's image
 * @param e : element to be modified
 * @param image : path of the new image
 * @return 1 if it failed, 0 if it succeeded
 */
int setImageElement(Element *e,const char *image);
/**
 * @brief set the element's image with a 's texture
 * @param e : element to be modified
 * @param image : texture of the new image
 * @return 1 if it failed, 0 if it succeeded
 */
int setImageTextureElement(Element *e,SDL_Texture * image);
/**
 * @brief set the element's coordinates
 * @param e : element to be modified
 * @param x : new abscissa coordinate
 * @param y : new ordinate coordinate
 */
int replaceElement(Element *e,float x,float y);
/**
 * @brief move an element
 * @param e : element to be modified
 * @param x : abscissa increment
 * @param y : ordinate increment
 * @return 1 if it was impossible, 0 if not
 */
int moveElement(Element *e,float x,float y);
/**
 * @brief resize an element
 * @param e : element to be modified
 * @param width : new width
 * @param height : new height
 * @return 1 if it was impossible, 0 if not
 */
int setDimensionElement(Element *e,float width,float height);
/**
 * @brief set the text size of the text of an element in this element
 * @param e : element to be modified
 * @param textSize : new size of the text (in percent)
 * @return 1 if it was impossible, 0 if not
 */
int setTextSize(Element *e,float textSize);
/**
 * @brief add a display code to an element (if it did not already had it)
 * @param e : element to be modified
 * @param displayCode : new display code
 * @param plan : plan linked to the new display code
 * @return 1 if it was impossible, 0 if not
 */
int addDisplayCodeElement(Element *e,int displayCode,int plan);
/**
 * @brief remove a display code to an element (if it has it)
 * @param e : element to be modified
 * @param displayCode : display code to be removed
 * @return 1 if it was impossible, 0 if not
 */
int delDisplayCodeElement(Element *e,int displayCode);
/**
 * @brief set the isDisplaied option of a display code (if the element has it)
 * @param e : element to be modified
 * @param displayCode : display code to be modified
 * @param isDisplaied : new isDisplaied option
 * @return 1 if it was impossible, 0 if not
 */
int setDisplayCodeElement(Element *e,int displayCode,int isDisplaied);
/**
 * @brief set the plan of a display code (if the element has it)
 * @param e : element to be modified
 * @param displayCode : display code to be modified
 * @param plan : new plan linked to the display code
 * @return 1 if it was impossible, 0 if not
 */
int setPlanElement(Element *e,int DisplayCode,int plan);
/**
 * @brief clear all elements of a plan in a display code of the current window
 * @param code : display code to be modified
 * @param plan : plan to be removed
 * @return 0 if it succeeded, 1 if not
 */
int clearPlanDisplayCode(int code, int plan);
/**
 * @brief set the continuous behaviour of an element
 * @param e : element to be modified
 * @param action : function to be called on each update call
 * @return 1 if it was impossible, 0 if not
 */
int setActionElement(Element *e,void (*action)(Element*));
/**
 * @brief set the behaviour of an element when a key is pressed
 * @param e : element to be modified
 * @param keyPress : function to be called when a key is pressed
 * @return 1 if it was impossible, 0 if not
 */
int setKeyPressedElement(Element *e,void (*keyPress)(Element*,SDL_Keycode c));
/**
 * @brief set the behaviour of an element when a key is released
 * @param e : element to be modified
 * @param keyReleased : function to be called when a key is released
 * @return 1 if it was impossible, 0 if not
 */
int setKeyReleasedElement(Element *e,void (*keyReleased)(Element*,SDL_Keycode c));
/**
 * @brief set the behaviour of an element when it is clicked
 * @param e : element to be modified
 * @param onCLick : function to be called when it is clicked
 * @return 1 if it was impossible, 0 if not
 */
  int setOnClickElement(Element *e,void (*onCLick)(Element*,int));
  int setOnMouseMotionElement(Element *e, void (*onMouseMotion)(Element*));
  int setUnMouseMotionElement(Element *e, void (*unMouseMotion)(Element*));
/**
 * @brief set the behaviour of an element when it is unclicked
 * @param e : element to be modified
 * @param unCLick : function to be called when it is unclicked
 * @return 1 if it was impossible, 0 if not
 */
  int setUnClickElement(Element *e,void (*unCLick)(Element*, int));
/**
 * @brief set the behaiour of an element when it is unselect
 * @param e : element to be modified
 * @param unSelect : new behaviour
 * @return 1 if it was impossible, 0 if not
 */
int setUnSelectElement(Element *e,void (*unSelect)(Element*));
/**
 * @brief set the behaiour of an element when it ends a sprite
 * @param e : element to be modified
 * @param endSprite : new behaviour
 * @return 1 if it was impossible, 0 if not
 */
int setEndSpriteElement(Element *e,void (*endSprite)(Element*,int));
/**
 * @brief add an element to another so that this other can modifie the first one
 * @param e : element to be modified
 * @param add : element to be add
 * @return 1 if it was impossible, 0 if not
 */
int addElementToElement(Element *e,Element *add);
/**
 * @brief remove an element to another so that this other can not modifie the first one
 * @param e : element to be modified
 * @param del : element to be removed
 * @return 1 if it was impossible, 0 if not
 */
int delElementToElement(Element *e,Element *del);
/**
 * @brief remove all elements binded to an element
 * @param e : element to be modified
 * @return 1 if it was impossible, 0 if not
 */
int clearElementToElement(Element *e);
/**
 * @brief add a clickable zone to the element (or a blocking one)
 * @param e : element to be modified
 * @param hb : clickable zone to be add
 * @param blocking : tells whether or not the clickable zone is a blocking one
 * @return 1 if it was impossible, 0 if not
 */
int addClickableElement(Element *e,Clickable *hb,int blocking);
/**
 * @brief increase the rotation speed of an element
 * @param e : element to be modified
 * @param s : rotation speed increment
 * @return 1 if it was impossible, 0 if not
 */
int addRotationSpeedElement(Element *e,float s);
/**
 * @brief set the rotation speed of an element
 * @param e : element to be modified
 * @param s : new rotation speed of the element
 * @return 1 if it was impossible, 0 if not
 */
int setRotationSpeedElement(Element *e,float s);
/**
 * @brief increase the angle of an element
 * @param e : element to be modified
 * @param a : angle increment
 * @return 1 if it was impossible, 0 if not
 */
int addAngleElement(Element *e,float a);
/**
 * @brief set the angle of an element
 * @param e : element to be modified
 * @param a : new angle of the element
 * @return 1 if it was impossible, 0 if not
 */
int setAngleElement(Element *e,float a);
/**
 * @brief set the rotation point's coordinates of an element
 * @param e : element to be modified
 * @param x : new abscissa coordinate of the rotation point
 * @param y : new ordinate coordinate of the rotation point
 * @return 1 if it was impossible, 0 if not
 */
int setRotationPointElement(Element *e,float x,float y);
/**
 * @brief set the element's data
 * @param e : element to be modified
 * @param data : new data of the element
 * @return 1 if it was impossible, 0 if not
 */
int setDataElement(Element *e,void *data);
/**
 * @brief set the element's freeing data's function (by default, set to free)
 * @param e : element to be modified
 * @param freeData : new data freeing behavior
 * @return 1 if it was impossible, 0 if not
 */
int setFreeDataElement(Element *e,void (*freeData)(void*));
/**
 * @brief free the element's data according to the element's freeing data behavior
 * @param e : element to be modified
 * @return 1 if it was impossible, 0 if not
 */
int freeDataElement(Element *e);
/**
 * @brief add an empty animation to the element
 * @param e : element
 * @param code : code of the new animation
 * @return 0 if the animation could be added, 1 if not
 */
int addAnimationElement(Element *e,int code);
/**
 * @brief remove an empty animation from the list
 * @param l : list of animation
 * @param code : code of the animation to be removed
 * @return 0 if the animation could be removed, 1 if not
 */
int delAnimationElement(Element *e,int code);
/**
 * @brief add a Sprite to the element
 * @param e : element
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : number of time the sprite should be displaied before going to the next sprite
 * @param codeS : identifier of the sprite to be added
 * @return 0 if the sprite was correctly added, 1 if not
 */
int addSpriteAnimationElement(Element *e,int code,int x,int y,int width,int height,int lifespan,int codeS);
/**
 * @brief remove a Sprite in the element
 * @param e : element
 * @param codeS : code of the sprite to be removed
 * @return 0 if the sprite was correctly removed, 1 if not
 */
int delSpriteAnimationElement(Element *e,int code,int codeS);
/**
 * @brief set the lifespan of a sprite
 * @param e : element
 * @param codeS : code of the sprite to be changed
 * @param lifespan : new number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the lifespan could be set, 1 if not
 */
int setLifeSpanSpriteAnimationElement(Element * e,int code,int codeS,unsigned lifespan);
/**
 * @brief go to te next sprite of the current animation of an element
 * @param e : element
 * @return 0 if it was possible, 1 if not
 */
int nextSpriteElement(Element * e);
/**
 * @brief go to the previous sprite of the current animation of an element
 * @param e : element
 * @return 0 if it was possible, 1 if not
 */
int previousSpriteElement(Element * e);
/**
 * @brief set the way to go from a sprite to another (forward (1), backward (-1), no move (0))
 * @param e : element
 * @param sens : new way
 * @return 0 if the way could be set, 1 if not
 */
int setWaySpriteAnimationElement(Element * e,int code, int sens);
/**
 * @brief go to te next animation of an element
 * @param e : element
 * @return 0 if it was possible, 1 if not
 */
int nextAnimationElement(Element * e);
/**
 * @brief go to the previous animation of an element
 * @param e : element
 * @return 0 if it was possible, 1 if not
 */
int previousAnimationElement(Element * e);
/**
 * @brief set the animation of an element
 * @param e : element to be modified
 * @param code : code of the animation to set
 * @return 0 if the animation is set, 1 if not
 */
int setAnimationElement(Element *e,int code);
/**
 * @brief set the sprite in the current animation of an element
 * @param e : element to be modified
 * @param codeS : code of the sprite to set
 * @return 0 if the sprite is set, 1 if not
 */
int setSpriteAnimationElement(Element *e,int codeS);
/**
 * @brief remove all elements from the current window
 * @return 0 if it was possible, 1 if not
 */
int clearWindow(void);
/**
 * @brief set the flip state of an element
 * @param e : element to be modified
 * @param flip : new flip state of the element
 * @return 0 if it was possible, 1 if not
 */
int setFlipStateElement(Element * e, SANDAL2_FLIP flip);
/**
 * @brief set the element's width
 * @param e : element to be modified
 * @param width : new width
 * @return 1 if there was an error, 0 if not
 */
int setWidthElement(Element * e, float width);
/**
 * @brief set the element's height
 * @param e : element to be modified
 * @param height : new height
 * @return 1 if there was an error, 0 if not
 */
int setHeightElement(Element * e, float height);
/**
 * @brief set the element's x coordinate
 * @param e : element to be modified
 * @param x : new x coordinate
 * @return 1 if there was an error, 0 if not
 */
int setCoordXElement(Element * e, float x);
/**
 * @brief set the element's y coordinate
 * @param e : element to be modified
 * @param y : new y coordinate
 * @return 1 if there was an error, 0 if not
 */
int setCoordYElement(Element * e, float y);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Element's list binded to an Element's iterator
 */
/**
 * @brief initialize the element's iterator on all the elements it can modifie
 * @param e : element from which to initialise the iterator
 * @return 1 if it succeeded, 0 if not
 */
int initIteratorElement(Element *e);
/**
 * @brief gives the current element's iterator's value and go to the next one
 * @param e : element to be modified
 * @return the current element
 */
Element* nextIteratorElement(Element *e);
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Element's list iterator
 */
/**
 * @brief initialise the iterator of all elements having a common display code
 * @param displayCode : common display code of the elements
 * @return 1 if it succeeded, 0 if not
 */
int initIterator(int displayCode);
/**
 * @brief gives the current iterator's value and go to the next one
 * @return the current element
 */
Element* nextElement();
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Entry modifications
 */
/**
 * @brief change the minimum and maximum size of a prompt (if a value is negative, it is not modified)
 * @param e : element to be modified
 * @param size_min : new minimum size of the prompt
 * @param size_max : new maximum size of the prompt
 * @return 0 if it was possible, 1 if not
 */
int setSizeEntry(Element *e,int size_min,int size_max);
/**
 * @brief set an element to crypted or uncrypted
 * @param e : element to be modified
 * @param isScripted : crypted option
 * @return 0 if it was possible, 1 if not
 */
int setScriptedEntry(Element *e,int isScripted);
/**
 * @brief add a character to a prompt
 * @param e : element to be modified
 * @param c : character to be added
 * @return 0 if it was possible, 1 if not
 */
int addCharEntry(Element *e,char c);
/**
 * @brief remove a character to a prompt
 * @param e : element to be modified
 * @return 0 if it was possible, 1 if not
 */
int delCharEntry(Element *e);
/* ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif
    
#endif
