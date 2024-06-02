cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
project(${PROJ} LANGUAGES CXX)

file(GLOB SRCLIST *.cxx)

# add_library(${PROJECT_NAME} ${LIBRARY_KIND} ${SRCLIST})
configAntlr4Target(f.g4)

