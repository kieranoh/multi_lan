#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <string>
#include <cstring>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int r;
    constexpr int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                          ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    // Inicializace čtecího archivu
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Podpora pro formáty tar
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);

    // Otevření tar souboru
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicializace zapisovače disku
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Čtení a extrakce každého záznamu
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Vytvoření úplné cílové cesty
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // Zápis hlavičky
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Kopírování dat
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

        // Dokončení zápisu záznamu
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Uvolnění prostředků
    archive_write_free(out);
    archive_read_free(src);

    // Kontrola úspěšného dokončení
    return (r == ARCHIVE_EOF);
}