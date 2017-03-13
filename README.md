# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make objects managment and
graphic display easier.

## Structures

### I. HitBox.h

  1. LineSDL2 : 
    A clickable zone delimited by a line (only one side of the line is clickable).

  2. CircleSDL2 :
    An elliptic shaped clickable zone.

  3. HitBox :
    A clickable zone made of a collection of lines and ellipses.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  4. ListHitBox : 
    A clickable zone defined by a collection of clickable HitBox and blocking HitBox.
    
### II. DisplayCode.h

  1. DisplayCode : 
    A package of information about a display code. It contains the display code, the plan and a flag to tell whether or not
    the object should be displaied.

  2. ListDisplayCode : 
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

   To begin with, you'll have to initialise SDL2 with initAllSDL2 for image, ttf and SDL2, or one of the
specific function in SANDAL2.h. Do not forget to close the SDL2 with either closeAllSDL2 or one or more functions
in SANDAL2.h.<br/><br/>
   Then you'll want to create a window (or more). For that, use the initFenetreSDL2 function. Then you can had
elements in it with all the create functions in ElementSDL2.h like createBlock or createEntryImage for example.
We will see later what you can do with all those elements more in details.<br/><br/>
   For the event management, you can bind functions to elements which will be called in the functions we will speak
about right now when specific conditions are met. You will not have to look when you touch an elements or what
function to call when a key is pressed. For that, use the functions like clickFenetreSDL2 or keyPressedFenetreSDL2.
When you want to update all your elements and the current window, use updateFenetreSDL2. For displaying, use displayFenetreSDL2. If you want to do that for every single window, use the 'all' version like displayAllFenetreSDL2 or unclickAllFenetreSDL2. Then again, do not forget to close your windows with closeFenetreSDL2 or closeAllFenetreSDL2.
Those functions are in SANDAL2.h.<br/><br/>
   If you want to iterate through all the windows, you can use initIteratorFenetreSDL2 and nextFenetreSDL2. You can also get and set informations about the window with all the functions in FenetreSDL2.h.<br/>

### II. Element manipulations