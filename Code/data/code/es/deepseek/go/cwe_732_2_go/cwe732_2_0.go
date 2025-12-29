package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Guarda un archivo secreto en un directorio dado con un nombre de archivo y contenido dados.
// El archivo solo debe ser accesible por el usuario actual.
//
// @param directory El directorio para guardar el archivo secreto.
// @param filename El nombre del archivo secreto.
// @param content El contenido del archivo secreto.
func saveSecreteFile(directory string, filename string, content string) error {
	// Crear el directorio si no existe con permisos solo para el usuario actual
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// Crear la ruta completa del archivo
	fullPath := filepath.Join(directory, filename)

	// Escribir el contenido en un archivo temporal primero
	tmpFile, err := ioutil.TempFile(directory, ".tmp_"+filename+"_*")
	if err != nil {
		return err
	}
	tmpPath := tmpFile.Name()

	// Escribir el contenido en el archivo temporal
	if _, err := tmpFile.Write([]byte(content)); err != nil {
		tmpFile.Close()
		os.Remove(tmpPath)
		return err
	}

	// Cerrar el archivo temporal
	if err := tmpFile.Close(); err != nil {
		os.Remove(tmpPath)
		return err
	}

	// Cambiar permisos del archivo temporal para que solo sea accesible por el usuario actual
	if err := os.Chmod(tmpPath, 0600); err != nil {
		os.Remove(tmpPath)
		return err
	}

	// Renombrar el archivo temporal al nombre final (operación atómica)
	if err := os.Rename(tmpPath, fullPath); err != nil {
		os.Remove(tmpPath)
		return err
	}

	return nil
}