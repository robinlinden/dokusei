load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "server",
    srcs = ["server.cpp"],
    deps = [
        "//grpc",
        "//platform",
        "//toxxx",
    ],
)

cc_binary(
    name = "client",
    srcs = ["client.cpp"],
    deps = [
        "//proto",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
