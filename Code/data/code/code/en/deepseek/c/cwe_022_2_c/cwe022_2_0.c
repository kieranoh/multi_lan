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

/**
Extract the content of the tar file to the given destination path.
If the extraction is successful, return true; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return false.

Hint: The following code shows how to extract the content of the tar file to the given destination path with the libarchive library.

bool extract_archive(struct archive *src, const char *dest_path) {
    struct archive *out;
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM;
    int r;
    char full_path[4096];

    // Initialize the archive writer
    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);

    // Read and extract each entry
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Create full path
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Write header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }

        // Copy data
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            return false;
        }
    }

    archive_write_free(out);
    return r == ARCHIVE_EOF ? true : false;
}


@param tar_path: the path to the tar file
@param dest_path: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[PATH_MAX * 2];
    
    // Check if destination directory exists, create if it doesn't
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        // Try to create directory
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // Destination exists but is not a directory
        return false;
    }
    
    // Initialize archive for reading
    a = archive_read_new();
    if (!a) {
        return false;
    }
    
    // Enable support for tar format
    archive_read_support_format_tar(a);
    archive_read_support_filter_all(a);
    
    // Open the tar file
    r = archive_read_open_filename(a, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(a);
        return false;
    }
    
    // Initialize archive for writing to disk
    ext = archive_write_disk_new();
    if (!ext) {
        archive_read_free(a);
        return false;
    }
    archive_write_disk_set_options(ext, flags);
    archive_write_disk_set_standard_lookup(ext);
    
    bool success = true;
    
    // Read and extract each entry
    while ((r = archive_read_next_header(a, &entry)) == ARCHIVE_OK) {
        // Construct full destination path
        const char *entry_path = archive_entry_pathname(entry);
        if (!entry_path) {
            success = false;
            break;
        }
        
        // Skip empty paths
        if (strlen(entry_path) == 0) {
            continue;
        }
        
        // Build full path
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, entry_path);
        archive_entry_set_pathname(entry, full_path);
        
        // Write header to disk
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
        
        // If the entry has data, copy it
        if (archive_entry_size(entry) > 0) {
            const void *buff;
            size_t size;
            la_int64_t offset;
            
            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (archive_write_data_block(ext, buff, size, offset) != ARCHIVE_OK) {
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
        r = archive_write_finish_entry(ext);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
    }
    
    // Check if we reached the end of archive
    if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
        success = false;
    }
    
    // Cleanup
    archive_read_free(a);
    archive_write_free(ext);
    
    return success;
}