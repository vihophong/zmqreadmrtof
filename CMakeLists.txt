# From https://root.cern.ch/faq/can-i-integrate-root-my-cmake-build

# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(readmrtof)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
#find_package(ROOT REQUIRED COMPONENTS Core RIO RooFit RooFitCore RooStats Hist Tree Matrix Physics MathCore Net)
find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Tree Matrix Physics MathCore Net)

#---Locate cppzmq package
find_package(cppzmq)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_CXX_FLAGS})

#pragma link C++ function pstart;
ROOT_GENERATE_DICTIONARY(G__readmrtof ${PROJECT_SOURCE_DIR}/readmrtof.h LINKDEF ${PROJECT_SOURCE_DIR}/readmrtofLinkDef.h)

#---Create  a main program using the library
add_library(readmrtof SHARED readmrtof.h  readmrtofLinkDef.h readmrtof.cc G__readmrtof.cxx)
target_link_libraries(readmrtof ${ROOT_LIBRARIES})
target_link_libraries(readmrtof cppzmq)

add_executable(merger readmrtofLinkDef.h readmrtof.h merger.cc G__readmrtof.cxx)
target_link_libraries(merger ${ROOT_LIBRARIES})
target_link_libraries(merger cppzmq)

#----------------------------------------------------------------------------
# Copy all resources including scripts, examples, text files, etc... to the build directory, i.e. the directory in which we
# build project. This is so that we can us the resources because it
# relies on these scripts being in the current working directory.
#
set(PROJ_DATA
    readmrtof.C
  )


foreach(_script ${PROJ_DATA})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
