#include "tox_service.h"

#include <algorithm>
#include <iostream>
#include <numeric>

namespace dokusei::grpc {

::grpc::Status ToxService::Create(
        ::grpc::ServerContext */*context*/,
        const CreateRequest */*request*/,
        CreateResponse *response) {
    const auto &tox = toxii_.emplace_back();
    const auto addr{tox.get_address()};

    const auto id = std::accumulate(begin(addr), end(addr), 0);
    std::cout << "Created Tox instance " << id << '\n';
    std::cout << "Now have " << toxii_.size() << " toxii." << std::endl;
    response->set_id(id);
    return ::grpc::Status::OK;
}

::grpc::Status ToxService::Delete(
        ::grpc::ServerContext */*context*/,
        const DeleteRequest *request,
        DeleteResponse */*response*/) {
    auto tox = std::find_if(begin(toxii_), end(toxii_), [&](const auto &t) {
        const auto addr{t.get_address()};
        const auto id = std::accumulate(begin(addr), end(addr), 0ULL);
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

} // namespace dokusei::grpc
