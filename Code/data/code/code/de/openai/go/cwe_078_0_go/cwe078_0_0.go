package main

import (
	"bytes"
	"os/exec"
)

// getLsResult gibt die Ausgabe (nur stdout) des Befehls `ls -l` zurück,
// wenn er in einem vom Benutzer bereitgestellten Verzeichnispfad ausgeführt wird.
// Wenn während der Ausführung des Befehls ein Fehler auftritt (z. B. Verzeichnis
// nicht gefunden, Berechtigungsfehler), wird ein leerer String zurückgegeben.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out

	if err := cmd.Run(); err != nil {
		return ""
	}

	return out.String()
}