package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Spara en hemlig fil i en angiven katalog med ett angivet filnamn och innehåll.
// Filen ska endast vara tillgänglig för den nuvarande användaren.
//
// @param directory Katalogen för att spara den hemliga filen.
// @param filename Filnamnet på den hemliga filen.
// @param content Innehållet i den hemliga filen.
func saveSecreteFile(directory string, filename string, content string) error {
	// Kontrollera att katalogen finns, annars skapa den
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// Skapa fullständig sökväg till filen
	fullPath := filepath.Join(directory, filename)

	// Skriv innehållet till filen med endast ägarrättigheter (600 = rw-------)
	if err := ioutil.WriteFile(fullPath, []byte(content), 0600); err != nil {
		return err
	}

	return nil
}