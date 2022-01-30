#include "proto/tox.grpc.pb.h"

#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

class ToxApiClient {
public:
    ToxApiClient(std::shared_ptr<grpc::Channel> channel)
            : stub_{ToxAPI::NewStub(std::move(channel))} {}

    std::uint64_t create() {
        grpc::ClientContext context;
        CreateResponse create_response;
        auto status = stub_->Create(&context, CreateRequest{}, &create_response);
        if (!status.ok()) {
            std::cout << "Failed to create Tox: " << status.error_message() << '\n';
            std::abort();
        }

        return create_response.id();
    }

    void kill(std::uint64_t id) {
        grpc::ClientContext context;
        DeleteRequest delete_request;
        delete_request.set_id(id);
        DeleteResponse delete_response;
        stub_->Delete(&context, delete_request, &delete_response);
    }

private:
    std::unique_ptr<ToxAPI::Stub> stub_;
};

int main() {
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    ToxApiClient client{std::move(channel)};

    auto id = client.create();
    std::cout << "Created Tox with ID " << id << '\n';

    client.kill(id);
    std::cout << "Killed Tox with ID " << id << '\n';
}
