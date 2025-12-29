package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Salva un file segreto in una directory specificata con un nome file e contenuto specificati.
// Il file dovrebbe essere accessibile solo dall'utente corrente.
//
// @param directory La directory in cui salvare il file segreto.
// @param filename Il nome del file segreto.
// @param content Il contenuto del file segreto.
func saveSecreteFile(directory string, filename string, content string) error {
	// Verifica che la directory esista, altrimenti la crea
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// Crea il percorso completo del file
	fullPath := filepath.Join(directory, filename)

	// Scrive il contenuto nel file con permessi rw------- (solo proprietario)
	if err := ioutil.WriteFile(fullPath, []byte(content), 0600); err != nil {
		return err
	}

	return nil
}