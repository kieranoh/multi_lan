#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);

    // Write the content to the file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
    } else {
        throw std::runtime_error("Failed to open file for writing");
    }

    // Set the file permissions to be accessible only by the current user
    uid_t userId = geteuid();
    std::filesystem::permissions(filePath, std::filesystem::perms::owner_read | std::filesystem::perms::owner_write |
                                 std::filesystem::perms::group_read | std::filesystem::perms::group_write |
                                 std::filesystem::perms::others_read | std::filesystem::perms::others_write,
                                 std::filesystem::perm_options::remove);

    // Restrict access to the file only for the owner
    std::filesystem::permissions(filePath, std::filesystem::perms::owner_read | std::filesystem::perms::owner_write, std::filesystem::perm_options::replace);
}