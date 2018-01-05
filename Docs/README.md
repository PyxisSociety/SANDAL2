# SANDAL2

SANDAL2 is a SDL2 wrapper which purpose is to make object managment and
graphic display easier.  

To generate the Doxygen documentation, use the command:  
`doxygen Doxyfile`  
<br/>
To see this read me file with a better display, you can go to [this project's
website](https://klevh.github.io/SANDAL2/).

## Useful links

From this "read-me", you can either go to :
* the [main read-me](../README.md) ;
* a [small tutorial](Tutorial.md) explaining how to use it ;
* or the page to report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new).

## Versions

0.0.0 : SDL2TK<br/>
0.1.0 : adding rotations<br/>
0.2.0 : clickable areas<br/>
0.3.0 : animation's managment<br/>
1.0.0 : project renamed SANDAL2<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;hide window objects from the user<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;hide element's lists from the user<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;going from an element's list structure to a list of list (display code) of list (plan) of elements<br/>
1.0.1 : possibility to hide event managment from the user<br/>
1.0.2 : adding shaded and blended text rendering<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding and correcting error's functions return<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;wrapping of TTF's font style<br/>
1.0.3 : adding identifier to sprites<br/>
1.0.4 : adding the possibility to set the window's icon<br/>
1.0.5 : adding the getter for the text of an element<br/>
1.0.6 : correcting the isDisplaied function<br/>
1.1.0 : correcting initIteratorElementSDL2 function<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding a freeing function to element's datas<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding a function to free an element's data without getting it<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding a structure that contains every function pointer (event handler)<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding an event handler to windows so that the user can add window events<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding functions to allow the user to add window event functions to a window<br/>
1.1.1 : adding functions so that windows can be closed in binded functions<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;changing error return type from int to unsigned long for event functions on more than one window<br/>
1.1.2 : changing functions not meant for the user to static in their source file, removing them from the header<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding the cast on all mallocs for C++ portability<br/>
1.1.3 : optimizing window managment<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;renaming HitBox by Clickable<br/>
1.1.4 : adding the possibility to change the correspondance between the origin of the window and the origin of all the elements placed<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;correcting C++ compatibility by renaming delete attribute of WindowSDL2 deleted<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;passing char * to const char * when possible<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding clearElementToElementSDL2, clearElementWindowSDL2, clearDisplayCode and clearPlanDisplayCode<br/>
1.2.0 : removing SDL2 from all the names (structures, functions, ...)<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;changing all functions name beginning with change to make them begin with set instead<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;changing all functions name beginning with remove to make them begin with del instead<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rennaming initWindow to createWindow<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rennaming setDisplayElement to setDisplayCodeElement<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rennaming isDisplaied to isDisplaiedElement<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rennaming createAnimationElement to addAnimationElement<br/>
1.2.1 : adding flipping on images<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rennaming resizeElement to setDimensionElement<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;adding functions getCoordXElement, getCoordYElement, getWidthElement, getHeightElement, setCoordXElement, setCoordYElement, setWidthElement and setHeightElement<br/>
1.2.2 : improving C++ compatibility <br/>

## Project's size

Font.c : 268 lines<br/>
Window.c : 291 lines<br/>
DisplayCode.c : 80 lines<br/>
Sprite.c : 308 lines<br/>
Clickable.c : 321 lines<br/>
Element.c : 1,883 lines<br/>
SANDAL2.c : 856 lines<br/>
<br/>
Total for source files : 4,015 lines<br/>
<br/>
Font.h : 115 lines<br/>
Window.h : 279 lines<br/>
DisplayCode.h : 78 lines<br/>
Sprite.h : 195 lines<br/>
Clickable.h : 219 lines<br/>
Element.h : 923 lines<br/>
SANDAL2.h : 201 lines<br/>
<br/>
Total for header files : 2,020 lines<br/>
<br/>
Total : 6,035 lines
