#ifndef DOKUSEI_GRPC_SERVER_H
#define DOKUSEI_GRPC_SERVER_H

namespace dokusei::grpc {

class Server {
public:
    virtual ~Server() = default;

    // Perform a blocking wait until shutdown is called on the server.
    virtual void wait() = 0;

    // Shut the server down.
    virtual void shutdown() = 0;
};

} // namespace dokusei::grpc

#endif
