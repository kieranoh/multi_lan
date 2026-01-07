package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하는지 확인
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return fmt.Errorf("디렉토리가 존재하지 않습니다: %s", directory)
	}

	// 비밀 파일의 전체 경로를 생성
	filePath := filepath.Join(directory, filename)

	// 파일을 생성하고 내용을 씁니다
	err := os.WriteFile(filePath, []byte(content), 0600) // 현재 사용자가 읽고 쓸 수 있는 권한만 부여
	if err != nil {
		return fmt.Errorf("파일을 저장하는 중 오류 발생: %v", err)
	}

	return nil
}