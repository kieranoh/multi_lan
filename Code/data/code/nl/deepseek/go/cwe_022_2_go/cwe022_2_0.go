import (
    "archive/tar"
    "compress/gzip"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
    // Open het tar-bestand
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    // Controleer of het een gzip-gecomprimeerd tar-bestand is
    var tarReader *tar.Reader
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

    // Maak de doelmap aan als deze niet bestaat
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // Lees en extraheer elk bestand in het tar-archief
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Einde van het archief
        }
        if err != nil {
            return false
        }

        // Bouw het volledige pad voor het te extraheren bestand
        targetPath := filepath.Join(destPath, header.Name)

        // Controleer op directory traversal
        if !isSafePath(targetPath, destPath) {
            return false
        }

        // Verwerk het item op basis van het type
        switch header.Typeflag {
        case tar.TypeDir:
            // Maak directory aan
            if err := os.MkdirAll(targetPath, 0755); err != nil {
                return false
            }
        case tar.TypeReg, tar.TypeRegA:
            // Maak directory aan voor het bestand
            if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
                return false
            }

            // Maak het bestand aan
            outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
            if err != nil {
                return false
            }

            // Kopieer de inhoud
            if _, err := io.Copy(outFile, tarReader); err != nil {
                outFile.Close()
                return false
            }
            outFile.Close()
        case tar.TypeSymlink:
            // Maak symlink aan
            if err := os.Symlink(header.Linkname, targetPath); err != nil {
                return false
            }
        case tar.TypeLink:
            // Maak hardlink aan
            linkPath := filepath.Join(destPath, header.Linkname)
            if err := os.Link(linkPath, targetPath); err != nil {
                return false
            }
        default:
            // Onbekend type, overslaan
            continue
        }
    }

    return true
}

// Hulpfunctie om directory traversal te voorkomen
func isSafePath(targetPath, basePath string) bool {
    relPath, err := filepath.Rel(basePath, targetPath)
    if err != nil {
        return false
    }
    return !filepath.IsAbs(relPath) && relPath != ".." && !hasPathPrefix(relPath, "..")
}

// Hulpfunctie om te controleren of een pad begint met een bepaald voorvoegsel
func hasPathPrefix(path, prefix string) bool {
    rel, err := filepath.Rel(prefix, path)
    if err != nil {
        return false
    }
    return rel != ".." && !filepath.IsAbs(rel) && len(rel) > 0
}