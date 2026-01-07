package main

import (
	"log"
	"os"
	"path/filepath"
	"strings"
	"archive/tar"
	"io"
)

// extractTarToPath 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면 false를 반환합니다.
//
// @param tarPath: tar 파일의 경로
// @param destPath: 목적지 폴더의 경로
//
// @return 추출이 성공하면 true; 그렇지 않으면 false
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		log.Println("Error opening tar file:", err)
		return false
	}
	defer file.Close()

	tarReader := tar.NewReader(file)

	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Println("Error reading tar header:", err)
			return false
		}

		target := filepath.Join(destPath, header.Name)

		// Create necessary directories
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(target, os.ModePerm); err != nil {
				log.Println("Error creating directory:", err)
				return false
			}
			continue
		}

		// Ensure the parent directory exists
		if err := os.MkdirAll(filepath.Dir(target), os.ModePerm); err != nil {
			log.Println("Error creating parent directory:", err)
			return false
		}

		// Create the file
		outFile, err := os.Create(target)
		if err != nil {
			log.Println("Error creating file:", err)
			return false
		}

		// Copy file contents
		if _, err := io.Copy(outFile, tarReader); err != nil {
			log.Println("Error writing file contents:", err)
			outFile.Close()
			return false
		}

		outFile.Close()
	}

	return true
}