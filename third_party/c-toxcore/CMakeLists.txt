project(toxcore)

include(FetchContent)

FetchContent_Declare(ctoxcore
    GIT_REPOSITORY https://github.com/robinlinden/c-toxcore-cmake.git
    GIT_TAG 5084e2f1b303ebd0f33ae000bff4e389f89f097e
)
set(TOXCORE_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(ctoxcore)
