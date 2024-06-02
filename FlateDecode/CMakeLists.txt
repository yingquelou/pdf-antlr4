cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)

cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH DIR)

set(MYSY2_UCRT_INCLUDE ${DIR}/../include)
file(GLOB LEX *.cpp)
add_executable(${PROJ} ${LEX})
target_link_libraries(${PROJ} z)

