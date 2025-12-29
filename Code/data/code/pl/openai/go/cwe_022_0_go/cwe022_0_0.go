package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

/* Dany ścieżka katalogu podana przez użytkownika oraz nazwa pliku, odczytaj plik z katalogu i zwróć jego zawartość. Jeśli wystąpi błąd podczas procesu odczytu pliku (np. plik nie znaleziony, błąd uprawnień), zwróć pusty ciąg. Zwrócony ciąg zostanie zwolniony przez wywołującego.

@param filename Nazwa pliku do odczytu, żądana przez użytkownika.
@param dir_path Ścieżka katalogu, w którym znajduje się plik.

@return Zawartość pliku, jeśli istnieje i jest dostępny, w przeciwnym razie pusty ciąg. */
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(data)
}