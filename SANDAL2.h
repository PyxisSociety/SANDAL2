#ifndef _MAIN_SDL2TK_KLEVH_
#define _MAIN_SDL2TK_KLEVH_

#include "ElementSDL2.h"

/**
 * @file SANDAL2.h
 * @author Baptiste PRUNIER (KLEVH)
 * @brief File to include which includes everything else.
 *  Compilation flags to use :
 *    -lSDL2 -lSDL2_ttf -lSDL2_image -lm
 */

/**
 * @brief list of windows
 *   WARNING : do not touch this variable, never ... trust me
 */
extern ListWindowSDL2 * _windows_SDL2TK;

/* -------------------------------------------------------
 * Initialisation et fermeture des outils SDL2
 */
/**
 * @brief Initialisation of SDL2, its image and fonts (return 1 if SDL2 initialisation error, 2 if image initialisation error, 3 if font initialisation error, 0 if not) using SDL2's image flags
 * @param imageFlags : SDL2's image flags
 * @return error code
 */
int initAllSDL2(int imageFlags);
/**
 * @brief Close SDL2, images and font
 */
void closeAllSDL2();
/**
 * @brief Initialisation of SDL2 alone
 * @return 0 if success, 1 if failed
 */
int initSDL2();
/**
 * @brief Initialisation of images alone
 * @param imageFlags : SDL2's image flags
 * @return 0 if success, 1 if failed
 */
int initImage(int imageFlags);
/**
 * @brief Initialisation of text alone
 * @return 0 if success, 1 if failed
 */
int initTexte();
/**
 * @brief Close SDL2
 */
void closeSDL2();
/**
 * @brief Close images
 */
void closeImage();
/**
 * @brief Close font
 */
void closeTexte();
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/**
 * @brief Free a window's memory
 */
void freeWindowSDL2(WindowSDL2 *fen);
/**
 * @brief Add a window to the list of windows
 * @param width : width of the window
 * @param height : height of the window
 * @param title : title of the window
 * @param SDLFlags : flags of SDL2
 * @param background : color of the background
 * @param displayCode : display code of the window
 */
void initWindowSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode);
/**
 * @brief update all the elements of the current window
 */
void updateWindowSDL2();
/**
 * @brief actualise the display of the current window 
 */
void displayWindowSDL2();
/**
 * @brief activation of click events on the current window
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 */
void clickWindowSDL2(int x,int y);
/**
 * @brief activation of unclick events on the current window
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 */
void unclickWindowSDL2(int x,int y);
/**
 * @brief activation of the key pressed events on the current window
 * @param c : key which was pressed
 */
void keyPressedWindowSDL2(char c);
/**
 * @brief activation of the key released events on the current window
 * @param c : key which was released
 */
void keyReleasedWindowSDL2(char c);
/**
 * @brief update all the elements of all the windows
 */
void updateAllWindowSDL2();
/**
 * @brief actualise the display of all the windows 
 */
void displayAllWindowSDL2();
/**
 * @brief activation of click events on all the windows
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 */
void clickAllWindowSDL2(int x,int y);
/**
 * @brief activation of unclick events on all the windows
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 */
void unclickAllWindowSDL2(int x,int y);
/**
 * @brief activation of the key pressed events on all windows
 * @param c : key which was pressed
 */
void keyPressedAllWindowSDL2(char c);
/**
 * @brief activation of the key released events on all windows
 * @param c : key which was released
 */
void keyReleasedAllWindowSDL2(char c);
/**
 * @brief close the current windows and go to the next
 */
void closeWindowSDL2();
/**
 * @brief close all windows
 */
void closeAllWindowSDL2();
/* ------------------------------------------------------- */

#endif
