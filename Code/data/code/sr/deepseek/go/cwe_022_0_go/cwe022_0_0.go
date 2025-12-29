import (
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Konstruišite punu putanju do datoteke
	fullPath := filepath.Join(dirPath, filename)
	
	// Pročitajte datoteku
	content, err := os.ReadFile(fullPath)
	if err != nil {
		// Ako dođe do greške, vratite prazan string
		return ""
	}
	
	// Vratite sadržaj datoteke kao string
	return string(content)
}