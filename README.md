# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make objects managment and
graphic display easier.

## About the author

   I am a French guy and I am studying computer science engineering. I made this wrapper because I found
boresome to have to create a display function for each menu's page, but I ended up going a little more further
in it. I hope you will enjoy using it, if you have any comment or advice, do not feel shy and tell me !<br>
I will really appreciate it.

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
When you want to update all your elements and the current window, use updateFenetreSDL2. For displaying, use displayFenetreSDL2.
If you want to do that for every single window, use the 'all' version like displayAllFenetreSDL2 or unclickAllFenetreSDL2.
Then again, do not forget to close your windows with closeFenetreSDL2 or closeAllFenetreSDL2.
Those functions are in SANDAL2.h.<br/><br/>
   If you want to iterate through all the windows, you can use initIteratorFenetreSDL2 and nextFenetreSDL2. You can also get and set informations about the window with all the functions in FenetreSDL2.h.<br/>

### II. Element manipulations

   An element is kind of an object with lots of display informations. It can have an image, a text or a color (for rectangles).
As said higher, they can be created with functions like createBlock or createButton for example. Once created, you can
modifie all informations about them. They have the following information :
* coordinates in the window ;
* dimensions ;
* a collection of display code, each display code has a plan ;
* a collection of clickable zone ;
* functions bind on it to be called for certain event (they will be listed later) ;
* a collection of animations ;
* a collection of elements which can be modified by the parent element ;
* a rotation speed ;
* a rotation (the current angle of the element) ;
* a package of data (void *);
* a package of informations if the element is a prompt.
<br/><br/>
   The functions that can be bind to the element are the following ones :
* action, to be called every update ;
* keyPress, to be called when a key is pressed ;
* keyReleased, to be called when a key is released ;
* click, to be called if the element is clicked (be careful, there have to be a clickable zone) ;
* unClick, to be called when the user release the click of the mouse on the clickable zone of the element ;
* unSelect, to be called when the user click elsewhere or unclick elsewhere ;
* endSprite, to be called when an animation reach its end, before starting of again.
<br/><br/>
   You can add elements to a current element so that the parent element will be able to modifie them in one of
the function you binded to it. In those function, you can modifie the element itself or other, even removing them.
Each animation of an element has a code so that you can switch from one to another. When you want to add a step
to the animation, you will have to define its coordinates in the image of the element (which should be a sprite sheet
or something the like). Each sprite has a lifespan, which correspond to the number of update call before going to the
next. That is if the animation is on 'automatic' mode. The mode can be set with the function setWayAnimationElementSDL2.
If there are no sprite, the entire image will be displaied.
<br/><br/>