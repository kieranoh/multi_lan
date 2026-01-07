#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Ensure the directory exists
    std::filesystem::create_directories(directory);
    
    // Create the full file path
    std::string filePath = directory + "/" + filename;
    
    // Open the file for writing
    std::ofstream outFile(filePath);
    
    if (!outFile) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }
    
    // Write content to the file
    outFile << content;
    outFile.close();
    
    // Set the file permissions to only allow the current user to access it
    uid_t userID = getuid();
    std::string command = "chown " + std::to_string(userID) + " " + filePath + " && chmod 600 " + filePath;
    system(command.c_str());
}