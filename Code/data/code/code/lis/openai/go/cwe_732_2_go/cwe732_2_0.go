package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// 주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로를 결합하여 비밀 파일의 전체 경로를 생성합니다.
	filePath := filepath.Join(directory, filename)
	
	// 비밀 파일을 생성합니다.
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600) // 권한을 0600으로 설정하여 소유자만 접근 가능하도록 합니다.
	if err != nil {
		return fmt.Errorf("파일을 생성할 수 없습니다: %w", err)
	}
	defer file.Close()

	// 파일에 내용을 작성합니다.
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("파일에 내용을 쓸 수 없습니다: %w", err)
	}

	return nil
}