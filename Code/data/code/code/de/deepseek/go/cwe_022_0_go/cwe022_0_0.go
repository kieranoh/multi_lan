import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Überprüfe, ob der Dateiname oder Verzeichnispfad leer ist
	if filename == "" || dirPath == "" {
		return ""
	}

	// Erstelle den vollständigen Pfad zur Datei
	fullPath := filepath.Join(dirPath, filename)

	// Öffne die Datei im schreibgeschützten Modus
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()

	// Lese den gesamten Dateiinhalt
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}

	// Konvertiere den Byte-Slice in einen String und gebe ihn zurück
	return string(content)
}