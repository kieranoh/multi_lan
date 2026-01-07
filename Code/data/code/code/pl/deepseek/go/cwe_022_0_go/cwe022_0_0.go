import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Połącz ścieżkę katalogu z nazwą pliku
	filePath := filepath.Join(dirPath, filename)
	
	// Otwórz plik
	file, err := os.Open(filePath)
	if err != nil {
		return ""
	}
	defer file.Close()
	
	// Odczytaj zawartość pliku
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}
	
	return string(content)
}