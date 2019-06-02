cmake_minimum_required(VERSION 3.5)



# debug flag

set(CMAKE_BUILD_TYPE Debug)



# directory name
get_filename_component(ENTITY ${CMAKE_SOURCE_DIR} NAME)
MESSAGE(INFO " ${ENTITY}")



# project name

project(${ENTITY} C)



# file helpers

file(GLOB SANDAL2_src
  "../../src/*.c")



# additionnal compilation flags

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO -O0")



# find packages

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../downloadable/cmake")

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



# creating executable
add_executable(
  ${PROJECT_NAME}
  main.c
  ${SANDAL2_src})



# linking external librairies
target_link_libraries(
  ${PROJECT_NAME}
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm)



# adding include dir
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ../../headers/)



# copying resource files

file(GLOB RESOURCES "${PROJECT_SOURCE_DIR}/../../downloadable/*")

file(COPY ${RESOURCES} DESTINATION ${PROJECT_BINARY_DIR}/downloadable)
