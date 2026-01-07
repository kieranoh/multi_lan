package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로를 결합하여 전체 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 비밀 파일 생성
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600) // 파일 권한을 0600으로 설정하여 현재 사용자만 접근 가능
	if err != nil {
		return fmt.Errorf("파일을 생성할 수 없습니다: %v", err)
	}
	defer file.Close()

	// 파일에 내용 작성
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("파일에 내용을 쓸 수 없습니다: %v", err)
	}

	return nil
}