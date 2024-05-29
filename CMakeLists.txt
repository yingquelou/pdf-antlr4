cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
project(${PROJ} LANGUAGES C CXX)

set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_C_STANDARD 26)
set(CMAKE_CXX_STANDARD 26)
# add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# set(CMAKE_MODULE_PATH "D:/Downloads/boost_1_85_0/tools/cmake/include")
# find_package(Boost REQUIRED NO_MODILE CONFIG
# PATHS
# "D:/Downloads/boost_1_85_0/tools/cmake/config"
# )

# set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
# set(VCPKG_CMAKE_SYSTEM_NAME MinGW)

# set(EXECUTABLE_OUTPUT_PATH bin)
# set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

# set(CMAKE_WIN32_EXECUTABLE ON)
# include_directories("C:/Program Files (x86)/Adobe/Acrobat DC/PDFMaker/Office/x64" "C:/Program Files (x86)/Adobe/Acrobat DC/Acrobat")

# install(TARGETS ${PROJ})
# add_subdirectory(ParserB)
add_subdirectory(ParserPdf)
# add_subdirectory(mycomC)
file(GLOB ANTLR4JAR ./antlr4-runtime/antlr4-*-complete.jar)
file(GLOB_RECURSE ANTLR4GRAMMAR *.g4)

foreach(ITEM ${ANTLR4GRAMMAR})
    cmake_path(GET ITEM PARENT_PATH ITEM_NAME)    
    cmake_path(GET ITEM STEM ITEM_PROJECT)    
    set(CUR_ANTLR_TARGET_DIR ${ITEM_NAME}/.antlr)
    file(MAKE_DIRECTORY ${CUR_ANTLR_TARGET_DIR})
add_custom_target(${ITEM_PROJECT}
    COMMAND java -jar ${ANTLR4JAR} -o ${CUR_ANTLR_TARGET_DIR} ${ITEM}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating C++ ANTLR files from ${ITEM}"
    )
list(APPEND ANTLR4_TARGETS ${CUR_ANTLR_TARGET_DIR})
endforeach()
add_custom_target(ANTLR4CLEAN 
COMMAND ${CMAKE_COMMAND} -E rm -rf ${ANTLR4_TARGETS}
DEPENDS ${ANTLR4_TARGETS})

# message(${ANTLR4GRAMMAR})

