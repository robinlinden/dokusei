cmake_minimum_required(VERSION 3.15...3.17)

project(dokusei)

add_subdirectory(third_party/c-toxcore)
add_subdirectory(third_party/catch2)
add_subdirectory(third_party/googletest)
add_subdirectory(third_party/grpc)

enable_testing()

add_subdirectory(lib/grpc)
add_subdirectory(lib/platform)
add_subdirectory(lib/proto)
add_subdirectory(lib/toxxx)
add_subdirectory(dokusei)
