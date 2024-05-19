cmake_minimum_required(VERSION 3.10)
project(Singleton)

set(CMAKE_CXX_STANDARD 23)


set(SOURCE_FILES
    Program.cpp
    ConceptualExample01.cpp
    ConceptualExample02.cpp
    Singleton_vs_Dependency_Injection.cpp
)

add_executable(Singleton ${SOURCE_FILES})

target_include_directories(Singleton PUBLIC ${PROJECT_SOURCE_DIR})
