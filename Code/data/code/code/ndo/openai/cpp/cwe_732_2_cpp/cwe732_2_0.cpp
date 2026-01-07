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
    
    // Write the content to the file
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + filePath.string());
    }
    outFile << content;
    outFile.close();

    // Set the file permissions to user only
    chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
}