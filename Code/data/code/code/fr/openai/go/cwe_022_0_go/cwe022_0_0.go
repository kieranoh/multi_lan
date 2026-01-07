package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir lit le contenu d'un fichier à partir d'un chemin de répertoire donné.
// Si le fichier n'existe pas ou s'il y a une erreur lors de la lecture, une chaîne vide est retournée.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(content)
}