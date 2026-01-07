package main

import (
	"os"
	"path/filepath"
	"golang.org/x/sys/unix"
)

// 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 비밀 파일의 전체 경로를 설정합니다.
	filePath := filepath.Join(directory, filename)

	// 파일을 생성하고 내용을 작성합니다.
	file, err := os.Create(filePath)
	if err != nil {
		return err
	}
	defer file.Close()

	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// 파일 접근 권한을 현재 사용자만 접근할 수 있도록 설정합니다.
	return unix.Chmod(filePath, 0600)
}