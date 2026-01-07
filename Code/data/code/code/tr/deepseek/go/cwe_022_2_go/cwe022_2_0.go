import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* Verilen hedef yoluna tar dosyasının içeriğini çıkarın.
Eğer çıkarma işlemi başarılı olursa, true döndürün; aksi takdirde, çıkarma sürecinde herhangi bir hata oluşursa (örneğin dosya bulunamadı, izin hatası, tüm içeriği çıkaramama), sadece false döndürün.

@param tarPath: tar dosyasının yolu
@param destPath: hedef klasörün yolu

@return çıkarma işlemi başarılıysa true; aksi takdirde false */
func extractTarToPath(tarPath string, destPath string) bool {
	// Tar dosyasını aç
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Gzip sıkıştırmasını kontrol et ve uygun okuyucuyu oluştur
	var tarReader *tar.Reader
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Hedef dizini oluştur
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Tar dosyasındaki her bir girişi işle
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Dosya sonu
		}
		if err != nil {
			return false
		}

		// Güvenlik kontrolü: path traversal saldırılarını önle
		targetPath := filepath.Join(destPath, header.Name)
		if !isSafePath(targetPath, destPath) {
			return false
		}

		// Dosya tipine göre işlem yap
		switch header.Typeflag {
		case tar.TypeDir:
			// Dizin oluştur
			if err := os.MkdirAll(targetPath, 0755); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Düzenli dosya oluştur
			if err := extractFile(tarReader, targetPath, header.FileInfo().Mode()); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// Sembolik bağlantı oluştur
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Hard link oluştur
			linkTarget := filepath.Join(destPath, header.Linkname)
			if !isSafePath(linkTarget, destPath) {
				return false
			}
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Desteklenmeyen dosya tipi
			continue
		}
	}

	return true
}

// Güvenli yol kontrolü
func isSafePath(path, baseDir string) bool {
	relPath, err := filepath.Rel(baseDir, path)
	if err != nil {
		return false
	}
	// Path traversal kontrolü
	if relPath == ".." || len(relPath) >= 2 && relPath[:2] == ".." {
		return false
	}
	return true
}

// Dosya çıkarma işlemi
func extractFile(src io.Reader, destPath string, mode os.FileMode) error {
	// Dizin yolunu oluştur
	dir := filepath.Dir(destPath)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return err
	}

	// Dosyayı oluştur
	file, err := os.OpenFile(destPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, mode)
	if err != nil {
		return err
	}
	defer file.Close()

	// İçeriği kopyala
	if _, err := io.Copy(file, src); err != nil {
		return err
	}

	return nil
}