# This CMake script provides functions for generating C++ ANTLR files.
# It includes functions for finding Java runtime, getting the output prefix of ANTLR4 files, and generating ANTLR4 files.

# find_package(Java COMPONENTS Runtime REQUIRED)
# This command is used to find the Java runtime component.

# function(getAntlr4OutputPrefix)
# This function is used to get the output prefix of ANTLR4 files.
# It takes a list of grammar files as input and removes the file extension to get the output prefix.
# The output prefix is stored in the ANTLR4_OUTPUT_PREFIX variable.

# function(antlr4_generate)
# This function is used to generate C++ ANTLR files.
# It takes several arguments including the target name, grammar file, output directory, and optional options.
# The function generates lexer and/or parser files based on the specified options.
# The generated files are stored in the specified output directory.
# The function also supports generating visitor and/or listener files for parser grammars.
# The function uses the ANTLR4 JAR file to generate the files.
# The generated files are added as dependencies to the target.
# The function sets several variables including the generated source files, generated header files, include directory, and tokens file.
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
set(single_value_args TARGET GRAMMAR_FILE OUTPUT_DIRECTORY)
set(multi_value_args LIB_DIR DEPENDS)
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
list(APPEND ${ANTLR4_TARGET}_ANTLR4_TOKENS_FILE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Lexer.tokens)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_INTERP_FILE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Lexer.interp)
endif()
if(ANTLR4_PARSER)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.h)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.cpp)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_TOKENS_FILE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.tokens)
list(APPEND ${ANTLR4_TARGET}_ANTLR4_INTERP_FILE ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.interp)
endif()
if(ANTLR4_LEXER AND (ANTLR4_LISTENER OR ANTLR4_VISITOR))
message(WARNING "LISTENER and VISITOR options are not supported for lexer grammars when yon specify LEXER option. Ignoring them.")
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
string(JOIN ";" LIB_DIR_STR ${ANTLR4_LIB_DIR})
if(LIB_DIR_STR)
set(LIB_DIR_STR "-lib;${LIB_DIR_STR}")
else()
set(LIB_DIR_STR "")
endif()
make_directory(${ANTLR4_OUTPUT_DIRECTORY})
add_custom_command(
  OUTPUT ${${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE}
  ${${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER}
  ${${ANTLR4_TARGET}_ANTLR4_TOKENS_FILE}
  ${${ANTLR4_TARGET}_ANTLR4_INTERP_FILE}
  COMMAND ${Java_JAVA_EXECUTABLE} -jar ${ANTLR4_JAR_LOCATION} ${ANTLR4_VISITOR} ${ANTLR4_LISTENER}
  ${LIB_DIR_STR}
  -o ${ANTLR4_OUTPUT_DIRECTORY}
  ${ANTLR4_GRAMMAR_FILE}
  WORKING_DIRECTORY ${ANTLR4_OUTPUT_DIRECTORY}
  DEPENDS ${ANTLR4_GRAMMAR_FILE} ${ANTLR4_DEPENDS}
  COMMENT "Generating C++ ANTLR files for ${ANTLR4_GRAMMAR_FILE}"
  MAIN_DEPENDENCY ${ANTLR4_GRAMMAR_FILE}
  BYPRODUCTS ${${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE} ${${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER} ${${ANTLR4_TARGET}_ANTLR4_TOKENS_FILE} ${${ANTLR4_TARGET}_ANTLR4_INTERP_FILE}
  VERBATIM
  )
set(${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE ${${ANTLR4_TARGET}_ANTLR4_GENERATED_SOURCE} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER ${${ANTLR4_TARGET}_ANTLR4_GENERATED_HEADER} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_INCLUDE_DIR ${ANTLR4_OUTPUT_DIRECTORY} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_GENERATED_DIR ${ANTLR4_OUTPUT_DIRECTORY} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_TOKENS_FILE ${${ANTLR4_TARGET}_ANTLR4_TOKENS_FILE} PARENT_SCOPE)
set(${ANTLR4_TARGET}_ANTLR4_INTERP_FILE ${${ANTLR4_TARGET}_ANTLR4_INTERP_FILE} PARENT_SCOPE)
endfunction()