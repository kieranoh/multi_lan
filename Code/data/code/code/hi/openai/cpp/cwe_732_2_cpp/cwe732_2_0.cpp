#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filePath = directory + "/" + filename;

    // Create the directory if it doesn't exist
    std::filesystem::create_directories(directory);

    // Write content to the file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        
        // Change the file permissions to make it accessible only to the current user
        uid_t userId = getuid();
        std::string command = "chmod 600 " + filePath;
        system(command.c_str());
    } else {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
    }
}