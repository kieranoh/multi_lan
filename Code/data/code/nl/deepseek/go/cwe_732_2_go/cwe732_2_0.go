package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Sla een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud.
// Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.
//
// @param directory De map om het geheime bestand op te slaan.
// @param filename De bestandsnaam van het geheime bestand.
// @param content De inhoud van het geheime bestand.
func saveSecreteFile(directory string, filename string, content string) error {
	// Controleer of de directory bestaat, zo niet, maak deze aan met alleen lees-/schrijfrechten voor de gebruiker
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		if err := os.MkdirAll(directory, 0700); err != nil {
			return err
		}
	}

	// Creëer het volledige pad naar het bestand
	fullPath := filepath.Join(directory, filename)

	// Schrijf de inhoud naar een tijdelijk bestand met strikte permissies
	tmpFile, err := ioutil.TempFile(directory, ".tmp_"+filename)
	if err != nil {
		return err
	}
	tmpPath := tmpFile.Name()

	// Schrijf de inhoud naar het tijdelijke bestand
	if _, err := tmpFile.Write([]byte(content)); err != nil {
		tmpFile.Close()
		os.Remove(tmpPath)
		return err
	}

	// Sluit het tijdelijke bestand
	if err := tmpFile.Close(); err != nil {
		os.Remove(tmpPath)
		return err
	}

	// Stel de permissies in op alleen lees-/schrijfrechten voor de gebruiker (0600)
	if err := os.Chmod(tmpPath, 0600); err != nil {
		os.Remove(tmpPath)
		return err
	}

	// Hernoem het tijdelijke bestand naar het uiteindelijke bestand
	if err := os.Rename(tmpPath, fullPath); err != nil {
		os.Remove(tmpPath)
		return err
	}

	return nil
}