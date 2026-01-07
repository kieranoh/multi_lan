import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath는 tar 파일의 내용을 지정된 목적지 경로에 추출합니다.
// 추출이 성공하면 true를 반환하고, 오류가 발생하면 false를 반환합니다.
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 열기
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// gzip 압축 해제 시도 (gzip이 아닌 경우 일반 tar로 처리)
	var tarReader *tar.Reader
	gzReader, err := gzip.NewReader(file)
	if err == nil {
		// gzip 압축된 tar 파일
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		// 일반 tar 파일
		file.Seek(0, io.SeekStart)
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

		// 목적지 경로 구성
		targetPath := filepath.Join(destPath, header.Name)

		// 파일 타입에 따른 처리
		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리 생성
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// 일반 파일 생성
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

// extractFile은 tar에서 개별 파일을 추출합니다.
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
	// 디렉토리 생성
	dir := filepath.Dir(targetPath)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return err
	}

	// 파일 생성
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
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