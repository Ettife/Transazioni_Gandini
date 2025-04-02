cmake_minimum_required(VERSION 3.27.8)
project(Transazioni_Gandini)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

set(SOURCE_FILES
        Transazione.h
        Transazione.cpp
        GestoreFile.h
        GestoreFile.cpp
        ContoCorrente.h
        ContoCorrente.cpp)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)