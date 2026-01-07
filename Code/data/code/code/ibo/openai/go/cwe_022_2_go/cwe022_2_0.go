package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.
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

	archive := tar.NewReader(file)

	for {
		header, err := archive.Next()
		if err == io.EOF {
			break // 모든 파일을 읽었습니다.
		}
		if err != nil {
			return false // tar 파일을 읽는 중 오류 발생
		}

		target := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			if err := os.MkdirAll(target, os.ModePerm); err != nil {
				return false // 디렉토리 생성 중 오류 발생
			}
		case tar.TypeReg:
			outFile, err := os.Create(target)
			if err != nil {
				return false // 파일 생성 중 오류 발생
			}
			if _, err := io.Copy(outFile, archive); err != nil {
				outFile.Close()
				return false // 파일 복사 중 오류 발생
			}
			outFile.Close()
		default:
			return false // 지원하지 않는 파일 형식
		}
	}
	return true // 성공적으로 모든 파일을 추출했습니다.
}