package main

import (
	"bytes"
	"os/exec"
	"path/filepath"
)

// getLsResult vraća izlaz (samo stdout) komande `ls -l` kada se izvrši u putanji direktorijuma koju je korisnik naveo.
// Ako dođe do greške tokom izvršenja komande (npr. direktorijum nije pronađen, greška u dozvolama), vraća prazan string.
func getLsResult(dirPath string) string {
	// Proveri da li je putanja validna
	if !isValidDir(dirPath) {
		return ""
	}

	// Pripremi komandu
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = &out // Da bismo uhvatili greške

	// Izvrši komandu
	err := cmd.Run()
	if err != nil {
		return ""
	}

	// Vraća izlaz komande
	return out.String()
}

// isValidDir proverava da li je data putanja validan direktorijum.
func isValidDir(dirPath string) bool {
	info, err := filepath.Abs(dirPath)
	if err != nil {
		return false
	}

	// Proveri da li je putanja direktorijum
	dirInfo, err := os.Stat(info)
	return err == nil && dirInfo.IsDir()
}