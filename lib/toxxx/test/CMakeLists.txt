project(test_dokusei_toxxx)

include(Catch)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/test_tox.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        dokusei::toxxx
        Catch2::Catch2
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

catch_discover_tests(${PROJECT_NAME})
