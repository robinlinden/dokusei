project(dokusei)

include(grpc_generate_cpp)
grpc_generate_cpp(SRCS HDRS proto/tox.proto)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SRCS}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_BINARY_DIR}/gen/
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        toxcore
        libprotobuf
        grpc++_reflection
)
