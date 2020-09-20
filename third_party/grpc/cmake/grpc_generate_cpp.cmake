function(grpc_generate_cpp SRCS HDRS)
    set(dest ${CMAKE_BINARY_DIR}/gen/proto)
    file(MAKE_DIRECTORY ${dest})
    foreach(FIL ${ARGN})
        get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
        get_filename_component(FIL_WE ${FIL} NAME_WE)

        list(APPEND ${SRCS} "${dest}/${FIL_WE}.pb.cc" "${dest}/${FIL_WE}.grpc.pb.cc")
        list(APPEND ${HDRS} "${dest}/${FIL_WE}.pb.h" "${dest}/${FIL_WE}.grpc.pb.h")

        add_custom_command(
            OUTPUT "${dest}/${FIL_WE}.grpc.pb.cc" "${dest}/${FIL_WE}.grpc.pb.h" "${dest}/${FIL_WE}.pb.cc" "${dest}/${FIL_WE}.pb.h"
            COMMAND protoc
            ARGS --cpp_out ${dest} --grpc_out ${dest} -I ${CMAKE_CURRENT_LIST_DIR}/proto --plugin=protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin> ${ABS_FIL}
            DEPENDS ${ABS_FIL} protoc grpc_cpp_plugin
            COMMENT "Running protoc on ${FIL}"
            VERBATIM)
    endforeach()

    set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
    set(${SRCS} ${${SRCS}} PARENT_SCOPE)
    set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()
