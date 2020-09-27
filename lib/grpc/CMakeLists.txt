project(dokusei_grpc)

add_library(${PROJECT_NAME}
    src/server_factory.cpp
    src/tox_service.cpp
)
add_library(dokusei::grpc ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include/
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        dokusei::proto
        dokusei::toxxx
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
