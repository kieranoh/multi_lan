import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Yhdistä hakemistopolku ja tiedostonimi turvallisesti
	filePath := filepath.Join(dirPath, filename)
	
	// Avaa tiedosto
	file, err := os.Open(filePath)
	if err != nil {
		// Palauta tyhjä merkkijono jos tiedostoa ei löydy tai muuta virhettä
		return ""
	}
	defer file.Close()
	
	// Lue tiedoston sisältö
	content, err := io.ReadAll(file)
	if err != nil {
		// Palauta tyhjä merkkijono jos lukemisessa tapahtuu virhe
		return ""
	}
	
	// Palauta sisältö merkkijonona
	return string(content)
}