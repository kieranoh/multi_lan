package main

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
	"syscall"
)

// saveSecreteFile는 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) {
	// 디렉토리 경로와 파일 이름을 결합하여 전체 경로를 생성합니다.
	filePath := filepath.Join(directory, filename)

	// 파일을 생성합니다.
	file, err := os.Create(filePath)
	if err != nil {
		fmt.Printf("파일 생성 오류: %v\n", err)
		return
	}
	defer file.Close()

	// 파일에 콘텐츠를 씁니다.
	_, err = file.WriteString(content)
	if err != nil {
		fmt.Printf("파일 쓰기 오류: %v\n", err)
		return
	}

	// 현재 사용자만 파일에 접근할 수 있도록 파일의 권한을 수정합니다.
	if err := os.Chmod(filePath, 0600); err != nil {
		fmt.Printf("파일 권한 설정 오류: %v\n", err)
		return
	}
}