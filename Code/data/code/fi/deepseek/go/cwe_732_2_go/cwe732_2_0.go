package main

import (
	"os"
	"path/filepath"
)

// Tallenna salainen tiedosto annettuun hakemistoon annetulla tiedostonimellä ja sisällöllä.
// Tiedoston tulee olla vain nykyisen käyttäjän saatavilla.
//
// @param directory Salauksen tiedoston tallentamiseen käytettävä hakemisto.
// @param filename Salaisen tiedoston nimi.
// @param content Salaisen tiedoston sisältö.
func saveSecreteFile(directory string, filename string, content string) {
	// Luo hakemisto, jos sitä ei ole olemassa
	if err := os.MkdirAll(directory, 0700); err != nil {
		panic(err)
	}

	// Luo tiedoston polku
	filePath := filepath.Join(directory, filename)

	// Kirjoita sisältö tiedostoon vain nykyisen käyttäjän oikeuksilla
	if err := os.WriteFile(filePath, []byte(content), 0600); err != nil {
		panic(err)
	}
}