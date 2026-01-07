package main

import (
	"os"
	"path/filepath"
)

// saveSecreteFile 저장할 디렉토리와 파일 이름, 내용을 받아 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하지 않으면 생성
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	filePath := filepath.Join(directory, filename)

	// 파일 생성
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// 내용 쓰기
	if _, err := file.WriteString(content); err != nil {
		return err
	}

	return nil
}