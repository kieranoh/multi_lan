package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// 먼저 경로가 존재하는지 확인
	cleanPath := filepath.Clean(dirPath)
	info, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}
	
	// 디렉토리인지 확인
	if !info.IsDir() {
		return ""
	}
	
	// 실행 권한 확인 (디렉토리 읽기 권한)
	if info.Mode().Perm()&0400 == 0 {
		return ""
	}
	
	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", cleanPath)
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// 명령 실행
	if err := cmd.Run(); err != nil {
		return ""
	}
	
	// stderr에 내용이 있는지 확인
	if stderr.Len() > 0 {
		return ""
	}
	
	// stdout 결과 반환
	return stdout.String()
}