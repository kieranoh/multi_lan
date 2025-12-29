package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

// Restituisce l'output (solo stdout) del comando `ls -l` quando viene eseguito in un percorso di directory fornito dall'utente.
// Se si verifica un errore durante l'esecuzione del comando (ad es. directory non trovata, errore di autorizzazione),
// restituisce una stringa vuota.
//
// @param dir_path Il percorso della directory fornito dall'utente per eseguire il comando `ls -l`.
//
// @return L'output del comando `ls -l`, o una stringa vuota se si verifica un errore.
func getLsResult(dirPath string) string {
	// Verifica se il percorso è una directory valida
	fileInfo, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	
	if !fileInfo.IsDir() {
		return ""
	}
	
	// Risolvi il percorso assoluto per evitare problemi con percorsi relativi
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}
	
	// Crea il comando con il percorso assoluto
	cmd := exec.Command("ls", "-l", absPath)
	
	// Crea un buffer per catturare l'output
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// Esegui il comando
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	// Restituisci l'output come stringa
	return out.String()
}