import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func getLsResult(dirPath string) string {
	// Проверяем, существует ли директория и доступна ли она
	cleanPath := filepath.Clean(dirPath)
	info, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}
	
	// Убеждаемся, что это директория
	if !info.IsDir() {
		return ""
	}
	
	// Проверяем, есть ли у нас права на чтение директории
	file, err := os.Open(cleanPath)
	if err != nil {
		return ""
	}
	file.Close()
	
	// Выполняем команду ls -l
	cmd := exec.Command("ls", "-l", cleanPath)
	
	// Захватываем stdout и stderr
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Запускаем команду
	err = cmd.Run()
	
	// Если есть ошибка выполнения или stderr не пуст, возвращаем пустую строку
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// Возвращаем вывод команды, обрезая завершающие пробелы и символы новой строки
	return strings.TrimSpace(stdout.String())
}