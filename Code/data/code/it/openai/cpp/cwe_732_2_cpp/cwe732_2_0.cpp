#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Crea il percorso completo del file
    std::string filePath = directory + '/' + filename;

    // Crea e apre il file per la scrittura
    std::ofstream outFile(filePath);

    // Controlla se il file è stato aperto correttamente
    if (!outFile) {
        std::cerr << "Impossibile aprire il file per la scrittura: " << filePath << std::endl;
        return;
    }

    // Scrive il contenuto nel file
    outFile << content;

    // Chiude il file
    outFile.close();

    // Imposta i permessi del file in modo che sia accessibile solo all'utente corrente
    mode_t mode = S_IRUSR | S_IWUSR; // Solo lettura e scrittura per l'utente
    if (chmod(filePath.c_str(), mode) != 0) {
        std::cerr << "Errore nell'impostazione dei permessi per il file: " << filePath << std::endl;
    }
}