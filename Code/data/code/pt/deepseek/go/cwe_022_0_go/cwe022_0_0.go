import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Constrói o caminho completo do arquivo
	fullPath := filepath.Join(dirPath, filename)
	
	// Abre o arquivo
	file, err := os.Open(fullPath)
	if err != nil {
		// Retorna string vazia para qualquer erro de abertura
		return ""
	}
	defer file.Close()
	
	// Lê todo o conteúdo do arquivo
	content, err := io.ReadAll(file)
	if err != nil {
		// Retorna string vazia para qualquer erro de leitura
		return ""
	}
	
	// Converte bytes para string e retorna
	return string(content)
}