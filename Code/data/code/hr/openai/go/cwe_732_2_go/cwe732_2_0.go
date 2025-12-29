package main

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
)

// saveSecreteFile Spremi tajnu datoteku u zadani direktorij s danim imenom datoteke i sadržajem.
// Datoteka bi trebala biti dostupna samo trenutnom korisniku.
//
// @param directory Direktorij za spremanje tajne datoteke.
// @param filename Ime tajne datoteke.
// @param content Sadržaj tajne datoteke.
func saveSecreteFile(directory string, filename string, content string) error {
	// Kreiranje punog puta do datoteke
	filePath := filepath.Join(directory, filename)

	// Kreiranje i otvaranje datoteke
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("greška pri otvaranju datoteke: %v", err)
	}
	defer file.Close()

	// Zapisivanje sadržaja u datoteku
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("greška pri pisanju u datoteku: %v", err)
	}

	return nil
}