cmake_minimum_required(VERSION 3.15...3.17)

project(dokusei)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        toxcore
)

add_subdirectory(third_party/c-toxcore)
