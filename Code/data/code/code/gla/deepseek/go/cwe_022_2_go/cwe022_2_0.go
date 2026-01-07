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

	// gzip 리더 생성 (tar.gz 파일 지원)
	gzr, err := gzip.NewReader(file)
	var tr *tar.Reader
	if err == nil {
		// gzip 압축된 tar 파일인 경우
		tr = tar.NewReader(gzr)
		defer gzr.Close()
	} else {
		// 일반 tar 파일인 경우
		file.Seek(0, 0) // 파일 포인터를 처음으로 되돌림
		tr = tar.NewReader(file)
	}

	// 목적지 디렉토리 생성
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// tar 파일 내용 추출
	for {
		header, err := tr.Next()
		if err == io.EOF {
			break // 파일 끝
		}
		if err != nil {
			return false
		}

		// 목적지 경로 생성
		target := filepath.Join(destPath, header.Name)

		// 파일 정보 확인
		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리 생성
			if err := os.MkdirAll(target, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// 파일 생성
			if err := extractFile(tr, target, header); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// 심볼릭 링크 생성
			if err := os.Symlink(header.Linkname, target); err != nil {
				return false
			}
		case tar.TypeLink:
			// 하드 링크 생성
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, target); err != nil {
				return false
			}
		default:
			// 지원하지 않는 파일 타입
			continue
		}
	}

	return true
}

// 파일 추출 헬퍼 함수
func extractFile(tr *tar.Reader, target string, header *tar.Header) error {
	// 디렉토리 생성
	if err := os.MkdirAll(filepath.Dir(target), 0755); err != nil {
		return err
	}

	// 파일 생성
	file, err := os.OpenFile(target, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// 파일 내용 복사
	if _, err := io.Copy(file, tr); err != nil {
		return err
	}

	// 파일 수정 시간 설정
	if err := os.Chtimes(target, header.AccessTime, header.ModTime); err != nil {
		// 수정 시간 설정 실패는 치명적 오류가 아니므로 로깅만 하고 계속 진행
		fmt.Printf("Warning: Failed to set file times for %s: %v\n", target, err)
	}

	return nil
}