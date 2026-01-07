package main

import (
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile는 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 저장된 파일은 현재 사용자만 접근할 수 있습니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하는지 확인
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return err
	}

	// 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 파일 생성 및 내용 작성
	err := os.WriteFile(filePath, []byte(content), 0600) // 0600은 소유자에게만 읽기/쓰기 권한을 부여함
	if err != nil {
		return err
	}

	// 파일의 권한 설정
	return os.Chmod(filePath, 0600)
}

func main() {
	// 이곳에 원하는 디렉토리, 파일 이름 및 내용을 삽입하여 saveSecreteFile을 호출할 수 있습니다.
}