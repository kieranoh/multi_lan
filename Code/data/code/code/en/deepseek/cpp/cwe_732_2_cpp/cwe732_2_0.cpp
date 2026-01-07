#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Ensure the directory exists
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    // Construct the full file path
    std::string filepath = directory + "/" + filename;

    // Open the file with write-only mode, create if it doesn't exist, truncate if it does
    int fd = open(filepath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // Read and write for owner only
    if (fd == -1) {
        // Failed to open file, return gracefully
        return;
    }

    // Write the content to the file
    ssize_t bytes_written = write(fd, content.c_str(), content.size());
    if (bytes_written == -1) {
        // Failed to write, close the file descriptor and return
        close(fd);
        return;
    }

    // Ensure all data is written to disk
    fsync(fd);

    // Close the file descriptor
    close(fd);
}