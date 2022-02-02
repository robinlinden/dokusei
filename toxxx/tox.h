#ifndef DOKUSEI_TOXXX_TOX_H
#define DOKUSEI_TOXXX_TOX_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct Tox;

namespace dokusei::toxxx {

std::string toxcore_version();

constexpr auto kAddressSize = 38;

struct Savedata {
    enum class Type {
        None,
        ToxSave,
        SecretKey,
    };

    Type type{Type::None};
    std::vector<std::uint8_t> data{};
};

class Toxxx {
public:
    Toxxx(Savedata const & = {});
    ~Toxxx();
    Toxxx(Toxxx &&) noexcept;
    Toxxx &operator=(Toxxx &&) noexcept;

    [[nodiscard]] std::array<uint8_t, kAddressSize> get_address() const;
    [[nodiscard]] std::vector<std::uint8_t> get_savedata() const;

private:
    ::Tox *tox_;
};

} // namespace dokusei::toxxx

#endif
