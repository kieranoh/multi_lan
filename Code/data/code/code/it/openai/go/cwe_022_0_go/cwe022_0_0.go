package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir legge il contenuto di un file da una directory specificata.
// Restituisce una stringa vuota in caso di errore (file non trovato, errore di autorizzazione, ecc.).
func readFileFromDir(filename, dirPath string) string {
	// Costruisce il percorso completo del file
	filePath := filepath.Join(dirPath, filename)

	// Legge il contenuto del file
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		// Restituisce una stringa vuota in caso di errore
		return ""
	}

	// Restituisce il contenuto del file come stringa
	return string(content)
}