package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Verificar se o caminho existe e é um diretório
	fileInfo, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	
	if !fileInfo.IsDir() {
		return ""
	}

	// Obter o caminho absoluto para evitar problemas com caminhos relativos
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}

	// Executar o comando ls -l
	cmd := exec.Command("ls", "-l", absPath)
	
	// Capturar a saída padrão
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// Executar o comando
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	return out.String()
}