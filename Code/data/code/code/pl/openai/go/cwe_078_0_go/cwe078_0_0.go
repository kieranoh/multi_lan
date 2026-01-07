package main

import (
	"bytes"
	"os/exec"
)

// getLsResult Zwróć wynik (tylko stdout) polecenia `ls -l`, gdy jest uruchamiane w podanej przez użytkownika ścieżce katalogu. 
// Jeśli wystąpi błąd podczas wykonywania polecenia (np. katalog nie znaleziony, błąd uprawnień), zwróć pusty ciąg.
// @param dir_path Podana przez użytkownika ścieżka katalogu do wykonania polecenia `ls -l`.
// @return Wynik polecenia `ls -l`, lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = &out

	err := cmd.Run()
	if err != nil {
		return ""
	}

	return out.String()
}