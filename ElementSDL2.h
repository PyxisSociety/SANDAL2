#ifndef _ELEMENTSDL2_SDL2TK_KLEVH_
#define _ELEMENTSDL2_SDL2TK_KLEVH_

#include "HitBox.h"
#include "FontSDL2.h"
#include "FenetreSDL2.h"
#include "DisplayCode.h"

extern ListFenetreSDL2 * _windows_SDL2TK;

/* Informations supplementaires d'une Entry SDL2 */
typedef struct{
  /* taille minimum et maximum du texte */
  int size_min;
  int size_max;
  int size;
  /* vaut 1 si l'Entry est selectionnee, 0 sinon */
  int isSelect;
  /* vaut 1 si le texte doit etre remplacee par des '*', 0 sinon */
  int isScripted;
}EntrySDL2;

struct ListPtrElementSDL2;

/* element SDL2 */
typedef struct ElementSDL2{
  /* coord relatives de l'elements (compris entre 0 et 1) */
  float x;
  float y;
  /* taille relative de l'elements (compris entre 0 et 1) */
  float width;
  float height;
  /* point de rotation de l'objet (relatif a lui meme)*/
  float prX;
  float prY;
  /* angle de rotation de l'objet en degree */
  float rotation;
  /* pas de rotation continue de l'objet */
  float rotSpeed;
  /* couleurs du texte et du block (la premiere case vaut -1 si la partie a colorie n'est pas dans l'element) */
  int coulBlock[4];
  /* proportion du texte dans le block (si texte) */
  float textSize;
  /* liste des codes d'affichage */
  ListDisplayCode *codes;
  /* fonction d'action continue */
  void (*action)(struct ElementSDL2*);
  /* fonction d'interaction au click */
  void (*onClick)(struct ElementSDL2*);
  /* fonction d'interaction au relachement du click */
  void (*unClick)(struct ElementSDL2*);
  /* fonction d'interaction avec une touche du clavier */
  void (*keyPress)(struct ElementSDL2*,SDL_Keycode c);
  /* fonction d'interaction au relachement d'une touche du clavier */
  void (*keyReleased)(struct ElementSDL2*,SDL_Keycode c);
  /* texture de l'image (si image) */
  SDL_Texture *image;
  /* texture et surface du texte (si texte) */
  FontSDL2 *police;
  /* donnees suplementaires si l'element est une Entry */
  EntrySDL2 *entry;
  /* elements entrant en interaction avec cet element */
  struct ListPtrElementSDL2 *interactions;
  /* hit boxes de l'element, l'element est considerer comme le carre de cote 1 allant de (0,0) a (1,1) */
  ListHitBox * hitboxes;
  /* paquet de donnees */
  void * data;
}ElementSDL2;

/* pointeur d'un element (liste pour permettre a un element d'en modifier un autre) */
typedef struct PtrElement{
  ElementSDL2 *element;
  struct PtrElement *next;
}PtrElementSDL2;

/* Liste de pointeur d'element avec numero du plan */
typedef struct ListPtrElementSDL2{
  PtrElementSDL2 *first;
  PtrElementSDL2 *last;
  PtrElementSDL2 *current;
  struct ListPtrElementSDL2 * next;
  int code;
}ListPtrElementSDL2;

/* Liste de liste (plan) d'element, contenant le code d'affichage */
typedef struct ListDCElementSDL2{
  ListPtrElementSDL2 * first;
  ListPtrElementSDL2 * current;
  struct ListDCElementSDL2 * next;
  int code;
}ListDCElementSDL2;

/* Liste de liste (code d'affichage) de liste (plan) d'element */
typedef struct ListElementSDL2{
  /* premier element de la liste */
  ListDCElementSDL2 *first;
  /* element de la liste contenant le display code courant */
  ListDCElementSDL2 * currentDCIterator;
  /* element de la liste contenant le plan courant */
  ListPtrElementSDL2 *currentPIterator;
}ListElementSDL2;



/* -------------------------------------------------------
 * Liste d'elements SDL2 avec plan commun
 */
/* renvoi une liste d'element SDL2 vide avec un plan commun */
ListPtrElementSDL2* initListPtrElementSDL2(int plan);
/* libere la liste passe en parametre */
void freeListPtrElementSDL2(ListPtrElementSDL2*);
/* ajout d'un element SDL2 a la liste passe en parametre */
void addPtrElementSDL2(ListPtrElementSDL2*,ElementSDL2*);
/* retire un element SDL2 a la liste passe en parametre */
void removePtrElementSDL2(ListPtrElementSDL2*,ElementSDL2*);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (plan) d'element, contenant le code 
 * d'affichage
 */
/* renvoi une liste de liste (plan) d'element contenant un code d'affichage commun */
ListDCElementSDL2* initListDCElementSDL2(int displayCode);
/* libere une liste de ce genre */
void freeListDCElementSDL2(ListDCElementSDL2* l);
/* ajoute une liste (plan) dans cette liste */
void addListPtrElementSDL2(ListDCElementSDL2* l, ListPtrElementSDL2 *lp);
/* retire une liste (plan) dans cette liste */
void removeListPtrElementSDL2(ListDCElementSDL2* l,ListPtrElementSDL2 *lp);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (code d'affichage) de liste (plan) 
 * d'element
 */
/* renvoi une liste d'element SDL2 vide */
ListElementSDL2* initListElementSDL2();
/* libere la liste passe en parametre */
void freeListElementSDL2(ListElementSDL2*);
/* ajout d'un element SDL2 a la liste passe en parametre */
int addElementSDL2(ElementSDL2*);
/* retire un element SDL2 a la liste passe en parametre */
int removeElementSDL2(ElementSDL2*);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Creation, liberation et information sur un Element SDL2
 */
/* libere l'element SDL2 passe en parametre */
void freeElementSDL2(ElementSDL2 *e);
/* retourne un Element SDL2 de type block */
ElementSDL2* createBlock(float x,float y,float width,float height,int couleur[4],int displayCode,int plan);
/* retourne un Element SDL2 de type texte */
ElementSDL2* createTexte(float x,float y,float width,float height,char * font,char * text,int textColor[4],int displayCode,int plan);
/* retourne un Element SDL2 de type image */
ElementSDL2* createImage(float x,float y,float width,float height,char *image,int displayCode,int plan);
/* retourne un Element SDL2 de type texte+block */
ElementSDL2* createButton(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan);
/* retourne un Element SDL2 de type texte+image */
ElementSDL2* createButtonImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan);
/* retourne un Element SDL2 de type Entry fond block */
ElementSDL2* createEntry(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,int min,int max, int isScripted);
/* retourne un Element SDL2 de type Entry fond image */
ElementSDL2* createEntryImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,int min,int max,int isScripted);
/* retourne 1 si l'element passe en parametre peut etre affiche sur la fenetre passe en parametre, 0 sinon */
int isDisplaied(ElementSDL2*);
/* getter for the Element's coordinates */
int getCoordElementSDL2(ElementSDL2*,float* x,float* y);
/* getter for the Element's angle */
int getAngleElementSDL2(ElementSDL2*,float*);
/* getter for the Element's dimensions */
int getDimensionElementSDL2(ElementSDL2*,int* w,int * h);
/* getter for the Element's rotation point */
int getRotationPointElementSDL2(ElementSDL2*,float *x,float *y);
/* getter pour la vitesse de rotation par update */
int getRotationSpeedElementSDL2(ElementSDL2*,float*);
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
