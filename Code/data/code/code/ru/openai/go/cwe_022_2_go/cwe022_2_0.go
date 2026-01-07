package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath извлекает содержимое tar-файла в указанный путь назначения.
// Если извлечение прошло успешно, возвращает true; в противном случае возвращает false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Открываем tar-файл
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Создаем новый тар-ридер
	tarReader := tar.NewReader(file)

	// Читаем из тар-файла
	for {
		// Получаем следующий файл из tar
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Достигнут конец файла
		}
		if err != nil {
			return false // Ошибка при чтении из tar
		}

		// Определяем путь для извлечения
		targetPath := filepath.Join(destPath, header.Name)

		// Проверка на директорию
		if header.Typeflag == tar.TypeDir {
			// Создаем директорию
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Ошибка при создании директории
			}
			continue
		}

		// Создаем файл
		outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false // Ошибка при открытии файла
		}

		// Копируем содержимое из tar в файл
		if _, err := io.Copy(outFile, tarReader); err != nil {
			outFile.Close()
			return false // Ошибка при копировании
		}

		// Закрываем файл
		if err := outFile.Close(); err != nil {
			return false // Ошибка при закрытии файла
		}
	}

	return true // Успешное извлечение
}