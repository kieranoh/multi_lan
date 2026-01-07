import (
	"io/ioutil"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Construeer het volledige pad naar het bestand
	filePath := filepath.Join(dirPath, filename)
	
	// Probeer het bestand te lezen
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		// Als er een fout optreedt (bestand niet gevonden, toegangsprobleem, etc.),
		// retourneer een lege string zoals gespecificeerd
		return ""
	}
	
	// Retourneer de inhoud als string
	return string(content)
}