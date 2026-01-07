#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <cstring>
#include <string>

/**
 * @brief Extracts the contents of a tar file to the given destination path.
 * 
 * @param tar_path The path to the tar file.
 * @param dest_path The path to the destination folder.
 * @return true if the extraction is successful; otherwise, false.
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;

    // Initialize archive reader
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);

    // Initialize archive writer for disk extraction
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Open the tar file
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // Extract each entry
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Construct full destination path
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // Write header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Copy data
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_read_free(src);
                archive_write_free(out);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Finish writing entry
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }

    // Cleanup
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);

    return r == ARCHIVE_EOF;
}