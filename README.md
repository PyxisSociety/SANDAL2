# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make object managment and
graphic display easier.  

To generate the Doxygen documentation, use the command:  
`doxygen Doxyfile`  
<br/>
To see this read me file with a better display, you can go to [this project's
website](https://klevh.github.io/SANDAL2/).

## About the author

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I am a French student, studying computer science engineering at ISIMA, France. 
I made this wrapper because I found boresome to have to create a display function for each menu's page, but I ended 
up going a little further in it. I hope you will enjoy using it, if you have any comment or advice, do not feel shy 
and tell me ! I will really appreciate it.

## Useful links

From this "read-me", you can either go to :
* the [read-me](Docs/README.md) with more informations about the project in itself ;
* or a [small tutorial](Docs/Tutorial.md) explaining how to use it.

## To Install/Uninstall On Linux

Regardless the way you install SANDAL2, you'll need to include SANDAL2.h and use `-lm -lSDL2 -lSDL2_ttf -lSDL2_image` compilation flags.

### I. Using the Debian Package

Installing :
```
wget https://github.com/Klevh/SANDAL2/raw/master/downloadable/sandal2.deb
dpkg -i sandal2.deb
```
Then you'll need to add `-lSANDAL2` as a compilation flag.

Uninstalling :
```
dpkg --purge sandal2
```

### II. Using the source code

```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
```
Then, you need to compile all .c files.

## Functionnality

### I. To begin with

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To begin with, you'll have to initialise SDL2 with initAllSDL2 for image, ttf and SDL2, or one of the
specific function in SANDAL2.h. Do not forget to close the SDL2 with either closeAllSDL2 or one or more functions
in SANDAL2.h (use the closing version for every opening you made).  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Then you'll want to create a window (or more). For that, use the initWindowSDL2 function. Then you can add
elements in it with all the create functions in ElementSDL2.h like createBlock or createEntryImage for example.
We will see later what you can do with all those elements more in details.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For the event management, you can bind functions to elements which will be called in the functions we will speak
about right now when specific conditions are met. You will not have to look when you touch an element or what
function to call when a key is pressed as long as you binded the right function and defined its clickable zone. For that, use functions like clickWindowSDL2 or keyPressedWindowSDL2.
When you want to update all your elements and the current window, use updateWindowSDL2. For displaying, use displayWindowSDL2.
If you want to do that for every single window, use the 'all' version like displayAllWindowSDL2 or unclickAllWindowSDL2.
Then again, do not forget to close your windows with closeWindowSDL2 or closeAllWindowSDL2.
Those functions are in SANDAL2.h.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;If you want to iterate through all the windows, you can use initIteratorWindowSDL2 and nextWindowSDL2. You can 
also get and set informations about the window with all the functions in WindowSDL2.h. There they are also functions to
 get informations about the current window such as its ID, its position and its size.  

### II. Element manipulations

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;An element is kind of an object with lots of display informations. It can have an image, a text or/and a color (for rectangles).
As said higher, they can be created with functions like createBlock or createButton for example. Once created, you can
modifie all informations about them. They have the following informations:
* coordinates in the window;
* dimensions;
* a collection of display code, each display code has a plan;
* a collection of clickable zone;
* functions bind on it to be called for certain event (they will be listed later);
* a collection of animations;
* a collection of elements which can be modified by the parent's element;
* a rotation speed;
* a rotation (the current angle of the element);
* a package of data (void *);
* a package of informations if the element is a prompt.
<br/><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The functions that can be bind to the element are the following ones:
* action, to be called every update;
* keyPress, to be called when a key is pressed;
* keyReleased, to be called when a key is released;
* click, to be called if the element is clicked (be careful, there have to be a clickable zone);
* unClick, to be called when the user release the click of the mouse on the clickable zone of the element;
* unSelect, to be called when the user click elsewhere or unclick elsewhere;
* endSprite, to be called when an animation reach its end, before starting of again.
<br/><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;You can bind elements to another (which will become their parent) so that the parent element will be able to modifie them in one of
the functions you binded to it. In those function, you can modifie the element itself or others, even removing them.
Each animation of an element has a code so that you can switch from one to another. When you want to add a step
to the animation, you will have to define its coordinates in the image of the element (which should be a sprite sheet
or something the like). Each sprite has a lifespan, which correspond to the number of update call before going to the
next. That is if the animation is on 'automatic' mode. The mode can be set with the function setWayAnimationElementSDL2.
If there are no sprite, the entire image will be displaied.<br/>

## Structures

### I. Clickable.h

  1. LineSDL2:  
    A clickable zone delimited by a line (only one side of the line is clickable).

  2. CircleSDL2:  
    An elliptic shaped clickable zone.

  3. Clickable:  
    A clickable zone made of a collection of lines and ellipses.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  4. ListClickable:  
    A clickable zone defined by a collection of clickable Clickable and blocking Clickable.

### II. Sprite.h

  1. Sprite:  
    A step in an animation defined by the rectangle in the image and its lifespan.

  2. ListSprite:  
    A list of Sprite forming a complete animation.

  3. ListAnimation:  
    A list of animations.

### III. DisplayCode.h

  1. DisplayCode:  
    A package of information about a display code. It contains the display code, the plan and a flag to tell whether or not
    the object should be displaied.

  2. ListDisplayCode:  
    A list of display codes.

### IV. FontSDL2.h

  1. FontSDL2:  
    A package of information about a text. It contains its font, its text, its color and its SDL2 texture.

### V. WindowSDL2.h

  1. WindowSDL2:  
    Representation of a window. It contains all informations (such as the dimension, the display code, ...) about a window.

  2. ListWindowSDL2:  
    A list of WindowSDL2, used to manage all your windows while hiding them to you.

  3. EventWindowSDL2:  
    All the behaviors a window can have.

### VI. ElementSDL2.h

  1. ElementSDL2:  
    A package of information about objects. It contains its coordinates (top left corner), its size, its color and so on.
    This is one of the only structure you'll be manipulating (even though not directly accessing to its values).

  2. PtrElementSDL2:  
    A structure mean to store an ElementSDL2's pointer

  3. ListPtrElementSDL2:  
    A list of PtrElementSDL2. Either used as a list of elements with a common plan or so that an element can change another.

  4. ListDCElementSDL2:  
    A list of lists of elements with a common plan, every lists in this list has a common display code.

  5. ListElementSDL2:  
    A list of ListDCElementSDL2.

  6. EventElementSDL2:  
    All the behaviors an element can have.

  7. Entry:  
    Entries' informations needed that other elements do not need.