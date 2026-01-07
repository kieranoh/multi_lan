package main

import (
    "io/ioutil"
    "path/filepath"
)

// readFileFromDir 사용자가 제공한 디렉토리 경로와 파일 이름을 사용하여
// 디렉토리에서 파일을 읽고 그 내용을 반환합니다. 
// 파일 읽기 과정에서 오류가 발생하면 빈 문자열을 반환합니다.
func readFileFromDir(filename, dirPath string) string {
    fullPath := filepath.Join(dirPath, filename)
    content, err := ioutil.ReadFile(fullPath)
    if err != nil {
        return ""
    }
    return string(content)
}