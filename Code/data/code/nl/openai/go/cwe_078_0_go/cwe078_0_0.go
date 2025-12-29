package main

import (
	"os/exec"
	"strings"
)

// getLsResult geeft de uitvoer van het `ls -l` commando in de opgegeven map terug.
// Bij een fout, zoals een onvindbare map of een toegangsprobleem, retourneert het een lege string.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}