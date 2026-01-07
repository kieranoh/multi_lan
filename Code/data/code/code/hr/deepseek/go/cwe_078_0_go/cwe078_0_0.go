import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Prvo provjeri je li put valjan i je li direktorij
	cleanPath := filepath.Clean(dirPath)
	fileInfo, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}
	
	// Provjeri je li to direktorij
	if !fileInfo.IsDir() {
		return ""
	}
	
	// Izvrši ls -l naredbu
	cmd := exec.Command("ls", "-l", cleanPath)
	
	// Postavi stdout i stderr buffer
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Pokreni naredbu
	err = cmd.Run()
	
	// Ako postoji bilo kakva pogreška, vrati prazan string
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// Vrati stdout kao string
	return stdout.String()
}