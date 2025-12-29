#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdio>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    std::array<char, 128> buffer;
    std::string result;

    // Exekutatu agindua eta irakurtzen hasi
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Ezin da pipe-a irekitu");
    }

    // Irakurri agindua exekutatu ondoren
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Egiaztatu emaitza hutsik den
    if (result.empty()) {
        return nullptr; // Errorea gertatu da
    }

    return result; // PEM formatuan RSA gako pribatua
}