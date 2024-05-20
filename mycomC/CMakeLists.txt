cmake_minimum_required(VERSION 3.10)

project(SampleCOMProject)

add_library(SampleCOMLibrary SHARED
    SampleCOMObject.c
    SampleCOMObject.def
)

target_include_directories(SampleCOMLibrary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(SampleCOMLibrary PROPERTIES
    PREFIX ""
)

