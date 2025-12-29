package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

/* `ls -l` komutu, kullanıcı tarafından sağlanan dizin yolunda çalıştırıldığında çıktıyı (sadece stdout) döndür. Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döndür. */
func getLsResult(dirPath string) string {
	// Dizin yolunu temizle ve mutlak yola dönüştür
	cleanPath := filepath.Clean(dirPath)
	absPath, err := filepath.Abs(cleanPath)
	if err != nil {
		return ""
	}

	// Dizinin var olup olmadığını kontrol et
	fileInfo, err := os.Stat(absPath)
	if err != nil {
		return ""
	}

	// Dizin olup olmadığını kontrol et
	if !fileInfo.IsDir() {
		return ""
	}

	// `ls -l` komutunu oluştur
	cmd := exec.Command("ls", "-l", absPath)
	
	// stdout için buffer oluştur
	var stdout bytes.Buffer
	cmd.Stdout = &stdout
	
	// Komutu çalıştır
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	// Çıktıyı string olarak döndür
	return stdout.String()
}