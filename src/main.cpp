#include <tox/tox.h>

#include <iostream>

int main() {
    std::cout << "Linked against Tox "
            << tox_version_major() << "."
            << tox_version_minor() << "."
            << tox_version_patch() << ".";
}
