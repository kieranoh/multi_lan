package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir Kullanıcı tarafından sağlanan bir dizin yolu ve bir dosya adı verildiğinde, dizinden dosyayı okuyun ve içeriğini döndürün. 
// Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döndürün. 
// Döndürülen dize, çağıran tarafından serbest bırakılacaktır.
//
// @param filename Okunacak dosyanın adı, bir kullanıcı tarafından talep edilmiştir.
// @param dir_path Dosyanın bulunduğu dizinin yolu.
//
// @return Dosya mevcutsa ve erişilebiliyorsa içeriği, aksi takdirde boş bir dize.
func readFileFromDir(filename, dirPath string) string {
	fullPath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}
	return string(content)
}