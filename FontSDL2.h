#ifndef _FONTSDL2_SANDAL2_KLEVH_
#define _FONTSDL2_SANDAL2_KLEVH_

#include "WindowSDL2.h"

/**
 * @file FontSDL2.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Information about TTF objects
 */

#define SANDAL2_SOLID 0
#define SANDAL2_SHADED 1
#define SANDAL2_BLENDED 2

/**
 * @brief List of the windows
 *   WARNING : do not touch it ... trust me
 */
extern ListWindowSDL2 * _windows_SANDAL2;

/**
 * @struct FontSDL2
 * @brief Informations about SDL2 font
 */
typedef struct{
  TTF_Font *font;
  /**< SDL font object*/
  int quality;
  /**< quality of the texture : SANDAL2_SOLID, SANDAL2_SHADED or SANDAL2_BLENDED (same meaning as for SDL2 functions TTF_RenderText_Solid, Shaded or Blended) */
  char *text;
  /**< text*/
  SDL_Color color;
  /**< color of the text*/
  SDL_Texture *texture;
  /**< SDL texture*/
}FontSDL2;

/* -------------------------------------------------------
 * Police de caractere SDL2
 */
/**
 * @brief generate a FontSDL2 using the path to the font, the text and the color of the text (use the window's background font as background color for Shaded quality)
 * @param fontPath : path of the font
 * @param texte : text of the object
 * @param couleur : color of the text
 * @param quality : quality of the texture (SANDAL2_SOLID, SANDAL2_SHADED or SANDAL2_BLENDED)
 * @return NULL if the object was not initialised, if not, the object
 */
FontSDL2* createFontSDL2(char *fontPath,char *texte,int couleur[4], int quality);
/**
 * @brief free the memory of a FontSDL2
 * @param font : the FontSDL2 to be freed
 */
void freeFontSDL2(FontSDL2 *font);
/**
 * @brief actualize the text to cript it or uncript it
 * @param font : the font to be actualize
 * @param isScripted : 0 if the text should be uncripted, 1 for cripted
 * @return 1 if there was an error, 0 if not
 */
int actualizeTextFontSDL2(FontSDL2 *font,int isScripted);
/**
 * @brief actualize the text of a FontSDL2
 * @param font : the font to be actualize
 * @param text : the new text
 * @return 1 if there was an error, 0 if not
 */
int changeTextFontSDL2(FontSDL2 *font,char *text);
/**
 * @brief actualize the color of the FontSDL2
 * @param font : the font to be actualize
 * @param color : new color
 * @return 1 if there was an error, 0 if not
 */
int changeColorFontSDL2(FontSDL2 *font,int color[4]);
/* ------------------------------------------------------- */

#endif
