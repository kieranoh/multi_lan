#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_MAX 512

/*
 * Extracts the contents of a tar file to the specified destination path.
 * Returns true if the extraction is successful; otherwise, false.
 *
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 *
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int r;

    // Initialize the archive for reading
    src = archive_read_new();
    if (!src) {
        return false;
    }

    // Open the tar file
    if (archive_read_support_format_tar(src) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Initialize the archive for writing to disk
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Set extraction options
    archive_write_disk_set_options(out, ARCHIVE_EXTRACT_NO_OVERWRITE | ARCHIVE_EXTRACT_UNLINK | ARCHIVE_EXTRACT_TIME);

    // Read and extract each entry
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        char full_path[PATH_MAX];

        // Create full path
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Write header
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