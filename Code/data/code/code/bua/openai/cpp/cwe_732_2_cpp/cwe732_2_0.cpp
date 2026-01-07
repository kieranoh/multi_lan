#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);

    // Open the file for writing
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Failed to create file: " + filePath.string());
    }

    // Write the content to the file
    outFile << content;
    outFile.close();

    // Set the file permissions to be accessible only by the owner
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Failed to set file permissions for: " + filePath.string());
    }
}