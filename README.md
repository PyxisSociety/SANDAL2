# SANDAL2

[![tests status](https://gitlab.com/BaptistePR/SANDAL2/badges/master/pipeline.svg)](https://gitlab.com/BaptistePR/SANDAL2/commits/master)
[![coverage report](https://gitlab.com/BaptistePR/SANDAL2/badges/master/coverage.svg)](https://gitlab.com/BaptistePR/SANDAL2/commits/master)
  
SANDAL2 is a graphics engine based on SDL2 which purpose is to make object managment and
graphic display easier.  

To generate the Doxygen documentation, use the command:  
`doxygen Doxyfile`  
<br/>

## About the author

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I hope you will enjoy using this tool, and if you have any comment or advice, do not feel shy 
and tell me (by posting an issue [here](https://github.com/Klevh/SANDAL2/issues/new)) ! I will really appreciate it.

## Contributors

[dabaldassi](https://github.com/dabaldassi) : version 1.2.3  

## Useful links

From this "read-me", you can either go to :
* the [read-me](Readmes/README.md) with more informations about the project in itself ;
* the [documentation](https://Klevh.github.io/SANDAL2/index.html) of the projet
* a [small tutorial](Readmes/Tutorial.md) explaining how to use it ;
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

## Compilation tools

### I. Make

A pseudo generic makefile is downloadable [here](https://github.com/Klevh/SANDAL2/blob/master/downloadable/Makefile)

### II. CMake

A `FindSANDAL2.cmake` file was created for this project. Also, find files can be found for SDL2_ttf and SDL2_image. All those files are downloadable [here](https://github.com/Klevh/SANDAL2/tree/master/downloadable/cmake).

