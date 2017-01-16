SET(PANCAKE_SEARCH_PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
        ~/Development/Private/pancake
        )

FIND_PATH(PANCAKE_INCLUDE_DIR Pancake.h
        HINTS
        $ENV{PANCAKEDIR}
        PATH_SUFFIXES include
        PATHS ${PANCAKE_SEARCH_PATHS}
        )

FIND_PATH(PANCAKE_SOURCE_DIR Pancake.cpp
        HINTS
        $ENV{PANCAKEDIR}
        PATH_SUFFIXES src
        PATHS ${PANCAKE_SEARCH_PATHS}
        )

#SET(PANCAKE_DIR ${PANCAKE_INCLUDE_DIR}/../ CACHE STRING "")
#SET(PANCAKE_SOURCE_DIR "${PANCAKE_DIR}src/" CACHE STRING "")

FIND_LIBRARY(PANCAKE_LIBRARY_TEMP
        NAMES PANCAKE
        HINTS
        $ENV{PANCAKEDIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${PANCAKE_SEARCH_PATHS}
        )

IF(NOT PANCAKE_BUILDING_LIBRARY)
    IF(NOT ${PANCAKE_INCLUDE_DIR} MATCHES ".framework")
        # Non-OS X framework versions expect you to also dynamically link to
        # PANCAKEmain. This is mainly for Windows and OS X. Other (Unix) platforms
        # seem to provide PANCAKEmain for compatibility even though they don't
        # necessarily need it.
        FIND_LIBRARY(PANCAKEMAIN_LIBRARY
                NAMES PANCAKEmain
                HINTS
                $ENV{PANCAKEDIR}
                PATH_SUFFIXES lib64 lib
                PATHS ${PANCAKE_SEARCH_PATHS}
                )
    ENDIF(NOT ${PANCAKE_INCLUDE_DIR} MATCHES ".framework")
ENDIF(NOT PANCAKE_BUILDING_LIBRARY)

# PANCAKE may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
    FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lPANCAKEmain -lPANCAKE -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
    SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

IF(PANCAKE_LIBRARY_TEMP)
    # For PANCAKEmain
    IF(NOT PANCAKE_BUILDING_LIBRARY)
        IF(PANCAKEMAIN_LIBRARY)
            SET(PANCAKE_LIBRARY_TEMP ${PANCAKEMAIN_LIBRARY} ${PANCAKE_LIBRARY_TEMP})
        ENDIF(PANCAKEMAIN_LIBRARY)
    ENDIF(NOT PANCAKE_BUILDING_LIBRARY)

    # For OS X, PANCAKE uses Cocoa as a backend so it must link to Cocoa.
    # CMake doesn't display the -framework Cocoa string in the UI even
    # though it actually is there if I modify a pre-used variable.
    # I think it has something to do with the CACHE STRING.
    # So I use a temporary variable until the end so I can set the
    # "real" variable in one-shot.
    IF(APPLE)
        SET(PANCAKE_LIBRARY_TEMP ${PANCAKE_LIBRARY_TEMP} "-framework Cocoa")
    ENDIF(APPLE)

    # For threads, as mentioned Apple doesn't need this.
    # In fact, there seems to be a problem if I used the Threads package
    # and try using this line, so I'm just skipping it entirely for OS X.
    IF(NOT APPLE)
        SET(PANCAKE_LIBRARY_TEMP ${PANCAKE_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
    ENDIF(NOT APPLE)

    # For MinGW library
    IF(MINGW)
        SET(PANCAKE_LIBRARY_TEMP ${MINGW32_LIBRARY} ${PANCAKE_LIBRARY_TEMP})
    ENDIF(MINGW)

    # Set the final string here so the GUI reflects the final state.
    SET(PANCAKE_LIBRARY ${PANCAKE_LIBRARY_TEMP} CACHE STRING "Where the PANCAKE Library can be found")
    # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
    SET(PANCAKE_LIBRARY_TEMP "${PANCAKE_LIBRARY_TEMP}" CACHE INTERNAL "")
ENDIF(PANCAKE_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PANCAKE REQUIRED_VARS PANCAKE_LIBRARY PANCAKE_INCLUDE_DIR)