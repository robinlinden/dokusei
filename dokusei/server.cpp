#include "dokusei/grpc/server_factory.h"
#include "dokusei/platform/platform.h"

#include "cctc/tox.h"

#include <iostream>

using namespace dokusei;

int main() {
    std::cout << "Linked against Tox " << cctc::toxcore_version() << std::endl;

    auto server = grpc::ServerFactory::create("0.0.0.0:50051");

    platform::set_ctrl_c_handler([&] {
        server->shutdown();
    });

    server->wait();

    std::cout << "Shutting down!" << std::endl;
}
