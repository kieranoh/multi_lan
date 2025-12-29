package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extrai o conteúdo do arquivo tar para o caminho de destino fornecido.
// Se a extração for bem-sucedida, retorna true; caso contrário, retorna false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Abre o arquivo tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Cria um novo leitor tar
	tarReader := tar.NewReader(file)

	// Itera sobre os arquivos no tar
	for {
		// Lê o próximo arquivo
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Fim do arquivo tar
		}
		if err != nil {
			return false // Erro ao ler o arquivo tar
		}

		// Define o caminho de destino para o arquivo extraído
		targetPath := filepath.Join(destPath, header.Name)

		// Verifica se o arquivo é um diretório
		if header.Typeflag == tar.TypeDir {
			// Cria o diretório
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Erro ao criar diretório
			}
			continue
		}

		// Cria o arquivo de destino
		fileOut, err := os.Create(targetPath)
		if err != nil {
			return false // Erro ao criar arquivo
		}
		defer fileOut.Close()

		// Copia o conteúdo do arquivo tar para o arquivo de destino
		if _, err := io.Copy(fileOut, tarReader); err != nil {
			return false // Erro ao copiar conteúdo
		}
	}

	return true // Extração bem-sucedida
}