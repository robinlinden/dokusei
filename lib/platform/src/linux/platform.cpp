#include "dokusei/platform/platform.h"

#include <signal.h>

#include <map>
#include <utility>

namespace dokusei::platform {
namespace {

std::map<int, std::function<void()>> signal_handlers{};

void signal_handler(int signal) {
    if (!signal_handlers.contains(signal)) {
        return;
    }

    signal_handlers.at(signal)();
}

} // namespace

void set_ctrl_c_handler(std::function<void()> handler) {
    signal_handlers[SIGINT] = std::move(handler);
    struct sigaction a;

    a.sa_handler = signal_handler;
    a.sa_flags = 0;
    sigaction(SIGINT, &a, NULL);
}

} // namespace dokusei::platform
