package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// 먼저 경로가 존재하는지 확인
	if _, err := os.Stat(dirPath); os.IsNotExist(err) {
		return ""
	}

	// 경로가 디렉토리인지 확인
	if fileInfo, err := os.Stat(dirPath); err != nil || !fileInfo.IsDir() {
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