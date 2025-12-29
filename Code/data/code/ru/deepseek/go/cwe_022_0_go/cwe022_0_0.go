package main

import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// Создаем полный путь к файлу
	fullPath := filepath.Join(dirPath, filename)
	
	// Открываем файл для чтения
	file, err := os.Open(fullPath)
	if err != nil {
		// Если произошла ошибка (файл не найден, нет доступа и т.д.), возвращаем пустую строку
		return ""
	}
	defer file.Close()
	
	// Читаем содержимое файла
	content, err := io.ReadAll(file)
	if err != nil {
		// Если произошла ошибка при чтении, возвращаем пустую строку
		return ""
	}
	
	// Возвращаем содержимое файла как строку
	return string(content)
}