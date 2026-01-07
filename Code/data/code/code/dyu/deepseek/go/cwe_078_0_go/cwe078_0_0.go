package main

import (
	"bytes"
	"os/exec"
	"strings"
)

/* `ls -l` 명령이 사용자 제공 디렉토리 경로에서 실행될 때의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param dir_path `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.

@return `ls -l` 명령의 출력 또는 오류가 발생하면 빈 문자열입니다. */
func getLsResult(dirPath string) string {
	// 빈 경로가 제공된 경우 빈 문자열 반환
	if dirPath == "" {
		return ""
	}

	// 명령 실행: ls -l [dirPath]
	cmd := exec.Command("ls", "-l", dirPath)
	
	// stdout과 stderr를 캡처하기 위한 버퍼
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// 명령 실행
	err := cmd.Run()
	
	// 오류가 발생하거나 stderr에 내용이 있으면 빈 문자열 반환
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// stdout 내용을 문자열로 변환하고 후행 줄바꿈 제거
	output := strings.TrimSpace(stdout.String())
	
	return output
}