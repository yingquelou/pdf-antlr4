cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)
file(GLOB LEX test.cpp)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams)
add_executable(${PROJ} ${LEX})
target_link_libraries(${PROJ} Boost::iostreams)

