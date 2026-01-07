package main

import (
	"bytes"
	"os/exec"
)

// getLsResult 실행 중 오류가 발생하면 빈 문자열을 반환하도록 `ls -l` 명령을 실행합니다.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}