package main

import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Construir la ruta completa del archivo
	fullPath := filepath.Join(dirPath, filename)
	
	// Abrir el archivo
	file, err := os.Open(fullPath)
	if err != nil {
		// Si hay algún error (archivo no encontrado, permisos, etc.), retornar cadena vacía
		return ""
	}
	defer file.Close()
	
	// Leer el contenido del archivo
	content, err := io.ReadAll(file)
	if err != nil {
		// Si hay error al leer, retornar cadena vacía
		return ""
	}
	
	// Convertir bytes a string y retornar
	return string(content)
}