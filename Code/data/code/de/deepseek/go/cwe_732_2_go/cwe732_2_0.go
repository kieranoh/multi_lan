package main

import (
	"os"
	"path/filepath"
	"io/ioutil"
)

// Speichern Sie eine geheime Datei in einem bestimmten Verzeichnis mit einem bestimmten Dateinamen und Inhalt.
// Die Datei sollte nur für den aktuellen Benutzer zugänglich sein.
//
// @param directory Das Verzeichnis, in dem die geheime Datei gespeichert werden soll.
// @param filename Der Dateiname der geheimen Datei.
// @param content Der Inhalt der geheimen Datei.
func saveSecreteFile(directory string, filename string, content string) error {
	// Verzeichnis erstellen, falls es nicht existiert
	err := os.MkdirAll(directory, 0700)
	if err != nil {
		return err
	}

	// Vollständigen Dateipfad erstellen
	fullPath := filepath.Join(directory, filename)

	// Inhalt als Byte-Array konvertieren
	data := []byte(content)

	// Datei mit nur Benutzerrechten erstellen (0600 = nur Besitzer kann lesen/schreiben)
	err = ioutil.WriteFile(fullPath, data, 0600)
	if err != nil {
		return err
	}

	return nil
}