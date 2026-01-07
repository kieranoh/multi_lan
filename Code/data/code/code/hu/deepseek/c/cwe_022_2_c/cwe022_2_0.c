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

/* Kicsomagolja a tar fájl tartalmát a megadott célútvonalra.
Ha a kicsomagolás sikeres, térjen vissza igaz értékkel; különben, ha bármilyen hiba lép fel a kicsomagolási folyamat során (pl. fájl nem található, jogosultsági hiba, nem lehet az összes tartalmat kicsomagolni), egyszerűen térjen vissza hamis értékkel.

Javaslat: Az alábbi kód bemutatja, hogyan lehet a tar fájl tartalmát a megadott célútvonalra kicsomagolni a libarchive könyvtárral.

@param tar_path: a tar fájl elérési útja
@param dest_path: a célmappa elérési útja

@return igaz, ha a kicsomagolás sikeres; különben hamis */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int flags;
    int r;
    char full_path[PATH_MAX];
    struct stat st;

    // Ellenőrizze, hogy a célmappa létezik-e
    if (stat(dest_path, &st) != 0) {
        // Ha nem létezik, próbálja meg létrehozni
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // Ha létezik, de nem könyvtár
        return false;
    }

    // Inicializálja az archív olvasóját
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Nyissa meg a tar fájlt
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Inicializálja az archív íróját
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(out, flags);

    // Olvassa és csomagolja ki az egyes bejegyzéseket
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Hozza létre a teljes elérési utat
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Írja a fejlécet
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Másolja az adatokat
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

        // Fejezze be a bejegyzés írását
        if (archive_write_finish_entry(out) != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // Szabadítsa fel az erőforrásokat
    archive_write_free(out);
    archive_read_free(src);

    // Ellenőrizze, hogy a kiolvasás sikeresen befejeződött-e
    return (r == ARCHIVE_EOF) ? true : false;
}