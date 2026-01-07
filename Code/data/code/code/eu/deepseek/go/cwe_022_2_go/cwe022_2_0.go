import (
	"archive/tar"
	"compress/gzip"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Ireki tar fitxategia
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Prozesatu gzip konprimitua edo tar arrunta
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

	// Prozesatu tar edukia
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Fitxategiaren amaiera
		}
		if err != nil {
			return false // Irakurketa errorea
		}

		// Segurtasun egiaztapena: bidea ez da destPath-tik kanpora joan behar
		targetPath := filepath.Join(destPath, header.Name)
		if !isSafePath(destPath, targetPath) {
			return false
		}

		// Sortu fitxategi/karpeta motaren arabera
		switch header.Typeflag {
		case tar.TypeDir:
			// Sortu direktorioa
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Sortu fitxategia
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			// Kopiatu edukia
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Sortu sinboliko esteka
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Sortu esteka gogorra
			linkTarget := filepath.Join(destPath, header.Linkname)
			if !isSafePath(destPath, linkTarget) {
				return false
			}
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Ez onartutako mota, jarraitu
			continue
		}
	}

	return true
}

// isSafePath egiaztatzen du bidea destPath-en barruan dagoen
func isSafePath(basePath, targetPath string) bool {
	rel, err := filepath.Rel(basePath, targetPath)
	if err != nil {
		return false
	}
	// Egiaztatu ez dagoela ".." hasieran
	return rel != ".." && !startsWith(rel, ".."+string(filepath.Separator))
}

// startsWith egiaztatzen du katea aurrizki batekin hasten den
func startsWith(s, prefix string) bool {
	if len(s) < len(prefix) {
		return false
	}
	return s[:len(prefix)] == prefix
}