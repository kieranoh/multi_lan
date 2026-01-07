package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// 먼저 디렉토리 존재 여부와 접근 권한 확인
	if _, err := os.Stat(dirPath); err != nil {
		return ""
	}

	// 경로를 절대 경로로 정규화
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}

	// 디렉토리인지 확인
	fileInfo, err := os.Stat(absPath)
	if err != nil || !fileInfo.IsDir() {
		return ""
	}

	// "ls -l" 명령 실행
	cmd := exec.Command("ls", "-l", absPath)
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// 명령 실행
	if err := cmd.Run(); err != nil {
		return ""
	}

	// stderr에 내용이 있으면 오류로 간주
	if stderr.Len() > 0 {
		return ""
	}

	// stdout 내용 반환 (개행 문자 포함)
	return stdout.String()
}