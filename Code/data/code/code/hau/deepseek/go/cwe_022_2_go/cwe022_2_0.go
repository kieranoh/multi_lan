import (
    "archive/tar"
    "compress/gzip"
    "fmt"
    "io"
    "os"
    "path/filepath"
    "strings"
)

func extractTarToPath(tarPath string, destPath string) bool {
    // 1. tar 파일 열기
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    var tarReader *tar.Reader

    // 2. gzip 압축 확인 및 적절한 reader 생성
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

    // 3. 목적지 폴더 생성
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // 4. tar 내용 추출
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // 정상적으로 모든 파일 처리 완료
        }
        if err != nil {
            return false // tar 읽기 오류
        }

        // 5. 안전성 검사: 경로 순회 공격 방지
        targetPath := filepath.Join(destPath, header.Name)
        if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
            return false // 경로 순회 공격 시도 감지
        }

        // 6. 파일 정보에 따라 처리
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

        // 7. 파일 시간 정보 설정 (가능한 경우)
        if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
            // 시간 설정 실패는 전체 실패로 간주하지 않음
            // (일부 시스템에서는 지원하지 않을 수 있음)
        }
    }

    return true
}

// 파일 추출 헬퍼 함수
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
    // 디렉토리 생성
    dir := filepath.Dir(targetPath)
    if err := os.MkdirAll(dir, 0755); err != nil {
        return err
    }

    // 파일 생성
    file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
    if err != nil {
        return err
    }
    defer file.Close()

    // 내용 복사
    if _, err := io.Copy(file, tarReader); err != nil {
        return err
    }

    return nil
}