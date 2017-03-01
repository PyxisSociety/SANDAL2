#ifndef _ELEMENTSDL2_SDL2TK_KLEVH_
#define _ELEMENTSDL2_SDL2TK_KLEVH_

#include "FontSDL2.h"
#include "FenetreSDL2.h"
#include "DisplayCode.h"

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
  /* couleurs du texte et du block (la premiere case vaut -1 si la partie a colorie n'est pas dans l'element) */
  int coulBlock[4];
  /* proportion du texte dans le block (si texte) */
  float textSize;
  /* liste des codes d'affichage */
  ListDisplayCode *codes;
  /* fonction d'action continue */
  void (*action)(FenetreSDL2 *,struct ElementSDL2*);
  /* fonction d'interaction au click */
  void (*onClick)(FenetreSDL2 *,struct ElementSDL2*);
  /* fonction d'interaction avec une touche du clavier */
  void (*keyPress)(FenetreSDL2 *,struct ElementSDL2*,SDL_Keycode c);
  /* fonction d'interaction au relachement d'une touche du clavier */
  void (*keyReleased)(FenetreSDL2 *,struct ElementSDL2*,SDL_Keycode c);
  /* texture de l'image (si image) */
  SDL_Texture *image;
  /* texture et surface du texte (si texte) */
  FontSDL2 *police;
  /* donnees suplementaires si l'element est une Entry */
  EntrySDL2 *entry;
  /* elements entrant en interaction avec cet element */
  struct ListPtrElementSDL2 *interactions;
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
void addElementSDL2(FenetreSDL2*,ElementSDL2*);
/* retire un element SDL2 a la liste passe en parametre */
void removeElementSDL2(FenetreSDL2*,ElementSDL2*);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Creation, liberation et information sur un Element SDL2
 */
/* libere l'element SDL2 passe en parametre */
void freeElementSDL2(ElementSDL2 *e);
/* retourne un Element SDL2 de type block */
ElementSDL2* createBlock(FenetreSDL2 *window,float x,float y,float width,float height,int couleur[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2*,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),void * data);
/* retourne un Element SDL2 de type texte */
ElementSDL2* createTexte(FenetreSDL2 *window,float x,float y,float width,float height,char * font,char * text,int textColor[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2*,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *, ElementSDL2*),void * data);
/* retourne un Element SDL2 de type image */
ElementSDL2* createImage(FenetreSDL2 *window,float x,float y,float width,float height,char *image,int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2*,ElementSDL2*),void * data);
/* retourne un Element SDL2 de type texte+block */
ElementSDL2* createButton(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *, ElementSDL2*),void * data);
/* retourne un Element SDL2 de type texte+image */
ElementSDL2* createButtonImage(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *, ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *, ElementSDL2*),void * data);
/* retourne un Element SDL2 de type Entry fond block */
ElementSDL2* createEntry(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *, ElementSDL2*),int min,int max, int isScripted,void * data);
/* retourne un Element SDL2 de type Entry fond image */
ElementSDL2* createEntryImage(FenetreSDL2 *window,float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,void (*onClick)(FenetreSDL2 *,ElementSDL2*),void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode),void (*action)(FenetreSDL2 *,ElementSDL2*),int min,int max,int isScripted,void * data);
/* retourne 1 si l'element passe en parametre peut etre affiche sur la fenetre passe en parametre, 0 sinon */
int isDisplaied(FenetreSDL2*,ElementSDL2*);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2
 */
/* change la police */
void changeFontElementSDL2(FenetreSDL2 * fen,ElementSDL2 *e,char * font);
/* change le texte */
void changeTextElementSDL2(FenetreSDL2 * fen,ElementSDL2 *e,char * text);
/* change la couleur du block */
void changeColorElementSDL2(ElementSDL2 *e,int color[4]);
/* change l'image */
int changeImageElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,char *image);
/* change les coordonnees*/
void replaceElementSDL2(FenetreSDL2 *window,ElementSDL2 *e,float x,float y);
/*deplace un element*/
void moveElementSDL2(FenetreSDL2 *window,ElementSDL2 *e,float x,float y);
/* change la taille */
void resizeElementSDL2(ElementSDL2 *e,float width,float height);
/* change la taille du texte */
void changeTextSize(ElementSDL2 *e,float textSize);
/* ajoute un code de display (si pas deja present) */
void addDisplayCodeElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,int displayCode,int plan);
/* supprime un code de display */
void removeDisplayCodeElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,int displayCode);
/* change l'option isDisplaied d'un code de display */
void setDisplayElementSDL2(ElementSDL2 *e,int displayCode,int isDisplaied);
/* change le plan d'un element pour un code de display */
void setPlanElementSDL2(FenetreSDL2 *f,ElementSDL2 *e,int DisplayCode,int plan);
/* change l'interaction continue */
void changeActionElementSDL2(ElementSDL2 *e,void (*action)(FenetreSDL2 *,ElementSDL2*));
/* change l'interaction a l'appuie d'une touche du clavier */
void changeKeyPressElementSDL2(ElementSDL2 *e,void (*keyPress)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode c));
/* change l'interaction au relachement d'une touche du clavier */
void changeKeyReleasedElementSDL2(ElementSDL2 *e,void (*keyReleased)(FenetreSDL2 *,ElementSDL2*,SDL_Keycode c));
/* change l'interaction au clique de souris */
void changeOnClickElementSDL2(ElementSDL2 *e,void (*onCLick)(FenetreSDL2 *,ElementSDL2*));
/* ajoute un element dans la liste d'interaction a la fin */
void addElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *add);
/* retire un element dans la liste d'interaction */
void delElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *del);
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
int initIterateur(FenetreSDL2 *l, int displayCode);
/* donne l'element actuel et prepare le prochain */
ElementSDL2* nextElementSDL2(FenetreSDL2 *l);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2 spécifique aux Entry
 */
/* change la taille min et taille max du texte (si une valeur <0, pas de changement sur cette valeur) */
void changeSizeEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e,int size_min,int size_max);
/* met l'option crypté de l'entry à la valeur isScripted */
void setScriptedEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e,int isScripted);
/* ajoute un caractere a une entry */
void addCharEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e,char c);
/* supprime un caractere a une entry */
void removeCharEntrySDL2(FenetreSDL2 *f,ElementSDL2 *e);
/* ------------------------------------------------------- */

#endif
