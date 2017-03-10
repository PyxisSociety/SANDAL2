# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make objects managment and
graphic display easier.

## Structures

1. HitBox.h

  * LineSDL2 :
    A clickable zone delimited by a line (only one side of the line is clickable).

  * CircleSDL2 :
    An elliptic shaped clickable zone.

  * HitBox :
    A clickable zone made of a collection of lines and ellipses.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  * ListHitBox :
    A clickable zone defined by a collection of clickable HitBox and blocking HitBox.
    
1. DisplayCode.h

  * DisplayCode :
    A package of information about a display code. It contains the display code, the plan and a flag to tell whether or not
    the object should be displaied.

  * ListDisplayCode :
    A list of display codes.

1. FontSDL2.h

  * FontSDL2 :
    A package of information about a text. It contains its font, its text, its color and its SDL2 texture.

1. FenetreSDL2.h

  * FenetreSDL2 :
    Representation of a window. It contains all informations (such as the dimension, the display code, ...) about a window.

  * ListFenetreSDL2 :
    A list of FenetreSDL2.

1. ElementSDL2.h

  * ElementSDL2 :
    A package of information about objects. It contains its coordinates (top left corner), its size, its color and so on.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  * PtrElementSDL2 :
    A structure mean to store an ElementSDL2's pointer

  * ListPtrElementSDL2 :
    A list of PtrElementSDL2. Either used as a list of elements with a common plan or so that an element can change another.

  * ListDCElementSDL2 :
    A list of lists of elements with a common plan, every lists in this list has a common display code.

  * ListElementSDL2 :
    A list of ListDCElementSDL2.

## Functionnality

1. To begin with

1. Element manipulations