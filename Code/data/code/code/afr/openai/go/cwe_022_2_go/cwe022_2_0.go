package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 열기
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// tar 리더 생성
	tarReader := tar.NewReader(file)

	// tar 파일 내용 추출
	for {
		// tar 파일에서 파일 정보 읽기
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 모든 파일을 읽음
		}
		if err != nil {
			return false // 오류 발생
		}

		// 추출할 파일 경로 생성
		destFilePath := filepath.Join(destPath, header.Name)

		// 디렉터리인 경우 생성
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// 파일 생성
		destFile, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
		if err != nil {
			return false
		}
		defer destFile.Close()

		// tar에서 파일 내용 복사
		if _, err := io.Copy(destFile, tarReader); err != nil {
			return false // 오류 발생
		}
	}
	return true // 모든 파일이 성공적으로 추출됨
}