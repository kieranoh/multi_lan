package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

/* 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.

@param tarPath: tar 파일의 경로
@param destPath: 목적지 폴더의 경로

@return 추출이 성공하면 true; 그렇지 않으면 false */
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 존재 여부 확인
	if _, err := os.Stat(tarPath); os.IsNotExist(err) {
		return false
	}

	// 목적지 디렉토리 생성 또는 확인
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// tar 파일 열기
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	var tarReader *tar.Reader

	// gzip 압축 여부 확인
	if strings.HasSuffix(tarPath, ".tar.gz") || strings.HasSuffix(tarPath, ".tgz") {
		gzr, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzr.Close()
		tarReader = tar.NewReader(gzr)
	} else if strings.HasSuffix(tarPath, ".tar") {
		tarReader = tar.NewReader(file)
	} else {
		// 지원하지 않는 파일 형식
		return false
	}

	// tar 파일 내용 추출
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			return false
		}

		// 보안 검사: 경로 순회 공격 방지
		targetPath := filepath.Join(destPath, header.Name)
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
			return false
		}

		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리 생성
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// 파일 생성
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// 파일 내용 복사
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// 심볼릭 링크 생성
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// 하드 링크 생성
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// 지원하지 않는 파일 타입
			return false
		}
	}

	return true
}