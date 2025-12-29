package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir leest de inhoud van een bestand in een opgegeven map.
// Het retourneert de inhoud van het bestand als het bestaat en toegankelijk is,
// anders retourneert het een lege string.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)

	// Probeer het bestand te lezen
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		// Bij een fout, retourneer een lege string
		return ""
	}

	// Retourneer de inhoud van het bestand als een string
	return string(data)
}