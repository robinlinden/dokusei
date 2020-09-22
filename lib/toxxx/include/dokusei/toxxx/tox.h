#ifndef DOKUSEI_TOXXX_TOX_H
#define DOKUSEI_TOXXX_TOX_H

#include <array>
#include <cstdint>
#include <string>

struct Tox;

namespace dokusei::toxxx {

std::string toxcore_version();

constexpr auto kAddressSize = 38;

class Toxxx {
public:
    Toxxx();
    ~Toxxx();
    Toxxx(Toxxx &&) noexcept;
    Toxxx &operator=(Toxxx &&) noexcept;

    [[nodiscard]] std::array<uint8_t, kAddressSize> get_address() const;

private:
    ::Tox *tox_;
};

} // namespace dokusei::toxxx

#endif
