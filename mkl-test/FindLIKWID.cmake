set(LIKWID_ROOT "/uufs/chpc.utah.edu/sys/installdir/likwid/5.0.1")

FIND_PATH(LIKWID_INCLUDE_DIR likwid.h HINTS ${LIKWID_ROOT}/include)
FIND_LIBRARY(LIKWID_LIBRARY likwid HINTS ${LIKWID_ROOT}/lib)
#FIND_PROGRAM(LIKWID_PIN likwid-pin HINTS ${LIKWID_ROOT}/bin)

if (LIKWID_INCLUDE_DIR AND LIKWID_LIBRARY)
  set(LIKWID_FOUND TRUE)
endif (LIKWID_INCLUDE_DIR AND LIKWID_LIBRARY)

if (LIKWID_FOUND)
  if (NOT LIKWID_FIND_QUIETLY)
    MESSAGE(STATUS "Found Likwid library: ${LIKWID_LIBRARY}")
    #MESSAGE(STATUS "Found likwid-pin: ${LIKWID_PIN}")
  endif (NOT LIKWID_FIND_QUIETLY)
else (LIKWID_FOUND)
  if (LIKWID_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find Likwid")
  endif (LIKWID_FIND_REQUIRED)
endif (LIKWID_FOUND)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
        LIKWID
        DEFAULT_MSG
        LIKWID_INCLUDE_DIR
)

mark_as_advanced(LIKWID_INCLUDE_DIR LIKWID_LIBRARY)

