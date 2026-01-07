package main

import (
	"io"
	"os"
	"path/filepath"
)

// readFileFromDir lee el contenido de un archivo en un directorio específico.
// Si ocurre algún error durante la lectura (archivo no encontrado, permisos, etc.),
// devuelve una cadena vacía.
func readFileFromDir(filename, dirPath string) string {
	// Construir la ruta completa del archivo
	fullPath := filepath.Join(dirPath, filename)
	
	// Abrir el archivo
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()
	
	// Leer todo el contenido del archivo
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}
	
	// Convertir bytes a string y devolver
	return string(content)
}