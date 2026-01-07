package main

import (
	"os"
	"path/filepath"
	"syscall"
)

// 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로와 파일 이름을 결합하여 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 새로운 파일 생성
	file, err := os.Create(filePath)
	if err != nil {
		return err
	}
	defer file.Close()

	// 파일에 내용 작성
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// 파일 권한을 현재 사용자만 접근 가능하도록 설정 (0600)
	if err := os.Chmod(filePath, 0600); err != nil {
		return err
	}

	return nil
}