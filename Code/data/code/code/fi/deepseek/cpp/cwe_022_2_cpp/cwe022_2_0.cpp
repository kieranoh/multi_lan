#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <cstdio>

/**
 * Purkaa tar-tiedoston sisältö annettuun kohdepolkuun. 
 * Jos purku onnistuu, palauta true; muuten, jos purkuprosessin aikana tapahtuu virhe 
 * (esim. tiedostoa ei löydy, käyttöoikeusvirhe, ei voida purkaa kaikkea sisältöä), 
 * palauta vain false.
 * 
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int r;
    const int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                      ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    // Alusta lukuarkisto
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Alusta arkistokirjoittaja
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Avaa tar-tiedosto
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // Lue ja pura jokainen merkintä
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Luo täydellinen polku
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // Kirjoita otsikko
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Kopioi data
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
        
        // Viimeistele merkinnän kirjoitus
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }

    // Siivous
    archive_read_free(src);
    archive_write_free(out);

    // Tarkista lopputila
    return (r == ARCHIVE_EOF) ? true : false;
}