#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string fullPath = directory + "/" + filename;

    // Open the file for writing
    std::ofstream outFile(fullPath);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << fullPath << std::endl;
        return;
    }

    // Write content to the file
    outFile << content;
    outFile.close();

    // Change file permissions to make it accessible only to the owner
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Error setting file permissions for: " << fullPath << std::endl;
    }
}