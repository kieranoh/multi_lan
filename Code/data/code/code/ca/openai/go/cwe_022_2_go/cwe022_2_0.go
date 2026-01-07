package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extreu el contingut del fitxer tar a la ruta de destinació donada.
// Si l'extracció és exitosa, retorna true; d'altra banda, si es produeix algun error durant
// el procés d'extracció (per exemple, fitxer no trobat, error de permís, no es pot extreure tot
// el contingut), simplement retorna false.
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	tarReader := tar.NewReader(file)

	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Hem arribat al final del fitxer tar
		}
		if err != nil {
			return false
		}

		// Preparem la ruta de destinació
		dest := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// Crear directoris
			if err := os.MkdirAll(dest, os.ModePerm); err != nil {
				return false
			}
		case tar.TypeReg:
			// Crear fitxers
			outFile, err := os.Create(dest)
			if err != nil {
				return false
			}
			_, err = io.Copy(outFile, tarReader)
			outFile.Close()
			if err != nil {
				return false
			}
		default:
			return false // Tipus de fitxer desconegut
		}
	}
	return true
}