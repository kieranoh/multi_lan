package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하는지 확인
	err := os.MkdirAll(directory, os.ModePerm)
	if err != nil {
		return err
	}

	// 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 파일 생성
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// 파일에 내용 작성
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// 파일의 권한을 현재 사용자만 접근할 수 있도록 설정
	err = os.Chmod(filePath, 0600)
	if err != nil {
		return err
	}

	return nil
}