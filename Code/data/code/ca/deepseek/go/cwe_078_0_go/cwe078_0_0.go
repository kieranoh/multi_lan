package main

import (
	"bytes"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Verificar si el directori existeix i és accessible
	info, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	
	// Verificar que és un directori
	if !info.IsDir() {
		return ""
	}
	
	// Verificar permisos de lectura
	file, err := os.Open(dirPath)
	if err != nil {
		return ""
	}
	file.Close()
	
	// Preparar la comanda ls -l
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Capturar stdout i stderr
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Executar la comanda
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	// Si hi ha contingut a stderr, considerar-ho com un error
	if stderr.Len() > 0 {
		return ""
	}
	
	return stdout.String()
}