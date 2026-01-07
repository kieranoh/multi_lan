package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(dirPath, filename)
	
	// 파일 존재 여부 확인
	if _, err := os.Stat(fullPath); os.IsNotExist(err) {
		// 파일이 존재하지 않으면 빈 문자열 반환
		return ""
	}
	
	// 파일 읽기 시도
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// 파일 읽기 오류 발생 시 빈 문자열 반환
		return ""
	}
	
	// 파일 내용을 문자열로 변환하여 반환
	return string(content)
}