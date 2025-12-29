package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// Extrahera innehållet i tar-filen till den angivna destinationssökvägen.
// Om extraktionen är framgångsrik, returnera true; annars, om något fel uppstår
// under extraktionsprocessen (t.ex. filen hittades inte, behörighetsfel, kan inte
// extrahera allt innehåll), returnera bara false.
//
// @param tarPath: sökvägen till tar-filen
// @param destPath: sökvägen till destinationsmappen
//
// @return true om extraktionen är framgångsrik; annars, false
func extractTarToPath(tarPath string, destPath string) bool {
	// Öppna tar-filen
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	var tarReader *tar.Reader

	// Kontrollera om filen är gzip-komprimerad genom att testa de första bytes
	buffer := make([]byte, 512)
	n, err := file.Read(buffer)
	if err != nil && err != io.EOF {
		return false
	}

	// Återställ filpekaren till början
	_, err = file.Seek(0, 0)
	if err != nil {
		return false
	}

	// Om filen är gzip-komprimerad, använd gzip.Reader
	if n >= 2 && buffer[0] == 0x1f && buffer[1] == 0x8b {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		// Annars, använd direkt tar.Reader
		tarReader = tar.NewReader(file)
	}

	// Skapa destinationsmappen om den inte finns
	err = os.MkdirAll(destPath, 0755)
	if err != nil {
		return false
	}

	// Iterera genom tar-filens poster
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Slut på arkivet
		}
		if err != nil {
			return false
		}

		// Bygg fullständig sökväg för målet
		targetPath := filepath.Join(destPath, header.Name)

		// Validera sökvägen för att förhindra directory traversal-attacker
		if !isSafePath(destPath, targetPath) {
			return false
		}

		// Hantera olika typer av poster
		switch header.Typeflag {
		case tar.TypeDir:
			// Skapa katalog
			err = os.MkdirAll(targetPath, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

		case tar.TypeReg, tar.TypeRegA:
			// Skapa föräldrakataloger om de inte finns
			err = os.MkdirAll(filepath.Dir(targetPath), 0755)
			if err != nil {
				return false
			}

			// Skapa filen
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Kopiera filinnehåll
			_, err = io.Copy(outFile, tarReader)
			outFile.Close()
			if err != nil {
				return false
			}

		case tar.TypeSymlink:
			// Skapa symbolisk länk
			err = os.Symlink(header.Linkname, targetPath)
			if err != nil {
				return false
			}

		case tar.TypeLink:
			// Skapa hård länk
			linkTarget := filepath.Join(destPath, header.Linkname)
			err = os.Link(linkTarget, targetPath)
			if err != nil {
				return false
			}

		default:
			// Ignorera andra typer av poster (som fifo, char device, etc.)
			continue
		}

		// Uppdatera tidsstämplar om möjligt
		if header.Typeflag == tar.TypeReg || header.Typeflag == tar.TypeRegA || header.Typeflag == tar.TypeDir {
			err = os.Chtimes(targetPath, header.AccessTime, header.ModTime)
			if err != nil {
				// Fortsätt även om tidsstämplar inte kan uppdateras
				continue
			}
		}
	}

	return true
}

// isSafePath kontrollerar att målsökvägen är inom basmappen för att förhindra
// directory traversal-attacker
func isSafePath(basePath, targetPath string) bool {
	relPath, err := filepath.Rel(basePath, targetPath)
	if err != nil {
		return false
	}

	// Kontrollera att den relativa sökvägen inte går utanför basmappen
	return !filepath.IsAbs(relPath) && relPath != ".." && relPath[:3] != "../"
}