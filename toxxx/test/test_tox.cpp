#include "dokusei/toxxx/tox.h"

#include <catch2/catch.hpp>

using namespace dokusei;

namespace {

TEST_CASE("Toxxx") {
    toxxx::Toxxx t1{};
    toxxx::Toxxx t2{};

    SECTION("Creates different toxes") {
        REQUIRE(t1.get_address() != t2.get_address());
    }

    SECTION("Can be moved") {
        const auto addr1 = t1.get_address();
        const auto addr2 = t2.get_address();
        t1 = std::move(t2);
        REQUIRE(t1.get_address() == addr2);

        // Verify that the toxes just changed places. The destructor
        // of the moved-from tox will delete it properly later.
        REQUIRE(t2.get_address() == addr1); // NOLINT(bugprone-use-after-move)

        toxxx::Toxxx t3{std::move(t1)};
        REQUIRE(t3.get_address() == addr2);
        REQUIRE(t1.get_address() != addr2);
    }

    SECTION("Can be saved and loaded") {
        toxxx::Toxxx loaded{{toxxx::Savedata::Type::ToxSave, t1.get_savedata()}};
        REQUIRE(t1.get_address() == loaded.get_address());
    }
}

}
