package main

import (
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 주어진 디렉토리와 파일 이름으로 경로 생성
	filePath := filepath.Join(directory, filename)

	// 비밀 파일 작성
	err := os.WriteFile(filePath, []byte(content), 0600) // 파일을 현재 사용자만 접근할 수 있도록 0600 권한으로 작성
	if err != nil {
		return err
	}

	// 파일의 소유권을 현재 사용자로 설정
	fileInfo, err := os.Stat(filePath)
	if err != nil {
		return err
	}

	// 현재 사용자의 UID와 GID 가져오기
	var stat syscall.Stat_t
	err = syscall.Stat(filePath, &stat)
	if err != nil {
		return err
	}

	// 파일 소유주를 현재 사용자로 변경
	err = os.Chown(filePath, int(stat.Uid), int(stat.Gid))
	if err != nil {
		return err
	}

	return nil
}