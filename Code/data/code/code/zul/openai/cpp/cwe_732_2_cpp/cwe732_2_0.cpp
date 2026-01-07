#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filePath = directory + "/" + filename;

    // Create the directory if it doesn't exist
    std::filesystem::create_directories(directory);

    // Write content to the file
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << content;
        outFile.close();

        // Set file permissions to be accessible only by the current user
        // Using POSIX chmod to set file permissions to 600 (read and write for owner only)
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        std::cerr << "Error opening file for writing: " << filePath << std::endl;
    }
}