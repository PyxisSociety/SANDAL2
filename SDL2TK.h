#ifndef _MAIN_SDL2TK_KLEVH_
#define _MAIN_SDL2TK_KLEVH_

#include "ElementSDL2.h"
#include "FenetreSDL2.h"

extern ListFenetreSDL2 * _windows_SDL2TK;

/* -------------------------------------------------------
 * Initialisation et fermeture des outils SDL2
 */
/* initialise la SDL2 (retourne 1 si erreur d'init SDL, 2 si erreur d'init image, 3 si erreur d'init TTF, 0 sinon) a partir des formats d'images passe en parametre */
int initAllSDL2(int imageFlags);
/* ferme la SDL2, image et texte */
void closeAllSDL2();
/* initialisation de la SDL2 (seule)*/
int initSDL2();
/* initialisation du texte SDL2 */
int initImage(int imageFlags);
/* initialisation de l'image SDL2 */
int initTexte();
/* ferme ma SDL2 seule */
void closeSDL2();
/* ferme image */
void closeImage();
/* ferme texte */
void closeTexte();
/* ------------------------------------------------------- */

/* -------------------------------------------------------
 * Fenetre SDL2
 */
/* libere la fenetre */
void freeFenetreSDL2(FenetreSDL2 *fen);
/* initialise la fenetre */
void initFenetreSDL2(int width,int height,char *title,int SDLFlags,int background[4],int displayCode);
/* update les elements de la fenetre */
void updateFenetreSDL2();
/* actualise l'affichage de la fenetre */
void displayFenetreSDL2();
/* activation des evenements de clique de souris */
void clickFenetreSDL2(int x,int y);
/* activation des evenements au relachement de clique de souris */
void unclickFenetreSDL2(int x,int y);
/* activation des evenements d'appuie sur une touche du clavier */
void keyPressedFenetreSDL2(char c);
/* activation des evenements au relachement d'une touche du clavier */
void keyReleasedFenetreSDL2(char c);
/* update les elements des fenetres */
void updateAllFenetreSDL2();
/* actualise l'affichage des fenetres passe en parametre */
void displayAllFenetreSDL2();
/* activation des evenements de clique de souris */
void clickAllFenetreSDL2(int x,int y);
/* activation des evenements au relachement de clique de souris */
void unclickAllFenetreSDL2(int x,int y);
/* activation des evenements d'appuie sur une touche du clavier */
void keyPressedAllFenetreSDL2(char c);
/* activation des evenements au relachement d'une touche du clavier */
void keyReleasedAllFenetreSDL2(char c);
/* ferme la fenetre courante et passe a la suivante */
void closeFenetreSDL2();
/* ferme toutes les fenetres */
void closeAllFenetreSDL2();
/* ------------------------------------------------------- */

#endif
