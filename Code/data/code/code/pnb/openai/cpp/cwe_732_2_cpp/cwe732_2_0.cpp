#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string fullPath = directory + "/" + filename;

    // Create and open the file for writing
    std::ofstream outFile(fullPath);
    
    // Check if the file is opened successfully
    if (!outFile) {
        std::cerr << "Error: Unable to create file " << fullPath << std::endl;
        return;
    }

    // Write the content to the file
    outFile << content;
    outFile.close();

    // Change the permissions of the file to be user-only accessible
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Error: Unable to set file permissions for " << fullPath << std::endl;
    }
}