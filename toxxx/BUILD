load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "toxxx",
    srcs = ["tox.cpp"],
    hdrs = ["tox.h"],
    include_prefix = "dokusei/toxxx",
    visibility = ["//visibility:public"],
    deps = ["@toxcore"],
)

cc_test(
    name = "toxxx_test",
    size = "small",
    srcs = glob(["test/*"]),
    deps = [
        ":toxxx",
        "@catch2",
    ],
)
