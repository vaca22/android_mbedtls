cmake_minimum_required(VERSION 3.18.1)


project("myapplication")



add_subdirectory(mbedtls)
INCLUDE_DIRECTORIES(mbedtls/include)

add_library( # Sets the name of the library.
        myapplication

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)



find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        myapplication

        mbedcrypto

        mbedx509

        mbedtls
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})