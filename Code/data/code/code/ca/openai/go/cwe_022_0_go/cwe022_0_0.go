package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir llegeix un fitxer d'un directori especificat i retorna el seu contingut.
// Si hi ha un error durant la lectura, retorna una cadena buida.
func readFileFromDir(filename, dirPath string) string {
	// Construïm el camí complet del fitxer
	fullPath := filepath.Join(dirPath, filename)

	// Intentem llegir el fitxer
	data, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// En cas d'error, retornem una cadena buida
		return ""
	}

	// Retornem el contingut del fitxer com a cadena
	return string(data)
}