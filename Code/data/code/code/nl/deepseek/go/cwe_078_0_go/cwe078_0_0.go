package main

import (
	"bytes"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
)

// getLsResult voert het `ls -l` commando uit in de opgegeven map.
// Als er een fout optreedt (bijv. map niet gevonden, toegangsprobleem),
// wordt een lege string teruggegeven.
func getLsResult(dirPath string) string {
	// Controleer of het pad bestaat en een map is
	info, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	if !info.IsDir() {
		return ""
	}

	// Maak het pad absoluut voor consistentie
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}

	// Voer het `ls -l` commando uit
	cmd := exec.Command("ls", "-l")
	cmd.Dir = absPath

	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// Voer het commando uit en vang eventuele fouten op
	if err := cmd.Run(); err != nil {
		return ""
	}

	// Controleer of er foutmeldingen zijn geschreven naar stderr
	if stderr.Len() > 0 {
		return ""
	}

	// Verwijder de laatste newline voor nettere uitvoer
	output := stdout.String()
	if len(output) > 0 && output[len(output)-1] == '\n' {
		output = output[:len(output)-1]
	}

	return output
}