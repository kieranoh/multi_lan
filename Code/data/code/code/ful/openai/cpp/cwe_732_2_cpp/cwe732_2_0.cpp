#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filePath = directory + "/" + filename;

    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);

    // Open the file for writing
    std::ofstream outFile(filePath);
    
    // Check if the file is successfully opened
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + filePath);
    }

    // Write content to the file
    outFile << content;
    outFile.close();

    // Set file permissions to be readable and writable only by the owner
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Unable to set file permissions: " + filePath);
    }
}