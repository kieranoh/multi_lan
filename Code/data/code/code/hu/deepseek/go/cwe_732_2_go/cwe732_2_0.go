import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal.
// A fájl csak a jelenlegi felhasználó számára legyen elérhető.
//
// @param directory A könyvtár, ahová a titkos fájlt menteni kell.
// @param filename A titkos fájl fájlneve.
// @param content A titkos fájl tartalma.
func saveSecreteFile(directory string, filename string, content string) error {
	// Ellenőrizzük, hogy a könyvtár létezik-e, ha nem, létrehozzuk
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		// A könyvtár létrehozása csak a jelenlegi felhasználónak
		if err := os.MkdirAll(directory, 0700); err != nil {
			return err
		}
	}

	// Teljes fájlútvonal összeállítása
	fullPath := filepath.Join(directory, filename)

	// Tartalom írása a fájlba
	// Csak a tulajdonos (jelenlegi felhasználó) számára olvasható/írható jogosultságok (0600)
	err := ioutil.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		return err
	}

	return nil
}