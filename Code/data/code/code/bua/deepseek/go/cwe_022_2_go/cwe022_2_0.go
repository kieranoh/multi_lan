import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

/* 주어진 목적지 경로로 tar 파일의 내용을 추출합니다.
추출이 성공하면 true를 반환하고, 그렇지 않으면 추출 과정 중 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.

@param tarPath: tar 파일의 경로
@param destPath: 목적지 폴더의 경로

@return 추출이 성공하면 true; 그렇지 않으면 false */
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일 존재 여부 확인
	if _, err := os.Stat(tarPath); os.IsNotExist(err) {
		return false
	}

	// 목적지 디렉토리 생성
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
	if strings.HasSuffix(strings.ToLower(tarPath), ".gz") ||
		strings.HasSuffix(strings.ToLower(tarPath), ".tgz") {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// tar 내용 추출
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			return false
		}

		// 안전한 경로 확인
		targetPath := filepath.Join(destPath, header.Name)
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
			return false
		}

		switch header.Typeflag {
		case tar.TypeDir:
			// 디렉토리 생성
			if err := os.MkdirAll(targetPath, 0755); err != nil {
				return false
			}
		case tar.TypeReg:
			// 파일 생성
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
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
		default:
			// 지원하지 않는 파일 타입
			return false
		}
	}

	return true
}