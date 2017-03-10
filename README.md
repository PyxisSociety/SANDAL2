# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make objects managment and
graphic display easier.

## Structures

### I. HitBox.h

  <u> 1. LineSDL2 : </u>
    A clickable zone delimited by a line (only one side of the line is clickable).

  <u> 2. CircleSDL2 : </u>
    An elliptic shaped clickable zone.

  <u> 3. HitBox : </u>
    A clickable zone made of a collection of lines and ellipses.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  <u> 4. ListHitBox : </u>
    A clickable zone defined by a collection of clickable HitBox and blocking HitBox.
    
### II. DisplayCode.h

  <u> 1. DisplayCode : </u>
    A package of information about a display code. It contains the display code, the plan and a flag to tell whether or not
    the object should be displaied.

  <u> 2. ListDisplayCode : </u>
    A list of display codes.

### III. FontSDL2.h

  <u> 1. FontSDL2 : </u>
    A package of information about a text. It contains its font, its text, its color and its SDL2 texture.

### IV. FenetreSDL2.h

  <u> 1. FenetreSDL2 : </u>
    Representation of a window. It contains all informations (such as the dimension, the display code, ...) about a window.

  <u> 2. ListFenetreSDL2 : </u>
    A list of FenetreSDL2.

### V. ElementSDL2.h

  <u> 1. ElementSDL2 : </u>
    A package of information about objects. It contains its coordinates (top left corner), its size, its color and so on.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  <u> 2. PtrElementSDL2 : </u>
    A structure mean to store an ElementSDL2's pointer

  <u> 3. ListPtrElementSDL2 : </u>
    A list of PtrElementSDL2. Either used as a list of elements with a common plan or so that an element can change another.

  <u> 4. ListDCElementSDL2 : </u>
    A list of lists of elements with a common plan, every lists in this list has a common display code.

  <u> 5. ListElementSDL2 : </u>
    A list of ListDCElementSDL2.

## Functionnality

### I. To begin with

### II. Element manipulations