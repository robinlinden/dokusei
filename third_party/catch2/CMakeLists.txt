project(catch2)

include(FetchContent)

FetchContent_Declare(catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 7f21cc6c5599f59835f769debf13b4c3e6148a28 # v2.13.0
)
FetchContent_MakeAvailable(catch2)

FetchContent_GetProperties(catch2
    SOURCE_DIR catch2_SOURCE_DIR
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
