package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Öppna tar-filen
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Skapa en ny tar-läsare
	reader := tar.NewReader(file)

	// Loopa igenom varje fil i tar-filen
	for {
		header, err := reader.Next()
		if err == io.EOF {
			break // Har nått slutet av tar-filen
		}
		if err != nil {
			return false
		}

		// Skapa en fullständig sökväg för den extraherade filen
		targetPath := filepath.Join(destPath, header.Name)

		// Hantera kataloger
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// Hantera filer
		fileOut, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false
		}
		defer fileOut.Close()

		// Kopiera innehållet från tar till den nya filen
		if _, err := io.Copy(fileOut, reader); err != nil {
			return false
		}
	}

	return true
}