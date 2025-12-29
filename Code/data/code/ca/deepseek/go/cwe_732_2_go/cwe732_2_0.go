package main

import (
	"io"
	"os"
	"path/filepath"
)

// Desa un fitxer secret en un directori donat amb un nom de fitxer i contingut donats.
// El fitxer ha de ser accessible només pel usuari actual.
//
// @param directory El directori on desar el fitxer secret.
// @param filename El nom del fitxer secret.
// @param content El contingut del fitxer secret.
func saveSecreteFile(directory string, filename string, content string) {
	// Combina el directori i el nom del fitxer per obtenir el camí complet
	fullPath := filepath.Join(directory, filename)

	// Crea el directori si no existeix
	err := os.MkdirAll(directory, 0700) // Permisos: rwx------ per al propietari
	if err != nil {
		panic(err)
	}

	// Crea el fitxer amb permisos restringits (només lectura/escriptura per al propietari)
	file, err := os.OpenFile(fullPath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600) // Permisos: rw-------
	if err != nil {
		panic(err)
	}
	defer file.Close()

	// Escriu el contingut al fitxer
	_, err = io.WriteString(file, content)
	if err != nil {
		panic(err)
	}
}