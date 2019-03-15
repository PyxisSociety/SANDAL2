cmake_minimum_required(VERSION 3.5)



# debug flag

set(CMAKE_BUILD_TYPE Debug)



# project name

project(SANDAL2_test C)



# file helpers

file(GLOB SANDAL2_src
  "../src/*.c")



# additionnal compilation flags

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage -D DEBUG_SDL2_NO_VIDEO -O0")



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



# iterating for each test file
set(test_files Action Clickable DisplayCode Element Font SANDAL2 Sprite Window)
foreach(test_file ${test_files})
  # creating executable
  add_executable(
    ${PROJECT_NAME}_${test_file}
    ${test_file}/main.c
    ${SANDAL2_src})

  # linking external librairies
  target_link_libraries(
    ${PROJECT_NAME}_${test_file}
    -lSDL2
    -lSDL2_ttf
    -lSDL2_image
    -lm)
  
  # adding include dir
  target_include_directories(
    ${PROJECT_NAME}_${test_file}
    PUBLIC ../headers/)
endforeach()
