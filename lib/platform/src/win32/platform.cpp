#include "dokusei/platform/platform.h"

#include <windows.h>

#include <map>
#include <utility>

namespace dokusei::platform {
namespace {

std::map<DWORD, std::function<void()>> ctrl_handlers{};

BOOL WINAPI ctrl_handler(DWORD ctrl_type) {
    if (!ctrl_handlers.contains(ctrl_type)) {
        return FALSE;
    }

    ctrl_handlers.at(ctrl_type)();
    return TRUE;
}

} // namespace

void set_ctrl_c_handler(std::function<void()> handler) {
    ctrl_handlers[CTRL_C_EVENT] = std::move(handler);
    SetConsoleCtrlHandler(ctrl_handler, TRUE);
}

} // namespace dokusei::platform
