package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extrae el contenido del archivo tar a la ruta de destino dada.
// Si la extracción es exitosa, devuelve true; de lo contrario, devuelve false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Abre el archivo tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Crea un nuevo lector de tar
	tarReader := tar.NewReader(file)

	// Itera sobre los archivos en el tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Fin del archivo tar
		}
		if err != nil {
			return false // Error al leer el archivo tar
		}

		// Determina la ruta del archivo en el sistema de archivos
		targetPath := filepath.Join(destPath, header.Name)

		// Maneja el caso de un directorio
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Error al crear el directorio
			}
			continue
		}

		// Crea el archivo destino
		targetFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false // Error al crear el archivo
		}
		defer targetFile.Close()

		// Copia el contenido del archivo tar al archivo destino
		if _, err := io.Copy(targetFile, tarReader); err != nil {
			return false // Error al copiar el contenido
		}
	}

	return true // Extracción exitosa
}