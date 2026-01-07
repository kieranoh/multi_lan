package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// Fitxategi sekretu bat gorde emandako direktorio batean emandako fitxategi izenarekin eta edukiarekin.
// Fitxategia egungo erabiltzailearentzat bakarrik eskuragarri egon behar da.
//
// @param directory Fitxategi sekretua gordetzeko direktorioa.
// @param filename Fitxategi sekretuaren izena.
// @param content Fitxategi sekretuaren edukia.
func saveSecreteFile(directory string, filename string, content string) error {
	// Direktorioaren bidea osatu
	filePath := filepath.Join(directory, filename)

	// Fitxategia sortu eta idatzi edukiari
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("fitxategia sortzerakoan errorea: %w", err)
	}
	defer file.Close()

	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("edukia idazterakoan errorea: %w", err)
	}

	// Fitxategiaren baimenak ezarri egungo erabiltzailearentzat bakarrik
	if err := os.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("baimenak ezartzerakoan errorea: %w", err)
	}

	return nil
}