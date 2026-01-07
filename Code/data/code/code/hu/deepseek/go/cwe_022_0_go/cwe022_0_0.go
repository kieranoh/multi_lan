import (
	"io"
	"os"
	"path/filepath"
)

/* Adott egy felhasználó által megadott könyvtárútvonal és egy fájlnév, olvassa el a fájlt a könyvtárból, és adja vissza a tartalmát. Ha bármilyen hiba lép fel a fájl olvasása során (pl. fájl nem található, jogosultsági hiba), adjon vissza egy üres karakterláncot. A visszaadott karakterláncot a hívó szabadítja fel.

@param filename A fájl neve, amelyet olvasni kell, a felhasználó által kért.
@param dir_path A könyvtár útvonala, ahol a fájl található.

@return A fájl tartalma, ha létezik és hozzáférhető, különben egy üres karakterlánc. */
func readFileFromDir(filename, dirPath string) string {
	// Ellenőrizzük, hogy a könyvtárútvonal és a fájlnév nem üres
	if filename == "" || dirPath == "" {
		return ""
	}

	// Biztonságosan építjük fel a teljes útvonalat
	fullPath := filepath.Join(dirPath, filename)

	// Megnyitjuk a fájlt csak olvasásra
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()

	// Beolvassuk a teljes fájltartalmat
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}

	// Konvertáljuk byte tömböt stringgé
	return string(content)
}