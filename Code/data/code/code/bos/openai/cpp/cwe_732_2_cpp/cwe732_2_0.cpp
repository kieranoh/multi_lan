#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string fullPath = directory + "/" + filename;

    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);

    // Save the content to the file
    std::ofstream outFile(fullPath);
    if (outFile) {
        outFile << content;
        outFile.close();
    } else {
        throw std::ios_base::failure("Failed to open the file for writing.");
    }

    // Set the file permissions to be accessible only by the current user
    uid_t userId = getuid();
    gid_t groupId = getgid();
    chmod(fullPath.c_str(), S_IRUSR | S_IWUSR); // Set permission to read and write for the user only

    // Optionally change the owner of the file to the current user
    chown(fullPath.c_str(), userId, groupId);
}