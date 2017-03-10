#ifndef _ELEMENTSDL2_SDL2TK_KLEVH_
#define _ELEMENTSDL2_SDL2TK_KLEVH_

#include "HitBox.h"
#include "FontSDL2.h"
#include "FenetreSDL2.h"
#include "DisplayCode.h"

/**
 * @file ElementSDL2.h
 * @brief Contains all structures related to Elements
 */

/**
 * @brief List of windows
 *   WARNING : Do not touch this list ... trust me
 */
extern ListFenetreSDL2 * _windows_SDL2TK;

/**
 * @struct EntrySDL2
 * @brief More informations about entry 
 */
typedef struct{
  int size_min;
  ///< minimum size of the text of the entry
  int size_max;
  ///< maximum size of the text of the entry
  int size;
  ///< actual size of the text of the entry
  /* vaut 1 si l'Entry est selectionnee, 0 sinon */
  int isSelect;
  ///< tells whether or not the Entry is selected (1 for yes, 0 for no)
  int isScripted;
  ///< tells whether or not the Entry is crypted (1 for yes, 0 for no)
}EntrySDL2;

struct ListPtrElementSDL2;

/**
 * @struct ElementSDL2
 * @brief All the informations of an element
 */
typedef struct ElementSDL2{
  float x;
  ///< abscissa coordinate of the top left of the element
  float y;
  ///< ordinate coordinate of the top left of the element
  float width;
  ///< width of the element
  float height;
  ///< height of the element
  float prX;
  ///< abscissa coordinate of the rotation point (if from 0 to 1, in the element)
  float prY;
  ///< ordinate coordinate of the rotation point (if from 0 to 1, in the element)
  float rotation;
  ///< rotation angle of the element
  float rotSpeed;
  ///< speed rotation (degree / update) of the element
  /* couleurs du texte et du block (la premiere case vaut -1 si la partie a colorie n'est pas dans l'element) */
  int coulBlock[4];
  ///< color of the block of the element (if first value -1, there is no block)
  float textSize;
  ///< text proportion in the block
  ListDisplayCode *codes;
  ///< list of display code of the element
  void (*action)(struct ElementSDL2*);
  ///< function called when update
  void (*onClick)(struct ElementSDL2*);
  ///< function called when the element is clicked
  void (*unClick)(struct ElementSDL2*);
  ///< function called when the element is unclicked
  void (*keyPress)(struct ElementSDL2*,SDL_Keycode c);
  ///< function called when a key is pressed
  void (*keyReleased)(struct ElementSDL2*,SDL_Keycode c);
  ///< function called when a key is released
  SDL_Texture *image;
  ///< texture of the image (NULL if no image)
  FontSDL2 *police;
  ///< informations about the text (NULL if no text)
  EntrySDL2 *entry;
  ///< informations about the entry (NULL if no entry)
  struct ListPtrElementSDL2 *interactions;
  ///< list of elements that this element can modifie
  ListHitBox * hitboxes;
  ///< list of clickable zones
  void * data;
  ///< data available for the user
}ElementSDL2;

/**
 * @struct PtrElementSDL2
 * @brief Structure used to store elements' pointers in a list of element
 */
typedef struct PtrElement{
  ElementSDL2 *element;
  ///< pointer of the element
  struct PtrElement *next;
  ///< next PtrElement in the list
}PtrElementSDL2;

/**
 * @struct ListPtrElementSDL2
 * @brief List of PtrElementSDL2
 */
typedef struct ListPtrElementSDL2{
  PtrElementSDL2 *first;
  ///< first PtrElementSDL2 of the list
  PtrElementSDL2 *last;
  ///< last PtrElementSDL2 of the list
  PtrElementSDL2 *current;
  ///< current PtrElementSDL2 of the list (used for iterator)
  struct ListPtrElementSDL2 * next;
  ///< next List of PtrElementSDL2
  int code;
  ///< plan of the list
}ListPtrElementSDL2;

/**
 * @struct ListDCElementSDL2
 * @brief List (display code) of list (plan) of element
 */
typedef struct ListDCElementSDL2{
  ListPtrElementSDL2 * first;
  ///< first list (plan) of element
  ListPtrElementSDL2 * current;
  ///< current list (plan) of element (used for iterator)
  struct ListDCElementSDL2 * next;
  ///< next list (display code) of list (plan) of element
  int code;
  ///< display code of this list
}ListDCElementSDL2;

/**
 * @struct ListElementSDL2
 * @brief List of list (display code) of list (plan) of elements
 */
typedef struct ListElementSDL2{
  ListDCElementSDL2 *first;
  ///< first list (display code) of list (plan) of elements
  ListDCElementSDL2 * currentDCIterator;
  ///< current list (display code) of list (plan) of elements (used for iterator)
  ListPtrElementSDL2 *currentPIterator;
  ///< current list (plan) of elements (used for iterator)
}ListElementSDL2;



/* -------------------------------------------------------
 * Liste d'elements SDL2 avec plan commun
 */
/**
 * @brief Initialise a list (plan) of elements
 * @param plan : plan of the list to be initialised
 * @return An empty list (plan) of elements
 */
ListPtrElementSDL2* initListPtrElementSDL2(int plan);
/**
 * @brief free the memory of a list (plan) of elements
 * @param l : list to be freed
 */
void freeListPtrElementSDL2(ListPtrElementSDL2* l);
/**
 * @brief add an element to a list (plan) of elements
 * @param l : list (plan) of elements which to add an element
 * @param e : element to add
 */
void addPtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e);
/**
 * @brief remove an element to a list (plan) of elements
 * @param l : list (plan) of elements which to remove an element
 * @param e : element to remove
 */
void removePtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (plan) d'element, contenant le code 
 * d'affichage
 */
/**
 * @brief Initialise a list (display code) of lists (plan) of elements
 * @param displayCode : display code of the list to be initialised
 * @return An empty list (display code) of lists (plan) of elements
 */
ListDCElementSDL2* initListDCElementSDL2(int displayCode);
/**
 * @brief free the memory of a list (display code) of lists (plan) of elements
 * @param l : list to be freed
 */
void freeListDCElementSDL2(ListDCElementSDL2* l);
/**
 * @brief add a list (plan) to a list (display code) of lists (plan) of elements
 * @param l : list (display code) of lists (plan) of elements which to add a list (plan)
 * @param lp : list (plan) to add
 */
void addListPtrElementSDL2(ListDCElementSDL2* l, ListPtrElementSDL2 *lp);
/**
 * @brief remove a list (plan) to a list (display code) of lists (plan) of elements
 * @param l : list (display code) of lists (plan) of elements which to remove an element
 * @param lp : list (plan) to remove
 */
void removeListPtrElementSDL2(ListDCElementSDL2* l,ListPtrElementSDL2 *lp);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (code d'affichage) de liste (plan) 
 * d'element
 */
/**
 * @brief Initialise a list of lists (display code) of lists (plan) of elements
 * @return An empty list  of lists (display code) of lists (plan) of elements
 */
ListElementSDL2* initListElementSDL2();
/**
 * @brief free the memory of a list of lists (display code) of lists (plan) of elements
 * @param l : list to be freed
 */
void freeListElementSDL2(ListElementSDL2* l);
/**
 * @brief add an element to a list of lists (display code) of lists (plan) of elements
 * @param l : list of lists (display code) of lists (plan) of elements which to add a list (plan)
 * @param e : element to be add
 */
int addElementSDL2(ElementSDL2* e);
/**
 * @brief remove an element to a list of lists (display code) of lists (plan) of elements
 * @param l : list of lists (display code) of lists (plan) of elements which to remove an element
 * @param e : element to remove
 */
int removeElementSDL2(ElementSDL2* e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Creation, liberation et information sur un Element SDL2
 */
/**
 * @brief Free the memory used by an element
 * @param e : element to be freed
 */
void freeElementSDL2(ElementSDL2 *e);
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
ElementSDL2* createBlock(float x,float y,float width,float height,int couleur[4],int displayCode,int plan);
/**
 * @brief Generate a text like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param displayCode : display code of the text
 * @param plan : plan of the text
 */
ElementSDL2* createTexte(float x,float y,float width,float height,char * font,char * text,int textColor[4],int displayCode,int plan);
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
ElementSDL2* createImage(float x,float y,float width,float height,char *image,int displayCode,int plan);
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
 * @param colorBlock : color of the rectangle (RGBA)
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 */
ElementSDL2* createButton(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan);
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
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 */
ElementSDL2* createButtonImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan);
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
 * @param colorBlock : color of the rectangle (RGBA)
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 * @param min : minimum number of character for the prompt to be validate
 * @param max : maximum number of character for the prompt to be validate
 * @param isScripted : flag which tells whether or not the prompt is cripted
 */
ElementSDL2* createEntry(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,int min,int max, int isScripted);
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
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 * @param min : minimum number of character for the prompt to be validate
 * @param max : maximum number of character for the prompt to be validate
 * @param isScripted : flag which tells whether or not the prompt is cripted
 */
ElementSDL2* createEntryImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,int min,int max,int isScripted);
/* retourne 1 si l'element passe en parametre peut etre affiche sur la fenetre passe en parametre, 0 sinon */
int isDisplaied(ElementSDL2* e);
/* getter for the Element's coordinates */
int getCoordElementSDL2(ElementSDL2* e,float* x,float* y);
/* getter for the Element's angle */
int getAngleElementSDL2(ElementSDL2* e,float*);
/* getter for the Element's dimensions */
int getDimensionElementSDL2(ElementSDL2* e,int* w,int * h);
/* getter for the Element's rotation point */
int getRotationPointElementSDL2(ElementSDL2* e,float *x,float *y);
/* getter pour la vitesse de rotation par update */
int getRotationSpeedElementSDL2(ElementSDL2* e,float*);
/* getter for data */
void * getDataElementSDL2(ElementSDL2* e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2
 */
/* change la police */
void setFontElementSDL2(ElementSDL2 *e,char * font);
/* change le texte */
void setTextElementSDL2(ElementSDL2 *e,char * text);
/* change la couleur du block */
void setColorElementSDL2(ElementSDL2 *e,int color[4]);
/* change l'image */
int setImageElementSDL2(ElementSDL2 *e,char *image);
/* change les coordonnees*/
void replaceElementSDL2(ElementSDL2 *e,float x,float y);
/*deplace un element*/
void moveElementSDL2(ElementSDL2 *e,float x,float y);
/* change la taille */
void resizeElementSDL2(ElementSDL2 *e,float width,float height);
/* change la taille du texte */
void setTextSize(ElementSDL2 *e,float textSize);
/* ajoute un code de display (si pas deja present) */
void addDisplayCodeElementSDL2(ElementSDL2 *e,int displayCode,int plan);
/* supprime un code de display */
void removeDisplayCodeElementSDL2(ElementSDL2 *e,int displayCode);
/* change l'option isDisplaied d'un code de display */
void setDisplayElementSDL2(ElementSDL2 *e,int displayCode,int isDisplaied);
/* change le plan d'un element pour un code de display */
void setPlanElementSDL2(ElementSDL2 *e,int DisplayCode,int plan);
/* change l'interaction continue */
void setActionElementSDL2(ElementSDL2 *e,void (*action)(ElementSDL2*));
/* change l'interaction a l'appuie d'une touche du clavier */
void setKeyPressElementSDL2(ElementSDL2 *e,void (*keyPress)(ElementSDL2*,SDL_Keycode c));
/* change l'interaction au relachement d'une touche du clavier */
void setKeyReleasedElementSDL2(ElementSDL2 *e,void (*keyReleased)(ElementSDL2*,SDL_Keycode c));
/* change l'interaction au clique de souris */
void setOnClickElementSDL2(ElementSDL2 *e,void (*onCLick)(ElementSDL2*));
/* change l'interaction au relachement d'un clique de souris */
void setUnClickElementSDL2(ElementSDL2 *e,void (*unCLick)(ElementSDL2*));
/* ajoute un element dans la liste d'interaction a la fin */
void addElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *add);
/* retire un element dans la liste d'interaction */
void delElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *del);
/* ajoute une hit boxe a un element */
void addHitBoxElementSDL2(ElementSDL2 *e,HitBox *hb);
/* augmente la vitesse de rotation de l'element de s */
void addRotationSpeedElementSDL2(ElementSDL2 *e,float s);
/* definie la vitesse de rotation de l'element */
void setRotationSpeedElementSDL2(ElementSDL2 *e,float s);
/* augmente l'angle de l'element de a */
void addAngleElementSDL2(ElementSDL2 *e,float a);
/* defini l'angle de l'elemant a a */
void setAngleElementSDL2(ElementSDL2 *e,float a);
/* defini le point de rotation de l'element */
void setRotationPointElementSDL2(ElementSDL2 *e,float x,float y);
/* defini le paquet de donnée */
void setDataElementSDL2(ElementSDL2 *e,void *data);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Iterateur de structure sur la liste d'ElementSDL2 lié a un autre ElementSL2
 */
/* initialisation de l'iterateur de structure d'un element */
int initIterateurElementSDL2(ElementSDL2 *e);
/* donne l'element actuel et prepare le prochain */
ElementSDL2* nextIterateurElementSDL2(ElementSDL2 *e);
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Iterateur de structure sur la liste d'ElementSDL2
 */
/* initialise l'iterateur de structure sur les elements ayant le display code*/
int initIterateur(int displayCode);
/* donne l'element actuel et prepare le prochain */
ElementSDL2* nextElementSDL2();
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2 spécifique aux Entry
 */
/* change la taille min et taille max du texte (si une valeur <0, pas de changement sur cette valeur) */
void changeSizeEntrySDL2(ElementSDL2 *e,int size_min,int size_max);
/* met l'option crypté de l'entry à la valeur isScripted */
void setScriptedEntrySDL2(ElementSDL2 *e,int isScripted);
/* ajoute un caractere a une entry */
void addCharEntrySDL2(ElementSDL2 *e,char c);
/* supprime un caractere a une entry */
void removeCharEntrySDL2(ElementSDL2 *e);
/* ------------------------------------------------------- */

#endif
