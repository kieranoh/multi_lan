#include <archive.h>
#include <archive_entry.h>
#include <string>

/**
 * Extracts the contents of a tar file to the specified destination path.
 * 
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 * 
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    struct archive *out = archive_write_disk_new();
    struct archive_entry *entry;
    int r;
    char full_path[1024];

    // Open the tar file for reading
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        return false;
    }

    // Initialize the archive writer
    if (!out) {
        archive_read_free(src);
        return false;
    }

    archive_write_disk_set_options(out, ARCHIVE_EXTRACT_NO_TRUNC);

    // Read each entry and extract
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Create full path
        snprintf(full_path, sizeof(full_path), "%s/%s",
                 dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Write the header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copy data
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                archive_read_free(src);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    archive_write_free(out);
    archive_read_free(src);
    return r == ARCHIVE_EOF ? true : false;
}