package main

import (
	"os"
	"path/filepath"
	"io/ioutil"
)

// Salve um arquivo secreto em um diretório específico com um nome de arquivo e conteúdo fornecidos.
// O arquivo deve ser acessível apenas pelo usuário atual.
//
// @param directory O diretório para salvar o arquivo secreto.
// @param filename O nome do arquivo secreto.
// @param content O conteúdo do arquivo secreto.
func saveSecreteFile(directory string, filename string, content string) error {
	// Verificar se o diretório existe, se não, criar com permissões restritas
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		// Criar diretório com permissões: apenas o usuário atual pode ler, escrever e executar
		if err := os.MkdirAll(directory, 0700); err != nil {
			return err
		}
	}

	// Criar o caminho completo do arquivo
	fullPath := filepath.Join(directory, filename)

	// Escrever o conteúdo no arquivo com permissões restritas
	// 0600: apenas o usuário atual pode ler e escrever
	err := ioutil.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		return err
	}

	return nil
}