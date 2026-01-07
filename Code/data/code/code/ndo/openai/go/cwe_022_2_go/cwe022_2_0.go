package main

import (
	"os"
	"path/filepath"
	"fmt"
	"io"
	"archive/tar"
	"github.com/pkg/errors"
)

// extractTarToPath 주어진 목적지 경로로 tar 파일의 내용을 추출합니다.
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

	// tar 파일의 모든 항목을 읽어서 추출
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 모든 항목을 다 읽음
		}
		if err != nil {
			return false // 오류 발생
		}

		// 추출할 파일의 경로 생성
		targetPath := filepath.Join(destPath, header.Name)

		// 디렉토리일 경우 생성
		if header.Typeflag == tar.TypeDir {
			err := os.MkdirAll(targetPath, os.ModePerm)
			if err != nil {
				return false // 디렉토리 생성 실패
			}
			continue
		}

		// 파일일 경우 생성 및 내용 복사
		if err := os.MkdirAll(filepath.Dir(targetPath), os.ModePerm); err != nil {
			return false // 디렉토리 생성 실패
		}

		outFile, err := os.Create(targetPath)
		if err != nil {
			return false // 파일 생성 실패
		}
		defer outFile.Close()

		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false // 내용 복사 실패
		}
	}

	return true // 모든 항목을 성공적으로 추출
}