import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Otvaranje tar datoteke
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Provera da li je datoteka gzip kompresovana (počinje sa gzip magic brojem)
	var tarReader *tar.Reader
	magicBytes := make([]byte, 2)
	_, err = file.Read(magicBytes)
	if err != nil {
		return false
	}
	
	// Vraćanje na početak datoteke
	file.Seek(0, 0)
	
	// Ako je gzip kompresovana (magic broj 0x1f8b)
	if magicBytes[0] == 0x1f && magicBytes[1] == 0x8b {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Kreiranje odredišne fascikle ako ne postoji
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Čitanje i ekstrakcija svih datoteka iz tar arhive
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Kraj arhive
		}
		if err != nil {
			return false
		}

		// Bezbednosna provera za putanju
		targetPath := filepath.Join(destPath, header.Name)
		if !isSafePath(destPath, targetPath) {
			return false
		}

		// Obrada različitih tipova datoteka
		switch header.Typeflag {
		case tar.TypeDir:
			// Kreiranje fascikle
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Kreiranje datoteke
			if err := extractFile(tarReader, targetPath, header); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// Kreiranje simboličke veze
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Kreiranje hard linka
			linkPath := filepath.Join(destPath, header.Linkname)
			if !isSafePath(destPath, linkPath) {
				return false
			}
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// Preskačemo ostale tipove (npr. karakter uređaje, FIFO itd.)
			continue
		}
	}

	return true
}

// extractFile ekstrahuje pojedinačnu datoteku iz tar arhive
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
	// Kreiranje nadređene fascikle ako ne postoji
	if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
		return err
	}

	// Kreiranje datoteke
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// Kopiranje sadržaja
	if _, err := io.Copy(file, tarReader); err != nil {
		return err
	}

	// Postavljanje vremena modifikacije
	if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
		// Ne vraćamo grešku ako postavljanje vremena ne uspe
		_ = err
	}

	return nil
}

// isSafePath proverava da li je putanja bezbedna (sprečava directory traversal)
func isSafePath(basePath, targetPath string) bool {
	relPath, err := filepath.Rel(basePath, targetPath)
	if err != nil {
		return false
	}
	
	// Provera za directory traversal
	if relPath == ".." || len(relPath) >= 2 && relPath[0:2] == ".." {
		return false
	}
	
	return true
}