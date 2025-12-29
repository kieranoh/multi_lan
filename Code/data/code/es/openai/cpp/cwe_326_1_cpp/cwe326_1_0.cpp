#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Crear un nombre de archivo temporal para almacenar parámetros DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Retorna una cadena vacía en caso de error
    }
    close(fd); // Cerramos el descriptor de archivo, ya que no lo necesitamos más

    // Longitud de clave DSA (ejemplo: 2048)
    const std::string key_length = "2048";

    // Comando para generar parámetros DSA
    std::string command1 = "openssl dsaparam -out " + std::string(param_filename) + " " + key_length;
    if (execute_command(command1) != "") {
        // Comando para generar clave privada DSA
        std::string command2 = "openssl gendsa -out /tmp/dsa_private_key.pem " + std::string(param_filename);
        if (execute_command(command2) != "") {
            // Leer la clave privada DSA desde el archivo generado
            std::string private_key = execute_command("cat /tmp/dsa_private_key.pem");
            // Limpiar el archivo temporal de parámetros y la clave privada
            unlink(param_filename);
            unlink("/tmp/dsa_private_key.pem");
            return private_key; // Retornar la clave privada DSA en formato PEM
        }
    }

    // Limpiar en caso de error
    unlink(param_filename);
    return ""; // Retorna cadena vacía si ocurrió un error
}