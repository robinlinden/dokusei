load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "grpc",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    include_prefix = "dokusei/grpc",
    visibility = ["//visibility:public"],
    deps = [
        "//proto",
        "//toxxx",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
