cmake_minimum_required(VERSION 3.5)



# debug flag

set(CMAKE_BUILD_TYPE Debug)



# project name

project(SANDAL2_test C)



# file helpers

file(GLOB SANDAL2_src
  "../src/*.c"
)



# creating executables

add_executable(
  ${PROJECT_NAME}_Action
  Action/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_Clickable
  Clickable/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_DisplayCode
  DisplayCode/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_Element
  Element/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_Font
  Font/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_SANDAL2
  SANDAL2/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_Sprite
  Sprite/main.c
  ${SANDAL2_src}
)
add_executable(
  ${PROJECT_NAME}_Window
  Window/main.c
  ${SANDAL2_src}
)



# additionnal compilation flags

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO -O0")
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_COMPILER_IS_GNUCXX 1)



# find packages

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake")

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



# linking external librairies

target_link_libraries(
  ${PROJECT_NAME}_Action
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_Clickable
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_DisplayCode
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_Element
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_Font
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_SANDAL2
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_Sprite
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)
target_link_libraries(
  ${PROJECT_NAME}_Window
  -lSDL2
  -lSDL2_ttf
  -lSDL2_image
  -lm
)



# adding include dir

target_include_directories(
  ${PROJECT_NAME}_Action
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_Clickable
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_DisplayCode
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_Element
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_Font
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_SANDAL2
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_Sprite
  PUBLIC ../headers/
)
target_include_directories(
  ${PROJECT_NAME}_Window
  PUBLIC ../headers/
)
