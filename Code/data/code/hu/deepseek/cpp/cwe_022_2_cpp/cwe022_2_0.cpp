#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <memory>

/**
 * Kicsomagolja a tar fájl tartalmát a megadott célútvonalra.
 * Ha a kicsomagolás sikeres, térjen vissza true; különben, ha bármilyen hiba lép fel
 * a kicsomagolási folyamat során (pl. fájl nem található, jogosultsági hiba,
 * nem lehet az összes tartalmat kicsomagolni), csak térjen vissza false.
 * 
 * @param tar_path: a tar fájl elérési útja
 * @param dest_path: a célmappa elérési útja
 * @return true, ha a kicsomagolás sikeres; különben false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    // Ellenőrizze, hogy a célmappa létezik-e, és ha nem, hozza létre
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        // A mappa nem létezik, próbálja meg létrehozni
        if (mkdir(dest_path.c_str(), 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // A cél elérési út nem mappa
        return false;
    }

    // Inicializálja az archívum olvasóját
    struct archive* src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Állítsa be az olvasó formátumot és szűrőket
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Nyissa meg az archívumot
    int r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Inicializálja az archívum íróját
    struct archive* out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // Állítsa be az író beállításait
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
                ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    struct archive_entry* entry;
    bool success = true;
    
    // Olvassa és csomagolja ki az egyes bejegyzéseket
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Hozza létre a teljes elérési utat
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        
        // Írja a fejlécet
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
        
        // Másolja az adatokat, ha van
        if (archive_entry_size(entry) > 0) {
            const void* buff;
            size_t size;
            la_int64_t offset;
            
            while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                    success = false;
                    break;
                }
            }
            
            if (r != ARCHIVE_EOF) {
                success = false;
                break;
            }
        }
        
        // Fejezze be a bejegyzés írását
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
    }
    
    // Ellenőrizze, hogy az olvasás sikeresen véget ért-e
    if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
        success = false;
    }
    
    // Szabadítsa fel az erőforrásokat
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);
    
    return success;
}