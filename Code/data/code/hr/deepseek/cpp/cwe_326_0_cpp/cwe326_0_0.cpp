#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Koristimo 2048-bitni RSA ključ kao standardnu sigurnu duljinu
    const int key_length = 2048;
    
    // Konstruiramo naredbu za generiranje privatnog RSA ključa
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Otvaramo pipe za čitanje izlaza iz naredbe
    std::array<char, 128> buffer;
    std::string result;
    
    // Koristimo unique_ptr za automatsko zatvaranje FILE* pokazivača
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Neuspješno otvaranje pipe-a
        return "";
    }
    
    // Čitamo izlaz iz naredbe
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Provjeravamo je li rezultat prazan (došlo je do pogreške)
    if (result.empty()) {
        return "";
    }
    
    return result;
}