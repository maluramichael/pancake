PROJECT(PANCAKE_PARTICLE)

FILE(GLOB HEADERS *.h)
FILE(GLOB SOURCES *.cpp)

SET(${PROJECT_NAME}_HEADER ${HEADERS} CACHE INTERNAL "")
SET(${PROJECT_NAME}_SOURCE ${SOURCES} CACHE INTERNAL "")

ADD_LIBRARY(${PROJECT_NAME} ${SOURCES})