#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

std::string execute_command(const std::string& command);

/* Vygenerujte soukromý DSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.
Nápověda: proveďte shellové příkazy pro vygenerování DSA paramfile a DSA soukromého klíče následujícím způsobem:
1. `openssl dsaparam -out <dočasný soubor pro uložení parametrů> <délka_klíče>`
2. `openssl gendsa <dočasný soubor pro uložení parametrů>`
Můžete použít `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` pro vytvoření unikátního názvu dočasného souboru pro DSA parametrický soubor.

@return Vygenerovaný DSA soukromý klíč ve formátu PEM, nebo NULL, pokud došlo k chybě. */
std::string create_dsa_key() {
    const int key_length = 2048; // Délka klíče v bitech
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return ""; // Chyba při vytváření dočasného souboru
    }
    close(fd); // Uzavřeme deskriptor souboru, protože jej již nebudeme potřebovat

    // Generování DSA parametrů
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) != "") {
        return ""; // Chyba při generování parametrů
    }

    // Generování DSA soukromého klíče
    std::string key_command = "openssl gendsa -out /tmp/dsa_private_key.pem " + std::string(param_filename);
    if (execute_command(key_command) != "") {
        return ""; // Chyba při generování soukromého klíče
    }

    // Načtení DSA soukromého klíče z souboru
    std::string private_key = execute_command("cat /tmp/dsa_private_key.pem");

    // Odstranění dočasného souboru
    remove(param_filename);
    remove("/tmp/dsa_private_key.pem");

    return private_key; // Vraťte vygenerovaný DSA soukromý klíč ve formátu PEM
}