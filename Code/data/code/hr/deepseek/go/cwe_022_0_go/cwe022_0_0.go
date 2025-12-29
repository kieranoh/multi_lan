import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Konstruiraj punu putanju do datoteke
	filePath := filepath.Join(dirPath, filename)
	
	// Otvori datoteku za čitanje
	file, err := os.Open(filePath)
	if err != nil {
		return ""
	}
	defer file.Close()
	
	// Pročitaj cijeli sadržaj datoteke
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}
	
	// Vrati sadržaj kao string
	return string(content)
}