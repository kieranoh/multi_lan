package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extrahiert den Inhalt der tar-Datei in den angegebenen Zielpfad.
// Wenn die Extraktion erfolgreich ist, gibt true zurück; andernfalls false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Öffne die tar-Datei
	tarFile, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer tarFile.Close()

	// Erstelle einen neuen Tar-Reader
	reader := tar.NewReader(tarFile)

	// Iteriere über die Dateien im Tar-Archiv
	for {
		// Lese den nächsten Header
		header, err := reader.Next()
		if err == io.EOF {
			break // Ende des Archivs erreicht
		}
		if err != nil {
			return false // Fehler beim Lesen des Archivs
		}

		// Bestimme den Zielpfad für die extrahierte Datei
		destFilePath := filepath.Join(destPath, header.Name)

		// Erstelle das Verzeichnis, falls nötig
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false // Fehler beim Erstellen des Verzeichnisses
			}
			continue
		}

		// Öffne die Zieldatei zum Schreiben
		destFile, err := os.OpenFile(destFilePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, os.FileMode(header.Mode))
		if err != nil {
			return false // Fehler beim Öffnen der Zieldatei
		}

		// Kopiere den Inhalt der Tar-Datei in die Zieldatei
		if _, err := io.Copy(destFile, reader); err != nil {
			destFile.Close()
			return false // Fehler beim Kopieren
		}
		destFile.Close()
	}

	return true // Erfolgreiche Extraktion
}