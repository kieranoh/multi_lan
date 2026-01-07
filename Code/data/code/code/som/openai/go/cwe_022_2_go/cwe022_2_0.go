package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"archive/tar"
	"io"
)

// extractTarToPath 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.
//
// @param tarPath: tar 파일의 경로
// @param destPath: 목적지 폴더의 경로
//
// @return 추출이 성공하면 true; 그렇지 않으면 false
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 열기
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// tar 리더 생성
	tarReader := tar.NewReader(file)

	// tar 파일의 내용을 반복하여 읽기
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 모든 항목을 읽었음
		}
		if err != nil {
			return false // 읽기 오류가 발생
		}

		// 목적지 파일 경로 생성
		targetPath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리 생성
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
		case tar.TypeReg:
			// 파일 생성
			fileToWrite, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			defer fileToWrite.Close()

			// tar 파일의 내용을 파일에 씀
			if _, err := io.Copy(fileToWrite, tarReader); err != nil {
				return false
			}
		default:
			return false // 알 수 없는 타입
		}
	}

	return true
}