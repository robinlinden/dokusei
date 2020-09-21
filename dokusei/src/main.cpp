#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <proto/tox.grpc.pb.h>
#include <tox/tox.h>

#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

namespace {
struct ToxDeleter {
    void operator()(Tox *const t) {
        tox_kill(t);
    }
};

struct ToxOptionsDeleter {
    void operator()(Tox_Options *const o) {
        tox_options_free(o);
    }
};

class ToxService final : public ToxAPI::Service {
public:
    grpc::Status Create(
            grpc::ServerContext *context,
            const CreateRequest *request,
            CreateResponse *response) override {
        std::unique_ptr<Tox_Options, ToxOptionsDeleter> opts{tox_options_new(nullptr), ToxOptionsDeleter{}};
        if (!opts) return grpc::Status::CANCELLED;

        std::unique_ptr<Tox, ToxDeleter> tox{tox_new(opts.get(), nullptr), ToxDeleter{}};
        if (!tox) return grpc::Status::CANCELLED;

        std::array<uint8_t, TOX_ADDRESS_SIZE> addr{};
        tox_self_get_address(tox.get(), addr.data());

        toxii.push_back(std::move(tox));

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
            std::array<uint8_t, TOX_ADDRESS_SIZE> addr{};
            tox_self_get_address(t.get(), addr.data());
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
    std::vector<std::unique_ptr<Tox, ToxDeleter>> toxii;
};
} // namespace

int main() {
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
