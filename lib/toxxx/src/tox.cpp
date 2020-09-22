#include "dokusei/toxxx/tox.h"

#include <tox/tox.h>

#include <sstream>

namespace dokusei::toxxx {

std::string toxcore_version() {
    std::stringstream ss;
    ss << tox_version_major() << "." << tox_version_minor() << "." << tox_version_patch();
    return ss.str();
}

static_assert(kAddressSize == TOX_ADDRESS_SIZE);

Toxxx::Toxxx() : tox_{[] {
    auto *const tox_options{tox_options_new(nullptr)};
    auto *const tox{tox_new(tox_options, nullptr)};
    return tox;
}()} {}

Toxxx::~Toxxx() {
    if (tox_ != nullptr) tox_kill(tox_);
}

Toxxx::Toxxx(Toxxx &&o) noexcept : tox_{o.tox_} {
    o.tox_ = nullptr;
}

Toxxx &Toxxx::operator=(Toxxx &&o) noexcept {
    tox_ = std::exchange(o.tox_, nullptr);
    return *this;
}

std::array<uint8_t, kAddressSize> Toxxx::get_address() const {
    std::array<uint8_t, kAddressSize> addr{};
    tox_self_get_address(tox_, addr.data());
    return addr;
}

} // namespace dokusei::toxxx
