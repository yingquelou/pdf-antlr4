cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
project(${PROJ} LANGUAGES C CXX)

set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)


file(GLOB ANTLR4JAR ./antlr4-runtime/antlr4-*-complete.jar)
list(APPEND ANTLR4OTPUTSUF Lexer Parser ParserBaseListener ParserListener ParserVisitor)
function(configAntlr4Output)
foreach(arg IN LISTS ARGV)
# string(REGEX MATCH "([^ ]+)(([Pp][Aa][Rr][Ss][Ee][Rr])|([Ll][Ee][Xx][Ee][Rr]))?\.g4?" ok ${arg})
string(REGEX REPLACE "(([Pp][Aa][Rr][Ss][Ee][Rr])|([Ll][Ee][Xx][Ee][Rr]))?\.g4?$" "" ok ${arg})
cmake_path(GET ok PARENT_PATH DIR)
cmake_path(GET ok STEM NAME)
# message(${ok})
foreach(curSuf IN LISTS ANTLR4OTPUTSUF)
    list(APPEND RET ${DIR}/.antlr/${NAME}${curSuf}.cpp ${DIR}/.antlr/${NAME}${curSuf}.h)
endforeach()
endforeach()
list(REMOVE_DUPLICATES RET)
    set(RET ${RET} PARENT_SCOPE)
endfunction()

function(configAntlr4Target g4Files RET)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
add_custom_target(${PROJ}Antlr4
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_CURRENT_LIST_DIR}/.antlr
        COMMAND java -jar ${ANTLR4JAR} ${${g4Files}}
        -o ${CMAKE_CURRENT_LIST_DIR}/.antlr 
        -visitor
        BYPRODUCTS ${RET}
        COMMENT "Generating C++ ANTLR files to ${CMAKE_CURRENT_LIST_DIR}/.antlr"
        )
endfunction()
include(CTest)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
# configAntlr4Output(E:/projects/github/pdf-antlr4/ParserPdf/pdfparser.g4)
# foreach(arg IN LISTS RET)
#     message(${arg})
# endforeach()
enable_testing()
# set(ANTLR4_JAR_LOCATION ${CMAKE_SOURCE_DIR}/antlr4-runtime)
# add_subdirectory(ParserPdf)
add_subdirectory(T)
# add_subdirectory(demo)
# add_subdirectory(ParserB)
# add_subdirectory(FlateDecode)