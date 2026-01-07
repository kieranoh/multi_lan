package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일을 열기
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// tar 리더 생성
	tarReader := tar.NewReader(file)

	// tar 파일의 각 항목을 읽기
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 모든 항목을 처리했으면 종료
		}
		if err != nil {
			return false // 오류가 발생하면 false 반환
		}

		// 추출할 파일의 경로 생성
		destFilePath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리일 경우 생성
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false
			}
		case tar.TypeReg:
			// 일반 파일일 경우 생성
			fileOut, err := os.Create(destFilePath)
			if err != nil {
				return false
			}
			// 파일 내용 복사
			if _, err := io.Copy(fileOut, tarReader); err != nil {
				fileOut.Close()
				return false
			}
			fileOut.Close()
		default:
			return false // 지원하지 않는 타입이면 false 반환
		}
	}

	return true // 모든 작업이 성공적으로 완료되면 true 반환
}