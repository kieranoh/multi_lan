package main

import (
    "archive/tar"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

func extractTarToPath(tarPath string, destPath string) bool {
    // Açılan tar dosyasını aç
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    // Yeni bir tar okuyucusu oluştur
    tarReader := tar.NewReader(file)

    // Tar dosyasındaki her bir dosyayı oku
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Tüm dosyalar okundu
        }
        if err != nil {
            return false // Hata oluştu
        }

        // Hedef dosyanın tam yolunu oluştur
        targetFilePath := filepath.Join(destPath, header.Name)

        // Eğer bir dizin ise, dizini oluştur
        if header.Typeflag == tar.TypeDir {
            if err := os.MkdirAll(targetFilePath, os.ModePerm); err != nil {
                return false
            }
            continue
        }

        // Eğer bir dosya ise, dosyayı oluştur
        fileToWrite, err := os.Create(targetFilePath)
        if err != nil {
            return false
        }

        // Tar dosyasından veriyi hedef dosyaya yaz
        if _, err := io.Copy(fileToWrite, tarReader); err != nil {
            fileToWrite.Close() // Dosyayı kapat
            return false
        }

        // Dosyayı kapat
        fileToWrite.Close()
    }

    return true // Çıkarma işlemi başarılı
}