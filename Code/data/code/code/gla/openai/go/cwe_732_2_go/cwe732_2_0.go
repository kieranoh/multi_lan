package main

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
	"syscall"
)

func saveSecreteFile(directory string, filename string, content string) {
	// 디렉토리가 존재하는지 확인합니다.
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		fmt.Printf("디렉토리가 존재하지 않습니다: %s\n", directory)
		return
	}

	// 비밀 파일의 전체 경로를 생성합니다.
	filePath := filepath.Join(directory, filename)

	// 파일을 생성하고 내용 작성
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		fmt.Printf("파일을 열 수 없습니다: %v\n", err)
		return
	}
	defer file.Close()

	_, err = file.WriteString(content)
	if err != nil {
		fmt.Printf("파일에 내용을 쓸 수 없습니다: %v\n", err)
		return
	}

	// 파일의 소유자 권한을 현재 사용자로 설정합니다.
	if runtime.GOOS == "linux" || runtime.GOOS == "darwin" {
		currentUser, err := os.UserHomeDir()
		if err != nil {
			fmt.Printf("사용자 홈 디렉토리를 가져오는 중 오류 발생: %v\n", err)
			return
		}

		if err := os.Chown(filePath, os.Geteuid(), os.Getegid()); err != nil {
			fmt.Printf("파일 소유권을 변경하는 중 오류 발생: %v\n", err)
			return
		}
	}

	fmt.Printf("비밀 파일이 성공적으로 저장되었습니다: %s\n", filePath)
}