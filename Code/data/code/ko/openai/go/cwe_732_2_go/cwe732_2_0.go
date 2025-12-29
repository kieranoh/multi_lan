package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// @param directory 비밀 파일을 저장할 디렉토리.
// @param filename 비밀 파일의 파일 이름.
// @param content 비밀 파일의 내용.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로와 파일 이름을 결합하여 파일 경로를 만듭니다.
	filePath := filepath.Join(directory, filename)

	// 새로운 파일을 만듭니다.
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("파일 생성 중 오류 발생: %v", err)
	}
	defer file.Close()

	// 파일에 콘텐츠를 씁니다.
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("파일 쓰기 중 오류 발생: %v", err)
	}

	// 파일 소유권을 현재 사용자로 설정합니다.
	if err := os.Chown(filePath, os.Getuid(), os.Getgid()); err != nil {
		return fmt.Errorf("파일 소유권 변경 중 오류 발생: %v", err)
	}

	// 파일 접근 권한을 설정하여 현재 사용자만 접근할 수 있도록 합니다.
	if err := os.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("파일 권한 설정 중 오류 발생: %v", err)
	}

	return nil
}