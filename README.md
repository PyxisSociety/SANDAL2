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
and tell me (by posting an issue [here](https://github.com/Klevh/SANDAL2/issues/new)) ! I will really appreciate it.

## Useful links

From this "read-me", you can either go to :
* the [read-me](Docs/README.md) with more informations about the project in itself ;
* the [documentation](https://Klevh.github.io/SANDAL2_Documentation) of the projet
* a [small tutorial](Docs/Tutorial.md) explaining how to use it ;
* or the page to report an issue about a tutorial lacking things, an update that could be done or anything that comes to your mind [here](https://github.com/Klevh/SANDAL2/issues/new).

## To Install/Uninstall On Linux (Debian)

Regardless the way you install SANDAL2, you'll need to include SANDAL2.h and use `-lm -lSDL2 -lSDL2_ttf -lSDL2_image` compilation flags. To install SDL2, you only needs to enter those commands :
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
```

### I. Using the Debian Package only

Installing :
```
sudo wget https://github.com/Klevh/SANDAL2/raw/master/downloadable/sandal2.deb
sudo dpkg -i sandal2.deb
```
Then you'll need to add `-lSANDAL2` as a compilation flag before all the SDL2 flags.

Uninstalling :
```
dpkg --purge sandal2
```

### II. Using the github repository

If the package is not made for your computer, or you simply want to use the github directory, you can clone the [github project](https://github.com/Klevh/SANDAL2/).
Once you have it, and you are in the directory of the repository, you can install the package using this command :
```
sudo make install
```
You can also directly use the source code. A Makefile is provided in `downloadable`.