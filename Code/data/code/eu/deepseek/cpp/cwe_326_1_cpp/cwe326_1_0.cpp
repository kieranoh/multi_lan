#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>

std::string create_dsa_key() {
    // DSA parametroen fitxategi temporala sortu
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd); // mkstemp-ek fitxategia irekitzen du, baina ez dugu behar

    // DSA gako pribatuaren fitxategi temporala sortu
    char key_filename[] = "/tmp/dsa_key_XXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);
        return "";
    }
    close(fd);

    // 1. DSA parametroak sortu (2048 biteko luzera)
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    std::string param_output = execute_command(param_command);
    
    // Aginduaren errorea egiaztatu (execute_command-k huts egiten badu, string hutsa itzultzen du)
    if (param_output.empty()) {
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }

    // 2. DSA gako pribatua sortu parametroetatik
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string key_output = execute_command(key_command);
    
    // Gakoa fitxategi temporalean gorde
    if (key_output.empty()) {
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }

    // Gakoaren edukia fitxategian idatzi
    FILE* key_file = fopen(key_filename, "w");
    if (!key_file) {
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }
    fwrite(key_output.c_str(), 1, key_output.size(), key_file);
    fclose(key_file);

    // 3. Gakoa PEM formatuan irakurri
    std::string read_command = "cat " + std::string(key_filename);
    std::string pem_key = execute_command(read_command);

    // Fitxategi temporalak ezabatu
    unlink(param_filename);
    unlink(key_filename);

    // PEM gakoa hutsa bada, errorea
    if (pem_key.empty()) {
        return "";
    }

    return pem_key;
}