package main

import (
    "archive/tar"
    "io"
    "os"
    "path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
    // tar 파일을 엽니다.
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    // tar 리더를 생성합니다.
    tarReader := tar.NewReader(file)

    // tar 파일의 각 항목을 읽습니다.
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // 모든 항목을 읽었으면 종료합니다.
        }
        if err != nil {
            return false // 읽기 오류 발생
        }

        // 추출할 파일의 경로를 생성합니다.
        targetPath := filepath.Join(destPath, header.Name)

        switch header.Typeflag {
        case tar.TypeDir:
            // 디렉토리인 경우 생성합니다.
            if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
                return false
            }
        case tar.TypeReg:
            // 파일인 경우 생성하고 내용을 씁니다.
            outFile, err := os.Create(targetPath)
            if err != nil {
                return false
            }
            _, err = io.Copy(outFile, tarReader)
            outFile.Close()
            if err != nil {
                return false
            }
        default:
            return false // 알 수 없는 타입
        }
    }
    
    return true // 모든 항목이 성공적으로 추출되었습니다.
}