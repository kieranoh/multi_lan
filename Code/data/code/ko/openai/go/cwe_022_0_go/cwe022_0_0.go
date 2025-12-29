package main

import (
	"io/ioutil"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 파일 경로 생성
	fullPath := filepath.Join(dirPath, filename)

	// 파일 읽기
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}

	// 내용 문자열 반환
	return string(content)
}