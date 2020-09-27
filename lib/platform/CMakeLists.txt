project(dokusei_platform)

add_library(${PROJECT_NAME}
    $<$<PLATFORM_ID:Windows>:src/win32/platform.cpp>
    $<$<PLATFORM_ID:Linux>:src/linux/platform.cpp>
)
add_library(dokusei::platform ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include/
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        dokusei::warning
        $<$<PLATFORM_ID:Windows>:kernel32>
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
