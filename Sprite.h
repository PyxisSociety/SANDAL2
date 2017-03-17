#ifndef _SPRITE_SANDAL2_KLEVH_
#define _SPRITE_SANDAL2_KLEVH_

#include <stdlib.h>

/**
 * @file Sprite.h
 * @author Baptiste PRUNIER (KLEVH)
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
  Sprite * first;
  ///< first step of the animation
  Sprite * current;
  ///< current step of the animation
  unsigned size;
  ///< number of steps in the animation
  int sens;
  ///< tells whether to go forward (1), backward (-1) or not to move (0)
  unsigned wasChanged;
  ///< tells how many time the current sprite was displaied
  int code;
  ///< identifier of the animation
  struct ListSprite * next;
  ///< next animation
  struct ListSprite * prev;
  ///< previous animation
}ListSprite;

/**
 * @struct ListAnimation
 * @brief a list of animations
 */
typedef struct{
  ListSprite * first;
  ///< first animation
  ListSprite * current;
  ///< current animation
  unsigned size;
  ///< number of animations
}ListAnimation;

/* -----------------------------------------------------
 * ListSprite
 */
/**
 * @brief create an empty list of sprite
 * @return the empty list of sprite
 */
ListSprite * initListSprite(int code);
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

/* -----------------------------------------------------
 * ListAnimation
 */
/**
 * @brief create an empty list of animation
 * @return the empty list of animation
 */
ListAnimation * initListAnimation();
/**
 * @brief free the memory of a list of animation
 * @param l : list to be freed
 */
void freeListAnimation(ListAnimation *l);
/**
 * @brief add an empty animation to the list
 * @param l : list of animation
 * @param code : code of the new animation
 * @return 0 if the animation could be added, 1 if not
 */
int createAnimation(ListAnimation *l,int code);
/**
 * @brief remove an empty animation from the list
 * @param l : list of animation
 * @param code : code of the animation to be removed
 * @return 0 if the animation could be removed, 1 if not
 */
int removeAnimation(ListAnimation *l,int code);
/**
 * @brief add a Sprite to an animation
 * @param l : list of animations
 * @param code : code of the animation to add the sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the sprite was correctly added, 1 if not
 */
int addSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height,unsigned lifespan);
/**
 * @brief remove a Sprite to an animation
 * @param l : list of animations
 * @param code : code of the animation to remove the sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @return 0 if the sprite was correctly removed, 1 if not
 */
int removeSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height);
/**
 * @brief set the lifespan of a sprite
 * @param l : list of animations
 * @param code : code of the animation to set the sprite
 * @param x : abscissa coordinate of the top left corner of the sprite in its image
 * @param y : ordinate coordinate of the top left corner of the sprite in its image
 * @param width : width of the sprite in its image
 * @param height : height of the sprite in its image
 * @param lifespan : new number of time the sprite should be displaied before going to the next sprite
 * @return 0 if the lifespan could be set, 1 if not
 */
int setLifeSpanSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height,unsigned lifespan);
/**
 * @brief set the current animation of a list of animations
 * @param l : list of animations
 * @param code : code of the animation to be set as current
 * @return 0 if the animation could be set as current, 1 if not
 */
int setAnimation(ListAnimation *l,int code);
/* ----------------------------------------------------- */
#endif
