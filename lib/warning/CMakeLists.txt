project(dokusei_warning)

add_library(${PROJECT_NAME} INTERFACE)
add_library(dokusei::warning ALIAS ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} INTERFACE
    $<$<CXX_COMPILER_ID:Clang,GNU>:
        -Wall;
        -Wcast-align;
        -Wdouble-promotion;
        -Werror;
        -Wextra;
        -Wformat=2;
        -Wmissing-declarations;
        # -Wno-unused-parameter;
        -Wnon-virtual-dtor;
        -Wnull-dereference;
        -Wold-style-cast;
        -Woverloaded-virtual;
        -Wshadow;
        -Wundef;
    >
)

add_library(dokusei_warning_low INTERFACE)
add_library(dokusei::warning::low ALIAS dokusei_warning_low)

target_compile_options(dokusei_warning_low INTERFACE
    $<$<CXX_COMPILER_ID:Clang,GNU>:
        -Wall;
        -Wcast-align;
        -Wdouble-promotion;
        -Werror;
        -Wextra;
        -Wformat=2;
        -Wmissing-declarations;
        -Wno-unused-parameter;
        # -Wnon-virtual-dtor;
        -Wnull-dereference;
        -Woverloaded-virtual;
        # -Wshadow;
        # -Wundef;
    >
)
