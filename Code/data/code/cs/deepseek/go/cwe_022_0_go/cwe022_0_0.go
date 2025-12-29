import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Sestavit plnou cestu k souboru
	fullPath := filepath.Join(dirPath, filename)
	
	// Otevřít soubor pro čtení
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()
	
	// Přečíst celý obsah souboru
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}
	
	// Převést bajty na řetězec a vrátit
	return string(content)
}