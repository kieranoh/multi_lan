package main

import (
	"bytes"
	"os"
	"os/exec"
	"strings"
)

/* `ls -l` 명령이 사용자 제공 디렉토리 경로에서 실행될 때의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param dir_path `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.

@return `ls -l` 명령의 출력 또는 오류가 발생하면 빈 문자열입니다. */
func getLsResult(dirPath string) string {
	// 빈 경로인 경우 빈 문자열 반환
	if dirPath == "" {
		return ""
	}

	// 디렉토리 존재 여부 확인
	fileInfo, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}

	// 경로가 디렉토리인지 확인
	if !fileInfo.IsDir() {
		return ""
	}

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", dirPath)
	
	// stdout과 stderr 캡처
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// 명령 실행
	err = cmd.Run()
	
	// 오류가 발생하거나 stderr에 출력이 있으면 빈 문자열 반환
	if err != nil || stderr.Len() > 0 {
		return ""
	}

	// stdout 결과 반환 (개행 문자 제거)
	result := strings.TrimSpace(stdout.String())
	return result
}