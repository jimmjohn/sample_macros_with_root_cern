################################################################################
##  CMakeLists.txt file for building analysis code for miniICAL nuon lifetime ##
##  @author   Jim M John                                                      ##
##  @mail     jim.john@tifr.res.in                                            ##
################################################################################

cmake_minimum_required(VERSION 3.9)

# set the project name
project(avalanche_size VERSION 1.0.0 LANGUAGES CXX)


# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_BUILD_TYPE Debug)

# sub directorires
#add_subdirectory(src)

#including root
find_package(ROOT CONFIG REQUIRED)
find_package(ROOT COMPONENTS Proof ProofPlayer ProofDraw TMVA)
#----------------------------------------------------------------------------
# Setup Root include directories and compile definitions
#
include("${ROOT_USE_FILE}")
#include("${ROOT_DIR}/modules/RootNewMacros.cmake")
#find_library(libproof NAMES libProof.so PATHS ${ROOTSYS}/lib)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR})

add_compile_options(-Wall -Wextra -pedantic)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.C)
# file(GLOB sources2 . $ENV{ROOTSYS}/lib/*.so)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)

separate_arguments(ROOT_EXE_LINKER_FLAGS)
add_executable(avalanche_size avalanche_size.C ${sources} ${headers})


target_compile_features(avalanche_size PRIVATE cxx_lambda_init_captures)
target_link_libraries(avalanche_size PUBLIC ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Testing
enable_testing()
