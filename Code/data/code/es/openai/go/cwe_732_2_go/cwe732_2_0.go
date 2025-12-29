package main

import (
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
	// Crear el directorio si no existe
	err := os.MkdirAll(directory, 0700)
	if err != nil {
		return err
	}

	// Crear la ruta del archivo
	filePath := filepath.Join(directory, filename)

	// Crear y abrir el archivo con permisos restringidos
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// Escribir el contenido en el archivo
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	return nil
}