package main

import (
	"os/exec"
	"strings"
)

// getLsResult는 사용자 제공 디렉토리 경로에서 `ls -l` 명령을 실행하고,
// 명령의 출력을 반환합니다. 오류가 발생하면 빈 문자열을 반환합니다.
//
// @param dirPath `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.
//
// @return `ls -l` 명령의 출력 또는 오류가 발생하면 빈 문자열입니다.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}