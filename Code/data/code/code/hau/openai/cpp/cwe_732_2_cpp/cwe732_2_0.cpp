#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full file path
    std::string filePath = directory + "/" + filename;

    // Open the file for writing
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        // Write content to the file
        outFile << content;
        outFile.close();

        // Set the file permissions so that only the owner can access it
        // S_IRUSR: owner can read, S_IWUSR: owner can write
        if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
            std::cerr << "Error setting file permissions." << std::endl;
        } else {
            std::cout << "Secrete file saved successfully!" << std::endl;
        }
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
    }
}