package main

import (
	"os/exec"
	"strings"
)

// getLsResult은 사용자 제공 디렉토리 경로에서 `ls -l` 명령을 실행하고,
// 명령의 출력을 반환합니다. 오류가 발생하면 빈 문자열을 반환합니다.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}