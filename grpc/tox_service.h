#ifndef DOKUSEI_GRPC_TOX_SERVICE_H
#define DOKUSEI_GRPC_TOX_SERVICE_H

#include "proto/tox.grpc.pb.h"

#include "cctc/tox.h"

#include <list>

namespace dokusei::grpc {

class ToxService final : public proto::ToxApi::Service {
public:
    ::grpc::Status Create(
            ::grpc::ServerContext *context,
            const proto::CreateRequest *request,
            proto::CreateResponse *response) override;

    ::grpc::Status Delete(
            ::grpc::ServerContext *context,
            const proto::DeleteRequest *request,
            proto::DeleteResponse *response) override;

    ::grpc::Status GetSavedata(
            ::grpc::ServerContext *,
            proto::GetSavedataRequest const *,
            proto::GetSavedataResponse *) override;

private:
    std::list<cctc::Tox> toxii_;
};

} // namespace dokusei::grpc

#endif
