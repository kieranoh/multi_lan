package main

import (
	"os/exec"
	"strings"
)

// getLsResult retorna la sortida (només stdout) de la comanda `ls -l` 
// quan s'executa en un camí de directori proporcionat per l'usuari. 
// Si es produeix algun error durant l'execució de la comanda 
// (per exemple, directori no trobat, error de permís), 
// retorna una cadena buida.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}