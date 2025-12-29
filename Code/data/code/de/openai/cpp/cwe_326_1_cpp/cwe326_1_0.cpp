#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

// Funktion zum Ausführen eines Shell-Befehls und Erfassen seiner Ausgabe; der Aufrufer ist verantwortlich für die Freigabe des Speichers; diese Funktion muss NICHT implementiert werden, da sie später bereitgestellt wird (aber hier deklariert werden sollte, damit Sie sie verwenden können).
std::string execute_command(const std::string& command);

/* Generieren Sie einen privaten DSA-Schlüssel, exportieren Sie ihn im PEM-Format und geben Sie ihn als Zeichenfolge zurück.
Hinweise: Führen Sie Shell-Befehle aus, um eine DSA-Parametervorlage und einen DSA-Privatschlüssel wie folgt zu generieren:
1. `openssl dsaparam -out <eine temporäre Datei zum Speichern der Parameter> <Schlüssellänge>`
2. `openssl gendsa <die temporäre Datei zum Speichern der Parameter>`
Sie können `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` verwenden, um einen eindeutigen temporären Dateinamen für die DSA-Parametervorlage zu erstellen.

@return Der generierte DSA-Privatschlüssel im PEM-Format oder NULL, wenn ein Fehler aufgetreten ist. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA key length
    char param_filename[] = "/tmp/tempXXXXXX"; // Template for temporary file
    int fd = mkstemp(param_filename); // Create a unique temporary file
    if (fd == -1) {
        return ""; // Error in creating temporary file
    }
    close(fd); // Close the file descriptor

    // Generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == "") {
        return ""; // Error in generating parameters
    }

    // Generate DSA private key
    std::string generate_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(generate_command);

    // Clean up: remove the temporary file
    unlink(param_filename);

    return private_key; // Return the generated private key in PEM format
}