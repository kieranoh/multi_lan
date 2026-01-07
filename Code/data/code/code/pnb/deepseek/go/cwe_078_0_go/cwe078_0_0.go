package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
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

	// 경로 정규화 및 절대 경로로 변환
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}

	// 경로가 실제로 존재하는지 확인
	if _, err := os.Stat(absPath); os.IsNotExist(err) {
		return ""
	}

	// `ls -l` 명령 실행
	cmd := exec.Command("ls", "-l", absPath)
	
	// stdout과 stderr 캡처
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// 명령 실행
	if err := cmd.Run(); err != nil {
		// 명령 실행 실패 시 빈 문자열 반환
		return ""
	}
	
	// stderr에 내용이 있으면 오류로 간주하고 빈 문자열 반환
	if stderr.Len() > 0 {
		return ""
	}
	
	// stdout 결과 반환 (개행 문자 제거하지 않고 원본 반환)
	result := stdout.String()
	
	// 결과가 비어있는지 확인
	if strings.TrimSpace(result) == "" {
		return ""
	}
	
	return result
}