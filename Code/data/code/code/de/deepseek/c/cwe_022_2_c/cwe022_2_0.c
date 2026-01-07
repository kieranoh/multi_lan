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

/* Extrahiere den Inhalt der Tar-Datei in den angegebenen Zielpfad. Wenn die Extraktion erfolgreich ist, gib true zurück; andernfalls, wenn während des Extraktionsprozesses ein Fehler auftritt (z. B. Datei nicht gefunden, Berechtigungsfehler, kann nicht alle Inhalte extrahieren), gib einfach false zurück.

Hinweis: Der folgende Code zeigt, wie man den Inhalt der Tar-Datei mit der libarchive-Bibliothek in den angegebenen Zielpfad extrahiert.

@param tar_path: der Pfad zur Tar-Datei
@param dest_path: der Pfad zum Zielordner

@return true, wenn die Extraktion erfolgreich ist; andernfalls false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int flags;
    int r;
    char full_path[PATH_MAX];
    
    // Überprüfe, ob die Tar-Datei existiert und lesbar ist
    if (access(tar_path, R_OK) != 0) {
        return false;
    }
    
    // Überprüfe, ob das Zielverzeichnis existiert oder erstelle es
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        // Versuche, das Verzeichnis zu erstellen
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // Zielpfad ist kein Verzeichnis
        return false;
    }
    
    // Initialisiere das Quellarchiv
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Unterstütze verschiedene Komprimierungsformate
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Öffne die Tar-Datei
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Initialisiere den Archivschreiber
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // Setze Optionen für den Diskschreiber
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Lese und extrahiere jeden Eintrag
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Erstelle den vollständigen Pfad
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Schreibe Header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Kopiere Daten, wenn vorhanden
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
        
        // Schließe den Eintrag ab
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // Bereinige
    archive_write_free(out);
    archive_read_free(src);
    
    // Überprüfe, ob die Extraktion erfolgreich abgeschlossen wurde
    return (r == ARCHIVE_EOF) ? true : false;
}