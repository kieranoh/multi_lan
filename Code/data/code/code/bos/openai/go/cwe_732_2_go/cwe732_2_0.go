package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// saveSecreteFile 저장된 디렉토리에 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) {
	// 디렉토리가 존재하지 않으면 생성합니다.
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		if err := os.MkdirAll(directory, os.ModePerm); err != nil {
			fmt.Println("디렉토리 생성 오류:", err)
			return
		}
	}

	// 파일의 경로를 설정합니다.
	filePath := filepath.Join(directory, filename)

	// 파일을 생성하고 내용을 작성합니다.
	if err := os.WriteFile(filePath, []byte(content), 0600); err != nil {
		fmt.Println("파일 저장 오류:", err)
		return
	}
}