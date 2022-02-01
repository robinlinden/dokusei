#ifndef DOKUSEI_GRPC_TOX_SERVICE_H
#define DOKUSEI_GRPC_TOX_SERVICE_H

#include "dokusei/toxxx/tox.h"

#include "proto/tox.grpc.pb.h"

#include <vector>

namespace dokusei::grpc {

class ToxService final : public proto::ToxAPI::Service {
public:
    ::grpc::Status Create(
            ::grpc::ServerContext *context,
            const proto::CreateRequest *request,
            proto::CreateResponse *response) override;

    ::grpc::Status Delete(
            ::grpc::ServerContext *context,
            const proto::DeleteRequest *request,
            proto::DeleteResponse *response) override;

private:
    std::vector<toxxx::Toxxx> toxii_;
};

} // namespace dokusei::grpc

#endif
