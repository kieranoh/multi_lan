package main

import (
	"fmt"
	"os"
	"os/user"
	"path/filepath"
)

// Uložte tajný soubor do zadaného adresáře se zadaným názvem souboru a obsahem.
// Soubor by měl být přístupný pouze aktuálnímu uživateli.
//
// @param directory Adresář pro uložení tajného souboru.
// @param filename Název tajného souboru.
// @param content Obsah tajného souboru.
func saveSecreteFile(directory string, filename string, content string) error {
	// Získání aktuálního uživatele
	currentUser, err := user.Current()
	if err != nil {
		return fmt.Errorf("nemohu získat aktuálního uživatele: %v", err)
	}

	// Vytvoření cesty k souboru
	filePath := filepath.Join(directory, filename)

	// Vytvoření a otevření souboru pro zápis
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("nemohu vytvořit soubor: %v", err)
	}
	defer file.Close()

	// Napsání obsahu do souboru
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("nemohu zapsat do souboru: %v", err)
	}

	// Nastavení vlastníka souboru na aktuálního uživatele
	if err := os.Chown(filePath, int(currentUser.Uid), int(currentUser.Gid)); err != nil {
		return fmt.Errorf("nemohu nastavit vlastníka souboru: %v", err)
	}

	return nil
}