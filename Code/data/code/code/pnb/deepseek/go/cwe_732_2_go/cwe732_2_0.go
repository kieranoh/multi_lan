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
	// 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(directory, filename)
	
	// 파일 내용을 바이트 배열로 변환
	data := []byte(content)
	
	// 파일 생성 및 쓰기 (사용자만 읽고 쓸 수 있도록 0600 권한 설정)
	// 0600: 소유자 읽기/쓰기 권한만 허용
	err := ioutil.WriteFile(fullPath, data, 0600)
	if err != nil {
		return err
	}
	
	return nil
}