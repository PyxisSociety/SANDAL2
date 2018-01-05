#ifndef FONT_SANDAL2_KLEVH
#define FONT_SANDAL2_KLEVH

#ifdef __cplusplus
extern "C" {
#endif
    
#include "Window.h"

/**
 * @file Font.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief Information about TTF objects
 */

#define SANDAL2_SOLID 0
/**< Type of text's texture rendering (see SDL2's TTF_RendreText_Solid)*/
#define SANDAL2_SHADED 1
/**< Type of text's texture rendering (see SDL2's TTF_RendreText_Shaded)*/
#define SANDAL2_BLENDED 2
/**< Type of text's texture rendering (see SDL2's TTF_RendreText_Blended)*/

#define SANDAL2_BOLD TTF_STYLE_BOLD
/**< Text font style : bold*/
#define SANDAL2_ITALIC TTF_STYLE_ITALIC
/**< Text font style : italic*/
#define SANDAL2_UNDERLINE TTF_STYLE_UNDERLINE
/**< Text font style : underline*/
#define SANDAL2_STRIKETHROUGH TTF_STYLE_STRIKETHROUGH
/**< Text font style : strikethrough*/
#define SANDAL2_NORMAL TTF_STYLE_NORMAL
/**< Text font style : normal*/

/**
 * @brief List of the windows
 *   WARNING : do not touch it ... trust me
 */
extern ListWindow * _windows_SANDAL2;

/**
 * @struct Font
 * @brief Informations about font
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
}Font;

/* -------------------------------------------------------
 * Text 
 */
/**
 * @brief generate a Font using the path to the font, the text and the color of the text (use the window's background font as background color for Shaded quality)
 * @param fontPath : path of the font
 * @param texte : text of the object
 * @param couleur : color of the text
 * @param quality : quality of the texture (SANDAL2_SOLID, SANDAL2_SHADED or SANDAL2_BLENDED)
 * @return NULL if the object was not initialised, if not, the object
 */
Font* createFont(const char *fontPath,const char * texte,int couleur[4], int quality);
/**
 * @brief free the memory of a Font
 * @param font : the Font to be freed
 */
void freeFont(Font *font);
/**
 * @brief actualize the text to cript it or uncript it
 * @param font : the font to be actualize
 * @param isScripted : 0 if the text should be uncripted, 1 for cripted
 * @return 1 if there was an error, 0 if not
 */
int actualizeTextFont(Font *font,int isScripted);
/**
 * @brief actualize the text of a Font
 * @param font : the font to be actualize
 * @param text : the new text
 * @return 1 if there was an error, 0 if not
 */
int setTextFont(Font *font,const char *text);
/**
 * @brief actualize the color of the Font
 * @param font : the font to be actualize
 * @param color : new color
 * @return 1 if there was an error, 0 if not
 */
int setColorFont(Font *font,int color[4]);
/**
 * @brief set the text's font style
 * @param font : the text to be modified
 * @param style : the style to apply
 * @return 1 if there was an error, 0 if not
 */
int setStyleFont(Font *font,int style);
/**
 * @breif get the text's font style
 * @param font : the text to get the font style
 * @param style : where to store the style
 * @return 1 if there was an error, 0 if not
 */
int getStyleFont(Font *font,int * style);
/* ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif
    
#endif
