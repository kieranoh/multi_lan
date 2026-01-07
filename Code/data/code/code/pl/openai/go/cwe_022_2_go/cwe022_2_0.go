package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath wydobywa zawartość pliku tar do podanej ścieżki docelowej.
// Jeśli ekstrakcja zakończy się sukcesem, zwraca true; w przeciwnym razie false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Otwórz plik tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Utwórz nowego tar readera
	tarReader := tar.NewReader(file)

	// Iteruj przez pliki w archiwum
	for {
		// Czytaj kolejną jednostkę tar
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Koniec archiwum
		}
		if err != nil {
			return false // Wystąpił błąd podczas czytania
		}

		// Ścieżka do pliku, który chcemy utworzyć
		targetPath := filepath.Join(destPath, header.Name)

		// Sprawdzenie, czy to katalog, i utworzenie katalogu
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Wystąpił błąd podczas tworzenia katalogu
			}
			continue
		}

		// Utwórz wszystkie wymagane katalogi
		if err := os.MkdirAll(filepath.Dir(targetPath), os.ModePerm); err != nil {
			return false // Wystąpił błąd podczas tworzenia katalogów
		}

		// Utwórz nowy plik
		outFile, err := os.Create(targetPath)
		if err != nil {
			return false // Wystąpił błąd podczas tworzenia pliku
		}
		defer outFile.Close()

		// Kopiuj zawartość z tar do pliku
		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false // Wystąpił błąd podczas kopiowania
		}
	}

	return true // Ekstrakcja zakończona sukcesem
}