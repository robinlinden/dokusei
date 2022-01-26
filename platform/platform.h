#ifndef DOKUSEI_PLATFORM_PLATFORM_H
#define DOKUSEI_PLATFORM_PLATFORM_H

#include <functional>

namespace dokusei::platform {

void set_ctrl_c_handler(std::function<void()> handler);

} // namespace dokusei::platform

#endif
