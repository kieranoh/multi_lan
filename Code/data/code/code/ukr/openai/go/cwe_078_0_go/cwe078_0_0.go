package main

import (
	"os/exec"
	"strings"
)

// getLsResult 실행 중 오류가 발생하면 빈 문자열을 반환합니다.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}