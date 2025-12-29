import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Proveri da li je putanja validna i da li direktorijum postoji
	cleanPath := filepath.Clean(dirPath)
	fileInfo, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}
	
	// Proveri da li je putanja direktorijum
	if !fileInfo.IsDir() {
		return ""
	}
	
	// Kreiraj komandu ls -l
	cmd := exec.Command("ls", "-l")
	cmd.Dir = cleanPath
	
	// Postavi stdout buffer
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// Izvrši komandu
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	return out.String()
}