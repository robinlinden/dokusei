project(dokusei_proto)

include(grpc_generate_cpp)
grpc_generate_cpp(SRCS HDRS proto/tox.proto)

add_library(${PROJECT_NAME}
    ${SRCS}
)
add_library(dokusei::proto ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_BINARY_DIR}/gen/
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        grpc++_reflection
        libprotobuf
)
