#include "dokusei/toxxx/tox.h"

#include <tox/tox.h>

#include <exception>
#include <sstream>
#include <utility>

namespace dokusei::toxxx {
namespace {

Tox_Savedata_Type into(Savedata::Type type) {
    switch (type) {
        case Savedata::Type::None: return TOX_SAVEDATA_TYPE_NONE;
        case Savedata::Type::ToxSave: return TOX_SAVEDATA_TYPE_TOX_SAVE;
        case Savedata::Type::SecretKey: return TOX_SAVEDATA_TYPE_SECRET_KEY;
        default: std::terminate();
    }
}

} // namespace

std::string toxcore_version() {
    std::stringstream ss;
    ss << tox_version_major() << "." << tox_version_minor() << "." << tox_version_patch();
    return ss.str();
}

static_assert(kAddressSize == TOX_ADDRESS_SIZE);

Toxxx::Toxxx(Savedata const &savedata) : tox_{[&savedata] {
    auto *const tox_options{tox_options_new(nullptr)};
    tox_options_set_savedata_type(tox_options, into(savedata.type));
    tox_options_set_savedata_data(tox_options, savedata.data.data(), savedata.data.size());
    auto *const tox{tox_new(tox_options, nullptr)};
    tox_options_free(tox_options);
    return tox;
}()} {}

Toxxx::~Toxxx() {
    if (tox_ != nullptr) tox_kill(tox_);
}

Toxxx::Toxxx(Toxxx &&o) noexcept : tox_{std::exchange(o.tox_, tox_new(nullptr, nullptr))} {
}

Toxxx &Toxxx::operator=(Toxxx &&o) noexcept {
    tox_ = std::exchange(o.tox_, tox_);
    return *this;
}

std::array<uint8_t, kAddressSize> Toxxx::get_address() const {
    std::array<uint8_t, kAddressSize> addr{};
    tox_self_get_address(tox_, addr.data());
    return addr;
}

std::vector<std::uint8_t> Toxxx::get_savedata() const {
    std::vector<std::uint8_t> savedata;
    savedata.resize(tox_get_savedata_size(tox_));
    tox_get_savedata(tox_, savedata.data());
    return savedata;
}

} // namespace dokusei::toxxx
