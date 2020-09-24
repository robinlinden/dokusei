#include "dokusei/grpc/server_factory.h"
#include "dokusei/toxxx/tox.h"
#include "dokusei/platform/platform.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace dokusei;

int main() {
    std::cout << "Linked against Tox " << toxxx::toxcore_version() << std::endl;

    std::atomic<bool> running{true};

    platform::set_ctrl_c_handler([&] {
        running.store(false);
    });

    auto server{grpc::ServerFactory::create("0.0.0.0:50051")};
    (void)server;

    while (running.load()) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);
    }

    std::cout << "Shutting down!" << std::endl;
}
