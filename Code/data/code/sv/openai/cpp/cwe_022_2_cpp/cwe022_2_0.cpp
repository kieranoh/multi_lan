#include <archive.h>
#include <archive_entry.h>
#include <string>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    struct archive *out = archive_write_disk_new();
    struct archive_entry *entry;
    
    if (!src || !out) {
        return false;
    }

    // Öppna tar-filen för läsning
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // Sätt diskoptions
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(out, flags);

    // Läs och extrahera varje post
    int r;
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Skapa fullständig sökväg
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // Skriv rubrik
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Kopiera data
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
    }

    archive_read_free(src);
    archive_write_free(out);
    return (r == ARCHIVE_EOF);
}