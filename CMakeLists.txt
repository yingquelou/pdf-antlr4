cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
project(${PROJ} LANGUAGES C CXX)

set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
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
include(CTest)
include_directories("D:/Downloads/boost_1_85_0" "./.antlr" "C:/Program Files (x86)/LIBANTLR4/include/antlr4-runtime")
link_directories("C:/Program Files (x86)/LIBANTLR4/lib" "C:/Program Files (x86)/LIBANTLR4/bin")
file(GLOB LEX ./.antlr/*.cpp)
add_executable(${PROJ} ok.cpp ${LEX})
target_link_libraries(${PROJ} antlr4-runtime)
# install(TARGETS ${PROJ})
add_test(NAME ${PROJ} COMMAND ${PROJ} WORKING_DIRECTORY "C:/Program Files (x86)/LIBANTLR4/bin")
# add_subdirectory(com)
