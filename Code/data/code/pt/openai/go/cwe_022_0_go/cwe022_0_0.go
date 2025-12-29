package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir lê um arquivo de um diretório especificado e retorna seu conteúdo.
// Se ocorrer um erro durante a leitura do arquivo, retorna uma string vazia.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(content)
}