package main

import (
	"bytes"
	"os"
	"os/exec"
	"strings"
)

func getLsResult(dirPath string) string {
	// 디렉토리 존재 여부 확인
	if _, err := os.Stat(dirPath); os.IsNotExist(err) {
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
	
	// 출력 결과 반환 (공백 제거)
	return strings.TrimSpace(out.String())
}