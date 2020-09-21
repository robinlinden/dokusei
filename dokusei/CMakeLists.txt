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

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:
            -Wno-deprecated-declarations; # Protobuf has lots of these in its headers.
        >
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_20
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
