cmake_minimum_required(VERSION 3.8)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)

file(GLOB LEX test.cpp)
add_executable(${PROJ} ${LEX})
find_package(Boost REQUIRED COMPONENTS system filesystem iostreams)
target_link_libraries(${PROJ} Boost::system Boost::filesystem Boost::iostreams)

