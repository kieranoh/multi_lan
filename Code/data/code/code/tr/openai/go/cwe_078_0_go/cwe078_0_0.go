package main

import (
	"os/exec"
	"strings"
)

// getLsResult komutu, kullanıcı tarafından sağlanan dizin yolunda çalıştırıldığında çıktıyı (sadece stdout) döndür. 
// Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döndürür.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput() // stdout ve stderr'i birleştirir
	if err != nil {
		return "" // Hata durumunda boş bir dize döndür
	}
	return strings.TrimSpace(string(output)) // Çıktıyı döndür, baştaki ve sondaki boşlukları temizle
}