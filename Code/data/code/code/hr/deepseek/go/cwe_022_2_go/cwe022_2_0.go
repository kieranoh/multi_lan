import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Otvori tar datoteku
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Provjeri je li datoteka gzip komprimirana
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

	// Prođi kroz sve datoteke u tar arhivi
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Kraj arhive
		}
		if err != nil {
			return false
		}

		// Kreiraj punu putanju za odredišnu datoteku
		targetPath := filepath.Join(destPath, header.Name)

		// Provjeri tip datoteke
		switch header.Typeflag {
		case tar.TypeDir:
			// Kreiraj direktorij
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Kreiraj roditeljski direktorij ako ne postoji
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			// Kreiraj datoteku
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Kopiraj sadržaj
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Kreiraj simboličku vezu
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Kreiraj tvrdu vezu
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Preskoči nepodržane tipove datoteka
			continue
		}
	}

	return true
}