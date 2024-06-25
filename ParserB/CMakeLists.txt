cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)

find_package(antlr4-runtime REQUIRED)
file(GLOB ANTLR4_JAR_LOCATION ${CMAKE_SOURCE_DIR}/antlr4-runtime/antlr4-*-complete.jar)
list(GET ANTLR4_JAR_LOCATION 0 ANTLR4_JAR_LOCATION)
file(GLOB LEXER ${CMAKE_CURRENT_LIST_DIR}/*Lexer.g4)
file(GLOB PARSER ${CMAKE_CURRENT_LIST_DIR}/*Parser.g4)

antlr4_configure(PREFIX ${PROJ})