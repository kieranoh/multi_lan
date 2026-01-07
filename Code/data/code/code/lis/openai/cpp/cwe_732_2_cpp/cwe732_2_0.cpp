#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);
    
    // Construct the full file path
    std::string filepath = directory + "/" + filename;

    // Open the file in write mode
    std::ofstream file(filepath);
    if (!file) {
        throw std::ios_base::failure("Failed to open the file for writing.");
    }

    // Write the content to the file
    file << content;
    file.close();

    // Set the file permissions to be accessible only by the user
    mode_t mode = S_IRUSR | S_IWUSR; // Read and write permissions for the owner only
    if (chmod(filepath.c_str(), mode) != 0) {
        throw std::runtime_error("Failed to change file permissions.");
    }
}