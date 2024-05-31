cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
project(${PROJ} LANGUAGES C CXX)

set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_C_STANDARD 26)
set(CMAKE_CXX_STANDARD 26)


file(GLOB ANTLR4JAR ./antlr4-runtime/antlr4-*-complete.jar)


function(configAntlr4Target g4Files)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
add_custom_target(${PROJ}Antlr4
        COMMAND java -jar ${ANTLR4JAR} ${${g4Files}}
        -o ${CMAKE_CURRENT_LIST_DIR}/.antlr
        COMMENT "Generating C++ ANTLR files to ${CMAKE_CURRENT_LIST_DIR}/.antlr"
        )       
endfunction()

# install(TARGETS ${PROJ})
# add_subdirectory(ParserB)
add_subdirectory(ParserPdf)
# add_subdirectory(mycomC)