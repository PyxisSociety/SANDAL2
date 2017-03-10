# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make objects managment and
graphic display easier.

## Structures

### I. HitBox.h

  1. <u>LineSDL2 : </u>
    A clickable zone delimited by a line (only one side of the line is clickable).

  2. <u>CircleSDL2 : </u>
    An elliptic shaped clickable zone.

  3. <u>HitBox : </u>
    A clickable zone made of a collection of lines and ellipses.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  4. <u>ListHitBox : </u>
    A clickable zone defined by a collection of clickable HitBox and blocking HitBox.
    
### II. DisplayCode.h

  1. <u>DisplayCode : </u>
    A package of information about a display code. It contains the display code, the plan and a flag to tell whether or not
    the object should be displaied.

  2. <u>ListDisplayCode : </u>
    A list of display codes.

### III. FontSDL2.h

  1. FontSDL2 :
    A package of information about a text. It contains its font, its text, its color and its SDL2 texture.

### IV. FenetreSDL2.h

  1. FenetreSDL2 :
    Representation of a window. It contains all informations (such as the dimension, the display code, ...) about a window.

  2. ListFenetreSDL2 :
    A list of FenetreSDL2.

### V. ElementSDL2.h

  1. ElementSDL2 :
    A package of information about objects. It contains its coordinates (top left corner), its size, its color and so on.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  2. PtrElementSDL2 :
    A structure mean to store an ElementSDL2's pointer

  3. ListPtrElementSDL2 :
    A list of PtrElementSDL2. Either used as a list of elements with a common plan or so that an element can change another.

  4. ListDCElementSDL2 :
    A list of lists of elements with a common plan, every lists in this list has a common display code.

  5. ListElementSDL2 :
    A list of ListDCElementSDL2.

## Functionnality

### I. To begin with

### II. Element manipulations