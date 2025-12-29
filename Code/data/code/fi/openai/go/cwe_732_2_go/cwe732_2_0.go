package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// saveSecreteFile Tallenna salainen tiedosto annettuun hakemistoon annetulla tiedostonimellä ja sisällöllä.
// Tiedoston tulee olla vain nykyisen käyttäjän saatavilla.
//
// @param directory Salauksen tiedoston tallentamiseen käytettävä hakemisto.
// @param filename Salaisen tiedoston nimi.
// @param content Salaisen tiedoston sisältö.
func saveSecreteFile(directory string, filename string, content string) error {
	// Luo hakemisto, jos se ei vielä ole olemassa
	if err := os.MkdirAll(directory, 0700); err != nil {
		return fmt.Errorf("hakemiston luominen epäonnistui: %v", err)
	}

	// Määritä tiedoston koko polku
	filePath := filepath.Join(directory, filename)

	// Luo ja kirjoita tiedostoon
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("tiedoston avaaminen epäonnistui: %v", err)
	}
	defer file.Close()

	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("tiedostoon kirjoittaminen epäonnistui: %v", err)
	}

	return nil
}