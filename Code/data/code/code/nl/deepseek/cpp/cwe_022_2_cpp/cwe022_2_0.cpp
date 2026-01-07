#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <sys/stat.h>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive* src = nullptr;
    struct archive* out = nullptr;
    struct archive_entry* entry = nullptr;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[4096];

    // Open source archive
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Support common tar formats
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Open the tar file
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Initialize disk writer
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Create destination directory if it doesn't exist
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        if (mkdir(dest_path.c_str(), 0755) != 0 && errno != EEXIST) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Read and extract each entry
    bool success = true;
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Construct full destination path
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Write header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }

        // Copy data if the entry has content
        if (archive_entry_size(entry) > 0) {
            const void* buff;
            size_t size;
            la_int64_t offset;
            
            while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                    success = false;
                    break;
                }
            }
            
            if (r != ARCHIVE_EOF) {
                success = false;
                break;
            }
        }

        // Finish writing this entry
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
    }

    // Check if we exited the loop due to EOF (success) or error
    if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
        success = false;
    }

    // Cleanup
    archive_write_free(out);
    archive_read_free(src);
    
    return success;
}