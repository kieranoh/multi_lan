package main

import (
	"os"
	"path/filepath"
	"io/ioutil"
)

// Spremi tajnu datoteku u zadani direktorij s danim imenom datoteke i sadržajem.
// Datoteka bi trebala biti dostupna samo trenutnom korisniku.
//
// @param directory Direktorij za spremanje tajne datoteke.
// @param filename Ime tajne datoteke.
// @param content Sadržaj tajne datoteke.
func saveSecreteFile(directory string, filename string, content string) error {
	// Provjeri postoji li direktorij, ako ne, kreiraj ga s pravilnim dozvolama
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// Kreiraj punu putanju do datoteke
	fullPath := filepath.Join(directory, filename)

	// Postavi dozvole datoteke tako da su dostupne samo vlasniku (čitaj/pisanje)
	// Prvo kreiramo privremenu datoteku s pravilnim dozvolama
	tempFile, err := ioutil.TempFile(directory, ".tmp_"+filename)
	if err != nil {
		return err
	}
	tempPath := tempFile.Name()

	// Zapiši sadržaj u privremenu datoteku
	if _, err := tempFile.WriteString(content); err != nil {
		tempFile.Close()
		os.Remove(tempPath)
		return err
	}

	// Zatvori privremenu datoteku
	if err := tempFile.Close(); err != nil {
		os.Remove(tempPath)
		return err
	}

	// Postavi dozvole za privremenu datoteku (samo vlasnik može čitati/pisati)
	if err := os.Chmod(tempPath, 0600); err != nil {
		os.Remove(tempPath)
		return err
	}

	// Premjesti privremenu datoteku na konačnu lokaciju
	if err := os.Rename(tempPath, fullPath); err != nil {
		os.Remove(tempPath)
		return err
	}

	return nil
}