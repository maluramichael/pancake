PROJECT(pancake)
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
SET(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)
FIND_PACKAGE(SDL2_mixer REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDL2_IMAGE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLMIXER_INCLUDE_DIR})

INCLUDE_DIRECTORIES(libs/json/src)

FILE(GLOB HEADERS 
    include/*.h
    include/Graphics/*.h
    include/Images/*.h
    include/UI/*.h
    include/Game/*.h
    include/Menu/*.h
    include/Particles/*.h
    include/Math/*.h

    libs/imgui/*.h

)

FILE(GLOB SOURCES 
    src/*.cpp
    src/Graphics/*.cpp
    src/Images/*.cpp
    src/UI/*.cpp
    src/Game/*.cpp
    src/Menu/*.cpp
    src/Particles/*.cpp
    src/Math/*.cpp

    libs/imgui/*.cpp

)

FILE(GLOB IMGUI_HEADER libs/imgui/*.h)

ADD_LIBRARY(pancake STATIC ${SOURCES} ${HEADERS})

INSTALL(TARGETS pancake DESTINATION "lib")

INSTALL(DIRECTORY include/ DESTINATION "include/Pancake")
INSTALL(FILES ${IMGUI_HEADER} DESTINATION "include/Pancake/UI")