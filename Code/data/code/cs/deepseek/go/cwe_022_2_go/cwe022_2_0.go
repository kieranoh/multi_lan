package main

import (
	"archive/tar"
	"errors"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Otevření tar souboru pro čtení
	tarFile, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer tarFile.Close()

	// Vytvoření tar readeru
	tarReader := tar.NewReader(tarFile)

	// Zajištění existence cílové cesty
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Iterace přes všechny položky v tar souboru
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Konec souboru
		}
		if err != nil {
			return false // Chyba při čtení hlavičky
		}

		// Vytvoření plné cílové cesty
		targetPath := filepath.Join(destPath, header.Name)
		
		// Ošetření bezpečnosti - kontrola, zda cílová cesta je uvnitř destPath
		absDest, err := filepath.Abs(destPath)
		if err != nil {
			return false
		}
		absTarget, err := filepath.Abs(targetPath)
		if err != nil {
			return false
		}
		relPath, err := filepath.Rel(absDest, absTarget)
		if err != nil || relPath == ".." || len(relPath) >= 2 && relPath[0:2] == ".." {
			return false // Path traversal attempt
		}

		// Zpracování podle typu položky
		switch header.Typeflag {
		case tar.TypeDir:
			// Vytvoření adresáře
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Vytvoření souboru
			if err := extractFile(tarReader, targetPath, header); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// Vytvoření symbolického odkazu
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Vytvoření hardlinku
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Ignorování nepodporovaných typů (např. zařízení)
			continue
		}

		// Nastavení časů modifikace
		if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
			// Není kritická chyba, pokračujeme
		}
	}

	return true
}

// Pomocná funkce pro extrakci souboru
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
	// Vytvoření adresářů v cestě, pokud neexistují
	if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
		return err
	}

	// Vytvoření souboru
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_RDWR|os.O_TRUNC, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// Zkopírování obsahu
	if _, err := io.Copy(file, tarReader); err != nil {
		// Pokud dojde k chybě, pokusíme se soubor smazat
		os.Remove(targetPath)
		return err
	}

	return nil
}