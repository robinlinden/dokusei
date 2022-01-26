load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "platform",
    srcs = select({
        "@platforms//os:linux": ["linux.cpp"],
        "@platforms//os:windows": ["win32.cpp"],
    }),
    hdrs = ["platform.h"],
    include_prefix = "dokusei/platform",
    linkopts = select({
        "@platforms//os:linux": [],
        "@platforms//os:windows": ["-DEFAULTLIB:Kernel32"],
    }),
    visibility = ["//visibility:public"],
)
