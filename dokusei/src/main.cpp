#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <proto/tox.grpc.pb.h>
#include <tox/tox.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

namespace {
class ToxService final : public ToxAPI::Service {
    grpc::Status Create(
            grpc::ServerContext *context,
            const CreateRequest *request,
            CreateResponse *response) override {
        const auto id = std::rand(); // NOLINT(cert-msc50-cpp): This is very temporary.
        std::cout << "Created Tox instance " << id << "." << std::endl;
        response->set_id(id);
        return grpc::Status::OK;
    }

    grpc::Status Delete(
            grpc::ServerContext *context,
            const DeleteRequest *request,
            DeleteResponse *response) override {
        std::cout << "Destroyed Tox instance " << request->id() << "." << std::endl;
        return grpc::Status::OK;
    }
};
} // namespace

int main() {
    std::srand(std::time(nullptr)); // NOLINT(cert-msc51-cpp): This is very temporary.

    std::cout << "Linked against Tox "
            << tox_version_major() << "."
            << tox_version_minor() << "."
            << tox_version_patch() << "."
            << std::endl;

    const std::string server_address{"0.0.0.0:50051"};
    ToxService service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
    std::cout << "Server listening on " << server_address << "." << std::endl;
    server->Wait();
}
