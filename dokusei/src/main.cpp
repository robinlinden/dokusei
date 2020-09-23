#include "dokusei/toxxx/tox.h"
#include "dokusei/platform/platform.h"

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <proto/tox.grpc.pb.h>

#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

using namespace dokusei;

namespace {

class ToxService final : public ToxAPI::Service {
public:
    grpc::Status Create(
            grpc::ServerContext *context,
            const CreateRequest *request,
            CreateResponse *response) override {
        const auto &tox = toxii.emplace_back();
        const auto addr{tox.get_address()};

        const auto id = std::accumulate(begin(addr), end(addr), 0);
        std::cout << "Created Tox instance " << id << "." << '\n';
        std::cout << "Now have " << toxii.size() << " toxii." << std::endl;
        response->set_id(id);
        return grpc::Status::OK;
    }

    grpc::Status Delete(
            grpc::ServerContext *context,
            const DeleteRequest *request,
            DeleteResponse *response) override {
        auto tox = std::find_if(begin(toxii), end(toxii), [&](const auto &t) {
            const auto addr{t.get_address()};
            const auto id = std::accumulate(begin(addr), end(addr), 0);
            return id == request->id();
        });

        if (tox == end(toxii)) {
            std::cout << "There is no Tox instance " << request->id() << " to destroy." << std::endl;
            return grpc::Status::CANCELLED;
        }

        toxii.erase(tox);
        std::cout << "Destroyed Tox instance " << request->id() << "." << '\n';
        std::cout << "Now have " << toxii.size() << " toxii." << std::endl;
        return grpc::Status::OK;
    }

private:
    std::vector<toxxx::Toxxx> toxii;
};
} // namespace

int main() {
    std::cout << "Linked against Tox "
            << toxxx::toxcore_version()
            << std::endl;

    const std::string server_address{"0.0.0.0:50051"};
    ToxService service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
    std::cout << "Server listening on " << server_address << "." << std::endl;

    platform::set_ctrl_c_handler([&] {
        std::cout << "Shutting down!" << std::endl;
        server->Shutdown();
    });

    std::thread([&] { server->Wait(); }).join();
}
