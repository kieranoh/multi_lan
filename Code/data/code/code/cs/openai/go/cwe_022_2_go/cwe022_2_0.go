package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Otevření tar souboru
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Vytvoření nového tar reader
	tarReader := tar.NewReader(file)

	// Procházení jednotlivých souborů v tar archivu
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Konec archivu
		}
		if err != nil {
			return false // Chyba při čtení tar souboru
		}

		// Vytvoření cesty pro extrakci
		destFilePath := filepath.Join(destPath, header.Name)

		// Kontrola, zda jde o adresář
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false // Chyba při vytváření adresáře
			}
			continue
		}

		// Vytvoření souboru pro extrahování
		if err := os.MkdirAll(filepath.Dir(destFilePath), os.ModePerm); err != nil {
			return false // Chyba při vytváření nadřazeného adresáře
		}
		destFile, err := os.Create(destFilePath)
		if err != nil {
			return false // Chyba při vytváření souboru
		}

		// Zkopírování obsahu z tar archivu do souboru
		if _, err := io.Copy(destFile, tarReader); err != nil {
			destFile.Close()
			return false // Chyba při kopírování obsahu
		}
		destFile.Close()
	}

	return true // Úspěšná extrakce
}