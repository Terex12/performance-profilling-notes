# a simple cmake script to locate Intel Math Kernel Library

# This script looks for two places:
#	- the environment variable MKLROOT
#	- the directory /opt/intel/mkl


# Stage 1: find the root directory

set(MKLROOT_PATH $ENV{MKLROOT})
if (NOT MKLROOT_PATH)
    # try to find at /opt/intel/mkl
    if (EXISTS "/uufs/chpc.utah.edu/sys/installdir/intel/mkl")
        set(MKLROOT_PATH "/uufs/chpc.utah.edu/sys/installdir/intel/mkl")
    endif (EXISTS "/uufs/chpc.utah.edu/sys/installdir/intel/mkl")
endif (NOT MKLROOT_PATH)

# Stage 2: find include path and libraries

if (MKLROOT_PATH)
    # root-path found

    set(EXPECT_MKL_INCPATH "${MKLROOT_PATH}/include")

    if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        set(EXPECT_MKL_LIBPATH "${MKLROOT_PATH}/lib")
    endif (CMAKE_SYSTEM_NAME MATCHES "Darwin")

    set(EXPECT_ICC_LIBPATH "$ENV{ICC_LIBPATH}")

    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        if (CMAKE_SIZEOF_VOID_P MATCHES 8)
            set(EXPECT_MKL_LIBPATH "${MKLROOT_PATH}/lib/intel64")
        else (CMAKE_SIZEOF_VOID_P MATCHES 8)
            set(EXPECT_MKL_LIBPATH "${MKLROOT_PATH}/lib/ia32")
        endif (CMAKE_SIZEOF_VOID_P MATCHES 8)
    endif (CMAKE_SYSTEM_NAME MATCHES "Linux")

    # set include
    message(status ${EXPECT_MKL_LIBPATH})

    if (IS_DIRECTORY ${EXPECT_MKL_INCPATH})
        set(MKL_INCLUDE_DIR ${EXPECT_MKL_INCPATH})
    endif (IS_DIRECTORY ${EXPECT_MKL_INCPATH})

    if (IS_DIRECTORY ${EXPECT_MKL_LIBPATH})
        set(MKL_LIBRARY_DIR ${EXPECT_MKL_LIBPATH})
    endif (IS_DIRECTORY ${EXPECT_MKL_LIBPATH})

    # find specific library files

    find_library(LIB_MKL_RT NAMES mkl_rt HINTS ${MKL_LIBRARY_DIR})
    find_library(LIB_PTHREAD NAMES pthread)

endif (MKLROOT_PATH)

set(MKL_LIBRARY
        ${LIB_MKL_RT}
        ${LIB_PTHREAD})
message (STATUS "MKL_LIBRARY ; ${MKL_LIBRARY}")
# deal with QUIET and REQUIRED argument

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(MKL DEFAULT_MSG
        MKL_LIBRARY_DIR
        LIB_MKL_RT
        LIB_PTHREAD
        MKL_INCLUDE_DIR)

mark_as_advanced(LIB_MKL_RT LIB_PTHREAD MKL_INCLUDE_DIR)
