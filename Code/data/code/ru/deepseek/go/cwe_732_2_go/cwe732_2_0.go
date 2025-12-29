package main

import (
	"os"
	"path/filepath"
)

// Сохраните секретный файл в указанной директории с заданным именем файла и содержимым.
// Файл должен быть доступен только текущему пользователю.
//
// @param directory Директория для сохранения секретного файла.
// @param filename Имя файла секретного файла.
// @param content Содержимое секретного файла.
func saveSecreteFile(directory string, filename string, content string) {
	// Создаем полный путь к файлу
	fullPath := filepath.Join(directory, filename)
	
	// Создаем директорию, если она не существует
	err := os.MkdirAll(directory, 0700) // 0700: только владелец имеет права на чтение, запись и выполнение
	if err != nil {
		panic(err)
	}
	
	// Создаем файл с правами доступа только для владельца
	file, err := os.OpenFile(fullPath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600) // 0600: только владелец имеет права на чтение и запись
	if err != nil {
		panic(err)
	}
	defer file.Close()
	
	// Записываем содержимое в файл
	_, err = file.WriteString(content)
	if err != nil {
		panic(err)
	}
}