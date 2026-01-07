package main

import (
	"bytes"
	"os/exec"
)

// getLsResult restituisce l'output (solo stdout) del comando `ls -l` quando viene eseguito in un percorso di directory fornito dall'utente.
// Se si verifica un errore durante l'esecuzione del comando (ad es. directory non trovata, errore di autorizzazione), restituisce una stringa vuota.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out
	var stderr bytes.Buffer
	cmd.Stderr = &stderr

	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}