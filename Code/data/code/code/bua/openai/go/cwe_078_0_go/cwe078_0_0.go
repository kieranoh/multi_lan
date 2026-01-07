package main

import (
	"os/exec"
	"strings"
)

// getLsResult은 사용자 제공 디렉토리 경로에서 `ls -l` 명령이 실행될 때의 출력(오직 stdout)을 반환합니다.
// 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
// @param dir_path `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.
// @return `ls -l` 명령의 출력 또는 오류가 발생하면 빈 문자열입니다.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}