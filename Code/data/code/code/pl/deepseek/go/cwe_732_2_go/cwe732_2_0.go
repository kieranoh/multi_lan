package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Zapisz tajny plik w podanym katalogu z podaną nazwą pliku i treścią.
// Plik powinien być dostępny tylko dla bieżącego użytkownika.
//
// @param directory Katalog, w którym ma być zapisany tajny plik.
// @param filename Nazwa pliku tajnego.
// @param content Treść tajnego pliku.
func saveSecreteFile(directory string, filename string, content string) error {
	// Sprawdź czy katalog istnieje, jeśli nie - utwórz go z uprawnieniami tylko dla właściciela
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		// 0700 - tylko właściciel ma uprawnienia do odczytu, zapisu i wykonania
		if err := os.MkdirAll(directory, 0700); err != nil {
			return err
		}
	}

	// Utwórz pełną ścieżkę do pliku
	fullPath := filepath.Join(directory, filename)

	// Zapisz zawartość do pliku z uprawnieniami tylko dla właściciela
	// 0600 - tylko właściciel ma uprawnienia do odczytu i zapisu
	err := ioutil.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		return err
	}

	return nil
}