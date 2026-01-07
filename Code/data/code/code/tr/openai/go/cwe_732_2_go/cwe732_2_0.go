package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin.
// Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.
//
// @param directory Gizli dosyanın kaydedileceği dizin.
// @param filename Gizli dosyanın dosya adı.
// @param content Gizli dosyanın içeriği.
func saveSecreteFile(directory string, filename string, content string) error {
	// Dizin yolunu oluştur
	filePath := filepath.Join(directory, filename)

	// Dosyayı oluştur ve aç
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("dosya açılırken hata: %v", err)
	}
	defer file.Close()

	// İçeriği dosyaya yaz
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("içerik yazılırken hata: %v", err)
	}

	return nil
}