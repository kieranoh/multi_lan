import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Nyisd meg a tar fájlt
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Ellenőrizd, hogy gzip-e vagy sima tar
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

	// Kicsomagolás folyamata
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // A tar fájl végére értünk
		}
		if err != nil {
			return false
		}

		// Készítsd elő a célútvonalat
		targetPath := filepath.Join(destPath, header.Name)

		// Ellenőrizd a fájltípust
		switch header.Typeflag {
		case tar.TypeDir:
			// Mappa létrehozása
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Fájl létrehozása
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Másold a fájl tartalmát
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Szimbolikus link létrehozása
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Hard link létrehozása
			linkPath := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// Nem támogatott fájltípus
			continue
		}
	}

	return true
}