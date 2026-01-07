package main

import (
	"fmt"
	"os"
	"path/filepath"
	"golang.org/x/sys/unix"
)

// saveSecreteFile salva un file segreto in una directory specificata con un nome file e contenuto specificati.
// Il file dovrebbe essere accessibile solo dall'utente corrente.
//
// @param directory La directory in cui salvare il file segreto.
// @param filename Il nome del file segreto.
// @param content Il contenuto del file segreto.
func saveSecreteFile(directory string, filename string, content string) error {
	// Creare il percorso completo del file
	filePath := filepath.Join(directory, filename)

	// Creare e scrivere nel file
	err := os.WriteFile(filePath, []byte(content), 0600) // Permessi per il proprietario solo
	if err != nil {
		return fmt.Errorf("errore durante la scrittura del file: %v", err)
	}

	// Imposta i permessi del file per garantire che sia accessibile solo all'utente corrente
	err = unix.Chmod(filePath, 0600)
	if err != nil {
		return fmt.Errorf("errore durante la modifica dei permessi del file: %v", err)
	}

	return nil
}