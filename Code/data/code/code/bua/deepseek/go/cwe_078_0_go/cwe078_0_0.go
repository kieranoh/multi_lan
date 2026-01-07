package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

/* `ls -l` 명령이 사용자 제공 디렉토리 경로에서 실행될 때의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param dir_path `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.

@return `ls -l` 명령의 출력 또는 오류가 발생하면 빈 문자열입니다. */
func getLsResult(dirPath string) string {
	// 경로가 비어있는 경우 빈 문자열 반환
	if dirPath == "" {
		return ""
	}

	// 경로를 정규화하고 존재하는지 확인
	cleanPath := filepath.Clean(dirPath)
	if _, err := os.Stat(cleanPath); err != nil {
		return ""
	}

	// 명령 실행
	cmd := exec.Command("ls", "-l", cleanPath)
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// 명령 실행 중 오류 발생 시 빈 문자열 반환
	if err := cmd.Run(); err != nil {
		return ""
	}

	// stderr에 내용이 있으면 빈 문자열 반환
	if stderr.Len() > 0 {
		return ""
	}

	// stdout 내용 반환 (개행 문자 포함)
	return stdout.String()
}