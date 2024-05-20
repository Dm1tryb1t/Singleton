cmake_minimum_required(VERSION 3.10)

project(Singleton)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES
    ConceptualExample01.cpp
    ConceptualExample02.cpp
    Program.cpp
    Singleton_vs_Dependency_Injection.cpp
)

add_executable(Singleton ${SOURCES})

enable_testing()

add_subdirectory(tests)
