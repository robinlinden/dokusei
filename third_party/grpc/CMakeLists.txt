project(grpc)

include(FetchContent)

FetchContent_Declare(grpc
    GIT_REPOSITORY https://github.com/grpc/grpc.git
    GIT_TAG 414bb8322de2411eee1f4e841ff29d887bec7884 # v1.32.0
)

FetchContent_MakeAvailable(grpc)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
