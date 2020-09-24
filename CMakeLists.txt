cmake_minimum_required(VERSION 3.15...3.17)

project(dokusei)

add_subdirectory(third_party/c-toxcore)
add_subdirectory(third_party/googletest)
add_subdirectory(third_party/grpc)

add_subdirectory(lib/grpc)
add_subdirectory(lib/platform)
add_subdirectory(lib/toxxx)
add_subdirectory(dokusei)
