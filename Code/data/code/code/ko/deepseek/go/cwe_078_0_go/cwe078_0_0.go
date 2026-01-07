package main

import (
	"bytes"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

/* `ls -l` 명령이 사용자 제공 디렉토리 경로에서 실행될 때의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리 없음, 권한 오류) 빈 문자열을 반환합니다.

@param dir_path `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.

@return 오류가 발생하면 빈 문자열 또는 `ls -l` 명령의 출력입니다. */
func getLsResult(dirPath string) string {
	// 입력 경로가 비어있는 경우 빈 문자열 반환
	if strings.TrimSpace(dirPath) == "" {
		return ""
	}

	// 경로가 존재하는지 확인
	cleanPath := filepath.Clean(dirPath)
	info, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}

	// 경로가 디렉토리가 아닌 경우 빈 문자열 반환
	if !info.IsDir() {
		return ""
	}

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", cleanPath)
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// 명령 실행 및 오류 처리
	if err := cmd.Run(); err != nil {
		return ""
	}

	// stderr에 내용이 있는 경우 빈 문자열 반환
	if stderr.Len() > 0 {
		return ""
	}

	// stdout 결과 반환 (개행 문자 포함)
	return strings.TrimSuffix(stdout.String(), "\n")
}