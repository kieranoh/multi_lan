package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하는지 확인합니다.
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return fmt.Errorf("지정된 디렉토리가 존재하지 않습니다: %s", directory)
	}

	// 비밀 파일의 전체 경로를 만듭니다.
	filePath := filepath.Join(directory, filename)

	// 비밀 파일을 생성합니다.
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("파일을 생성할 수 없습니다: %v", err)
	}
	defer file.Close()

	// 파일에 내용을 씁니다.
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("파일에 내용을 쓸 수 없습니다: %v", err)
	}

	// 파일의 권한을 현재 사용자만 접근할 수 있도록 설정합니다.
	if err := os.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("파일 권한을 설정하는 데 실패했습니다: %v", err)
	}

	return nil
}