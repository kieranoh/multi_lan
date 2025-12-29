package main

import (
	"bytes"
	"os/exec"
)

// getLsResult retorna a saída (apenas stdout) do comando `ls -l` quando é executado em um caminho de diretório fornecido pelo usuário.
// Se ocorrer algum erro durante a execução do comando (por exemplo, diretório não encontrado, erro de permissão), retorna uma string vazia.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}