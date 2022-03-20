#include "tox_service.h"

#include <algorithm>
#include <iostream>
#include <numeric>

namespace dokusei::grpc {
namespace {

cctc::Savedata::Type into(proto::ToxOptions_SavedataType type) {
    switch (type) {
        case proto::ToxOptions_SavedataType_UNKNOWN:
        case proto::ToxOptions_SavedataType_NONE:
            return cctc::Savedata::Type::None;
        case proto::ToxOptions_SavedataType_TOX_SAVE:
            return cctc::Savedata::Type::ToxSave;
        case proto::ToxOptions_SavedataType_SECRET_KEY:
            return cctc::Savedata::Type::ToxSave;
        default:
            return cctc::Savedata::Type::None;
    }
}

bool option_requires_savedata(proto::ToxOptions_SavedataType type) {
    return type != proto::ToxOptions_SavedataType_UNKNOWN
            && type != proto::ToxOptions_SavedataType_NONE;
}

} // namespace

::grpc::Status ToxService::Create(
        ::grpc::ServerContext */*context*/,
        const proto::CreateRequest *request,
        proto::CreateResponse *response) {
    auto const &options = request->options();
    if (options.savedata().empty() && option_requires_savedata(options.savedata_type())) {
        std::cout << "Received create request with inconsistent savedata options\n";
        return ::grpc::Status::CANCELLED;
    }

    auto const &savedata = options.savedata();
    const auto &tox = toxii_.emplace_back(
            cctc::Savedata{into(options.savedata_type()), {begin(savedata), end(savedata)}});
    const auto addr{tox.self_get_address()};
    const auto addr_bytes = addr.bytes();

    const auto id = std::accumulate(begin(addr_bytes), end(addr_bytes), 0);
    std::cout << "Created Tox instance " << id << '\n';
    std::cout << "Now have " << toxii_.size() << " toxii." << std::endl;
    response->set_id(id);
    return ::grpc::Status::OK;
}

::grpc::Status ToxService::Delete(
        ::grpc::ServerContext */*context*/,
        const proto::DeleteRequest *request,
        proto::DeleteResponse */*response*/) {
    auto tox = std::find_if(begin(toxii_), end(toxii_), [&](const auto &t) {
        const auto addr{t.self_get_address()};
        const auto addr_bytes = addr.bytes();

        const auto id = std::accumulate(begin(addr_bytes), end(addr_bytes), 0ULL);
        return id == request->id();
    });

    if (tox == end(toxii_)) {
        std::cout << "There is no Tox instance " << request->id() << " to destroy." << std::endl;
        return ::grpc::Status::CANCELLED;
    }

    toxii_.erase(tox);
    std::cout << "Destroyed Tox instance " << request->id() << '\n';
    std::cout << "Now have " << toxii_.size() << " toxii." << std::endl;
    return ::grpc::Status::OK;
}

::grpc::Status ToxService::GetSavedata(
        ::grpc::ServerContext *,
        proto::GetSavedataRequest const *request,
        proto::GetSavedataResponse *response) {
    auto tox = std::find_if(begin(toxii_), end(toxii_), [&](const auto &t) {
        const auto addr{t.self_get_address()};
        const auto addr_bytes = addr.bytes();
        const auto id = std::accumulate(begin(addr_bytes), end(addr_bytes), 0ULL);
        return id == request->id();
    });

    if (tox == end(toxii_)) {
        return ::grpc::Status::CANCELLED;
    }

    auto savedata = tox->get_savedata();
    response->set_data({begin(savedata), end(savedata)});
    return ::grpc::Status::OK;
}

} // namespace dokusei::grpc
