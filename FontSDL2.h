#ifndef _FONTSDL2_SDL2TK_KLEVH_
#define _FONTSDL2_SDL2TK_KLEVH_

#include "FenetreSDL2.h"

extern ListFenetreSDL2 * _windows_SDL2TK;
/* police de caractere SDL2 */
typedef struct{
  TTF_Font *font;
  char *text;
  SDL_Color color;
  SDL_Texture *texture;
}FontSDL2;

/* -------------------------------------------------------
 * Police de caractere SDL2
 */
/* creer et renvoi l'objet FontSDL2 genere a partir de la police dont l'adresse est passe en parametre (renvoi NULL en cas d'erreur)*/
FontSDL2* createFontSDL2(char *fontPath,char *texte,int couleur[4]);
/* libere la police passe en parametre */
void freeFontSDL2(FontSDL2 *font);
/* actualise le texte */
void actualizeTextFontSDL2(FontSDL2 *font,int isScripted);
/* change le texte */
void changeTextFontSDL2(FontSDL2 *font,char *text);
/* change la couleur du texte */
void changeColorFontSDL2(FontSDL2 *font,int color[4]);
/* ------------------------------------------------------- */

#endif
