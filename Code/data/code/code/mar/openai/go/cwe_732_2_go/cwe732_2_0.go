package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로 생성
	filePath := filepath.Join(directory, filename)

	// 파일 내용 쓰기
	if err := ioutil.WriteFile(filePath, []byte(content), 0600); err != nil {
		return err
	}

	return nil
}