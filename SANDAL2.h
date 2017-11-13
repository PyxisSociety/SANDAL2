#ifndef _MAIN_SANDAL2_KLEVH_
#define _MAIN_SANDAL2_KLEVH_

#include "ElementSDL2.h"

/**
 * @file SANDAL2.h
 * @author Baptiste PRUNIER (KLEVH)
 * @version 1.1.0
 * @brief File to include which includes everything else.
 *  Compilation flags to use :
 *    -lSDL2 -lSDL2_ttf -lSDL2_image -lm
 */

/**
 * @brief list of windows
 *   WARNING : do not touch this variable, never ... trust me
 */
extern ListWindowSDL2 * _windows_SANDAL2;

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
void closeAllSDL2(void);
/**
 * @brief Initialisation of SDL2 alone
 * @return 0 if success, 1 if failed
 */
int initSDL2(void);
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
int initTexte(void);
/**
 * @brief Close SDL2
 */
void closeSDL2(void);
/**
 * @brief Close images
 */
void closeImage(void);
/**
 * @brief Close font
 */
void closeTexte(void);
/* ------------------------------------------------------- */

/* ------------------------------------------------------- 
 * Creation, modification et suppression des fenetres
 */
/**
 * @brief Add a window to the list of windows
 * @param width : width of the window
 * @param height : height of the window
 * @param title : title of the window
 * @param SDLFlags : flags of SDL2
 * @param background : color of the background
 * @param displayCode : display code of the window
 * @return 1 if it failed, 0 if not
 */
int initWindowSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode);
/**
 * @brief close the current windows and go to the next, do not use this one in elements' or windows' binded functions, use shouldCloseWindowSDL2() instead
 * @return 1 if it failed, 0 if not
 */
int closeWindowSDL2(void);
/**
 * @brief tells that the current window should be closed, do not use this one in functions that are not binded to windows or elements, use closeWindowSDL2() instead
 * @return 1 if it failed, 0 if not
 */
int shouldCloseWindowSDL2(void);
/**
 * @brief close all windows
 * @return 1 if it failed, 0 if not
 */
int closeAllWindowSDL2(void);
/**
 * @brief Toggle the full screen mode of the current window
 * @return 0 if succeeded, 1 if not
 */
int toggleFullScreenWindowSDL2(void);
/**
 * @brief Tells whether or not the window is in full screen mode
 * @return 1 if the current window is in full screen mode, 0 if not or if there is no current window
 */
int isFullScreenWindowSDL2(void);
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Gestion des Fenetres SDL2
 */
/**
 * @brief update all the elements of the current window
 * @return 1 if it failed, 0 if not
 */
int updateWindowSDL2(void);
/**
 * @brief actualise the display of the current window 
 * @return 1 if it failed, 0 if not
 */
int displayWindowSDL2(void);
/**
 * @brief activation of click events on the current window
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 * @return 1 if it failed, 0 if not
 */
int clickWindowSDL2(int x,int y);
/**
 * @brief activation of unclick events on the current window
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 * @return 1 if it failed, 0 if not
 */
int unclickWindowSDL2(int x,int y);
/**
 * @brief activation of the key pressed events on the current window
 * @param c : key which was pressed
 * @return 1 if it failed, 0 if not
 */
int keyPressedWindowSDL2(char c);
/**
 * @brief activation of the key released events on the current window
 * @param c : key which was released
 * @return 1 if it failed, 0 if not
 */
int keyReleasedWindowSDL2(char c);
/**
 * @brief update all the elements of all the windows
 * @return 1 if it failed, 0 if not
 */
unsigned long updateAllWindowSDL2(void);
/**
 * @brief actualise the display of all the windows 
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long displayAllWindowSDL2(void);
/**
 * @brief activation of click events on all the windows
 * @param x : abscissa coordinate of the mouse during the click
 * @param y : ordinate coordinate of the mouse during the click
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long clickAllWindowSDL2(int x,int y);
/**
 * @brief activation of unclick events on all the windows
 * @param x : abscissa coordinate of the mouse during the unclick
 * @param y : ordinate coordinate of the mouse during the unclick
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long unclickAllWindowSDL2(int x,int y);
/**
 * @brief activation of the key pressed events on all windows
 * @param c : key which was pressed
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long keyPressedAllWindowSDL2(char c);
/**
 * @brief activation of the key released events on all windows
 * @param c : key which was released
 * @return 0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one
 */
unsigned long keyReleasedAllWindowSDL2(char c);
/* ------------------------------------------------------- */

/* ------------------------------------------------------- 
 * Gestion d'evenement
 */
/**
 * @brief Get the event (if there is one) and apply the corresponding functions
 * @param error: where to store the error flag (0 if it succeeded, a binary code telling which window failed (example : 100101 tells that the second and the fifth window failed, the first bit on the rigth only tells that there was an error), if you have more window than bits for int, you will not be able to tell which of the window failed in those which have a bigger number than the number of bit minus one)
 * @return 1 if the user asked to close the window, 0 if not
 */
int PollEventSDL2(unsigned long * error);
/* ------------------------------------------------------- */

#endif
