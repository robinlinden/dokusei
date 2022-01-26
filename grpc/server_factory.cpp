#include "dokusei/grpc/server_factory.h"

#include "tox_service.h"

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace dokusei::grpc {
namespace {

class ServerImpl final : public Server {
public:
    explicit ServerImpl(std::string address) :
            address_{std::move(address)} {}

    ~ServerImpl() override {
        server_->Shutdown();
        server_->Wait();
    }

private:
    std::string address_;
    ToxService tox_service_{};
    std::unique_ptr<::grpc::Server> server_{[this] {
        ::grpc::ServerBuilder builder;
        builder.AddListeningPort(address_, ::grpc::InsecureServerCredentials());
        builder.RegisterService(&tox_service_);
        std::cout << "Server listening on " << address_ << std::endl;
        return builder.BuildAndStart();
    }()};
};

} // namespace

std::unique_ptr<Server> ServerFactory::create(std::string address) {
    return std::make_unique<ServerImpl>(std::move(address));
}

} // namespace dokusei::grpc
