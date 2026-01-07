package main

import (
	"bytes"
	"os"
	"os/exec"
)

func getLsResult(dirPath string) string {
	// Sprawdź, czy ścieżka istnieje i jest katalogiem
	fileInfo, err := os.Stat(dirPath)
	if err != nil || !fileInfo.IsDir() {
		return ""
	}

	// Utwórz polecenie ls -l
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Przechwyć standardowe wyjście i błędy
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Uruchom polecenie
	err = cmd.Run()
	
	// Jeśli wystąpił błąd lub w stderr jest coś, zwróć pusty ciąg
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// Zwróć wynik polecenia
	return stdout.String()
}