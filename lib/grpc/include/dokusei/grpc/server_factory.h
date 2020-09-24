#ifndef DOKUSEI_GRPC_SERVER_FACTORY_H
#define DOKUSEI_GRPC_SERVER_FACTORY_H

#include "dokusei/grpc/server.h"

#include <memory>
#include <string>

namespace dokusei::grpc {

class ServerFactory {
public:
    ServerFactory() = delete;
    [[nodiscard]] static std::unique_ptr<Server> create(std::string address);
};

} // namespace dokusei::grpc

#endif
