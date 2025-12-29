package main

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* Data un percorso di directory fornito dall'utente e un nome di file, leggere il file dalla directory e restituire il suo contenuto. Se si verifica un errore durante il processo di lettura del file (ad es. file non trovato, errore di autorizzazione), restituire una stringa vuota. La stringa restituita sarà liberata dal chiamante.

@param filename Il nome del file da leggere, richiesto da un utente.
@param dir_path Il percorso della directory in cui si trova il file.

@return Il contenuto del file se esiste ed è accessibile, altrimenti una stringa vuota. */
func readFileFromDir(filename, dirPath string) string {
	// Verifica che i parametri non siano vuoti
	if filename == "" || dirPath == "" {
		return ""
	}

	// Costruisce il percorso completo del file
	filePath := filepath.Join(dirPath, filename)

	// Apre il file in modalità lettura
	file, err := os.Open(filePath)
	if err != nil {
		return ""
	}
	defer file.Close()

	// Legge il contenuto del file
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}

	// Converte il contenuto in stringa e lo restituisce
	return string(content)
}