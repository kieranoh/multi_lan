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

	// tar 파일의 각 파일 추출
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 모든 파일을 추출했으면 종료
		}
		if err != nil {
			return false // 읽기 오류 발생
		}

		// 추출할 파일의 경로 생성
		targetPath := filepath.Join(destPath, header.Name)

		// 디렉토리 생성
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // 디렉토리 생성 오류
			}
			continue
		}

		// 파일 생성
		targetFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false // 파일 생성 오류
		}

		// 파일에 데이터 복사
		if _, err := io.Copy(targetFile, tarReader); err != nil {
			targetFile.Close()
			return false // 데이터 복사 오류
		}
		targetFile.Close()
	}

	return true // 모든 파일을 성공적으로 추출
}