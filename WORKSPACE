load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Bazel
# =========================================================

http_archive(
    name = "platforms",  # Apache-2.0
    sha256 = "079945598e4b6cc075846f7fd6a9d0857c33a7afc0de868c2ccb96405225135d",
    url = "https://github.com/bazelbuild/platforms/releases/download/0.0.4/platforms-0.0.4.tar.gz",
)

http_archive(
    name = "rules_proto",  # Apache-2.0
    sha256 = "66bfdf8782796239d3875d37e7de19b1d94301e8972b3cbd2446b332429b4df1",
    strip_prefix = "rules_proto-4.0.0",
    url = "https://github.com/bazelbuild/rules_proto/archive/4.0.0.tar.gz",
)

# Third-party
# =========================================================

http_archive(
    name = "catch2",  # BSL-1.0
    sha256 = "b9b592bd743c09f13ee4bf35fc30eeee2748963184f6bea836b146e6cc2a585a",
    strip_prefix = "Catch2-2.13.8",
    url = "https://github.com/catchorg/Catch2/archive/v2.13.8.tar.gz",
)

http_archive(
    name = "com_github_grpc_grpc",  # Apache-2.0
    sha256 = "9647220c699cea4dafa92ec0917c25c7812be51a18143af047e20f3fb05adddc",
    strip_prefix = "grpc-1.43.0",
    url = "https://github.com/grpc/grpc/archive/v1.43.0.tar.gz",
)

http_archive(
    name = "libsodium",  # ISC
    build_file = "//third_party:libsodium.BUILD",
    patch_cmds = ["cp builds/msvc/version.h src/libsodium/include/sodium/"],
    sha256 = "d59323c6b712a1519a5daf710b68f5e7fde57040845ffec53850911f10a5d4f4",
    strip_prefix = "libsodium-1.0.18",
    url = "https://github.com/jedisct1/libsodium/archive/1.0.18.tar.gz",
)

http_archive(
    name = "msgpack-c",  # BSL-1.0
    build_file = "//third_party:msgpack-c.BUILD",
    sha256 = "420fe35e7572f2a168d17e660ef981a589c9cbe77faa25eb34a520e1fcc032c8",
    strip_prefix = "msgpack-c-4.0.0",
    url = "https://github.com/msgpack/msgpack-c/releases/download/c-4.0.0/msgpack-c-4.0.0.tar.gz",
)

http_archive(
    name = "pthread",  # LGPL-2.1-only
    build_file = "//third_party:pthread.BUILD",
    sha256 = "e6aca7aea8de33d9c8580bcb3a0ea3ec0a7ace4ba3f4e263ac7c7b66bc95fb4d",
    strip_prefix = "pthreads-w32-2-9-1-release",
    url = "https://sourceware.org/pub/pthreads-win32/pthreads-w32-2-9-1-release.tar.gz",
)

http_archive(
    name = "toxcore",  # GPL-3.0-or-later
    build_file = "//third_party:toxcore.BUILD",
    patch_cmds = [
        "rm toxcore/BUILD.bazel",
        "rm toxencryptsave/BUILD.bazel",
    ],
    sha256 = "d9cdf5d690fe8e217dcaba5b988fb943bbe7bda919a2fde6d9506df047e5f4cb",
    strip_prefix = "c-toxcore-0.2.17",
    url = "https://github.com/TokTok/c-toxcore/archive/v0.2.17.tar.gz",
)

http_archive(
    name = "upb",  # BSD-3-Clause
    # Fix upb not building with --incompatible_disallow_empty_glob
    patch_cmds = [
        "sed -i '/google\\/\\*\\*\\/\\*/d' BUILD",
        "sed -i '/tests\\/\\*\\*\\/\\*/d' BUILD",
        "sed -i '/upbc\\/\\*\\*\\/\\*/d' BUILD",
    ],
    sha256 = "7c02096dceb6b1249feaf11e4531f6bf31b9abdbd2305038349d1f1749bf88ea",
    strip_prefix = "upb-0e0de7d9f927aa888d9a0baeaf6576bbbb23bf0b",
    url = "https://github.com/protocolbuffers/upb/archive/0e0de7d9f927aa888d9a0baeaf6576bbbb23bf0b.tar.gz",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()
