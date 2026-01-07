#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filepath = directory + "/" + filename;

    // Save the content to the file
    std::ofstream outFile(filepath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filepath << std::endl;
        return;
    }

    // Change the file permissions to make it accessible only to the current user
    uid_t userId = getuid();
    if (chown(filepath.c_str(), userId, -1) != 0) {
        std::cerr << "Failed to change file ownership: " << filepath << std::endl;
        return;
    }

    // Set file permissions to 600 (read and write for owner only)
    if (chmod(filepath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Failed to set file permissions: " << filepath << std::endl;
    }
}