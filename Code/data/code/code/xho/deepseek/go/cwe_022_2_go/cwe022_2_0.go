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

    // 목적지 디렉토리 생성 (이미 존재해도 오류 발생하지 않음)
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // tar 리더 생성
    tr := tar.NewReader(file)

    // tar 파일 내 모든 항목 처리
    for {
        header, err := tr.Next()
        if err == io.EOF {
            break // 정상적으로 모든 항목 처리 완료
        }
        if err != nil {
            return false // 읽기 오류 발생
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
            // 일반 파일 생성
            if err := extractFile(tr, targetPath, header); err != nil {
                return false
            }
        case tar.TypeSymlink:
            // 심볼릭 링크 생성
            if err := os.Symlink(header.Linkname, targetPath); err != nil {
                return false
            }
        case tar.TypeLink:
            // 하드 링크 생성
            if err := os.Link(filepath.Join(destPath, header.Linkname), targetPath); err != nil {
                return false
            }
        default:
            // 지원하지 않는 파일 타입은 건너뜀
            continue
        }
    }

    return true
}

// 파일 추출 헬퍼 함수
func extractFile(tr *tar.Reader, targetPath string, header *tar.Header) error {
    // 디렉토리 생성
    if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
        return err
    }

    // 파일 생성
    file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
    if err != nil {
        return err
    }
    defer file.Close()

    // 파일 내용 복사
    if _, err := io.Copy(file, tr); err != nil {
        return err
    }

    // 수정 시간 설정
    if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
        return err
    }

    return nil
}