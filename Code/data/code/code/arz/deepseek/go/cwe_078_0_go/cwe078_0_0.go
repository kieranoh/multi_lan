package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// 먼저 디렉토리 존재 여부 확인
	if _, err := os.Stat(dirPath); err != nil {
		return ""
	}

	// 디렉토리인지 확인
	fileInfo, err := os.Stat(dirPath)
	if err != nil || !fileInfo.IsDir() {
		return ""
	}

	// 디렉토리 읽기 권한 확인
	if _, err := os.ReadDir(dirPath); err != nil {
		return ""
	}

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", dirPath)
	
	// stdout 캡처
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// 명령 실행
	if err := cmd.Run(); err != nil {
		return ""
	}
	
	return out.String()
}