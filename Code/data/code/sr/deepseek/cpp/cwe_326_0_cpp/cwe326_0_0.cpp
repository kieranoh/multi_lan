#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Postavljamo dužinu ključa na 2048 bita (standardna vrednost za RSA)
    const int key_length = 2048;
    
    // Formiramo komandu za generisanje privatnog RSA ključa
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Otvaramo pipe za čitanje izlaza iz komande
    std::array<char, 128> buffer;
    std::string result;
    
    // Koristimo unique_ptr sa custom deleterom za automatsko zatvaranje FILE*
    auto pipe_deleter = [](FILE* f) { if (f) pclose(f); };
    std::unique_ptr<FILE, decltype(pipe_deleter)> pipe(popen(command.c_str(), "r"), pipe_deleter);
    
    // Proveravamo da li je pipe uspešno otvoren
    if (!pipe) {
        return "";  // Vraćamo prazan string umesto NULL jer je povratni tip std::string
    }
    
    // Čitamo izlaz iz komande
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Proveravamo da li je rezultat prazan (greška u generisanju)
    if (result.empty()) {
        return "";
    }
    
    return result;
}