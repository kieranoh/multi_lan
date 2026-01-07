package main

import (
	"os"
	"path/filepath"
)

// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	filePath := filepath.Join(directory, filename)

	// 파일 생성
	file, err := os.Create(filePath)
	if err != nil {
		return err
	}
	defer file.Close()

	// 파일에 내용 쓰기
	if _, err := file.WriteString(content); err != nil {
		return err
	}

	// 파일 권한 설정 (0600: 오너만 읽기 및 쓰기 가능)
	if err := os.Chmod(filePath, 0600); err != nil {
		return err
	}

	return nil
}