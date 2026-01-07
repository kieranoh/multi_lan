#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filePath = directory + "/" + filename;

    // Create the directory if it doesn't exist
    std::filesystem::create_directories(directory);

    // Open the file in write mode
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        // Write the content to the file
        outFile << content;
        outFile.close();

        // Set the file permissions to be accessible only by the current user
        std::filesystem::permissions(filePath, std::filesystem::perms::owner_read | std::filesystem::perms::owner_write, 
                                      std::filesystem::perm_options::replace);
    } else {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
    }
}