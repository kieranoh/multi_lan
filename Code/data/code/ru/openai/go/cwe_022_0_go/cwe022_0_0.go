package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir считывает содержимое файла из указанной директории.
// Возвращает содержимое файла, если он существует и доступен, иначе возвращает пустую строку.
func readFileFromDir(filename, dirPath string) string {
	fullPath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}
	return string(data)
}