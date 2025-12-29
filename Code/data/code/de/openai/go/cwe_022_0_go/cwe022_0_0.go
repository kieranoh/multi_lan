package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir liest den Inhalt einer Datei aus dem angegebenen Verzeichnis.
// Wenn die Datei nicht gefunden wird oder ein Fehler auftritt, wird ein leerer String zurückgegeben.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(data)
}