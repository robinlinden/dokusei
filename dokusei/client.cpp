#include "proto/tox.grpc.pb.h"

#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <utility>

namespace dokusei {
namespace {

class ToxApiClient {
public:
    ToxApiClient(std::shared_ptr<grpc::Channel> channel)
            : stub_{proto::ToxApi::NewStub(std::move(channel))} {}

    std::uint64_t create(std::optional<std::string> savedata = std::nullopt) {
        grpc::ClientContext context;
        proto::CreateRequest request{};
        if (savedata) {
            auto opts = request.mutable_options();
            opts->set_savedata(*savedata);
            opts->set_savedata_type(proto::ToxOptions_SavedataType_TOX_SAVE);
        }
        proto::CreateResponse create_response;
        auto status = stub_->Create(&context, request, &create_response);
        if (!status.ok()) {
            std::cout << "Failed to create Tox: " << status.error_message() << '\n';
            std::abort();
        }

        return create_response.id();
    }

    void kill(std::uint64_t id) {
        grpc::ClientContext context;
        proto::DeleteRequest delete_request;
        delete_request.set_id(id);
        proto::DeleteResponse delete_response;
        stub_->Delete(&context, delete_request, &delete_response);
    }

    std::string get_savedata(std::uint64_t id) {
        grpc::ClientContext context;
        proto::GetSavedataRequest request;
        request.set_id(id);
        proto::GetSavedataResponse response;
        stub_->GetSavedata(&context, request, &response);
        return response.data();
    }

private:
    std::unique_ptr<proto::ToxApi::Stub> stub_;
};

} // namespace
} // namespace dokusei

int main() {
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    dokusei::ToxApiClient client{std::move(channel)};

    auto id = client.create();
    std::cout << "Created Tox with ID " << id << '\n';

    auto savedata = client.get_savedata(id);
    std::cout << "Got savedata of size " << savedata.size() << '\n';

    client.kill(id);
    std::cout << "Killed Tox with ID " << id << '\n';

    id = client.create(std::move(savedata));
    std::cout << "Created Tox with ID " << id << '\n';

    client.kill(id);
    std::cout << "Killed Tox with ID " << id << '\n';
}
