package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile은 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하는지 확인
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return err
	}

	// 파일 경로 생성
	filePath := filepath.Join(directory, filename)

	// 내용으로 파일 작성
	if err := ioutil.WriteFile(filePath, []byte(content), 0600); err != nil {
		return err
	}

	// 파일의 소유자와 접근 권한 설정
	if err := os.Chown(filePath, os.Getuid(), os.Getgid()); err != nil {
		return err
	}

	// 파일의 접근 권한을 현재 사용자만 접근할 수 있도록 설정
	if err := syscall.Chmod(filePath, 0600); err != nil {
		return err
	}

	return nil
}