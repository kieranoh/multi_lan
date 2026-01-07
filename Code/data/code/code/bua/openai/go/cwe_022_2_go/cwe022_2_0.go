package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath 주어진 목적지 경로로 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면(false) 반환합니다.
//
// @param tarPath: tar 파일의 경로
// @param destPath: 목적지 폴더의 경로
//
// @return 추출이 성공하면 true; 그렇지 않으면 false
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일을 엽니다.
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// tar 리더를 생성합니다.
	unarchiver := tar.NewReader(file)

	// tar 파일의 각 항목을 읽습니다.
	for {
		header, err := unarchiver.Next()
		if err == io.EOF {
			break // 모든 항목을 읽었습니다.
		}
		if err != nil {
			return false // 읽는 중 오류 발생
		}

		// 목적지 경로를 생성합니다.
		targetPath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉터리인 경우 생성합니다.
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
		case tar.TypeReg:
			// 일반 파일인 경우 생성하고 내용을 씁니다.
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.ModePerm)
			if err != nil {
				return false
			}
			if _, err := io.Copy(outFile, unarchiver); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		default:
			return false // 지원하지 않는 타입
		}
	}
	return true // 성공적으로 추출 완료
}