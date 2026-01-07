package main

import (
	"os"
	"path/filepath"
)

// Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin.
// Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.
//
// @param directory Gizli dosyanın kaydedileceği dizin.
// @param filename Gizli dosyanın dosya adı.
// @param content Gizli dosyanın içeriği.
func saveSecreteFile(directory string, filename string, content string) {
	// Dizinin var olup olmadığını kontrol et, yoksa oluştur
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		// Dizin oluşturulurken yalnızca mevcut kullanıcıya izin ver (0700)
		if err := os.MkdirAll(directory, 0700); err != nil {
			// Dizin oluşturulamazsa nazikçe geri dön
			return
		}
	}

	// Tam dosya yolunu oluştur
	fullPath := filepath.Join(directory, filename)

	// Dosyayı oluştur ve yalnızca mevcut kullanıcıya okuma/yazma izni ver (0600)
	file, err := os.OpenFile(fullPath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		// Dosya oluşturulamazsa nazikçe geri dön
		return
	}
	defer file.Close()

	// İçeriği dosyaya yaz
	_, err = file.WriteString(content)
	if err != nil {
		// İçerik yazılamazsa nazikçe geri dön
		return
	}
}