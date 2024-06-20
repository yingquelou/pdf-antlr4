# FILEPATH: ./cmake/antlr4-generator.cmake

# This CMake script provides functions for generating C++ ANTLR files using the ANTLR4 tool.

# Function: getAntlr4OutputPrefix
# Description: Retrieves the output prefix for ANTLR4 generated files.
# Parameters:
#   - ARGV: List of grammar files.
# Returns: None

# Function: antlr4_generate
# Description: Generates C++ ANTLR files based on the specified options and arguments.
# Parameters:
#   - TARGET: The target name for the generated files.
#   - GRAMMAR_FILE: The ANTLR grammar file.
#   - OUTPUT_DIRECTORY (optional): The output directory for the generated files. If not specified, the current binary directory is used.
#   - LIB_DIR (optional): The directory containing ANTLR4 runtime libraries.
#   - LEXER (optional): Specifies whether to generate lexer files. Default is true.
#   - PARSER (optional): Specifies whether to generate parser files. Default is true.
#   - VISITOR (optional): Specifies whether to generate visitor files. Default is false.
#   - LISTENER (optional): Specifies whether to generate listener files. Default is false.
# Returns: None
find_package(Java COMPONENTS Runtime REQUIRED)

function(getAntlr4OutputPrefix)
foreach(arg IN LISTS ARGV)
string(REGEX REPLACE "(([Pp][Aa][Rr][Ss][Ee][Rr])|([Ll][Ee][Xx][Ee][Rr]))?\.g4?$" "" ok ${arg})
cmake_path(GET ok FILENAME ok)
list(APPEND output ${ok})
endforeach()
list(REMOVE_DUPLICATES output)
set(ANTLR4_OUTPUT_PREFIX ${output} PARENT_SCOPE)
endfunction()

function(antlr4_generate)
set(options_args LEXER PARSER VISITOR LISTENER)
set(single_value_args TARGET GRAMMAR_FILE OUTPUT_DIRECTORY LIB_DIR)
set(multi_value_args)
cmake_parse_arguments(ANTLR4 "${options_args}" "${single_value_args}" "${multi_value_args}" ${ARGN})
if(ANTLR4_UNPARSED_ARGUMENTS)
message(UNPARSED_ARGUMENTS:${ANTLR4_UNPARSED_ARGUMENTS})  
endif()
if(NOT ANTLR4_TARGET)
  message(FATAL_ERROR "TARGET not specified")
endif()
if(NOT ANTLR4_GRAMMAR_FILE)
  message(FATAL_ERROR "GRAMMAR_FILE not specified")
endif()
if(NOT ANTLR4_OUTPUT_DIRECTORY)
set(ANTLR4_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(ANTLR4_LEXER AND ANTLR4_PARSER)
message(FATAL_ERROR "Cannot specify both LEXER and PARSER options together. Please specify only one of them.")
endif()
if(NOT (ANTLR4_LEXER OR ANTLR4_PARSER))
  set(ANTLR4_LEXER TRUE)
  set(ANTLR4_PARSER TRUE)
endif()
getAntlr4OutputPrefix(${ANTLR4_GRAMMAR_FILE})
if(ANTLR4_LEXER)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Lexer.h)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Lexer.cpp)
endif()
if(ANTLR4_PARSER)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.h)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.cpp)
endif()
if(ANTLR4_VISITOR AND ANTLR4_PARSER)
set(ANTLR4_VISITOR "-visitor")
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserBaseVisitor.h ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserVisitor.h)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserBaseVisitor.cpp ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserVisitor.cpp)
else()
set(ANTLR4_VISITOR "-no-visitor")
endif()
if(ANTLR4_LISTENER AND ANTLR4_PARSER)
set(ANTLR4_LISTENER "-listener")
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserBaseListener.h ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserListener.h)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserBaseListener.cpp ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}ParserListener.cpp)
else()
set(ANTLR4_LISTENER "-no-listener")
endif()
string(JOIN " -lib " LIB_DIR_STR ${ANTLR4_LIB_DIR})
if(LIB_DIR_STR)
set(LIB_DIR_STR "-lib ${LIB_DIR_STR}")
else()
set(LIB_DIR_STR "")
endif()
add_custom_command(
  OUTPUT ${${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE}
  COMMAND ${Java_JAVA_EXECUTABLE} -jar ${ANTLR4_JAR_LOCATION} ${ANTLR4_VISITOR} ${ANTLR4_LISTENER}
  ${LIB_DIR_STR}
  -o ${ANTLR4_OUTPUT_DIRECTORY}
  ${ANTLR4_GRAMMAR_FILE}
  WORKING_DIRECTORY ${ANTLR4_OUTPUT_DIRECTORY}
  DEPENDS ${ANTLR4_GRAMMAR_FILE}
  COMMENT "Generating C++ ANTLR files"
  VERBATIM
  )
set(${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_INCLUDE_DIR ${ANTLR4_OUTPUT_DIRECTORY} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_GENERATED_DIR ${ANTLR4_OUTPUT_DIRECTORY} PARENT_SCOPE)
endfunction()