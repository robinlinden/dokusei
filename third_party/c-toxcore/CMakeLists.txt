project(toxcore)

include(FetchContent)

FetchContent_Declare(ctoxcore
    GIT_REPOSITORY https://github.com/toktok/c-toxcore.git
    GIT_TAG 9be4dbb4335bf7d893c8d00566d3276ab6dedd14 # v0.2.12
)
option(BOOTSTRAP_DAEMON "" OFF)
FetchContent_MakeAvailable(ctoxcore)

# Fix c-toxcore having a weird target name.
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME}
    INTERFACE
        toxcore_static
)

# Fix c-toxcore using a different include structure installed vs as a cmake target.
FetchContent_GetProperties(ctoxcore
    SOURCE_DIR ctoxcore_SOURCE_DIR
)
configure_file(${ctoxcore_SOURCE_DIR}/toxcore/tox.h ${CMAKE_BINARY_DIR}/toxcore_fix/tox/tox.h)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_BINARY_DIR}/toxcore_fix/
)
