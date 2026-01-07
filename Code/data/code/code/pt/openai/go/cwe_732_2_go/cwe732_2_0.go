package main

import (
	"fmt"
	"os"
	"path/filepath"
	"golang.org/x/sys/unix"
)

// saveSecreteFile salva um arquivo secreto em um diretório específico com um nome de arquivo e conteúdo fornecidos.
// O arquivo deve ser acessível apenas pelo usuário atual.
func saveSecreteFile(directory string, filename string, content string) error {
	// Cria o caminho completo do arquivo
	filePath := filepath.Join(directory, filename)

	// Cria o arquivo com permissão de leitura e escrita apenas para o usuário
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
	if err != nil {
		return fmt.Errorf("erro ao criar o arquivo: %v", err)
	}
	defer file.Close()

	// Escreve o conteúdo no arquivo
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("erro ao escrever no arquivo: %v", err)
	}

	// Define as permissões do arquivo para que apenas o usuário atual possa acessá-lo (opcional, já que 0600 já faz isso)
	if err := unix.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("erro ao definir permissões do arquivo: %v", err)
	}

	return nil
}