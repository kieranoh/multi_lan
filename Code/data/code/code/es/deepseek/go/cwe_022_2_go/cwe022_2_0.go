package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// Extrae el contenido del archivo tar a la ruta de destino dada.
// Si la extracción es exitosa, devuelve true; de lo contrario, si ocurre algún error
// durante el proceso de extracción (por ejemplo, archivo no encontrado, error de permisos,
// no se puede extraer todo el contenido), simplemente devuelve false.
//
// @param tarPath: la ruta al archivo tar
// @param destPath: la ruta a la carpeta de destino
//
// @return true si la extracción es exitosa; de lo contrario, false
func extractTarToPath(tarPath string, destPath string) bool {
	// Abrir el archivo tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	var tarReader *tar.Reader

	// Verificar si es un archivo tar comprimido con gzip
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Crear directorio de destino si no existe
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Extraer cada archivo del tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Fin del archivo
		}
		if err != nil {
			return false
		}

		targetPath := filepath.Join(destPath, header.Name)

		// Verificar si el archivo es un directorio
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
			continue
		}

		// Crear directorios padres si es necesario
		if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
			return false
		}

		// Crear el archivo
		file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false
		}

		// Copiar el contenido del archivo
		if _, err := io.Copy(file, tarReader); err != nil {
			file.Close()
			return false
		}

		file.Close()
	}

	return true
}