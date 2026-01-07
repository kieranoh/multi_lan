import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Sačuvajte tajni fajl u datom direktorijumu sa datim imenom fajla i sadržajem.
// Fajl bi trebao biti dostupan samo trenutnom korisniku.
//
// @param directory Direktorijum u kojem se čuva tajni fajl.
// @param filename Ime tajnog fajla.
// @param content Sadržaj tajnog fajla.
func saveSecreteFile(directory string, filename string, content string) error {
	// Kreiraj punu putanju do fajla
	fullPath := filepath.Join(directory, filename)
	
	// Proveri da li direktorijum postoji, ako ne, kreiraj ga sa permisijama 0700
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		if err := os.MkdirAll(directory, 0700); err != nil {
			return err
		}
	}
	
	// Napiši sadržaj u fajl sa permisijama 0600 (samo vlasnik može da čita i piše)
	err := ioutil.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		return err
	}
	
	return nil
}