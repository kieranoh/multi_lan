import (
    "archive/tar"
    "compress/gzip"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

/* Extrahiere den Inhalt der tar-Datei in den angegebenen Zielpfad.
Wenn die Extraktion erfolgreich ist, gib true zurück; andernfalls, wenn während des Extraktionsprozesses ein Fehler auftritt (z. B. Datei nicht gefunden, Berechtigungsfehler, kann nicht alle Inhalte extrahieren), gib einfach false zurück.

@param tarPath: der Pfad zur tar-Datei
@param destPath: der Pfad zum Zielordner

@return true, wenn die Extraktion erfolgreich ist; andernfalls false */
func extractTarToPath(tarPath string, destPath string) bool {
    // Öffne die tar-Datei
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    var tarReader *tar.Reader

    // Prüfe, ob die Datei gzip-komprimiert ist
    if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
        gzReader, err := gzip.NewReader(file)
        if err != nil {
            return false
        }
        defer gzReader.Close()
        tarReader = tar.NewReader(gzReader)
    } else {
        tarReader = tar.NewReader(file)
    }

    // Erstelle den Zielordner, falls er nicht existiert
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // Extrahiere alle Dateien
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Ende der tar-Datei erreicht
        }
        if err != nil {
            return false
        }

        // Erstelle den vollständigen Pfad für die extrahierte Datei
        targetPath := filepath.Join(destPath, header.Name)

        // Prüfe auf path traversal Angriffe
        if !isSafePath(destPath, targetPath) {
            return false
        }

        // Verarbeite den Header basierend auf dem Typ
        switch header.Typeflag {
        case tar.TypeDir:
            // Erstelle Verzeichnis
            if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
                return false
            }
        case tar.TypeReg, tar.TypeRegA:
            // Erstelle Datei
            if err := extractFile(tarReader, targetPath, header); err != nil {
                return false
            }
        case tar.TypeSymlink:
            // Erstelle symbolischen Link
            if err := os.Symlink(header.Linkname, targetPath); err != nil {
                return false
            }
        case tar.TypeLink:
            // Erstelle Hardlink
            linkPath := filepath.Join(destPath, header.Linkname)
            if err := os.Link(linkPath, targetPath); err != nil {
                return false
            }
        default:
            // Überspringe andere Typen (z.B. Gerätedateien)
            continue
        }
    }

    return true
}

// Hilfsfunktion zum Extrahieren einer einzelnen Datei
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
    // Stelle sicher, dass das übergeordnete Verzeichnis existiert
    if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
        return err
    }

    // Erstelle die Datei
    file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
    if err != nil {
        return err
    }
    defer file.Close()

    // Kopiere den Inhalt
    if _, err := io.Copy(file, tarReader); err != nil {
        return err
    }

    return nil
}

// Hilfsfunktion zum Prüfen auf path traversal Angriffe
func isSafePath(basePath, targetPath string) bool {
    relPath, err := filepath.Rel(basePath, targetPath)
    if err != nil {
        return false
    }
    
    // Prüfe, ob der relative Pfad außerhalb des Basisverzeichnisses liegt
    return !filepath.IsAbs(relPath) && relPath != ".." && 
           !filepath.HasPrefix(relPath, ".."+string(filepath.Separator)) &&
           !filepath.HasPrefix(relPath, string(filepath.Separator))
}