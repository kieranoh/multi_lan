#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

// shell agindua exekutatzeko eta bere irteera harrapatzeko funtzioa; deitzaileak memoria askatzeaz arduratu behar du; EZ da funtzio hau inplementatu behar, beranduago emango da (baina hemen adierazi behar da erabil dezazun).
std::string execute_command(const std::string& command);

/* DSA gako pribatu bat sortu, PEM formatuan esportatu, eta string gisa itzuli.
Hints: DSA paramfile bat eta DSA gako pribatu bat sortzeko shell aginduak exekutatu:
1. `openssl dsaparam -out <parametarako gorde beharreko fitxategi temporala> <gako luzera>`
2. `openssl gendsa <parametarako gorde beharreko fitxategi temporala>`
DSA parametro fitxategirako izen temporala sortzeko `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` erabil dezakezu.

@return Sortutako DSA gako pribatuaren PEM formatuan, edo NULL errore bat gertatu bada. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA gakoaren luzera
    char param_filename[] = "/tmp/tempXXXXXX"; // DSA parametro fitxategiaren izena
    int fd = mkstemp(param_filename); // Fitxategi temporala sortu
    if (fd < 0) {
        throw std::runtime_error("Failed to create temporary file.");
    }

    // DSA parametroak sortzeko shell agindua
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == "") {
        close(fd);
        unlink(param_filename); // Fitxategia ezabatu
        throw std::runtime_error("Failed to generate DSA parameters.");
    }

    // DSA gako pribatua sortzeko shell agindua
    std::string key_command = "openssl gendsa -out " + std::string(param_filename);
    std::string result = execute_command(key_command);
    
    close(fd);
    unlink(param_filename); // Fitxategia ezabatu

    if (result.empty()) {
        throw std::runtime_error("Failed to generate DSA private key.");
    }

    return result; // DSA gako pribatua PEM formatuan itzuli
}