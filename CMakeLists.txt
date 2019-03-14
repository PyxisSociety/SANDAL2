cmake_minimum_required(VERSION 3.5)



# Project informations

project(SANDAL2 C)
set(PROJECT_VERSION 1.4.0)



# file helpers

file(GLOB main_src
     "src/*.c"
)

file(GLOB main_headers
     "headers/*.h"
)



# shared library

add_library(
        ${PROJECT_NAME} SHARED
        ${main_src}
)



# adding include dir

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        headers/
)



# additionnal compilation flags and infos

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO" CACHE STRING "Configuration type" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO" CACHE STRING "Configuration type" FORCE)
set(CMAKE_C_COMPILER /usr/bin/gcc)



# finding packages

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
IF(SDL2_FOUND)
  MESSAGE(INFO " SDL2 lib found at ${SDL2_LIBRARIES}")
ELSE()
  MESSAGE(ERROR " SDL2 not found")
ENDIF()

find_package(SDL2TTF REQUIRED)
IF(SDL2_TTF_FOUND)
  MESSAGE(INFO " SDL2_ttf lib found at ${SDL2_TTF_LIBRARIES}")
ELSE()
  MESSAGE(ERROR " SDL2_ttf not found")
ENDIF()

find_package(SDL2_image REQUIRED)
IF(SDL2_image_FOUND)
  MESSAGE(INFO " SDL2_image lib found at ${SDL2_image_LIBRARIES}")
ELSE()
  MESSAGE(ERROR " SDL2_image not found")
ENDIF()



# linking extern librairies

target_link_libraries(
        ${PROJECT_NAME}
        -lSDL2
        -lSDL2_ttf
        -lSDL2_image
        -lm
)



# project properties

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${main_headers}")




# package installation

include(GNUInstallDirs)

configure_file(sandal2.pc.in sandal2.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/sandal2.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SANDAL2
)
