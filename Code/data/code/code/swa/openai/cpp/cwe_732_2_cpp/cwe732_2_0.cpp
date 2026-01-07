#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filePath = directory + "/" + filename;

    // Open the file for writing
    std::ofstream outfile(filePath);
    if (!outfile) {
        std::cerr << "Error creating file: " << filePath << std::endl;
        return;
    }

    // Write the content to the file
    outfile << content;
    outfile.close();

    // Set the file permissions to only allow the current user to access it
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Error setting file permissions for: " << filePath << std::endl;
    }
}