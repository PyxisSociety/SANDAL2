#ifndef _SPRITE_SANDAL2_KLEVH_
#define _SPRITE_SANDAL2_KLEVH_

#include <stdlib.h>

/**
 * @file Sprite.h
 * @brief Sprite manager for SANDAL2
 */

/**
 * @struct Sprite
 * @brief informations about a step of an animation
 */
typedef struct Sprite{
  struct Sprite * next;
  ///< next step of the animation
  struct Sprite * prev;
  ///< previous step of the animation
  int coords[4];
  ///< [0] and [1] for the coordinates of the top left corner and [2] and [3] respectively for the width and the height
  unsigned lifespan;
  ///< number of time minus one the Sprite should be displaied before going to the next
}Sprite;

/**
 * @struct ListSprite
 * @brief all steps of an animation
 */
typedef struct ListSprite{
  struct Sprite * first;
  ///< first step of the animation
  struct Sprite * current;
  ///< current step of the animation
  unsigned size;
  ///< number of steps in the animation
  int sens;
  ///< tells whether to go forward (1), backward (-1) or not to move (0)
  unsigned wasChanged;
  ///< tells how many time the current sprite was displaied
}ListSprite;

/* -----------------------------------------------------
 * ListSprite
 */
/**
 * @brief create an empty list of sprite
 * @return the empty list of sprite
 */
ListSprite * initListSprite();
/**
 * @brief free the memory of a list of sprite
 * @param l : list to be freed
 */
void freeListSprite(ListSprite * l);
/**
 * @brief add a Sprite to the list
 * @param l : list of sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the sprite was correctly added, 1 if not
 */
int addSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan);
/**
 * @brief remove a Sprite to the list
 * @param l : list of sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @return 0 if the sprite was correctly removed, 1 if not
 */
int removeSprite(ListSprite * l,int x,int y,int width,int height);
/**
 * @brief set the lifespan of a sprite
 * @param l : list of sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : new number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the lifespan could be set, 1 if not
 */
int setLifeSpanSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan);
/* ----------------------------------------------------- */

#endif
