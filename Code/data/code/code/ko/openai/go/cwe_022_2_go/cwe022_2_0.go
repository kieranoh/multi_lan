package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath 주어진 목적지 경로로 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면 false를 반환합니다.
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

	// tar 파일 추출
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 모든 파일이 추출됨
		}
		if err != nil {
			return false // 읽기 오류 발생
		}

		// 파일 경로 생성
		destFilePath := filepath.Join(destPath, header.Name)

		// 디렉토리인 경우 생성
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// 파일 생성
		destFile, err := os.OpenFile(destFilePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, os.FileMode(header.Mode))
		if err != nil {
			return false
		}
		defer destFile.Close()

		// tar 파일의 내용을 새 파일에 복사
		if _, err := io.Copy(destFile, tarReader); err != nil {
			return false
		}
	}

	return true
}