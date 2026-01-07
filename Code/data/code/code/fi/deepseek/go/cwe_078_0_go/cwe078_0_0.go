package main

import (
	"bytes"
	"os"
	"os/exec"
	"strings"
)

func getLsResult(dirPath string) string {
	// Tarkista, että hakemisto on olemassa ja että siihen on käyttöoikeus
	fileInfo, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	
	// Varmista, että se on hakemisto
	if !fileInfo.IsDir() {
		return ""
	}
	
	// Luo komento suoritettavaksi
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Luo bufferit stdoutille ja stderrille
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Suorita komento
	err = cmd.Run()
	
	// Jos virhe tapahtui, palauta tyhjä merkkijono
	if err != nil {
		return ""
	}
	
	// Jos stderr sisältää dataa, palauta tyhjä merkkijono
	if stderr.Len() > 0 {
		return ""
	}
	
	// Palauta stdoutin sisältö ilman ylimääräisiä välilyöntejä lopussa
	return strings.TrimSpace(stdout.String())
}