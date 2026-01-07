package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func saveSecreteFile(directory string, filename string, content string) {
	// 경로 생성
	filePath := filepath.Join(directory, filename)

	// 파일 생성
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()

	// 내용 작성
	_, err = file.WriteString(content)
	if err != nil {
		fmt.Println("Error writing to file:", err)
		return
	}
}