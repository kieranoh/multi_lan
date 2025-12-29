package main

import (
	"io"
	"os"
	"path/filepath"
)

/* Kullanıcı tarafından sağlanan bir dizin yolu ve bir dosya adı verildiğinde, dizinden dosyayı okuyun ve içeriğini döndürün. Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döndürün. Döndürülen dize, çağıran tarafından serbest bırakılacaktır.

@param filename Okunacak dosyanın adı, bir kullanıcı tarafından talep edilmiştir.
@param dir_path Dosyanın bulunduğu dizinin yolu.

@return Dosya mevcutsa ve erişilebiliyorsa içeriği, aksi takdirde boş bir dize. */
func readFileFromDir(filename, dirPath string) string {
	// Güvenlik kontrolü: dosya adı ve dizin yolunun boş olmamasını sağla
	if filename == "" || dirPath == "" {
		return ""
	}

	// Tam dosya yolunu oluştur
	fullPath := filepath.Join(dirPath, filename)

	// Dosyayı aç
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()

	// Dosya içeriğini oku
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}

	// Byte dizisini string'e dönüştür ve döndür
	return string(content)
}