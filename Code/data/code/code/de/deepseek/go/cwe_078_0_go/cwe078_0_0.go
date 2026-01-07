import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Überprüfe, ob der Pfad existiert und ein Verzeichnis ist
	if info, err := os.Stat(dirPath); err != nil || !info.IsDir() {
		return ""
	}

	// Erstelle den Befehl mit dem angegebenen Verzeichnis
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	// Führe den Befehl aus und erfasse die Ausgabe
	var out bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = nil // Stderr ignorieren, da wir bei Fehlern leeren String zurückgeben

	if err := cmd.Run(); err != nil {
		return ""
	}

	return out.String()
}