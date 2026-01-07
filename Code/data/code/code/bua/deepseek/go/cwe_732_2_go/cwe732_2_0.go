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
func saveSecreteFile(directory string, filename string, content string) {
	// 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(directory, filename)

	// 디렉토리가 존재하지 않으면 생성
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		err := os.MkdirAll(directory, 0700) // 현재 사용자만 접근 가능한 권한으로 디렉토리 생성
		if err != nil {
			panic(err)
		}
	}

	// 파일에 내용을 쓰기 (현재 사용자만 읽기/쓰기 권한)
	err := ioutil.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		panic(err)
	}
}