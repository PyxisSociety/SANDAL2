#ifndef _FONTSDL2_SDL2TK_KLEVH_
#define _FONTSDL2_SDL2TK_KLEVH_

#include "WindowSDL2.h"

/**
 * @file FontSDL2.h
 * @brief Information about TTF objects
 */

/**
 * @brief List of the windows
 *   WARNING : do not touch it ... trust me
 */
extern ListWindowSDL2 * _windows_SDL2TK;

/**
 * @struct FontSDL2
 * @brief Informations about SDL2 font
 */
typedef struct{
  TTF_Font *font;
  ///< SDL font object
  char *text;
  ///< text
  SDL_Color color;
  ///< color of the text
  SDL_Texture *texture;
  ///< SDL texture
}FontSDL2;

/* -------------------------------------------------------
 * Police de caractere SDL2
 */
/**
 * @brief generate a FontSDL2 using the path to the font, the text and the color of the text
 * @param fontPath : path of the font
 * @param texte : text of the object
 * @param couleur : color of the text
 * @return NULL if the object was not initialised, if not, the object
 */
FontSDL2* createFontSDL2(char *fontPath,char *texte,int couleur[4]);
/**
 * @brief free the memory of a FontSDL2
 * @param font : the FontSDL2 to be freed
 */
void freeFontSDL2(FontSDL2 *font);
/**
 * @brief actualize the text to cript it or uncript it
 * @param font : the font to be actualize
 * @param isScripted : 0 if the text should be uncripted, 1 for cripted
 */
void actualizeTextFontSDL2(FontSDL2 *font,int isScripted);
/**
 * @brief actualize the text of a FontSDL2
 * @param font : the font to be actualize
 * @param text : the new text
 */
void changeTextFontSDL2(FontSDL2 *font,char *text);
/**
 * @brief actualize the color of the FontSDL2
 * @param font : the font to be actualize
 * @param color : new color
 */
void changeColorFontSDL2(FontSDL2 *font,int color[4]);
/* ------------------------------------------------------- */

#endif
