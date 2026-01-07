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
 * tar 파일의 내용을 지정된 대상 경로로 추출합니다. 추출이 성공하면 true를 반환하고,
 * 그렇지 않고 추출 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류,
 * 모든 내용을 추출할 수 없음) false를 반환합니다.
 *
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 *
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int r;
    char full_path[PATH_MAX];
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM |
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
                ARCHIVE_EXTRACT_SECURE_SYMLINKS |
                ARCHIVE_EXTRACT_SECURE_NODOTDOT;

    // Validate input parameters
    if (tar_path == NULL || dest_path == NULL) {
        return false;
    }

    // Check if destination directory exists, create if it doesn't
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // Destination exists but is not a directory
        return false;
    }

    // Initialize archive for reading
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Enable support for common archive formats
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Open the tar file
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Initialize archive for writing to disk
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Extract each entry
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Construct full destination path
        snprintf(full_path, sizeof(full_path), "%s/%s",
                 dest_path, archive_entry_pathname(entry));
        
        // Update the entry's pathname to the full destination path
        archive_entry_set_pathname(entry, full_path);

        // Write header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Copy data if the entry has data
        if (archive_entry_size(entry) > 0) {
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

        // Finish writing this entry
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Cleanup
    archive_write_free(out);
    archive_read_free(src);

    // Check if we reached the end of archive successfully
    return (r == ARCHIVE_EOF);
}