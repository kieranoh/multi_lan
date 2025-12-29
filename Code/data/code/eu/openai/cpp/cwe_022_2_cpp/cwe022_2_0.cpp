#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstdio>

/**
 * Tarte fitxategiaren edukia emandako helmuga bidean ateratzeko. Ateratzea arrakastatsua bada, itzuli egia; bestela, ateratze prozesuan errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea, ez da edukirik ateratzen), itzuli faltsua.
 *
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    struct archive *out = archive_write_disk_new();
    struct archive_entry *entry;
    int r;

    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    archive_write_disk_set_options(out, 0);
    
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

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
    return r == ARCHIVE_EOF;
}