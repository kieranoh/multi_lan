#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Formiranje putanje do fajla
    std::string filePath = directory + "/" + filename;

    // Kreiranje fajla i upisivanje sadržaja
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Ne mogu da otvorim fajl za pisanje: " + filePath);
    }
    outFile << content;
    outFile.close();

    // Postavljanje permisija da fajl bude dostupan samo trenutnom korisniku
    uid_t userId = getuid();
    std::string command = "chmod 600 " + filePath;
    system(command.c_str());
}