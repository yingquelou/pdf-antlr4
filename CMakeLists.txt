cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
project(${PROJ} LANGUAGES C CXX)

set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)


include(CTest)

enable_testing()
add_subdirectory(ParserPdf)
# add_subdirectory(T)
# add_subdirectory(demo)
# add_subdirectory(ParserB)
# add_subdirectory(FlateDecode)