#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Primer, assegurar que el directori existeix
    struct stat dirStat;
    if (stat(directory.c_str(), &dirStat) != 0) {
        // El directori no existeix, intentar crear-lo
        if (mkdir(directory.c_str(), 0700) != 0) {
            std::cerr << "Error: No es pot crear el directori '" << directory << "'" << std::endl;
            return;
        }
    } else if (!S_ISDIR(dirStat.st_mode)) {
        std::cerr << "Error: '" << directory << "' no és un directori" << std::endl;
        return;
    }

    // Construir el camí complet del fitxer
    std::string fullPath = directory + "/" + filename;

    // Obrir el fitxer amb permisos restringits (només propietari pot llegir i escriure)
    int fd = open(fullPath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        std::cerr << "Error: No es pot obrir o crear el fitxer '" << fullPath << "'" << std::endl;
        return;
    }

    // Escriure el contingut al fitxer
    ssize_t bytesWritten = write(fd, content.c_str(), content.size());
    if (bytesWritten == -1) {
        std::cerr << "Error: No es pot escriure al fitxer '" << fullPath << "'" << std::endl;
        close(fd);
        return;
    }

    // Tancar el fitxer
    close(fd);

    // Verificar que els permisos són correctes (opcional, però bo per a seguretat extra)
    if (chmod(fullPath.c_str(), 0600) != 0) {
        std::cerr << "Advertència: No s'han pogut ajustar els permisos del fitxer '" << fullPath << "'" << std::endl;
    }
}