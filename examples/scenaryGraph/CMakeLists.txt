cmake_minimum_required(VERSION 3.5)

# Nom du projet

project(SANDAL2_example_animation)

# creation executable

add_executable(
  ${PROJECT_NAME}
  main.c
)

# trouver les packages

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SANDAL2 REQUIRED)
IF(SANDAL2_FOUND)
  MESSAGE(INFO " SANDAL2 lib found at ${SANDAL2_LIBRARIES}")
ELSE()
  MESSAGE(ERROR " SANDAL2 not found")
ENDIF()

find_package(SDL2 REQUIRED)
IF(SDL2_FOUND)
  MESSAGE(INFO " SDL2 lib found at ${SANDAL2_LIBRARIES}")
ELSE()
  MESSAGE(ERROR " SDL2 not found")
ENDIF()

# linking external libraries

target_link_libraries(
  ${PROJECT_NAME}
  SANDAL2
  SDL2
  -lm
)

# adding include dir

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC .)

# copy resource files in build

file(GLOB RESOURCE_FILES
  "${PROJECT_SOURCE_DIR}/resources/*")

file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_BINARY_DIR})
