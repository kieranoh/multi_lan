package main

import (
	"os"
	"path/filepath"
	"golang.org/x/sys/windows" // or "golang.org/x/sys/unix" for Unix-like systems
)

// 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 파일 생성
	file, err := os.OpenFile(filePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// 파일에 내용 쓰기
	if _, err := file.WriteString(content); err != nil {
		return err
	}

	// 현재 사용자만 접근할 수 있도록 파일 권한 설정 (Windows의 경우)
	if err := windows.SetFileSecurity(filePath, windows.DACL_SECURITY_INFORMATION, nil); err != nil {
		return err
	}

	return nil
}