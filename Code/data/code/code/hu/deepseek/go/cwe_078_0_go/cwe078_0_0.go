import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Ellenőrizzük, hogy a könyvtár létezik-e és elérhető-e
	cleanPath := filepath.Clean(dirPath)
	info, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}
	
	// Ellenőrizzük, hogy könyvtár-e
	if !info.IsDir() {
		return ""
	}
	
	// Végrehajtjuk az ls -l parancsot
	cmd := exec.Command("ls", "-l", cleanPath)
	
	// Csak a stdout-ot rögzítjük
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// A hibákat eldobjuk, mert üres stringet kell visszaadnunk hiba esetén
	cmd.Stderr = nil
	
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	return out.String()
}