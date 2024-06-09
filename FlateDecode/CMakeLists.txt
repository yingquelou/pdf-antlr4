cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)

cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH DIR)

set(MYSY2_UCRT_INCLUDE ${DIR}/../include)
file(GLOB LEX *.cpp)
add_executable(${PROJ} ${LEX})
target_link_libraries(${PROJ} z)
if(EXISTS ${CMAKE_SOURCE_DIR}/tmp)
    add_test(NAME ${PROJ} COMMAND ${PROJ} ${CMAKE_SOURCE_DIR}/tmp/*.stream
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tmp)
    message(${PROJ})
endif()

