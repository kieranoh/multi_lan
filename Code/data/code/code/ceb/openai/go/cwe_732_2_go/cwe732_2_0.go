package main

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
)

// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하는지 확인
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return fmt.Errorf("지정된 디렉토리가 존재하지 않습니다: %s", directory)
	}

	// 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 파일 생성
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600) // 0600은 소유자만 접근 가능
	if err != nil {
		return fmt.Errorf("파일을 생성할 수 없습니다: %s", err)
	}
	defer file.Close()

	// 내용 작성
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("파일에 내용을 작성할 수 없습니다: %s", err)
	}

	return nil
}