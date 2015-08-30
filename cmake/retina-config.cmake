# Retina CMake config file
#
# This file sets the following variables:
# Retina_FOUND - Always TRUE.
# Retina_INCLUDE_DIRS - Directories containing the Retina include files.
# Retina_IDL_DIRS - Directories containing the Retina IDL files.
# Retina_LIBRARIES - Libraries needed to use Retina.
# Retina_DEFINITIONS - Compiler flags for Retina.
# Retina_VERSION - The version of Retina found.
# Retina_VERSION_MAJOR - The major version of Retina found.
# Retina_VERSION_MINOR - The minor version of Retina found.
# Retina_VERSION_REVISION - The revision version of Retina found.
# Retina_VERSION_CANDIDATE - The candidate version of Retina found.

message(STATUS "Found Retina-1.0.0")
set(Retina_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Retina_INCLUDE_DIRS
#    "/usr/local/include/retina-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Retina_IDL_DIRS
#    "/usr/local/include/retina-1/idl")
set(Retina_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Retina_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Retina_LIBRARIES
        "/usr/local/components/lib/libretina.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Retina_LIBRARIES
        "/usr/local/components/lib/libretina.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Retina_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Retina_VERSION 1.0.0)
set(Retina_VERSION_MAJOR 1)
set(Retina_VERSION_MINOR 0)
set(Retina_VERSION_REVISION 0)
set(Retina_VERSION_CANDIDATE )

