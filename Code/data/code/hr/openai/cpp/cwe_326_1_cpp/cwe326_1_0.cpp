#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

/* Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
   @return Generirani DSA privatni ključ u PEM formatu, ili NULL ako je došlo do pogreške. */
std::string create_dsa_key() {
    // Kreirajte privremenu datoteku za pohranu DSA parametara
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Neuspjeh u stvaranju privremene datoteke
    }
    close(fd);

    // Navodimo dužinu ključa
    const int key_length = 2048; // ili bilo koja druga podržana dužina

    // Koristimo openssl za generisanje DSA parametara
    std::string command1 = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command1) != "") {
        return ""; // Greška u generisanju DSA parametara
    }

    // Generišemo DSA privatni ključ
    std::string command2 = "openssl gendsa -out " + std::string(param_filename) + " " + std::string(param_filename);
    std::string result = execute_command(command2);
    
    // Oslobađanje privremene datoteke
    unlink(param_filename);

    return result; // Vraćamo generirani DSA privatni ključ u PEM formatu
}