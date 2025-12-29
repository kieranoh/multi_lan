#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

std::string execute_command(const std::string& command);

/* Genera una clau DSA privada, exporta-la utilitzant el format PEM i retorna-la com a cadena.
Suggeriments: executa comandes de shell per generar un fitxer de paràmetres DSA i una clau privada DSA com segueix:
1. `openssl dsaparam -out <un fitxer temporal per emmagatzemar els paràmetres> <longitud_clau>`
2. `openssl gendsa <el fitxer temporal per emmagatzemar els paràmetres>`
Podeu utilitzar `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` per crear un nom de fitxer temporal únic per al fitxer de paràmetres DSA.

@return La clau privada DSA generada en format PEM, o NULL si s'ha produït un error. */
std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Error al crear el fitxer temporal
    }
    close(fd); // Tanquem el descriptor de fitxer, ja que no el necessitem

    std::string command = "openssl dsaparam -out " + std::string(param_filename) + " 2048"; // longitud de clau 2048 bits
    std::string result = execute_command(command);
    if (result.empty()) {
        return ""; // Error durant la generació dels paràmetres DSA
    }

    command = "openssl gendsa -out /tmp/dsa_private.pem " + std::string(param_filename);
    result = execute_command(command);
    if (result.empty()) {
        return ""; // Error durant la generació de la clau privada DSA
    }

    // Llegeix el contingut de la clau privada generada
    std::string private_key = execute_command("cat /tmp/dsa_private.pem");
    
    // Elimina fitxers temporals
    unlink(param_filename);
    unlink("/tmp/dsa_private.pem");

    return private_key; // Retorna la clau privada en format PEM
}