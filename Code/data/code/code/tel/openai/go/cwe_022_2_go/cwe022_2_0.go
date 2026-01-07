package main

import (
	"fmt"
	"os"
	"path/filepath"
	.tar "archive/tar"
	"io"
	"os"
)

// extractTarToPath 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.
//
// @param tarPath: tar 파일의 경로
// @param destPath: 목적지 폴더의 경로
//
// @return 추출이 성공하면 true; 그렇지 않으면 false
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	reader := tar.NewReader(file)

	for {
		header, err := reader.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			return false
		}

		target := filepath.Join(destPath, header.Name)
		switch header.Typeflag {
		case tar.TypeDir:
			if err := os.MkdirAll(target, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg:
			outFile, err := os.OpenFile(target, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			if _, err := io.Copy(outFile, reader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		default:
			return false
		}
	}

	return true
}