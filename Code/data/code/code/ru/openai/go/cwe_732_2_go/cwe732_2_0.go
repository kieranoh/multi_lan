package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile сохраняет секретный файл в указанной директории с заданным именем файла и содержимым.
// Файл будет доступен только текущему пользователю.
func saveSecreteFile(directory string, filename string, content string) error {
	// Создание полного пути к файлу
	filePath := filepath.Join(directory, filename)

	// Создание файла с заданным именем
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("не удалось создать файл: %v", err)
	}
	defer file.Close()

	// Запись содержимого в файл
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("не удалось записать в файл: %v", err)
	}

	// Установка прав доступа файла, чтобы он был доступен только текущему пользователю
	if err := os.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("не удалось изменить права доступа к файлу: %v", err)
	}

	return nil
}