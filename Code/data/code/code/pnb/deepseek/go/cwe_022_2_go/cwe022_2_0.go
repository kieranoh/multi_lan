package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.

@param tarPath: tar 파일의 경로
@param destPath: 목적지 폴더의 경로

@return 추출이 성공하면 true; 그렇지 않으면 false */
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 열기
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// gzip 압축 여부 확인 및 적절한 reader 생성
	var tarReader *tar.Reader
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// 목적지 디렉토리 생성
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// tar 파일 내용 추출
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 파일 끝
		}
		if err != nil {
			return false
		}

		// 목적지 경로 생성
		targetPath := filepath.Join(destPath, header.Name)

		// 파일 타입에 따른 처리
		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리 생성
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// 파일 생성
			if err := extractFile(tarReader, targetPath, header); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// 심볼릭 링크 생성
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// 하드 링크 생성
			linkPath := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// 지원하지 않는 파일 타입은 건너뜀
			continue
		}
	}

	return true
}

// 개별 파일 추출 헬퍼 함수
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
	// 디렉토리 생성
	dir := filepath.Dir(targetPath)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return err
	}

	// 파일 생성
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// 파일 내용 복사
	if _, err := io.Copy(file, tarReader); err != nil {
		return err
	}

	return nil
}