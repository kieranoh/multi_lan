import (
    "archive/tar"
    "compress/gzip"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
    // Otwórz plik tar
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    var tarReader *tar.Reader

    // Sprawdź, czy plik jest skompresowany gzip
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

    // Utwórz katalog docelowy, jeśli nie istnieje
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // Przetwarzaj każdy wpis w archiwum tar
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Koniec archiwum
        }
        if err != nil {
            return false
        }

        // Zbuduj pełną ścieżkę docelową
        targetPath := filepath.Join(destPath, header.Name)

        // Sprawdź typ wpisu
        switch header.Typeflag {
        case tar.TypeDir:
            // Utwórz katalog
            if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
                return false
            }
        case tar.TypeReg, tar.TypeRegA:
            // Utwórz plik
            if err := extractFile(tarReader, targetPath, header); err != nil {
                return false
            }
        case tar.TypeSymlink:
            // Utwórz dowiązanie symboliczne
            if err := os.Symlink(header.Linkname, targetPath); err != nil {
                return false
            }
        case tar.TypeLink:
            // Utwórz twarde dowiązanie
            linkPath := filepath.Join(destPath, header.Linkname)
            if err := os.Link(linkPath, targetPath); err != nil {
                return false
            }
        default:
            // Pomijamy inne typy (np. znaki specjalne)
            continue
        }
    }

    return true
}

func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
    // Utwórz katalog nadrzędny, jeśli nie istnieje
    if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
        return err
    }

    // Utwórz plik
    file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
    if err != nil {
        return err
    }
    defer file.Close()

    // Skopiuj zawartość
    if _, err := io.Copy(file, tarReader); err != nil {
        return err
    }

    // Ustaw czas modyfikacji
    if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
        // Nie zwracamy błędu, ponieważ to tylko dodatkowa funkcjonalność
        fmt.Printf("Warning: Could not set file times for %s: %v\n", targetPath, err)
    }

    return nil
}