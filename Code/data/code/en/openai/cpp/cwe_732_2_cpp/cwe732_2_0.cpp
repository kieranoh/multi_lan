#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the file
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);

    // Write content to the file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();

        // Change the file permissions to allow only the owner to read/write
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    }
}