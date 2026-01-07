package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

/* 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.

@param tarPath: tar 파일의 경로
@param destPath: 목적지 폴더의 경로

@return 추출이 성공하면 true; 그렇지 않으면 false */
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 열기
	tarFile, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer tarFile.Close()

	// tar 리더 생성
	tarReader := tar.NewReader(tarFile)

	// 목적지 디렉토리 생성
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// tar 파일의 각 항목 처리
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // tar 파일 끝
		}
		if err != nil {
			return false
		}

		// 안전한 경로 생성
		targetPath := filepath.Join(destPath, header.Name)
		if !isSafePath(destPath, targetPath) {
			return false
		}

		// 파일 정보 확인
		fileInfo := header.FileInfo()

		// 디렉토리인 경우
		if fileInfo.IsDir() {
			if err := os.MkdirAll(targetPath, fileInfo.Mode()); err != nil {
				return false
			}
			continue
		}

		// 심볼릭 링크인 경우
		if header.Typeflag == tar.TypeSymlink {
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
			continue
		}

		// 일반 파일인 경우
		// 상위 디렉토리 생성
		if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
			return false
		}

		// 파일 생성
		file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, fileInfo.Mode())
		if err != nil {
			return false
		}

		// 파일 내용 복사
		if _, err := io.Copy(file, tarReader); err != nil {
			file.Close()
			return false
		}

		// 파일 닫기
		file.Close()
	}

	return true
}

// 경로 안전성 검사: 대상 경로가 기준 디렉토리 내에 있는지 확인
func isSafePath(baseDir, targetPath string) bool {
	relPath, err := filepath.Rel(baseDir, targetPath)
	if err != nil {
		return false
	}
	// 상위 디렉토리로 이동하는 경로인지 확인
	if relPath == ".." || len(relPath) >= 3 && relPath[0:3] == ".."+string(filepath.Separator) {
		return false
	}
	return true
}