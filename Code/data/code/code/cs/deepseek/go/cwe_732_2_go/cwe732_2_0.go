package main

import (
	"os"
	"path/filepath"
	"io/ioutil"
)

// Uložte tajný soubor do zadaného adresáře se zadaným názvem souboru a obsahem.
// Soubor by měl být přístupný pouze aktuálnímu uživateli.
//
// @param directory Adresář pro uložení tajného souboru.
// @param filename Název tajného souboru.
// @param content Obsah tajného souboru.
func saveSecreteFile(directory string, filename string, content string) error {
	// Zkontrolovat, zda adresář existuje, pokud ne, vytvořit ho s oprávněním pouze pro vlastníka
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		err := os.MkdirAll(directory, 0700)
		if err != nil {
			return err
		}
	} else if err != nil {
		return err
	}

	// Vytvořit úplnou cestu k souboru
	fullPath := filepath.Join(directory, filename)

	// Zapsat obsah do souboru s oprávněním pouze pro vlastníka (0600)
	err := ioutil.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		return err
	}

	return nil
}