# find_package(Java COMPONENTS Runtime REQUIRED)

#
# The ANTLR generator will output the following files given the input file f.g4
#
# Input  -> f.g4
# Output -> f.h
#        -> f.cpp
#
# the following files will only be produced if there is a parser contained
# Flag -visitor active
# Output -> <f>BaseVisitor.h
#        -> <f>BaseVisitor.cpp
#        -> <f>Visitor.h
#        -> <f>Visitor.cpp
#
# Flag -listener active
# Output -> <f>BaseListener.h
#        -> <f>BaseListener.cpp
#        -> <f>Listener.h
#        -> <f>Listener.cpp
#
# See documentation in markup
#

function(getAntlr4OutputPrefix)
foreach(arg IN LISTS ARGV)
# string(REGEX MATCH "([^ ]+)(([Pp][Aa][Rr][Ss][Ee][Rr])|([Ll][Ee][Xx][Ee][Rr]))?\.g4?" ok ${arg})
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
set(multi_value_args)
cmake_parse_arguments(ANTLR4 "${options_args}" "${single_value_args}" "${multi_value_args}" ${ARGN})
if(ANTLR4_UNPARSED_ARGUMENTS)
message(UNPARSED_ARGUMENTS:${ANTLR4_UNPARSED_ARGUMENTS})  
endif()
if(NOT ANTLR4_TARGET)
  message(FATAL_ERROR "TARGET not specified")
endif()
if(NOT ANTLR4_GRAMMAR_FILE)
  message(FATAL_ERROR "GRAMMAR_FILES not specified")
endif()

# message(${ANTLR4_PARSER})  
# message(${ANTLR4_LEXER})  
# message(${ANTLR4_VISITOR})  
# message(${ANTLR4_LISTENER})  
# message(${ANTLR4_GRAMMAR_FILES})
set(ENUM_LEXER_PARSER 0)
if(ANTLR4_LEXER)
math(EXPR ENUM_LEXER_PARSER "${ENUM_LEXER_PARSER}+1")
endif()
if(ANTLR4_PARSER)
math(EXPR ENUM_LEXER_PARSER "${ENUM_LEXER_PARSER}+1")
endif()
if(ENUM_LEXER_PARSER GREATER 1)
message(FATAL_ERROR "Only one of LEXER, PARSER can be specified")
endif()
if(ENUM_LEXER_PARSER EQUAL 0)
  set(ANTLR4_LEXER TRUE)
  set(ANTLR4_PARSER TRUE)
endif()
getAntlr4OutputPrefix(${ANTLR4_GRAMMAR_FILE})
if(ANTLR4_LEXER)
list(APPEND ANTLR4_GENERATED_FILES ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Lexer.h ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Lexer.cpp)
endif()
if(ANTLR4_PARSER)
list(APPEND ANTLR4_GENERATED_FILES ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.h ${ANTLR4_OUTPUT_DIRECTORY}/${ANTLR4_OUTPUT_PREFIX}Parser.cpp)
endif()

set(ANTLR4_GENERATED_FILES ${ANTLR4_GENERATED_FILES} PARENT_SCOPE)
endfunction()
